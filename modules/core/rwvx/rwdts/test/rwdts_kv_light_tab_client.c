
/*
 * 
 *   Copyright 2016 RIFT.IO Inc
 *
 *   Licensed under the Apache License, Version 2.0 (the "License");
 *   you may not use this file except in compliance with the License.
 *   You may obtain a copy of the License at
 *
 *       http://www.apache.org/licenses/LICENSE-2.0
 *
 *   Unless required by applicable law or agreed to in writing, software
 *   distributed under the License is distributed on an "AS IS" BASIS,
 *   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *   See the License for the specific language governing permissions and
 *   limitations under the License.
 *
 */


/**
 * @file rwdts_kv_light_client.c
 * @author Prashanth Bhaskar (Prashanth.Bhaskar@riftio.com)
 * @date 2014/10/02
 * @brief Do nothing test program to validate declarations, linkage, compile-time stuff
 */

#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

#include <rwlib.h>
#include <rwtrace.h>
#include <rwsched.h>
#include <rwsched_object.h>
#include <rwsched_queue.h>
#include <rwsched_source.h>
#include <rwsched/cfrunloop.h>
#include <rwsched/cfsocket.h>
#include <rwmsg.h>
#include <rwdts_redis.h>
#include <rwdts_kv_light_api.h>
#include <rwdts_kv_light_api_gi.h>

struct {
  rwdts_kv_handle_t *handle;
  rwdts_kv_table_handle_t *tab_handle;
  rwsched_instance_ptr_t rwsched;
  rwsched_tasklet_ptr_t tasklet;
  rwsched_dispatch_source_t source;
  int serial_num;
  long long timeout;
} myUserData;

char *getTime(void)
{
 struct timeval tv;
 struct tm* ptm;
 char time_string[40];
 long milliseconds;
 static char buf[4096];

 gettimeofday (&tv, NULL);
 ptm = localtime (&tv.tv_sec);
 strftime (time_string, sizeof (time_string), "%Y-%m-%d %H:%M:%S", ptm);
 milliseconds = tv.tv_usec / 1000;
 snprintf(buf, sizeof(buf), "%s.%03ld", time_string, milliseconds);
 return buf;
}

struct abc {
  int a;
  int b;
  int c;
} a;

static rwdts_kv_light_reply_status_t rwdts_kv_light_tab_del_callback(rwdts_kv_light_del_status_t status, void *userdata)
{
  if(RWDTS_KV_LIGHT_DEL_SUCCESS == status) {
    fprintf(stderr, "Successfully deleted the data\n");
  }
  return RWDTS_KV_LIGHT_REPLY_DONE;
}

static rwdts_kv_light_reply_status_t rwdts_kv_light_del_callback(rwdts_kv_light_del_status_t status,
                                                                 void *userdata)
{
  rwdts_kv_table_handle_t *tab_handle = (rwdts_kv_table_handle_t *)userdata;

  if(RWDTS_KV_LIGHT_DEL_SUCCESS == status) {
    fprintf(stderr, "Successfully deleted the data\n");
  }
  rwdts_kv_light_del_table(tab_handle, rwdts_kv_light_tab_del_callback, NULL);
  return RWDTS_KV_LIGHT_REPLY_DONE;
}


static rwdts_kv_light_reply_status_t rwdts_kv_light_tab_exist(int exists,
                                                              void *userdata)
{
  rwdts_kv_table_handle_t *data = (rwdts_kv_table_handle_t *)userdata;
  if (exists == 1) {
    fprintf(stderr, "Exists\n");
  }
  rwdts_kv_light_table_delete_key(data, (myUserData.serial_num), "test",
                                  "FOO", 3, rwdts_kv_light_del_callback, (void *)data);
  return RWDTS_KV_LIGHT_REPLY_DONE;
}

static rwdts_kv_light_reply_status_t rwdts_kv_light_get_callback(void *val,
                                                                 int val_len,
                                                                 int serial_num,
                                                                 void *userdata)
{
   struct abc *reply = (struct abc*)val;
   rwdts_kv_table_handle_t *data = (rwdts_kv_table_handle_t *)userdata;
   if (reply) {
     if ((reply->a == a.a) && (reply->b == a.b) && (reply->c == a.c)) {
       fprintf(stderr, "Successfully extracted data from database\n");
       fprintf(stderr, "a->a(%d), a->b(%d), a->c(%d)\n", reply->a, reply->b, reply->c);
     }
     rwdts_kv_light_tab_field_exists(data, "FOO", 3, rwdts_kv_light_tab_exist, (void *)data);
   }
   return RWDTS_KV_LIGHT_REPLY_DONE;
}

static rwdts_kv_light_reply_status_t rwdts_kv_light_set_callback(rwdts_kv_light_set_status_t status,
                                                                 int serial_num, void *userdata)
{
  rwdts_kv_table_handle_t *data = (rwdts_kv_table_handle_t *)userdata;
  if(RWDTS_KV_LIGHT_SET_SUCCESS == status) {
    fprintf(stderr, "Successfully inserted the data\n");
    myUserData.serial_num = serial_num;
  }

  rwdts_kv_light_table_get_sernum_by_key(data, "FOO", 3,
                                         rwdts_kv_light_get_callback, (void*)data);

  return RWDTS_KV_LIGHT_REPLY_DONE;
}

void redis_initialized(void *userdata, rw_status_t status)
{
  rwdts_kv_table_handle_t *data = (rwdts_kv_table_handle_t *)userdata;
  /* ok, redis client connection to databases are up */
  fprintf(stderr, "[%s]Riftdb is up\n", getTime());
  RW_ASSERT(status == RW_STATUS_SUCCESS);
  a.a = 1;
  a.b = 2;
  a.c = 3;

  rwdts_kv_light_table_insert(data, myUserData.serial_num, "test", "FOO", 3,
                              (void*)&a, sizeof(a), rwdts_kv_light_set_callback,
                              (void*)data);

}

int main(int argc, char **argv, char **envp) {

  if (3 != argc) {
    fprintf(stderr, "Usage: ./rwdts_redis_client <ip> <port>\n");
    return -1;
  }

  //uint16_t port = atoi(argv[2]);

  myUserData.handle = rwdts_kv_allocate_handle(REDIS_DB);
  rwsched_instance_ptr_t rwsched = NULL;
  rwsched = rwsched_instance_new();
  RW_ASSERT(rwsched);

  rwsched_tasklet_ptr_t tasklet = NULL;
  tasklet = rwsched_tasklet_new(rwsched);
  RW_ASSERT(tasklet);

  myUserData.tab_handle = rwdts_kv_light_register_table(myUserData.handle, 1);
  rwdts_kv_handle_db_connect(myUserData.handle, rwsched, tasklet, "127.0.0.1:9997",
                             "test", NULL, redis_initialized, myUserData.tab_handle);

  myUserData.rwsched = rwsched;
  myUserData.tasklet = tasklet;
  myUserData.serial_num = 1;

  rwsched_dispatch_main_until(tasklet, 1000, 0);

  return 1;
}

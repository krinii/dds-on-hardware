#include "dds/dds.h"
#include "TestDataType_3.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define DEPTH 20
#define DEBUG false

static volatile int sigintH = 1;

/* Handel Ctrl-C */
void sigintHandler(int sig_num) {
  sigintH = 0;
}

bool contentFilter(const void *sample);

int main (int argc, char ** argv)
{
  dds_entity_t participant;
  dds_entity_t topic;
  dds_entity_t writer;
  dds_return_t rc;
  TestDataType_data msg;
  uint32_t status = 0;
  dds_qos_t *qos;
  (void)argc;
  (void)argv;

  signal(SIGINT, sigintHandler);

  /* Create a Participant. */
  /* dds_create_participant ( domain (int: 0 - 230), qos, listener ) */
  participant = dds_create_participant (DDS_DOMAIN_DEFAULT, NULL, NULL);
  if (participant < 0)
    DDS_FATAL("dds_create_participant: %s\n", dds_strretcode(-participant));

  /* Create a Topic. */
  /* dds_create_topic ( participant, descriptor, name, qos, listener ) */
  topic = dds_create_topic (
    participant, &TestDataType_data_desc, "TestDataType_data", NULL, NULL);
  if (topic < 0)
    DDS_FATAL("dds_create_topic: %s\n", dds_strretcode(-topic));
  
  // ContentFilter
  //dds_set_topic_filter(topic, contentFilter);

  /* Create QoS */
  qos = dds_create_qos ();
  /* Change History QoS setting */
  //dds_qset_history(qos, DDS_HISTORY_KEEP_LAST, DEPTH);
  //dds_qset_durability(qos, DDS_DURABILITY_TRANSIENT_LOCAL);
  //dds_qset_durability_service(qos, 0, DDS_HISTORY_KEEP_LAST, DEPTH, DDS_LENGTH_UNLIMITED, DDS_LENGTH_UNLIMITED, DDS_LENGTH_UNLIMITED);

  /* Create a Writer. */
  /* dds_create_writer ( participant_or_publisher, topic, qos, listener ) */
  //writer = dds_create_writer (participant, topic, qos, NULL);
  writer = dds_create_writer (participant, topic, NULL, NULL);
  if (writer < 0)
    DDS_FATAL("dds_create_writer: %s\n", dds_strretcode(-writer));

  printf("=== [Publisher]  Waiting for a reader to be discovered ...\n");
  fflush (stdout);

  /*rc = dds_set_status_mask(writer, DDS_PUBLICATION_MATCHED_STATUS);
  if (rc != DDS_RETCODE_OK)
    DDS_FATAL("dds_set_status_mask: %s\n", dds_strretcode(-rc));

  while(!(status & DDS_PUBLICATION_MATCHED_STATUS) && sigintH)
  {
    rc = dds_get_status_changes (writer, &status);
    if (rc != DDS_RETCODE_OK)
      DDS_FATAL("dds_get_status_changes: %s\n", dds_strretcode(-rc));

    //Polling sleep.
    dds_sleepfor (DDS_MSECS (20));
  }*/

  int i = 0;
  
  /* Create a message to write. */
  //msg.instanceID = 3.0;

  printf("Msg size: %d \n", sizeof(msg));
  printf("arr size: %d \n", sizeof(msg.arr));
  fflush (stdout);

  while (sigintH){
    /*if (DEBUG){
      printf ("=== [Publisher]  Writing : \n");
      printf ("Message (%"PRId32", %s; Temp: %.2f; HUM: %d; %"PRId32")\n", msg.instanceID, msg.message, msg.temperature, msg.humidity, msg.msgNr);
      fflush (stdout);
    }*/
    

    rc = dds_write (writer, &msg);
    /*if (rc != DDS_RETCODE_OK)
      DDS_FATAL("dds_write: %s\n", dds_strretcode(-rc));*/

  	/*
    dds_sleepfor (DDS_MSECS (500));
    
    if (hum < 30) hum_iter = 1;
    else if (hum > 80) hum_iter = -1;
    hum = hum + hum_iter;

    if (temp < 20.0) temp_iter = 0.5;
    else if (temp > 25.0) temp_iter = -0.5;
    temp = temp + temp_iter;

    i ++;*/
  }

  //printf("Delete\n");
  //fflush(stdout);
  /* Deleting the participant will delete all its children recursively as well. */
  rc = dds_delete (participant);
  if (rc != DDS_RETCODE_OK)
    DDS_FATAL("dds_delete: %s\n", dds_strretcode(-rc));

  return EXIT_SUCCESS;
}

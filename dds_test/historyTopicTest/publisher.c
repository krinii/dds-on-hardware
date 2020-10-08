#include "dds/dds.h"
#include "TestDataType.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

#define DEPTH 5

static volatile int sigintH = 1;

/* Handel Ctrl-C */
void sigintHandler(int sig_num) {
  sigintH = 0;
}

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

  /* Create QoS */
  //qos = dds_create_qos ();
  /* Change History QoS setting */
  //dds_qset_history(qos, DDS_HISTORY_KEEP_LAST, DEPTH);

  /* Create a Topic. */
  /* dds_create_topic ( participant, descriptor, name, qos, listener ) */
  topic = dds_create_topic (
    participant, &TestDataType_data_desc, "TestDataType_data", NULL, NULL);
  if (topic < 0)
    DDS_FATAL("dds_create_topic: %s\n", dds_strretcode(-topic));

  /* Create a Writer. */
  /* dds_create_writer ( participant_or_publisher, topic, qos, listener ) */
  writer = dds_create_writer (participant, topic, NULL, NULL);
  if (writer < 0)
    DDS_FATAL("dds_create_writer: %s\n", dds_strretcode(-writer));

  printf("=== [Publisher]  Waiting for a reader to be discovered ...\n");
  fflush (stdout);

  rc = dds_set_status_mask(writer, DDS_PUBLICATION_MATCHED_STATUS);
  if (rc != DDS_RETCODE_OK)
    DDS_FATAL("dds_set_status_mask: %s\n", dds_strretcode(-rc));

  while(!(status & DDS_PUBLICATION_MATCHED_STATUS) && sigintH)
  {
    rc = dds_get_status_changes (writer, &status);
    if (rc != DDS_RETCODE_OK)
      DDS_FATAL("dds_get_status_changes: %s\n", dds_strretcode(-rc));

    /* Polling sleep. */
    dds_sleepfor (DDS_MSECS (20));
  }
  int i = 0;
  //while (i < 10  && sigintH){
  while (sigintH){
    /* Create a message to write. */
    //msg.userID = i;
    msg.userID = 1;
    msg.message = "I send you this message with dds";
    msg.msgNr = i;

    printf ("=== [Publisher]  Writing : ");
    printf ("Message (%"PRId32", %s; %"PRId32")\n", msg.userID, msg.message, msg.msgNr);
    fflush (stdout);

    rc = dds_write (writer, &msg);
    if (rc != DDS_RETCODE_OK)
      DDS_FATAL("dds_write: %s\n", dds_strretcode(-rc));

  	dds_sleepfor (DDS_MSECS (500));
    i ++;
  }

  //printf("Delete\n");
  //fflush(stdout);
  /* Deleting the participant will delete all its children recursively as well. */
  rc = dds_delete (participant);
  if (rc != DDS_RETCODE_OK)
    DDS_FATAL("dds_delete: %s\n", dds_strretcode(-rc));

  return EXIT_SUCCESS;
}

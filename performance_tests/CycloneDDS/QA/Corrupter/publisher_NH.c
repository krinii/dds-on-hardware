#include "dds/dds.h"
#include "TestDataType.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

//#define DEPTH 10

static volatile int sigintH = 1;

/* Handel Ctrl-C */
void sigintHandler(int sig_num) {
  sigintH = 0;
}

// ### Writer
void liveliness_lost(dds_entity_t writer, const dds_liveliness_lost_status_t status, void *arg);
void offered_deadline_missed(dds_entity_t writer, const dds_offered_deadline_missed_status_t status, void *arg);
void offered_incompatialbe_qos(dds_entity_t writer, const dds_offered_incompatible_qos_status_t status, void *arg);
void publication_mateched(dds_entity_t writer, const dds_publication_matched_status_t status, void *arg);

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

  dds_listener_t *listener = NULL;

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

  /* Create QoS */
  qos = dds_create_qos ();
  dds_qset_reliability (qos, DDS_RELIABILITY_RELIABLE, DDS_SECS (10));
  //dds_qset_reliability (qos, DDS_RELIABILITY_BEST_EFFORT, DDS_SECS (10));

  /* Change History QoS setting */
  //dds_qset_history(qos, DDS_HISTORY_KEEP_LAST, DEPTH);
  //dds_qset_durability(qos, DDS_DURABILITY_TRANSIENT_LOCAL);
  //dds_qset_durability(qos, DDS_DURABILITY_TRANSIENT);
  //dds_qset_durability(qos, DDS_DURABILITY_PERSISTENT);
  //dds_qset_durability_service(qos, 0, DDS_HISTORY_KEEP_LAST, DEPTH, DDS_LENGTH_UNLIMITED, DDS_LENGTH_UNLIMITED, DDS_LENGTH_UNLIMITED);

  listener = dds_create_listener(NULL);
  dds_lset_liveliness_lost(listener, liveliness_lost);
  dds_lset_offered_deadline_missed(listener, offered_deadline_missed);
  dds_lset_offered_incompatible_qos(listener, offered_incompatialbe_qos);

  /* Create a Writer. */
  /* dds_create_writer ( participant_or_publisher, topic, qos, listener ) */
  //writer = dds_create_writer (participant, topic, qos, NULL);
  writer = dds_create_writer (participant, topic, qos, listener);
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

    //Polling sleep.
    dds_sleepfor (DDS_MSECS (20));
  }

  int i = 0;
  msg.instanceID = 1;
  double tmp = 1.0;
  msg.value = 15;
  msg.message = "Not History Pub";
  //while (i < 10  && sigintH){
  while (sigintH){
    /* Create a message to write. */
    msg.arr[0] = tmp;

    printf ("=== [Publisher]  Writing : ");
    printf ("ID: %.4f, arr[0]: %.4f, Value: %d, Message: %s\n", msg.instanceID, msg.arr[0], msg.value, msg.message);
    fflush (stdout);

    rc = dds_write (writer, &msg);
    if (rc != DDS_RETCODE_OK)
      DDS_FATAL("dds_write: %s\n", dds_strretcode(-rc));

  	dds_sleepfor (DDS_MSECS (500));
    i ++;
    tmp++;
  }

  //printf("Delete\n");
  //fflush(stdout);
  /* Deleting the participant will delete all its children recursively as well. */
  rc = dds_delete (participant);
  if (rc != DDS_RETCODE_OK)
    DDS_FATAL("dds_delete: %s\n", dds_strretcode(-rc));

  return EXIT_SUCCESS;
}

void liveliness_lost(dds_entity_t writer, const dds_liveliness_lost_status_t status, void *arg){
  printf("\n ===== Liveliness Lost ===== \n");
  fflush(stdout);
}
void offered_deadline_missed(dds_entity_t writer, const dds_offered_deadline_missed_status_t status, void *arg){
  printf("\n ===== Offered Deadline Missed ===== \n");
  fflush(stdout);
}
void offered_incompatialbe_qos(dds_entity_t writer, const dds_offered_incompatible_qos_status_t status, void *arg){
  printf("\n ===== Offered Incompatible QoS ===== \n");
  fflush(stdout);
}
void publication_mateched(dds_entity_t writer, const dds_publication_matched_status_t status, void *arg){
  printf("\n ===== Publication Matched ===== \n");
  fflush(stdout);
}
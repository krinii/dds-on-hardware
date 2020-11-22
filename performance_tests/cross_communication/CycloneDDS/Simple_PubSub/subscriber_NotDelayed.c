#include "dds/dds.h"
#include "HelloWorld.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

/* An array of one message (aka sample in dds terms) will be used. */
#define MAX_SAMPLES 100
//#define DEPTH 7

static volatile int sigintH = 1;

/* Handel Ctrl-C */
void sigintHandler(int sig_num) {
  sigintH = 0;
}

bool checkSampleState(dds_sample_info_t infos[], dds_return_t count);
bool checkValidData(dds_sample_info_t infos[], dds_return_t count);

void requested_qos(dds_entity_t reader, const dds_requested_incompatible_qos_status_t status, void *arg);
void sample_lost(dds_entity_t reader, const dds_sample_lost_status_t status, void *arg);
void sample_rejected(dds_entity_t reader, const dds_sample_rejected_status_t status, void *arg);
void liveliness_changed(dds_entity_t reader, const dds_liveliness_changed_status_t status, void *arg);
void requested_dealine_missed(dds_entity_t reader, const dds_requested_deadline_missed_status_t status, void *arg);
void requested_incompatible_qos(dds_entity_t reader, const dds_requested_incompatible_qos_status_t status, void *arg);
void subscription_macthed(dds_entity_t reader, const dds_subscription_matched_status_t status, void *arg);

int main (int argc, char ** argv)
{
  dds_entity_t participant;
  dds_entity_t topic;
  dds_entity_t reader;
  HelloWorld_data *msg;

  dds_listener_t *listener = NULL;

  static HelloWorld_data data[MAX_SAMPLES];
  void *samples[MAX_SAMPLES];
  dds_sample_info_t infos[MAX_SAMPLES];
  dds_return_t rc;
  dds_qos_t *qos;
  (void)argc;
  (void)argv;

  signal(SIGINT, sigintHandler);

  /* Create a Participant. */
  /* dds_create_participant ( domain (int: 0 - 230), qos, listener ) */
  //participant = dds_create_participant (DDS_DOMAIN_DEFAULT, NULL, NULL);
  participant = dds_create_participant (0, NULL, NULL);
  if (participant < 0)
    DDS_FATAL("dds_create_participant: %s\n", dds_strretcode(-participant));

  /* Create a Topic. */
  /* dds_create_topic ( participant, descriptor, name, qos, listener ) */
  topic = dds_create_topic (
    participant, &HelloWorld_data_desc, "HelloWorldTopic", NULL, NULL);
  if (topic < 0)
    DDS_FATAL("dds_create_topic: %s\n", dds_strretcode(-topic));

  /* Create a reliable Reader. */
  /* dds_create_writer ( participant_or_publisher, topic, qos, listener ) */
  qos = dds_create_qos ();
  dds_qset_reliability (qos, DDS_RELIABILITY_RELIABLE, DDS_SECS (10));
  //dds_qset_reliability (qos, DDS_RELIABILITY_BEST_EFFORT, DDS_SECS (10));
  
  /* Change History setting */
  //dds_qset_history(qos, DDS_HISTORY_KEEP_LAST, DEPTH);
  //dds_qset_durability(qos, DDS_DURABILITY_TRANSIENT_LOCAL);
  //dds_qset_durability(qos, DDS_DURABILITY_TRANSIENT);
  //dds_qset_durability(qos, DDS_DURABILITY_PERSISTENT);

  listener = dds_create_listener(NULL);
  dds_lset_requested_incompatible_qos(listener, requested_qos);
  dds_lset_sample_lost(listener, sample_lost);
  dds_lset_sample_rejected(listener, sample_rejected);
  dds_lset_liveliness_changed(listener, liveliness_changed);
  dds_lset_requested_deadline_missed(listener, requested_dealine_missed);
  dds_lset_requested_incompatible_qos(listener, requested_incompatible_qos);
  dds_lset_subscription_matched(listener, subscription_macthed);

  //reader = dds_create_reader (participant, topic, qos, NULL);
  reader = dds_create_reader (participant, topic, qos, listener);
  if (reader < 0)
    DDS_FATAL("dds_create_reader: %s\n", dds_strretcode(-reader));
  dds_delete_qos(qos);

  printf ("\n=== [Subscriber] Waiting for a sample ...\n");
  fflush (stdout);

  /* Initialize sample buffer, by pointing the void pointer within
   * the buffer array to a valid sample memory location. */
  //samples[0] = PubSubLoopData_Msg__alloc ();
  //samples[1] = PubSubLoopData_Msg__alloc ();

  /* Initialize sample data */
  memset (data, 0, sizeof (data));
  for (int i = 0; i < MAX_SAMPLES; i++)
  {
    samples[i] = &data[i];
  }

  //Sleep for testing
  //dds_sleepfor (DDS_MSECS (1000));

  int j = 0;

  //while ((j < 10) && sigintH){
  while (sigintH){
    /* Poll until data has been read. */
    // Needs to be done dds_take/read does not seem to overwrite rc if didn't get a new message
  	rc = 0;
    while (true && sigintH)
    {
      rc = 0;
      /* Do the actual read.
        * The return value contains the number of read samples. */
      rc = dds_read (reader, samples, infos, MAX_SAMPLES, MAX_SAMPLES);
      //rc = dds_take (reader, samples, infos, MAX_SAMPLES, MAX_SAMPLES);
      if (rc < 0)
        DDS_FATAL("dds_read: %s\n", dds_strretcode(-rc));

      /*printf ("Data? \n");
      fflush (stdout);*/

      /*printf("--- Sample state = %d, %d, %d, %d, %d rc = %d \n", infos[0].sample_state, infos[1].sample_state, infos[2].sample_state, infos[3].sample_state, infos[4].sample_state, rc);
      fflush (stdout);*/
      /* Check if we read some data and it is valid. */
      //if ((rc > 0) && checkValidData(infos))
      if ((rc > 0) && checkValidData(infos, rc) && checkSampleState(infos, rc))
      {
        printf ("== New Read \n");
        fflush (stdout);
        for (int i = 0; i < rc; i ++){
          /*printf("--- Sample state = %d \n", infos[i].sample_state);
          fflush (stdout);*/
          //if ((rc > 0) && (infos[i].valid_data)){
          if ((rc > 0) && (infos[i].valid_data) && (infos[i].sample_state == DDS_SST_NOT_READ)){
            /* Print Message. */
            msg = (HelloWorld_data*) samples[i];
            printf ("=== [Subscriber] Received : ");
            printf ("instanceID: %d, value: %f, rc: %d\n", msg->instanceID, msg->value, rc);
            fflush (stdout);
          }
        }
        break;
      }
      else
      {
        /* Polling sleep. */
        dds_sleepfor (DDS_MSECS (20));
      }
      dds_sleepfor (DDS_MSECS (100));
    }
    j++;
  }

  /* Free the data location. */
  //PubSubLoopData_Msg_free (samples[0], DDS_FREE_ALL);

  for (unsigned int i = 0; i < MAX_SAMPLES; i++)
  {
    HelloWorld_data_free (&data[i], DDS_FREE_CONTENTS);
  }

  //printf("Delete\n");
  //fflush(stdout);

  /* Deleting the participant will delete all its children recursively as well. */
  rc = dds_delete (participant);
  if (rc != DDS_RETCODE_OK)
    DDS_FATAL("dds_delete: %s\n", dds_strretcode(-rc));

  return EXIT_SUCCESS;
}

bool checkSampleState(dds_sample_info_t infos[], dds_return_t count){
  for (int i = 0; i < count; i++){
    if(infos[i].sample_state == DDS_SST_NOT_READ)
      return true;
  }
  return false; 
}

bool checkValidData(dds_sample_info_t infos[], dds_return_t count){
  for (int i = 0; i < count; i++){
    if(infos[i].valid_data)
      return true;
  }
  return false;
}
void requested_qos(dds_entity_t reader, const dds_requested_incompatible_qos_status_t status, void *arg){
  printf("\n ===== Requested QoS ===== \n");
  fflush(stdout);
}

void sample_lost(dds_entity_t reader, const dds_sample_lost_status_t status, void *arg){
  printf("\n ===== Sample Lost ===== \n");
  fflush(stdout);
}
void sample_rejected(dds_entity_t reader, const dds_sample_rejected_status_t status, void *arg){
  printf("\n ===== Samples Rejected ===== \n");
  fflush(stdout);
}
void liveliness_changed(dds_entity_t reader, const dds_liveliness_changed_status_t status, void *arg){
  printf("\n ===== Liveliness Changed ===== \n");
  fflush(stdout);
}
void requested_dealine_missed(dds_entity_t reader, const dds_requested_deadline_missed_status_t status, void *arg){
  printf("\n ===== Requested Deadline Missed ===== \n");
  fflush(stdout);
}
void requested_incompatible_qos(dds_entity_t reader, const dds_requested_incompatible_qos_status_t status, void *arg){
  printf("\n ===== Requested Incompatible QoS ===== \n");
  fflush(stdout);
}
void subscription_macthed(dds_entity_t reader, const dds_subscription_matched_status_t status, void *arg){
  printf("\n ===== Subscruption Macthed ===== \n");
  fflush(stdout);
}
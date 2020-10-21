#include "dds/dds.h"
#include "TestDataType.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

/* An array of one message (aka sample in dds terms) will be used. */
#define MAX_SAMPLES 100000
#define DEPTH MAX_SAMPLES // DEPTH is used in other functions so it still has to be here
//#define DEPTH 5 // Irrelevant with history kind HISTORY_KEEP_ALL

static volatile int sigintH = 1;

/* Handel Ctrl-C */
void sigintHandler(int sig_num) {
  sigintH = 0;
}

//bool checkSampleState(dds_sample_info_t infos[DEPTH]);
//bool checkValidData(dds_sample_info_t infos[DEPTH]);

bool checkSampleState(dds_sample_info_t infos[], dds_return_t count);
bool checkValidData(dds_sample_info_t infos[], dds_return_t count);

bool contentFilter(const void *sample);

int main (int argc, char ** argv)
{
  dds_entity_t participant;
  dds_entity_t topic, topic2;
  dds_entity_t reader, reader2;
  TestDataType_data *msg, *msg2;

  static TestDataType_data data[MAX_SAMPLES];
  static TestDataType_data data2[MAX_SAMPLES];
  void *samples[MAX_SAMPLES];
  void *samples2[MAX_SAMPLES];
  dds_sample_info_t infos[MAX_SAMPLES];
  dds_sample_info_t infos2[MAX_SAMPLES];
  dds_return_t rc;
  dds_return_t rc2;
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

  topic2 = dds_create_topic (
    participant, &TestDataType_data_desc, "TestDataType_data", NULL, NULL);
  if (topic2 < 0)
    DDS_FATAL("dds_create_topic: %s\n", dds_strretcode(-topic2));

  // ContentFilter
  dds_set_topic_filter(topic, contentFilter);

  /* Create a reliable Reader. */
  /* dds_create_writer ( participant_or_publisher, topic, qos, listener ) */
  qos = dds_create_qos ();
  dds_qset_reliability (qos, DDS_RELIABILITY_RELIABLE, DDS_SECS (10));
  /* Change History setting */
  //dds_qset_history(qos, DDS_HISTORY_KEEP_ALL, DEPTH);
  //dds_qset_durability(qos, DDS_DURABILITY_TRANSIENT_LOCAL);

  reader = dds_create_reader (participant, topic, qos, NULL);
  if (reader < 0)
    DDS_FATAL("dds_create_reader: %s\n", dds_strretcode(-reader));
  
  reader2 = dds_create_reader (participant, topic, qos, NULL);
  if (reader2 < 0)
    DDS_FATAL("dds_create_reader: %s\n", dds_strretcode(-reader2));
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

  memset (data2, 0, sizeof (data2));
  for (int i = 0; i < MAX_SAMPLES; i++)
  {
    samples2[i] = &data2[i];
  }

  //Sleep for testing
  //dds_sleepfor (DDS_MSECS (2000));

  setbuf(stdout, NULL);

  while (sigintH){
    /* Poll until data has been read. */
    // Needs to be done dds_take/read does not seem to overwrite rc if didn't get a new message
  	rc = 0;
    rc2 = 0;
    while (sigintH)
    {
      rc = 0;
      rc2 = 0;
      /* Do the actual read.
        * The return value contains the number of read samples. */
      rc = dds_read (reader, samples, infos, MAX_SAMPLES, MAX_SAMPLES);
      //rc = dds_take (reader, samples, infos, MAX_SAMPLES, MAX_SAMPLES);
      if (rc < 0)
        DDS_FATAL("dds_read: %s\n", dds_strretcode(-rc));

      rc2 = dds_read (reader2, samples, infos, MAX_SAMPLES, MAX_SAMPLES);
      if (rc2 < 0)
        DDS_FATAL("dds_read: %s\n", dds_strretcode(-rc2));

      /*printf ("Data? \n");
      fflush (stdout);*/

      /*printf("--- Sample state = %d rc = %d \n", infos[DEPTH-1].sample_state, rc);
      fflush (stdout);*/
      /* Check if we read some data and it is valid. */
      //if ((rc > 0) && checkValidData(infos))
      //if ( ((rc > 0) && checkValidData(infos, rc) && checkSampleState(infos, rc)) || ((rc2 > 0) && checkValidData(infos2, rc2) && checkSampleState(infos2, rc2)) )
      if ( ((rc > 0) && checkValidData(infos, rc) && checkSampleState(infos, rc)) )
      {
        printf ("=== [Subscriber] Received : ");
        printf ("Messages numbers: \n");
        fflush (stdout);
        for (int i = 0; i < rc; i ++){
          /*printf("--- Sample state = %d \n", infos[i].sample_state);
          fflush (stdout);*/
          //if ((rc > 0) && (infos[i].valid_data)){
          if ((rc > 0) && (infos[i].valid_data) && (infos[i].sample_state == DDS_SST_NOT_READ)){
            /* Print Message. */
            msg = (TestDataType_data*) samples[i];
            //printf ("%d, ", msg->msgNr);
            printf ("DR1: Instance: %d; HUM: %d; TEMP: %.2f; Nr: %d \n", msg->instanceID, msg->humidity, msg->temperature, msg->msgNr);
          }
        }
        /*for (int i = 0; i < rc2; i ++){
          //if ((rc > 0) && (infos[i].valid_data)){
          if ((rc2 > 0) && (infos2[i].valid_data) && (infos2[i].sample_state == DDS_SST_NOT_READ)){
            //Print Message.
            msg2 = (TestDataType_data*) samples2[i];
            //printf ("%d, ", msg->msgNr);
            printf ("DR2: Instance: %d; HUM: %d; TEMP: %.2f; Nr: %d \n", msg2->instanceID, msg2->humidity, msg2->temperature, msg2->msgNr);
          }
        }*/
        //printf("\n");
        fflush (stdout);
        break;
      }
      else
      {
        /* Polling sleep. */
        dds_sleepfor (DDS_MSECS (20));
      }
      dds_sleepfor (DDS_MSECS (1000));
    }
  }

  /* Free the data location. */
  //PubSubLoopData_Msg_free (samples[0], DDS_FREE_ALL);

  for (unsigned int i = 0; i < MAX_SAMPLES; i++)
  {
    TestDataType_data_free (&data[i], DDS_FREE_CONTENTS);
  }

  //printf("Delete\n");
  //fflush(stdout);

  /* Deleting the participant will delete all its children recursively as well. */
  rc = dds_delete (participant);
  if (rc != DDS_RETCODE_OK)
    DDS_FATAL("dds_delete: %s\n", dds_strretcode(-rc));

  return EXIT_SUCCESS;
}

//bool checkSampleState(dds_sample_info_t infos[DEPTH]){
bool checkSampleState(dds_sample_info_t infos[], dds_return_t count){
  for (int i = 0; i < count; i++){
    if(infos[i].sample_state == DDS_SST_NOT_READ)
      return true;
  }
  return false; 
}

//bool checkValidData(dds_sample_info_t infos[DEPTH]){
bool checkValidData(dds_sample_info_t infos[], dds_return_t count){
  for (int i = 0; i < count; i++){
    if(infos[i].valid_data)
      return true;
  }
  return false;
}

bool contentFilter(const void *sample){
  TestDataType_data *msg = (TestDataType_data*)sample;
  if (msg->msgNr < 25){
    return true;
  }
  return false;
}

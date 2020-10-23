#include "dds/dds.h"
#include "TestDataType.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

/* An array of one message (aka sample in dds terms) will be used. */
#define MAX_SAMPLES 100000
//#define DEPTH MAX_SAMPLES // DEPTH is used in other functions so it still has to be here
#define DEPTH 20 // Irrelevant with history kind HISTORY_KEEP_ALL

static volatile int sigintH = 1;

/* Handel Ctrl-C */
void sigintHandler(int sig_num) {
  sigintH = 0;
}


bool checkSampleState(dds_sample_info_t infos[], dds_return_t count);
bool checkValidData(dds_sample_info_t infos[], dds_return_t count);
bool contentFilter(const void *sample);

void data_available(dds_entity_t reader, void *arg);
void offered_qos(dds_entity_t writer, const dds_offered_incompatible_qos_status_t status, void *arg);
void requested_qos(dds_entity_t reader, const dds_requested_incompatible_qos_status_t status, void *arg);

TestDataType_data *msg;
static TestDataType_data data[MAX_SAMPLES];
void *samples[MAX_SAMPLES];
dds_sample_info_t infos[MAX_SAMPLES];
dds_return_t rc;

int msg_count = 0;

int main (int argc, char ** argv)
{
  dds_entity_t participant;
  dds_entity_t topic;
  dds_entity_t reader;
  dds_listener_t *listener = NULL;

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

  /* Create a reliable Reader. */
  /* dds_create_writer ( participant_or_publisher, topic, qos, listener ) */
  qos = dds_create_qos ();
  dds_qset_reliability (qos, DDS_RELIABILITY_RELIABLE, DDS_SECS (10));
  /* Change History setting */
  //dds_qset_history(qos, DDS_HISTORY_KEEP_LAST, DEPTH);
  //dds_qset_durability(qos, DDS_DURABILITY_TRANSIENT_LOCAL);

  listener = dds_create_listener(NULL);
  dds_lset_requested_incompatible_qos(listener, requested_qos);
  dds_lset_offered_incompatible_qos(listener, offered_qos);
  dds_lset_data_available(listener, data_available);

  //reader = dds_create_reader (participant, topic, qos, NULL);
  reader = dds_create_reader (participant, topic, qos, listener);
  if (reader < 0)
    DDS_FATAL("dds_create_reader: %s\n", dds_strretcode(-reader));
  dds_delete_qos(qos);

  if (listener == NULL){
    printf("\n ===== WHAT?!?!?!?!?!? \n");
    fflush(stdout);
  }

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
  FILE *fp;
  int tmp_msg_count = 0;
  while (sigintH){
    // Do nothing
    
    for (int i = 0; i < 100; i++){
      msg_count = 0; // Reset counter
      dds_sleepfor (DDS_MSECS (5000)); 
      // can be replaced with "status = dds_waitset_attach (waitSet, waitSet, waitSet);". I think
      // Block with dds_waitset_wait() function
      // and unblock with "dds_waitset_set_trigger (waitSet, true);" in sigintHandler function
      // or anywhere you wanna stop the program
      
      tmp_msg_count = msg_count;
      fp = fopen("/home/k/Desktop/Workspaces/Master_Project/Git_Repositories/dds-on-hardware/performance_tests/CycloneDDS/writingSpeedTest/data/test_2_bytes.txt", "a");
      fprintf(fp, "%d,%d,\n", i, tmp_msg_count);
      fclose(fp);
      printf("Message Count: %d\n", tmp_msg_count);
      fflush(stdout);
    }

    break;
    //printf ("\n=== Looped \n");
    //fflush (stdout);
  }

  /* Free the data location. */
  //PubSubLoopData_Msg_free (samples[0], DDS_FREE_ALL);

  for (unsigned int i = 0; i < MAX_SAMPLES; i++)
  {
    TestDataType_data_free (&data[i], DDS_FREE_CONTENTS);
  }

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

void data_available(dds_entity_t reader, void *arg){
  //printf("\n ===== Data_available ===== \n");
  
  rc = 0;
  /* Do the actual read.
    * The return value contains the number of read samples. */
  //rc = dds_read (reader, samples, infos, MAX_SAMPLES, MAX_SAMPLES);
  rc = dds_take (reader, samples, infos, MAX_SAMPLES, MAX_SAMPLES);
  if (rc < 0)
    DDS_FATAL("dds_read: %s\n", dds_strretcode(-rc));

  for (int i = 0; i < rc; i ++){
    /*printf("--- Sample state = %d \n", infos[i].sample_state);
    fflush (stdout);*/
    if ((rc > 0) && (infos[i].valid_data)){
    //if ((rc > 0) && (infos[i].valid_data) && (infos[i].sample_state == DDS_SST_NOT_READ)){
      /* Print Message. */
      //msg = (TestDataType_data*) samples[i];
      //printf ("%d, ", msg->msgNr);
      //printf ("Instance: %d; HUM: %d; TEMP: %.2f; Nr: %d \n", msg->instanceID, msg->humidity, msg->temperature, msg->msgNr);
      msg_count++;
    }
    
  }
  
  //fflush(stdout);
}

void offered_qos(dds_entity_t writer, const dds_offered_incompatible_qos_status_t status, void *arg){
  printf("\n ===== Offered QoS ===== \n");
  fflush(stdout);
}

void requested_qos(dds_entity_t reader, const dds_requested_incompatible_qos_status_t status, void *arg){
  printf("\n ===== Requested QoS ===== \n");
  fflush(stdout);
}
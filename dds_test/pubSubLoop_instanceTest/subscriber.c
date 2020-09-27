#include "dds/dds.h"
#include "PubSubLoopData.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>

/* An array of one message (aka sample in dds terms) will be used. */
#define MAX_SAMPLES 20

static volatile int sigintH = 1;

/* Handel Ctrl-C */
void sigintHandler(int sig_num) {
  sigintH = 0;
}

int main (int argc, char ** argv)
{
  dds_entity_t participant;
  dds_entity_t topic;
  dds_entity_t reader;
  PubSubLoopData_Msg *msg;

  static PubSubLoopData_Msg data[MAX_SAMPLES];
  void *samples[MAX_SAMPLES];
  dds_sample_info_t infos[MAX_SAMPLES];
  dds_return_t rc;
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
    participant, &PubSubLoopData_Msg_desc, "PubSubLoopData_Msg", NULL, NULL);
  if (topic < 0)
    DDS_FATAL("dds_create_topic: %s\n", dds_strretcode(-topic));

  /* Create a reliable Reader. */
  /* dds_create_writer ( participant_or_publisher, topic, qos, listener ) */
  qos = dds_create_qos ();
  dds_qset_reliability (qos, DDS_RELIABILITY_RELIABLE, DDS_SECS (10));
  reader = dds_create_reader (participant, topic, qos, NULL);
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
      /* Do the actual read.
        * The return value contains the number of read samples. */
      //rc = dds_read (reader, samples, infos, MAX_SAMPLES, MAX_SAMPLES);
      rc = dds_take (reader, samples, infos, MAX_SAMPLES, MAX_SAMPLES);
      if (rc < 0)
        DDS_FATAL("dds_read: %s\n", dds_strretcode(-rc));
      /* Check if we read some data and it is valid. */
      if ((rc > 0) && (infos[0].valid_data))
      {
        for (int i = 0; i < rc; i ++){
          if ((rc > 0) && (infos[i].valid_data)){
            /* Print Message. */
            msg = (PubSubLoopData_Msg*) samples[i];
            printf ("=== [Subscriber] Received : ");
            printf ("Message (%"PRId32", %s; %d)\n", msg->userID, msg->message, msg->msgNr);
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
      dds_sleepfor (DDS_MSECS (1000));
    }
    j++;
  }

  /* Free the data location. */
  //PubSubLoopData_Msg_free (samples[0], DDS_FREE_ALL);

  for (unsigned int i = 0; i < MAX_SAMPLES; i++)
  {
    PubSubLoopData_Msg_free (&data[i], DDS_FREE_CONTENTS);
  }

  //printf("Delete\n");
  //fflush(stdout);

  /* Deleting the participant will delete all its children recursively as well. */
  rc = dds_delete (participant);
  if (rc != DDS_RETCODE_OK)
    DDS_FATAL("dds_delete: %s\n", dds_strretcode(-rc));

  return EXIT_SUCCESS;
}

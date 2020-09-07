#include "dds/dds.h"
#include "simplePingPongData.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* An array of one message (aka sample in dds terms) will be used. */
#define MAX_SAMPLES 1

int main (int argc, char ** argv)
{
  dds_entity_t participant;
  dds_entity_t topic;
  dds_entity_t reader;
  
  dds_entity_t writer;
  dds_entity_t subscriber;
  dds_entity_t publisher;
  dds_return_t status;


  sPingPongData_Msg *msg;
  sPingPongData_Msg msgO;
  void *samples[MAX_SAMPLES];
  dds_sample_info_t infos[MAX_SAMPLES];
  dds_return_t rc;
  dds_qos_t *qos;

  const char *pubPartitions[] = { "pong" };
  const char *subPartitions[] = { "ping" };
  dds_qos_t *pubQos;
  dds_qos_t *dwQos;
  dds_qos_t *drQos;
  dds_qos_t *subQos;

  (void)argc;
  (void)argv;

  /* Create a Participant. */
  /* dds_create_participant ( domain (int: 0 - 230), qos, listener ) */
  participant = dds_create_participant (DDS_DOMAIN_DEFAULT, NULL, NULL);
  if (participant < 0)
    DDS_FATAL("dds_create_participant: %s\n", dds_strretcode(-participant));

  /* Create a Topic. */
  /* A DDS_Topic is created for our sample type on the domain participant. */
  /* dds_create_topic ( participant, descriptor, name, qos, listener ) */
  topic = dds_create_topic (
    participant, &sPingPongData_Msg_desc, "sPingPongData", NULL, NULL);
  if (topic < 0)
    DDS_FATAL("dds_create_topic: %s\n", dds_strretcode(-topic));

  /* Publisher and DataWriter ********************************************************************************************************* */

  /* A DDS Publisher is created on the domain participant. */
  /* The Publisher's qos is given a partition (So it is not connected to its own reader) */
  qos = dds_create_qos ();
  dds_qset_partition (qos, 1, pubPartitions);

  publisher = dds_create_publisher (participant, qos, NULL);
  if (publisher < 0)
    DDS_FATAL("dds_create_publisher: %s\n", dds_strretcode(-publisher));
  dds_delete_qos (qos);


  /* A DDS DataWriter is created on the Publisher & Topic with a modififed Qos. */
  qos = dds_create_qos ();
  dds_qset_reliability (qos, DDS_RELIABILITY_RELIABLE, DDS_SECS(10));
  dds_qset_writer_data_lifecycle (qos, false);
  writer = dds_create_writer (publisher, topic, qos, NULL);
  if (writer < 0)
    DDS_FATAL("dds_create_writer: %s\n", dds_strretcode(-writer));
  dds_delete_qos (qos);


  /* Subscriber and DataReader ********************************************************************************************************* */

  /* A DDS Subscriber is created on the domain participant. */
  qos = dds_create_qos ();
  dds_qset_partition (qos, 1, subPartitions);

  subscriber = dds_create_subscriber (participant, qos, NULL);
  if (subscriber < 0)
    DDS_FATAL("dds_create_subscriber: %s\n", dds_strretcode(-subscriber));
  dds_delete_qos (qos);


  /* Create a reliable Reader. */
  /* A DDS DataReader is created on the Subscriber & Topic with a modified QoS. */
  /* dds_create_reader ( participant_or_publisher, topic, qos, listener ) */
  qos = dds_create_qos ();
  dds_qset_reliability (qos, DDS_RELIABILITY_RELIABLE, DDS_SECS (10));
  reader = dds_create_reader (subscriber, topic, qos, NULL);
  if (reader < 0)
    DDS_FATAL("dds_create_reader: %s\n", dds_strretcode(-reader));
  dds_delete_qos(qos);

  printf ("\n=== [Pong] Waiting for a sample ...\n");
  fflush (stdout);

  /* Initialize sample buffer, by pointing the void pointer within
   * the buffer array to a valid sample memory location. */
  samples[0] = sPingPongData_Msg__alloc ();
  //samples[1] = PubSubLoopData_Msg__alloc ();


  while (true)
  {
    /* Do the actual read.
     * The return value contains the number of read samples. */
    rc = dds_read (reader, samples, infos, MAX_SAMPLES, MAX_SAMPLES);
    //rc = dds_take (reader, samples, infos, MAX_SAMPLES, MAX_SAMPLES);
    //printf ("***rc: %d*** \n", rc);
    //printf("*** infos: %d \n", infos[i].valid_data);
    //fflush (stdout);
    if (rc < 0)
      DDS_FATAL("dds_read: %s\n", dds_strretcode(-rc));

    /* Check if we read some data and it is valid. */
    if ((rc > 0) && (infos[0].valid_data))
    {
      /* Print Message. */
      msg = (sPingPongData_Msg*) samples[0];
      printf ("=== [Subscriber] Received : ");
      printf ("Message (%"PRId32", %s)\n", msg->userID, msg->message);
      fflush (stdout);

      msgO.userID = 1;
      msgO.message = "Got it, Ping";
      printf ("=== [Publisher]  Writing : ");
      printf ("Message (%"PRId32", %s)\n", msgO.userID, msgO.message);
      fflush (stdout);
      rc = dds_write (writer, &msgO);
      if (rc != DDS_RETCODE_OK)
        DDS_FATAL("dds_write: %s\n", dds_strretcode(-rc));
      break;
    }
    else
    {
      /* Polling sleep. */
      dds_sleepfor (DDS_MSECS (20));
    }
  }

  /* Free the data location. */
  sPingPongData_Msg_free (samples[0], DDS_FREE_ALL);

  /* Deleting the participant will delete all its children recursively as well. */
  rc = dds_delete (participant);
  if (rc != DDS_RETCODE_OK)
    DDS_FATAL("dds_delete: %s\n", dds_strretcode(-rc));

  return EXIT_SUCCESS;
}

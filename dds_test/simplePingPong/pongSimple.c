#include "dds/dds.h"
#include "simplePingPongData.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* --- Defines --- */
/* An array of one message (aka sample in dds terms) will be used. */
#define MAX_SAMPLES 10

/* --- Globals ---*/
static sPingPongData_Msg data[MAX_SAMPLES];
void *samples[MAX_SAMPLES];
dds_sample_info_t infos[MAX_SAMPLES];

/* --- Function prototypes --- */
dds_entity_t prepare_dds(dds_entity_t *dw, dds_entity_t *dr, dds_entity_t *topic, dds_entity_t *participant);
sPingPongData_Msg* readMsg(dds_return_t *rc, dds_entity_t *dr);


int main (int argc, char ** argv)
{
  dds_entity_t participant;
  dds_entity_t reader;
  dds_entity_t writer;
  dds_return_t status;
  dds_entity_t topic;

  sPingPongData_Msg *msg;
  sPingPongData_Msg msgO;
  dds_return_t rc;

  (void)argc;
  (void)argv;

  /* Initialize sample buffer, by pointing the void pointer within
  * the buffer array to a valid sample memory location. */
  //samples[0] = sPingPongData_Msg__alloc ();

  /* Initialize sample data */
  memset (data, 0, sizeof (data));
  for (int i = 0; i < MAX_SAMPLES; i++)
  {
    samples[i] = &data[i];
  }

  prepare_dds(&writer, &reader, &topic, &participant);

  printf ("\n=== [Pong] Waiting for a sample ...\n");
  fflush (stdout);

  int i = 0;
  while (i<10){
    //msg = readMsg(&rc, &reader, msg);
    msg = readMsg(&rc, &reader);

    printf ("=== [Subscriber] Received : ");
    printf ("Message (%"PRId32", %s)\n", msg->userID, msg->message);
    fflush (stdout);

    msgO.userID = 20 + i;
    msgO.message = "Yeah I got it, Ping";
    //printf ("=== [Publisher]  Writing : ");
    //printf ("Message (%"PRId32", %s)\n", msgO.userID, msgO.message);
    //fflush (stdout);

    rc = dds_write (writer, &msgO);
    if (rc != DDS_RETCODE_OK)
      DDS_FATAL("dds_write: %s\n", dds_strretcode(-rc));
    i++;
  }
  //sPingPongData_Msg_free (samples[0], DDS_FREE_ALL);

  for (unsigned int i = 0; i < MAX_SAMPLES; i++)
  {
    sPingPongData_Msg_free (&data[i], DDS_FREE_CONTENTS);
  }

  /* Deleting the participant will delete all its children recursively as well. */
  rc = dds_delete (participant);
  if (rc != DDS_RETCODE_OK)
    DDS_FATAL("dds_delete: %s\n", dds_strretcode(-rc));

  return EXIT_SUCCESS;
}

/**
 * @brief Set up topic, dataWriter, and dataReader.
 * The function is very specific and should be look through and changed upon re-use.
*/
dds_entity_t prepare_dds(dds_entity_t *dw, dds_entity_t *dr, dds_entity_t *topic, dds_entity_t *participant){
  dds_entity_t subscriber;
  dds_entity_t publisher;
  dds_qos_t *qos;
  const char *pubPartitions[] = { "pong" };
  const char *subPartitions[] = { "ping" };
  dds_qos_t *pubQos;
  dds_qos_t *dwQos;
  dds_qos_t *drQos;
  dds_qos_t *subQos;

  /* Create a Participant. */
  /* dds_create_participant ( domain (int: 0 - 230), qos, listener ) */
  *participant = dds_create_participant (DDS_DOMAIN_DEFAULT, NULL, NULL);
  if (*participant < 0)
    DDS_FATAL("dds_create_participant: %s\n", dds_strretcode(-*participant));

  /* Create a Topic. */
  /* A DDS_Topic is created for our sample type on the domain participant. */
  /* dds_create_topic ( participant, descriptor, name, qos, listener ) */
  *topic = dds_create_topic (
    *participant, &sPingPongData_Msg_desc, "sPingPongData", NULL, NULL);
  if (*topic < 0)
    DDS_FATAL("dds_create_topic: %s\n", dds_strretcode(-*topic));

  /* Publisher and DataWriter ********************************************************************************************************* */

  /* A DDS Publisher is created on the domain participant. */
  /* The Publisher's qos is given a partition (So it is not connected to its own reader) */
  qos = dds_create_qos ();
  dds_qset_partition (qos, 1, pubPartitions);

  publisher = dds_create_publisher (*participant, qos, NULL);
  if (publisher < 0)
    DDS_FATAL("dds_create_publisher: %s\n", dds_strretcode(-publisher));
  dds_delete_qos (qos);


  /* A DDS DataWriter is created on the Publisher & Topic with a modififed Qos. */
  qos = dds_create_qos ();
  dds_qset_reliability (qos, DDS_RELIABILITY_RELIABLE, DDS_SECS(10));
  dds_qset_writer_data_lifecycle (qos, false);
  *dw = dds_create_writer (publisher, *topic, qos, NULL);
  if (*dw < 0)
    DDS_FATAL("dds_create_writer: %s\n", dds_strretcode(-*dw));
  dds_delete_qos (qos);


  /* Subscriber and DataReader ********************************************************************************************************* */

  /* A DDS Subscriber is created on the domain participant. */
  qos = dds_create_qos ();
  dds_qset_partition (qos, 1, subPartitions);

  subscriber = dds_create_subscriber (*participant, qos, NULL);
  if (subscriber < 0)
    DDS_FATAL("dds_create_subscriber: %s\n", dds_strretcode(-subscriber));
  dds_delete_qos (qos);


  /* Create a reliable Reader. */
  /* A DDS DataReader is created on the Subscriber & Topic with a modified QoS. */
  /* dds_create_reader ( participant_or_publisher, topic, qos, listener ) */
  qos = dds_create_qos ();
  dds_qset_reliability (qos, DDS_RELIABILITY_RELIABLE, DDS_SECS (10));
  *dr = dds_create_reader (subscriber, *topic, qos, NULL);
  if (*dr < 0)
    DDS_FATAL("dds_create_reader: %s\n", dds_strretcode(-*dr));
  dds_delete_qos(qos);
}

/**
 * @brief Read and return a message from the given dataReader.
 * The function makes the required sample_info array and buffer array of pointers, their size is desided by MAX_SAMPLES. The buffer's pointer type has to be changed manually based on the IDL.
 */
sPingPongData_Msg* readMsg(dds_return_t *rc, dds_entity_t *dr){
  //void *samples[MAX_SAMPLES];
  //dds_sample_info_t infos[MAX_SAMPLES];
  /* Initialize sample buffer, by pointing the void pointer within
   * the buffer array to a valid sample memory location. */
  //samples[0] = sPingPongData_Msg__alloc ();

  sPingPongData_Msg *msg;

  while (true)
  {
    /* Do the actual read.
     * The return value contains the number of read samples. */
    // Important to use take and NOT read (find out why that is)
    *rc = dds_take (*dr, samples, infos, MAX_SAMPLES, MAX_SAMPLES);
    //rc = dds_take (reader, samples, infos, MAX_SAMPLES, MAX_SAMPLES);
    if (*rc < 0)
      DDS_FATAL("dds_read: %s\n", dds_strretcode(-*rc));

    /* Check if we read some data and it is valid. */
    if ((*rc > 0) && (infos[0].valid_data))
    {
      /* Print Message. */
      msg = (sPingPongData_Msg*) samples[0];
      //printf ("=== [Subscriber] Received : ");
      //printf ("Message (%"PRId32", %s)\n", msg->userID, msg->message);
      //fflush (stdout);
      break;
    }
    else
    {
      /* Polling sleep. */
      dds_sleepfor (DDS_MSECS (20));
    }
  }
  /* Free the data location. */
  //sPingPongData_Msg_free (samples[0], DDS_FREE_ALL);
  return msg;
}
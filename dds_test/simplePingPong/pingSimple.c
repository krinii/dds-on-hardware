#include "dds/dds.h"
#include "simplePingPongData.h"
#include <stdio.h>
#include <stdlib.h>

/* An array of one message (aka sample in dds terms) will be used. */
#define MAX_SAMPLES 1

dds_entity_t prepare_dds(dds_entity_t *dw, dds_entity_t *dr, dds_entity_t *topic, dds_entity_t *participant);

dds_entity_t createParticipant(dds_entity_t *participantP);
dds_entity_t createTopic(dds_entity_t *topicP);

uint32_t discoverReader(dds_return_t *rc, dds_entity_t *dw);

sPingPongData_Msg* readMsg(dds_return_t *rc, dds_entity_t *dr, sPingPongData_Msg *msg);

int main (int argc, char ** argv)
{
  dds_entity_t participant;
  dds_entity_t topic;
  dds_entity_t writer;
  dds_entity_t reader;
  dds_return_t rc;

  sPingPongData_Msg msgO;
  sPingPongData_Msg *msg;
  (void)argc;
  (void)argv;

  /* Function that sets up the dds entities */
  prepare_dds(&writer, &reader, &topic, &participant);


  printf("=== [Ping]  Waiting for a reader to be discovered ...\n");
  fflush (stdout);

  discoverReader(&rc, &writer);


  /* Create a message to write. */
  msgO.userID = 0;
  msgO.message = "Did you get the message, Pong";

  /* To user: Print the information which is going to be sent */
  printf ("=== [Publisher]  Writing : ");
  printf ("Message (%"PRId32", %s)\n", msgO.userID, msgO.message);
  fflush (stdout);

  rc = dds_write (writer, &msgO);
  if (rc != DDS_RETCODE_OK)
    DDS_FATAL("dds_write: %s\n", dds_strretcode(-rc));

  /* Wait for a message on the dataReader and then read it */
  msg = readMsg(&rc, &reader, msg);

  printf ("=== [Subscriber] Received : ");
  printf ("Message (%"PRId32", %s)\n", msg->userID, msg->message);
  fflush (stdout);

  /* Deleting the participant will delete all its children recursively as well. */
  rc = dds_delete (participant);
  if (rc != DDS_RETCODE_OK)
    DDS_FATAL("dds_delete: %s\n", dds_strretcode(-rc));

  return EXIT_SUCCESS;
}

dds_entity_t prepare_dds(dds_entity_t *dw, dds_entity_t *dr, dds_entity_t *topic, dds_entity_t *participant){

  dds_entity_t publisher;
  dds_entity_t subscriber;

  const char *pubPartitions[] = { "ping" };
  const char *subPartitions[] = { "pong" };
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
  /* dds_create_topic ( participant, descriptor, name, qos, listener ) */
  *topic = dds_create_topic (
    *participant, &sPingPongData_Msg_desc, "sPingPongData", NULL, NULL);
  if (*topic < 0)
    DDS_FATAL("dds_create_topic: %s\n", dds_strretcode(-*topic));

  /* Create Publisher and DataWriter ********************************************************************************************************* */

  /* A DDS_Publisher is created on the domain participant. */
  pubQos = dds_create_qos ();
  dds_qset_partition (pubQos, 1, pubPartitions);

  publisher = dds_create_publisher (*participant, pubQos, NULL);
  if (publisher < 0)
    DDS_FATAL("dds_create_publisher: %s\n", dds_strretcode(-publisher));
  dds_delete_qos (pubQos);

  /* Create a Writer. */
  /* A DDS_DataWriter is created on the Publisher & Topic with a modified Qos. */
  dwQos = dds_create_qos ();
  dds_qset_reliability (dwQos, DDS_RELIABILITY_RELIABLE, DDS_SECS (10));
  dds_qset_writer_data_lifecycle (dwQos, false);
  /* dds_create_writer ( participant_or_publisher, topic, qos, listener ) */
  *dw = dds_create_writer (publisher, *topic, dwQos, NULL);
  if (*dw < 0)
    DDS_FATAL("dds_create_writer: %s\n", dds_strretcode(-*dw));
  dds_delete_qos(dwQos);

  /* Create Subscriber and DataReader ********************************************************************************************************* */

  /* A DDS_Subscriber is created on the domain participant. */
  subQos = dds_create_qos ();

  dds_qset_partition (subQos, 1, subPartitions);

  subscriber = dds_create_subscriber (*participant, subQos, NULL);
  if (subscriber < 0)
    DDS_FATAL("dds_create_subscriber: %s\n", dds_strretcode(-subscriber));
  dds_delete_qos (subQos);

  /* A DDS_DataReader is created on the Subscriber & Topic with a modified QoS. */
  drQos = dds_create_qos ();
  dds_qset_reliability (drQos, DDS_RELIABILITY_RELIABLE, DDS_SECS(10));
  *dr = dds_create_reader (subscriber, *topic, drQos, NULL);
  if (*dr < 0)
    DDS_FATAL("dds_create_reader: %s\n", dds_strretcode(-*dr));
  dds_delete_qos (drQos);

  return (*participant);
}

/**
 * @brief Wait for a dataReader, matching the given dataWriter, to be dicovered.
*/
uint32_t discoverReader(dds_return_t *rc, dds_entity_t *dw){
  uint32_t status = 0;
  /* Set status enabled on entity.This operation enables the status(es) based on the mask set */
  /* dds_set _status_mask (entity, mask) 
   * entity: Entity to enable the status. 
   * mask: Status value that indicates the status to be enabled */
  // Make writer "listen" for the status
  *rc = dds_set_status_mask(*dw, DDS_PUBLICATION_MATCHED_STATUS);
  if (*rc != DDS_RETCODE_OK)
    DDS_FATAL("dds_set_status_mask: %s\n", dds_strretcode(-*rc));

  // Wait for a matching dataReader to appear on the network
  while(!(status & DDS_PUBLICATION_MATCHED_STATUS))
  {
    *rc = dds_get_status_changes (*dw, &status);
    if (*rc != DDS_RETCODE_OK)
      DDS_FATAL("dds_get_status_changes: %s\n", dds_strretcode(-*rc));

    /* Polling sleep. */
    dds_sleepfor (DDS_MSECS (20));
  }
  return status;
}

/**
 * @brief Read and return a message from the given dataReader.
 * The function makes the required sample_info array and buffer array of pointers, their size is desided by MAX_SAMPLES. The buffer's pointer type has to be changed manually based on the IDL.
 */
sPingPongData_Msg* readMsg(dds_return_t *rc, dds_entity_t *dr, sPingPongData_Msg *msg){
  /* Prepare to read */

  void *samples[MAX_SAMPLES];
  dds_sample_info_t infos[MAX_SAMPLES];
  /* Initialize sample buffer, by pointing the void pointer within
   * the buffer array to a valid sample memory location. */
  samples[0] = sPingPongData_Msg__alloc ();

  /* Poll until data has been read. */
  while (true)
  {
    /* Do the actual read.
     * The return value contains the number of read samples. */
    *rc = dds_read (*dr, samples, infos, MAX_SAMPLES, MAX_SAMPLES);
    if (*rc < 0)
      DDS_FATAL("dds_read: %s\n", dds_strretcode(-*rc));

    /* Check if we read some data and it is valid. */
    if ((*rc > 0) && (infos[0].valid_data))
    {
      /* Print Message. */
      msg = (sPingPongData_Msg*) samples[0];
      // Prints has been moved out of function for easier re-use
      /*printf ("=== [Subscriber] Received : ");
      printf ("Message (%"PRId32", %s)\n", msg->userID, msg->message);
      fflush (stdout);*/
      break;
    }
    else
    {
      /* Polling sleep. */
      dds_sleepfor (DDS_MSECS (20));
    }
  }
  return msg;
}
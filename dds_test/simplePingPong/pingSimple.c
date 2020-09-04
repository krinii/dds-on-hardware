#include "dds/dds.h"
#include "simplePingPongData.h"
#include <stdio.h>
#include <stdlib.h>

/* An array of one message (aka sample in dds terms) will be used. */
#define MAX_SAMPLES 1

int main (int argc, char ** argv)
{
  dds_entity_t participant;
  dds_entity_t topic;
  dds_entity_t writer;
  dds_entity_t reader;
  dds_return_t rc;

  dds_entity_t publisher;
  dds_entity_t subscriber;

  const char *pubPartitions[] = { "ping" };
  const char *subPartitions[] = { "pong" };
  dds_qos_t *pubQos;
  dds_qos_t *dwQos;
  dds_qos_t *drQos;
  dds_qos_t *subQos;

  sPingPongData_Msg msgO;
  sPingPongData_Msg *msg;
  uint32_t status = 0;
  (void)argc;
  (void)argv;

  /* Create a Participant. */
  /* dds_create_participant ( domain (int: 0 - 230), qos, listener ) */
  participant = dds_create_participant (DDS_DOMAIN_DEFAULT, NULL, NULL);
  if (participant < 0)
    DDS_FATAL("dds_create_participant: %s\n", dds_strretcode(-participant));

  /* Create a Topic. */
  /* dds_create_topic ( participant, descriptor, name, qos, listener ) */
  topic = dds_create_topic (
    participant, &sPingPongData_Msg_desc, "sPingPongData", NULL, NULL);
  if (topic < 0)
    DDS_FATAL("dds_create_topic: %s\n", dds_strretcode(-topic));

  /* Publisher and DataWriter ********************************************************************************************************* */

  /* A DDS_Publisher is created on the domain participant. */
  pubQos = dds_create_qos ();
  dds_qset_partition (pubQos, 1, pubPartitions);

  publisher = dds_create_publisher (participant, pubQos, NULL);
  if (publisher < 0)
    DDS_FATAL("dds_create_publisher: %s\n", dds_strretcode(-publisher));
  dds_delete_qos (pubQos);

  /* Create a Writer. */
  /* A DDS_DataWriter is created on the Publisher & Topic with a modified Qos. */
  dwQos = dds_create_qos ();
  dds_qset_reliability (dwQos, DDS_RELIABILITY_RELIABLE, DDS_SECS (10));
  dds_qset_writer_data_lifecycle (dwQos, false);
  /* dds_create_writer ( participant_or_publisher, topic, qos, listener ) */
  writer = dds_create_writer (publisher, topic, dwQos, NULL);
  if (writer < 0)
    DDS_FATAL("dds_create_writer: %s\n", dds_strretcode(-writer));
  dds_delete_qos(dwQos);

  /* Subscriber and DataReader ********************************************************************************************************* */

  /* A DDS_Subscriber is created on the domain participant. */
  subQos = dds_create_qos ();

  dds_qset_partition (subQos, 1, subPartitions);

  subscriber = dds_create_subscriber (participant, subQos, NULL);
  if (subscriber < 0)
    DDS_FATAL("dds_create_subscriber: %s\n", dds_strretcode(-subscriber));
  dds_delete_qos (subQos);
  /* A DDS_DataReader is created on the Subscriber & Topic with a modified QoS. */
  drQos = dds_create_qos ();
  dds_qset_reliability (drQos, DDS_RELIABILITY_RELIABLE, DDS_SECS(10));
  reader = dds_create_reader (subscriber, topic, drQos, NULL);
  if (reader < 0)
    DDS_FATAL("dds_create_reader: %s\n", dds_strretcode(-reader));
  dds_delete_qos (drQos);




  printf("=== [Ping]  Waiting for a reader to be discovered ...\n");
  fflush (stdout);

  rc = dds_set_status_mask(writer, DDS_PUBLICATION_MATCHED_STATUS);
  if (rc != DDS_RETCODE_OK)
    DDS_FATAL("dds_set_status_mask: %s\n", dds_strretcode(-rc));

  while(!(status & DDS_PUBLICATION_MATCHED_STATUS))
  {
    rc = dds_get_status_changes (writer, &status);
    if (rc != DDS_RETCODE_OK)
      DDS_FATAL("dds_get_status_changes: %s\n", dds_strretcode(-rc));

    /* Polling sleep. */
    dds_sleepfor (DDS_MSECS (20));
  }

  /* Create a message to write. */
  msgO.userID = 0;
  msgO.message = "Did you get it, Pong";

  printf ("=== [Publisher]  Writing : ");
  printf ("Message (%"PRId32", %s)\n", msgO.userID, msgO.message);
  fflush (stdout);

  rc = dds_write (writer, &msg);
  if (rc != DDS_RETCODE_OK)
    DDS_FATAL("dds_write: %s\n", dds_strretcode(-rc));



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
    rc = dds_read (reader, samples, infos, MAX_SAMPLES, MAX_SAMPLES);
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
      break;
    }
    else
    {
      /* Polling sleep. */
      dds_sleepfor (DDS_MSECS (20));
    }
  }


  /* Deleting the participant will delete all its children recursively as well. */
  rc = dds_delete (participant);
  if (rc != DDS_RETCODE_OK)
    DDS_FATAL("dds_delete: %s\n", dds_strretcode(-rc));

  return EXIT_SUCCESS;
}

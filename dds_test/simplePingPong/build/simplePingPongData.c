/****************************************************************

  Generated by Eclipse Cyclone DDS IDL to C Translator
  File name: simplePingPongData.c
  Source: simplePingPongData.idl
  Cyclone DDS: V0.5.0

*****************************************************************/
#include "simplePingPongData.h"


static const dds_key_descriptor_t sPingPongData_Msg_keys[1] =
{
  { "userID", 0 }
};

static const uint32_t sPingPongData_Msg_ops [] =
{
  DDS_OP_ADR | DDS_OP_TYPE_4BY | DDS_OP_FLAG_KEY, offsetof (sPingPongData_Msg, userID),
  DDS_OP_ADR | DDS_OP_TYPE_STR, offsetof (sPingPongData_Msg, message),
  DDS_OP_RTS
};

const dds_topic_descriptor_t sPingPongData_Msg_desc =
{
  sizeof (sPingPongData_Msg),
  sizeof (char *),
  DDS_TOPIC_FIXED_KEY | DDS_TOPIC_NO_OPTIMIZE,
  1u,
  "sPingPongData::Msg",
  sPingPongData_Msg_keys,
  3,
  sPingPongData_Msg_ops,
  "<MetaData version=\"1.0.0\"><Module name=\"sPingPongData\"><Struct name=\"Msg\"><Member name=\"userID\"><Long/></Member><Member name=\"message\"><String/></Member></Struct></Module></MetaData>"
};

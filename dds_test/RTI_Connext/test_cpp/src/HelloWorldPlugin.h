

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from HelloWorld.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef HelloWorldPlugin_1436885487_h
#define HelloWorldPlugin_1436885487_h

#include "HelloWorld.h"

struct RTICdrStream;

#ifndef pres_typePlugin_h
#include "pres/pres_typePlugin.h"
#endif

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

extern "C" {

    #define HelloWorldPlugin_get_sample PRESTypePluginDefaultEndpointData_getSample 

    #define HelloWorldPlugin_get_buffer PRESTypePluginDefaultEndpointData_getBuffer 
    #define HelloWorldPlugin_return_buffer PRESTypePluginDefaultEndpointData_returnBuffer

    #define HelloWorldPlugin_create_sample PRESTypePluginDefaultEndpointData_createSample 
    #define HelloWorldPlugin_destroy_sample PRESTypePluginDefaultEndpointData_deleteSample 

    /* --------------------------------------------------------------------------------------
    Support functions:
    * -------------------------------------------------------------------------------------- */

    NDDSUSERDllExport extern HelloWorld*
    HelloWorldPluginSupport_create_data_w_params(
        const struct DDS_TypeAllocationParams_t * alloc_params);

    NDDSUSERDllExport extern HelloWorld*
    HelloWorldPluginSupport_create_data_ex(RTIBool allocate_pointers);

    NDDSUSERDllExport extern HelloWorld*
    HelloWorldPluginSupport_create_data(void);

    NDDSUSERDllExport extern RTIBool 
    HelloWorldPluginSupport_copy_data(
        HelloWorld *out,
        const HelloWorld *in);

    NDDSUSERDllExport extern void 
    HelloWorldPluginSupport_destroy_data_w_params(
        HelloWorld *sample,
        const struct DDS_TypeDeallocationParams_t * dealloc_params);

    NDDSUSERDllExport extern void 
    HelloWorldPluginSupport_destroy_data_ex(
        HelloWorld *sample,RTIBool deallocate_pointers);

    NDDSUSERDllExport extern void 
    HelloWorldPluginSupport_destroy_data(
        HelloWorld *sample);

    NDDSUSERDllExport extern void 
    HelloWorldPluginSupport_print_data(
        const HelloWorld *sample,
        const char *desc,
        unsigned int indent);

    /* ----------------------------------------------------------------------------
    Callback functions:
    * ---------------------------------------------------------------------------- */

    NDDSUSERDllExport extern PRESTypePluginParticipantData 
    HelloWorldPlugin_on_participant_attached(
        void *registration_data, 
        const struct PRESTypePluginParticipantInfo *participant_info,
        RTIBool top_level_registration, 
        void *container_plugin_context,
        RTICdrTypeCode *typeCode);

    NDDSUSERDllExport extern void 
    HelloWorldPlugin_on_participant_detached(
        PRESTypePluginParticipantData participant_data);

    NDDSUSERDllExport extern PRESTypePluginEndpointData 
    HelloWorldPlugin_on_endpoint_attached(
        PRESTypePluginParticipantData participant_data,
        const struct PRESTypePluginEndpointInfo *endpoint_info,
        RTIBool top_level_registration, 
        void *container_plugin_context);

    NDDSUSERDllExport extern void 
    HelloWorldPlugin_on_endpoint_detached(
        PRESTypePluginEndpointData endpoint_data);

    NDDSUSERDllExport extern void    
    HelloWorldPlugin_return_sample(
        PRESTypePluginEndpointData endpoint_data,
        HelloWorld *sample,
        void *handle);    

    NDDSUSERDllExport extern RTIBool 
    HelloWorldPlugin_copy_sample(
        PRESTypePluginEndpointData endpoint_data,
        HelloWorld *out,
        const HelloWorld *in);

    /* ----------------------------------------------------------------------------
    (De)Serialize functions:
    * ------------------------------------------------------------------------- */

    NDDSUSERDllExport extern RTIBool
    HelloWorldPlugin_serialize_to_cdr_buffer(
        char * buffer,
        unsigned int * length,
        const HelloWorld *sample); 

    NDDSUSERDllExport extern RTIBool
    HelloWorldPlugin_serialize_to_cdr_buffer_ex(
        char *buffer,
        unsigned int *length,
        const HelloWorld *sample,
        DDS_DataRepresentationId_t representation);

    NDDSUSERDllExport extern RTIBool 
    HelloWorldPlugin_deserialize(
        PRESTypePluginEndpointData endpoint_data,
        HelloWorld **sample, 
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_sample, 
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern RTIBool
    HelloWorldPlugin_deserialize_from_cdr_buffer(
        HelloWorld *sample,
        const char * buffer,
        unsigned int length);    
    #ifndef NDDS_STANDALONE_TYPE
    NDDSUSERDllExport extern DDS_ReturnCode_t
    HelloWorldPlugin_data_to_string(
        const HelloWorld *sample,
        char *str,
        DDS_UnsignedLong *str_size, 
        const struct DDS_PrintFormatProperty *property);    
    #endif

    NDDSUSERDllExport extern unsigned int 
    HelloWorldPlugin_get_serialized_sample_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    /* --------------------------------------------------------------------------------------
    Key Management functions:
    * -------------------------------------------------------------------------------------- */
    NDDSUSERDllExport extern PRESTypePluginKeyKind 
    HelloWorldPlugin_get_key_kind(void);

    NDDSUSERDllExport extern unsigned int 
    HelloWorldPlugin_get_serialized_key_max_size(
        PRESTypePluginEndpointData endpoint_data,
        RTIBool include_encapsulation,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern unsigned int 
    HelloWorldPlugin_get_serialized_key_max_size_for_keyhash(
        PRESTypePluginEndpointData endpoint_data,
        RTIEncapsulationId encapsulation_id,
        unsigned int current_alignment);

    NDDSUSERDllExport extern RTIBool 
    HelloWorldPlugin_deserialize_key(
        PRESTypePluginEndpointData endpoint_data,
        HelloWorld ** sample,
        RTIBool * drop_sample,
        struct RTICdrStream *stream,
        RTIBool deserialize_encapsulation,
        RTIBool deserialize_key,
        void *endpoint_plugin_qos);

    NDDSUSERDllExport extern
    struct RTIXCdrInterpreterPrograms *HelloWorldPlugin_get_programs();

    /* Plugin Functions */
    NDDSUSERDllExport extern struct PRESTypePlugin*
    HelloWorldPlugin_new(void);

    NDDSUSERDllExport extern void
    HelloWorldPlugin_delete(struct PRESTypePlugin *);

}

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* HelloWorldPlugin_1436885487_h */


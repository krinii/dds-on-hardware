

/*
WARNING: THIS FILE IS AUTO-GENERATED. DO NOT MODIFY.

This file was generated from HelloWorld.idl using "rtiddsgen".
The rtiddsgen tool is part of the RTI Connext distribution.
For more information, type 'rtiddsgen -help' at a command shell
or consult the RTI Connext manual.
*/

#ifndef HelloWorld_1436885487_h
#define HelloWorld_1436885487_h

#ifndef NDDS_STANDALONE_TYPE
#ifndef ndds_c_h
#include "ndds/ndds_c.h"
#endif
#else
#include "ndds_standalone_type.h"
#endif

extern const char *HelloWorldTYPENAME;

typedef struct HelloWorld {

    DDS_Char *   msg ;

} HelloWorld ;
#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, start exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport __declspec(dllexport)
#endif

#ifndef NDDS_STANDALONE_TYPE
NDDSUSERDllExport DDS_TypeCode* HelloWorld_get_typecode(void); /* Type code */
NDDSUSERDllExport RTIXCdrTypePlugin *HelloWorld_get_type_plugin_info(void);
NDDSUSERDllExport RTIXCdrSampleAccessInfo *HelloWorld_get_sample_access_info(void);
#endif

DDS_SEQUENCE(HelloWorldSeq, HelloWorld);

NDDSUSERDllExport
RTIBool HelloWorld_initialize(
    HelloWorld* self);

NDDSUSERDllExport
RTIBool HelloWorld_initialize_ex(
    HelloWorld* self,RTIBool allocatePointers,RTIBool allocateMemory);

NDDSUSERDllExport
RTIBool HelloWorld_initialize_w_params(
    HelloWorld* self,
    const struct DDS_TypeAllocationParams_t * allocParams);  

NDDSUSERDllExport
RTIBool HelloWorld_finalize_w_return(
    HelloWorld* self);

NDDSUSERDllExport
void HelloWorld_finalize(
    HelloWorld* self);

NDDSUSERDllExport
void HelloWorld_finalize_ex(
    HelloWorld* self,RTIBool deletePointers);

NDDSUSERDllExport
void HelloWorld_finalize_w_params(
    HelloWorld* self,
    const struct DDS_TypeDeallocationParams_t * deallocParams);

NDDSUSERDllExport
void HelloWorld_finalize_optional_members(
    HelloWorld* self, RTIBool deletePointers);  

NDDSUSERDllExport
RTIBool HelloWorld_copy(
    HelloWorld* dst,
    const HelloWorld* src);

#if (defined(RTI_WIN32) || defined (RTI_WINCE) || defined(RTI_INTIME)) && defined(NDDS_USER_DLL_EXPORT)
/* If the code is building on Windows, stop exporting symbols.
*/
#undef NDDSUSERDllExport
#define NDDSUSERDllExport
#endif

#endif /* HelloWorld */


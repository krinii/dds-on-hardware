cmake_minimum_required(VERSION 3.5)

# Find the CycloneDDS package. If it is not in a default location, try
# finding it relative to the example where it most likely resides.
find_package(CycloneDDS REQUIRED COMPONENTS idlc PATHS "/home/k/Desktop/Workspaces/Libraries/cyclonedds")

# This is a convenience function, provided by the CycloneDDS package,
# that will supply a library target related the the given idl file.
# In short, it takes the idl file, generates the source files with
# the proper data types and compiles them into a library.
idlc_generate(TestDataType_lib "TestDataType.idl")
idlc_generate(TestDataTypeMedium_lib "TestDataType_Medium.idl")
idlc_generate(TestDataType100_lib "TestDataType_100.idl")
idlc_generate(TestDataType150_lib "TestDataType_150.idl")
idlc_generate(TestDataType200_lib "TestDataType_200.idl")
idlc_generate(TestDataTypeLarge_lib "TestDataType_Large.idl")

# Both executables have only one related source file.
add_executable(publisherLoop publisher.c)
add_executable(subscriberLoop_Listener subscriber_listener.c)

add_executable(publisherLoop_medium publisher_medium.c)
add_executable(subscriberLoop_medium subscriber_medium.c)

add_executable(publisherLoop_100 publisher_100.c)
add_executable(subscriberLoop_100 subscriber_100.c)

add_executable(publisherLoop_150 publisher_150.c)
add_executable(subscriberLoop_150 subscriber_150.c)

add_executable(publisherLoop_200 publisher_200.c)
add_executable(subscriberLoop_200 subscriber_200.c)

add_executable(publisherLoop_large publisher_large.c)
add_executable(subscriberLoop_large subscriber_large.c)

# Both executables need to be linked to the idl data type library and
# the ddsc API library.
target_link_libraries(publisherLoop TestDataType_lib CycloneDDS::ddsc)
target_link_libraries(subscriberLoop_Listener TestDataType_lib CycloneDDS::ddsc)

target_link_libraries(publisherLoop_medium TestDataTypeMedium_lib CycloneDDS::ddsc)
target_link_libraries(subscriberLoop_medium TestDataTypeMedium_lib CycloneDDS::ddsc)

target_link_libraries(publisherLoop_100 TestDataType100_lib CycloneDDS::ddsc)
target_link_libraries(subscriberLoop_100 TestDataType100_lib CycloneDDS::ddsc)

target_link_libraries(publisherLoop_150 TestDataType150_lib CycloneDDS::ddsc)
target_link_libraries(subscriberLoop_150 TestDataType150_lib CycloneDDS::ddsc)

target_link_libraries(publisherLoop_200 TestDataType200_lib CycloneDDS::ddsc)
target_link_libraries(subscriberLoop_200 TestDataType200_lib CycloneDDS::ddsc)

target_link_libraries(publisherLoop_large TestDataTypeLarge_lib CycloneDDS::ddsc)
target_link_libraries(subscriberLoop_large TestDataTypeLarge_lib CycloneDDS::ddsc)

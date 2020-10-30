cmake_minimum_required(VERSION 3.5)

# Find the CycloneDDS package. If it is not in a default location, try
# finding it relative to the example where it most likely resides.
# find_package(CycloneDDS REQUIRED COMPONENTS idlc PATHS "/home/k/Desktop/Workspaces/Libraries/cyclonedds")
find_package(CycloneDDS REQUIRED COMPONENTS idlc PATHS "/home/ubuntu/testDDS")

# This is a convenience function, provided by the CycloneDDS package,
# that will supply a library target related the the given idl file.
# In short, it takes the idl file, generates the source files with
# the proper data types and compiles them into a library.
idlc_generate(TestDataType_lib "TestDataType.idl")
idlc_generate(TestDataType2_lib "TestDataType_2.idl")
idlc_generate(TestDataType3_lib "TestDataType_3.idl")
idlc_generate(TestDataType4_lib "TestDataType_4.idl")
idlc_generate(TestDataType5_lib "TestDataType_5.idl")
idlc_generate(TestDataType6_lib "TestDataType_6.idl")

# Both executables have only one related source file.
add_executable(publisherLoop_1 publisher_1.c)
add_executable(subscriberLoop_1 subscriber_1.c)

add_executable(publisherLoop_2 publisher_2.c)
add_executable(subscriberLoop_2 subscriber_2.c)

add_executable(publisherLoop_3 publisher_3.c)
add_executable(subscriberLoop_3 subscriber_3.c)

add_executable(publisherLoop_4 publisher_4.c)
add_executable(subscriberLoop_4 subscriber_4.c)

add_executable(publisherLoop_5 publisher_5.c)
add_executable(subscriberLoop_5 subscriber_5.c)

add_executable(publisherLoop_6 publisher_6.c)
add_executable(subscriberLoop_6 subscriber_6.c)

# Both executables need to be linked to the idl data type library and
# the ddsc API library.
target_link_libraries(publisherLoop_1 TestDataType_lib CycloneDDS::ddsc)
target_link_libraries(subscriberLoop_1 TestDataType_lib CycloneDDS::ddsc)

target_link_libraries(publisherLoop_2 TestDataType2_lib CycloneDDS::ddsc)
target_link_libraries(subscriberLoop_2 TestDataType2_lib CycloneDDS::ddsc)

target_link_libraries(publisherLoop_3 TestDataType3_lib CycloneDDS::ddsc)
target_link_libraries(subscriberLoop_3 TestDataType3_lib CycloneDDS::ddsc)

target_link_libraries(publisherLoop_4 TestDataType4_lib CycloneDDS::ddsc)
target_link_libraries(subscriberLoop_4 TestDataType4_lib CycloneDDS::ddsc)

target_link_libraries(publisherLoop_5 TestDataType5_lib CycloneDDS::ddsc)
target_link_libraries(subscriberLoop_5 TestDataType5_lib CycloneDDS::ddsc)

target_link_libraries(publisherLoop_6 TestDataType6_lib CycloneDDS::ddsc)
target_link_libraries(subscriberLoop_6 TestDataType6_lib CycloneDDS::ddsc)

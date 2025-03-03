cmake_minimum_required(VERSION 3.5)

# Find the CycloneDDS package. If it is not in a default location, try
# finding it relative to the example where it most likely resides.
find_package(CycloneDDS REQUIRED COMPONENTS idlc PATHS "/home/k/Desktop/Workspaces/Libraries/cyclonedds")

# This is a convenience function, provided by the CycloneDDS package,
# that will supply a library target related the the given idl file.
# In short, it takes the idl file, generates the source files with
# the proper data types and compiles them into a library.
idlc_generate(HelloWorldData_lib "HelloWorldData.idl")

# Both executables have only one related source file.
add_executable(HelloworldPublisher publisher.c)
add_executable(HelloworldSubscriber subscriber.c)

# Both executables need to be linked to the idl data type library and
# the ddsc API library.
target_link_libraries(HelloworldPublisher HelloWorldData_lib CycloneDDS::ddsc)
target_link_libraries(HelloworldSubscriber HelloWorldData_lib CycloneDDS::ddsc)

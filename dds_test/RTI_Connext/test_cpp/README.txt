=======================
C++ Hello World Example
=======================

An example publication and subscription pair to send and receive simple strings.

Purpose
=======

This example shows how to perform basic publish-subscribe communication.

For convenience, complete source code and a sample makefile for several
architectures have been provided.  You may generate your own
makefile or project file with rtiddsgen if you wish to run the example
in other architectures.

How to Compile and Run
======================

Make sure the environment variable NDDSHOME is defined before compiling
the example.

UNIX-based Systems
------------------

Optional
--------
If you do not wish to use the supplied makefile you may use rtiddsgen to
generate a makefile for your machine's architecture and compiler.
For example, if both the publisher and the subscriber application
will run on sparcSol2.10 machines and you want to compile with the gcc3.4.2
compiler run rtiddsgen for the sparcSol2.10gcc3.4.2 architecture:

rtiddsgen -language C++ -example sparcSol2.10gcc3.4.2 src/HelloWorld.idl

This will create a makefile & type support files in the src directory.
You may get messages saying that some files already exist and will
not be replaced. You can safely ignore those messages since all the
source files for this example are already provided.  You may specify
an alternate output with the -d option of rtiddsgen.

Compiling
---------
Before compiling, make sure that the desired verion of compiler and linker
is in your PATH environment variable.

Then compile by typing:

gmake -f make/makefile_HelloWorld_sparcSol2.10gcc3.4.2

Run the subscriber by typing:

objs/sparcSol2.10gcc3.4.2/HelloWorld_subscriber <Domain_ID> <Number_of_Samples>

and run the publisher by typing:

objs/sparcSol2.10gcc3.4.2/HelloWorld_publisher <Domain_ID> <Number_of_Samples>


Windows Systems
---------------

Optional
--------
If you do not wish to use the supplied projects you may use rtiddsgen to
generate solution and project files for your machine's architecture and compiler.
For example, if both the publisher and the subscriber application
will run on 64-bit Windows machines and you want to compile with Visual Studio
2015 run rtiddsgen for the x64Win64VS2015 architecture:

rtiddsgen -language C++ -example x64Win64VS2015 src\HelloWorld.idl

This will create solution, project files & type support files in the
src directory.  You may get messages saying that some files already exist and
will not be replaced. You can safely ignore those messages since all the
source files for this example are already provided.  You may specify
an alternate output with the -d option of rtiddsgen.

Compiling
---------

Open the generated solution file with MS Visual Studio. Build the
two projects, HelloWorld_publisher and HelloWorld_subscriber with the
settings you prefer.  If you select a DLL configuration be sure the
path to %NDDSHOME%\lib\<architecture> is in your PATH environment variable
prior to executing Visual Studio.  To see your build settings right-click
the menu area and check the Build option.  Build either the
HelloWorld_publisher or the HelloWorld_subscriber.

Run the subscriber by typing in a command prompt:

objs\<architecture>\HelloWorld_subscriber.exe <Domain_ID> <Number_of_Samples>

and run the publisher by typing:

objs\<architecture>\HelloWorld_publisher.exe <Domain_ID> <Number_of_Samples>


Optional
========
You can specify the list of nodes that you want to talk to in an environment 
variable or a file called NDDS_DISCOVERY_PEERS. If your platform does not 
support multicast, or has multicast disabled by default, you must set this
list.

Please consult the Platform Notes and online documentation for details.

Both applications accept two optional arguments:

<Domain_ID>: In order for the two applications to communicate, they have to use
the same domain ID number. By default, both Hello World applications use
domain ID 0.
If you want to use a specific domain ID, enter it as the first argument 
(valid IDs are >=0). If you are sharing a machine with others, you may
want to use separate domain IDs.

<Number_of_Samples>: 
In the publishing application, the second parameter is used as the number of
samples to publish before terminating. 
In the subscribing application, the second parameter is used as the number of
4-second intervals for which it will sleep/awake before terminating.


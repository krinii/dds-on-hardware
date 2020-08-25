FROM ubuntu:latest
# RUN mkdir dds
# COPY cyclonedds ./dds
RUN apt-get -y update && apt-get install -y \ 
    build-essential \
    cmake \
    maven \
    openjdk-8-jdk

# ## How to install cmake-3.17.0
# RUN apt-get --yes install build-essential
# RUN mkdir cmakeFolder
# COPY cmake-3.17.0 ./cmakeFolder
# RUN ./cmakeFolder/bootstrap -- -DCMAKE_USE_OPENSSL=OFF ./cmakeFolder/
# RUN make -C cmakeFolder/
# RUN make install -C cmakeFolder/

# Follow installing guide from https://github.com/eclipse-cyclonedds/cyclonedds
RUN mkdir cyclonedds
COPY cyclonedds ./cyclonedds
RUN mkdir testDDS
COPY ddsSetupScript .
RUN chmod +x ddsSetupScript
RUN ./ddsSetupScript

# RUN cmake -DCMAKE_INSTALL_PREFIX=../../testDDS ..

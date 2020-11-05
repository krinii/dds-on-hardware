// Copyright 2016 Proyectos y Sistemas de Mantenimiento SL (eProsima).
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

/**
 * @file HelloWorldPublisher.cpp
 *
 */

#include "HelloWorldPubSubTypes.h"

#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>
#include <fastdds/dds/publisher/Publisher.hpp>
#include <fastdds/dds/publisher/DataWriter.hpp>
#include <fastdds/dds/publisher/DataWriterListener.hpp>

#include <signal.h>

#define DEBUG false

using namespace eprosima::fastdds::dds;

static volatile int sigintH = 1;

/* Handel Ctrl-C */
void sigintHandler(int sig_num) {
  sigintH = 0;
}

class HelloWorldPublisher
{
private:

    HelloWorld hello_;

    DomainParticipant* participant_;

    Publisher* publisher_;

    Topic* topic_;

    DataWriter* writer_;

    TypeSupport type_;

    class PubListener : public DataWriterListener
    {
    public:

        PubListener()
            : matched_(0)
        {
        }

        ~PubListener() override
        {
        }

        void on_publication_matched(
                DataWriter*,
                const PublicationMatchedStatus& info) override
        {
            if (DEBUG){
                if (info.current_count_change == 1)
                {
                    matched_ = info.total_count;
                    std::cout << "Publisher matched." << std::endl;
                }
                else if (info.current_count_change == -1)
                {
                    matched_ = info.total_count;
                    std::cout << "Publisher unmatched." << std::endl;
                }
                else
                {
                    std::cout << info.current_count_change
                            << " is not a valid value for PublicationMatchedStatus current count change." << std::endl;
                }
            }
        }

        std::atomic_int matched_;

    } listener_;

public:

    HelloWorldPublisher()
        : participant_(nullptr)
        , publisher_(nullptr)
        , topic_(nullptr)
        , writer_(nullptr)
        , type_(new HelloWorldPubSubType())
    {
    }

    virtual ~HelloWorldPublisher()
    {
        if (writer_ != nullptr)
        {
            publisher_->delete_datawriter(writer_);
        }
        if (publisher_ != nullptr)
        {
            participant_->delete_publisher(publisher_);
        }
        if (topic_ != nullptr)
        {
            participant_->delete_topic(topic_);
        }
        DomainParticipantFactory::get_instance()->delete_participant(participant_);
    }

    //!Initialize the publisher
    bool init()
    {
        //hello_.index(0);
        //hello_.message("HelloWorld");
        //double val[10] = {1.0, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9};
        /*std::array<double, 1> val;
        val[0] = 4.8578964;
        hello_.arr(val);*/
        std::cout << "Size of arr: " << sizeof(hello_.arr()) << std::endl;
        //std::cout << "val[0]: " << (val[0]) << std::endl;

        DomainParticipantQos participantQos;
        participantQos.name("Participant_publisher");
        participant_ = DomainParticipantFactory::get_instance()->create_participant(0, participantQos);

        if (participant_ == nullptr)
        {
            return false;
        }

        // Register the Type
        type_.register_type(participant_);

        // Create the publications Topic
        topic_ = participant_->create_topic("HelloWorldTopic", "HelloWorld", TOPIC_QOS_DEFAULT);

        if (topic_ == nullptr)
        {
            return false;
        }

        // Create the Publisher
        publisher_ = participant_->create_publisher(PUBLISHER_QOS_DEFAULT, nullptr);

        if (publisher_ == nullptr)
        {
            return false;
        }

        // Create the DataWriter
        DataWriterQos dwQos;
        dwQos.reliability().kind = BEST_EFFORT_RELIABILITY_QOS;
        dwQos.reliability().max_blocking_time = 10;
        //writer_ = publisher_->create_datawriter(topic_, DATAWRITER_QOS_DEFAULT, &listener_);
        writer_ = publisher_->create_datawriter(topic_, dwQos, &listener_);

        if (writer_ == nullptr)
        {
            return false;
        }
        return true;
    }

    //!Send a publication
    bool publish() // Not being used in speed test
    {
        if ((listener_.matched_ > 0) && sigintH) //Makes sure there is a listener on the other end, remove if you just want it to write anyway
        {
            //hello_.index(hello_.index() + 1);
            std::array<double, 64000> val = hello_.arr();
            val[0] = val[0] + 1.0;
            hello_.arr(val);
            writer_->write(&hello_);
            return true;
        }
        return false;
    }

    //!Run the Publisher
    void run(
            uint32_t samples)
    {
        uint32_t samples_sent = 0;
        //while ((samples_sent < samples) && sigintH)
        while (sigintH)
        {
            writer_->write(&hello_);
            //samples_sent++;
            /*if (publish())
            {
                samples_sent++;
                //std::array<double, 10> val = hello_.arr();
                //std::cout << "arr: " << val[0] << " SENT" << std::endl;
            }*/
            //std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        //std::cout << "Samples sent: " << samples_sent << std::endl;
    }
};

int main(
        int argc,
        char** argv)
{
    signal(SIGINT, sigintHandler);
    std::cout << "Starting publisher." << std::endl;
    
    int samples = 100000;

    HelloWorldPublisher* mypub = new HelloWorldPublisher();

    if(mypub->init())
    {
        mypub->run(static_cast<uint32_t>(samples));
    }

    std::cout << "Publisher cleanup" << std::endl;
    delete mypub;
    return 0;
}

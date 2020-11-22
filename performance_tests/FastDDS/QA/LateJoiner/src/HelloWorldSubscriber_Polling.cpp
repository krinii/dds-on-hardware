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
 * @file HelloWorldSubscriber.cpp
 *
 */

#include "HelloWorldPubSubTypes.h"

#include <fastdds/dds/domain/DomainParticipantFactory.hpp>
#include <fastdds/dds/domain/DomainParticipant.hpp>
#include <fastdds/dds/topic/TypeSupport.hpp>
#include <fastdds/dds/subscriber/Subscriber.hpp>
#include <fastdds/dds/subscriber/DataReader.hpp>
#include <fastdds/dds/subscriber/DataReaderListener.hpp>
#include <fastdds/dds/subscriber/qos/DataReaderQos.hpp>
#include <fastdds/dds/subscriber/SampleInfo.hpp>

#include <signal.h>

using namespace eprosima::fastdds::dds;

static volatile int sigintH = 1;

/* Handel Ctrl-C */
void sigintHandler(int sig_num) {
  sigintH = 0;
}

class HelloWorldSubscriber
{
private:

    DomainParticipant* participant_;

    Subscriber* subscriber_;

    DataReader* reader_;

    Topic* topic_;

    TypeSupport type_;

    class SubListener : public DataReaderListener
    {
    public:

        SubListener()
            : samples_(0)
        {
        }

        ~SubListener() override
        {
        }

        void on_subscription_matched(
                DataReader*,
                const SubscriptionMatchedStatus& info) override
        {
            if (info.current_count_change == 1)
            {
                std::cout << "Subscriber matched." << std::endl;
            }
            else if (info.current_count_change == -1)
            {
                std::cout << "Subscriber unmatched." << std::endl;
            }
            else
            {
                std::cout << info.current_count_change
                        << " is not a valid value for SubscriptionMatchedStatus current count change" << std::endl;
            }
        }

        void on_data_available(
                DataReader* reader) override
        {
            SampleInfo info;
            
            /*if (reader->take_next_sample(&hello_, &info) == ReturnCode_t::RETCODE_OK)
            {
                if (info.instance_state == ALIVE)
                {
                    samples_++;
                    std::cout << "Message Received" << std::endl;
                    std::cout << "Value: " << hello_.value() << " RECEIVED." << std::endl;
                }
            }*/
            while(reader->take_next_sample(&hello_, &info) == ReturnCode_t::RETCODE_OK)
            {
                if (info.instance_state == ALIVE)
                {
                    samples_++;
                    std::cout << "Message Received" << std::endl;
                    std::cout << "Value: " << hello_.value() << " RECEIVED." << std::endl;
                }
            }
        }

        HelloWorld hello_;

        std::atomic_int samples_;

    } listener_;

public:

    HelloWorldSubscriber()
        : participant_(nullptr)
        , subscriber_(nullptr)
        , topic_(nullptr)
        , reader_(nullptr)
        , type_(new HelloWorldPubSubType())
    {
    }

    virtual ~HelloWorldSubscriber()
    {
        if (reader_ != nullptr)
        {
            subscriber_->delete_datareader(reader_);
        }
        if (topic_ != nullptr)
        {
            participant_->delete_topic(topic_);
        }
        if (subscriber_ != nullptr)
        {
            participant_->delete_subscriber(subscriber_);
        }
        DomainParticipantFactory::get_instance()->delete_participant(participant_);
    }

    //!Initialize the subscriber
    bool init()
    {
        DomainParticipantQos participantQos;
        participantQos.name("Participant_subscriber");
        participant_ = DomainParticipantFactory::get_instance()->create_participant(0, participantQos);

        if (participant_ == nullptr)
        {
            return false;
        }

        // Register the Type
        type_.register_type(participant_);

        // Create the subscriptions Topic
        topic_ = participant_->create_topic("HelloWorldTopic", "HelloWorld", TOPIC_QOS_DEFAULT);

        if (topic_ == nullptr)
        {
            return false;
        }

        // Create the Subscriber
        subscriber_ = participant_->create_subscriber(SUBSCRIBER_QOS_DEFAULT, nullptr);

        if (subscriber_ == nullptr)
        {
            return false;
        }

        //subscriber_->

        // Create the DataReader
        DataReaderQos drQos;
        //drQos.reliability().kind = RELIABLE_RELIABILITY_QOS;
        //drQos.reliability().max_blocking_time = 10;
        drQos.reliability().kind = BEST_EFFORT_RELIABILITY_QOS;

        drQos.history().kind = KEEP_LAST_HISTORY_QOS;
        drQos.history().depth = 7;
        drQos.durability().kind = TRANSIENT_LOCAL_DURABILITY_QOS;
        //drQos.durability().kind = TRANSIENT_DURABILITY_QOS;

        drQos.resource_limits().max_samples_per_instance = 5;
        drQos.resource_limits().max_samples = 200;

        //reader_ = subscriber_->create_datareader(topic_, DATAREADER_QOS_DEFAULT, &listener_);
        //reader_ = subscriber_->create_datareader(topic_, drQos, &listener_);
        reader_ = subscriber_->create_datareader(topic_, drQos);

        if (reader_ == nullptr)
        {
            return false;
        }

        return true;
    }

    //!Run the Subscriber
    void run(
        uint32_t samples)
    {
        HelloWorld dataME_;
        std::atomic_int samplesME_;
        SampleInfo infoME;
        //while(listener_.samples_ < samples)
        while(sigintH)
        {
            while(reader_->read_next_sample(&dataME_, &infoME) == ReturnCode_t::RETCODE_OK)
            {
                if (infoME.instance_state == ALIVE)
                {
                    samplesME_++;
                    //std::cout << "Message Received" << std::endl;
                    std::cout << "Value: " << dataME_.value() << ", nSample: " << samplesME_ << std::endl;
                }
            }
            //std::cout << "Cycled" << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }
};

int main(
        int argc,
        char** argv)
{
    signal(SIGINT, sigintHandler);

    std::cout << "Starting subscriber." << std::endl;
    int samples = 1;

    HelloWorldSubscriber* mysub = new HelloWorldSubscriber();
    if(mysub->init())
    {
        mysub->run(static_cast<uint32_t>(samples));
    }

    delete mysub;
    std::cout << "Subscriber clean up." << std::endl;
    return 0;
}

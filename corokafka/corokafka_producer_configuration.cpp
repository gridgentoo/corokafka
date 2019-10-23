/*
** Copyright 2019 Bloomberg Finance L.P.
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
*/
#include <corokafka/corokafka_producer_configuration.h>

namespace Bloomberg {
namespace corokafka {

//========================================================================
//                       PRODUCER CONFIGURATION
//========================================================================
const std::string ProducerConfiguration::s_internalOptionsPrefix = "internal.producer.";

const Configuration::OptionSet ProducerConfiguration::s_internalOptions = {
    "internal.producer.max.queue.length",
    "internal.producer.payload.policy",
    "internal.producer.preserve.message.order",
    "internal.producer.retries",
    "internal.producer.timeout.ms",
    "internal.producer.wait.for.acks",
    "internal.producer.wait.for.acks.timeout.ms",
    "internal.producer.flush.wait.for.acks",
    "internal.producer.flush.wait.for.acks.timeout.ms",
    "internal.producer.log.level",
    "internal.producer.auto.throttle",
    "internal.producer.auto.throttle.multiplier",
    "internal.producer.queue.full.notification"
};

const Configuration::OptionSet ProducerConfiguration::s_internalTopicOptions;

ProducerConfiguration::ProducerConfiguration(const std::string& topicName,
                                             Options options,
                                             Options topicOptions) :
    Configuration(KafkaType::Producer, topicName, std::move(options), std::move(topicOptions))
{
}

void ProducerConfiguration::setDeliveryReportCallback(Callbacks::DeliveryReportCallback callback)
{
    _deliveryReportCallback = std::move(callback);
}

const Callbacks::DeliveryReportCallback& ProducerConfiguration::getDeliveryReportCallback() const
{
    return _deliveryReportCallback;
}

void ProducerConfiguration::setPartitionerCallback(Callbacks::PartitionerCallback callback)
{
    _partitionerCallback = callback;
}

const Callbacks::PartitionerCallback& ProducerConfiguration::getPartitionerCallback() const
{
    return _partitionerCallback;
}

void ProducerConfiguration::setQueueFullCallback(Callbacks::QueueFullCallback callback)
{
    _queueFullCallback = callback;
}

const Callbacks::QueueFullCallback& ProducerConfiguration::getQueueFullCallback() const
{
    return _queueFullCallback;
}

}
}

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
#ifndef BLOOMBERG_COROKAFKA_PRODUCER_CONFIGURATION_H
#define BLOOMBERG_COROKAFKA_PRODUCER_CONFIGURATION_H

#include <corokafka/corokafka_callbacks.h>
#include <corokafka/corokafka_utils.h>
#include <corokafka/corokafka_configuration.h>
#include <corokafka/corokafka_topic.h>

namespace Bloomberg {
namespace corokafka {

//========================================================================
//                       PRODUCER CONFIGURATION
//========================================================================
/**
 * @brief The ProducerConfiguration is a builder class which contains
 *        configuration information for a specific topic. This configuration consists
 *        of both RdKafka and CoroKafka configuration options as per documentation
 *        (see CONFIGURATION.md in the respective projects).
 *        At a minimum, the user should supply a 'metadata.broker.list' in the constructor 'options'
 *        as well as a key and a payload serializer callback.
 */
class ProducerConfiguration : public Configuration
{
    friend class Configuration;
public:
    /**
     * @brief Create a producer configuration.
     * @param topic The topic to which this configuration applies.
     * @param options The producer configuration options (for both RdKafka and CoroKafka).
     * @param topicOptions The topic configuration options (for both RdKafka and CoroKafka).
     * @note 'metadata.broker.list' must be supplied in 'options'.
     */
    ProducerConfiguration(const std::string& topicName,
                          Options options,
                          Options topicOptions);
    
    /**
     * @brief Set the delivery report callback.
     * @param callback The callback.
     */
    void setDeliveryReportCallback(Callbacks::DeliveryReportCallback callback);
    
    /**
     * @brief Get the delivery report callback
     * @return The callback.
     */
    const Callbacks::DeliveryReportCallback& getDeliveryReportCallback() const;
    
    /**
     * @brief Set the partitioner callback.
     * @param callback The callback.
     * @remark A default hash partitioner is already supplied internally and as such using this callback is optional.
     */
    void setPartitionerCallback(Callbacks::PartitionerCallback callback);
    
    /**
     * @brief Get the partitioner callback.
     * @return The callback.
     */
    const Callbacks::PartitionerCallback& getPartitionerCallback() const;
    
    /**
     * @brief Set the queue full callback.
     * @param callback The callback.
     */
    void setQueueFullCallback(Callbacks::QueueFullCallback callback);
    
    /**
     * @brief Get the queue full callback.
     * @return The callback.
     */
    const Callbacks::QueueFullCallback& getQueueFullCallback() const;
private:
    Callbacks::DeliveryReportCallback           _deliveryReportCallback;
    Callbacks::PartitionerCallback              _partitionerCallback;
    Callbacks::QueueFullCallback                _queueFullCallback;
    static const OptionSet                      s_internalOptions;
    static const OptionSet                      s_internalTopicOptions;
    static const std::string                    s_internalOptionsPrefix;
};

}}

#endif //BLOOMBERG_COROKAFKA_PRODUCER_CONFIGURATION_H

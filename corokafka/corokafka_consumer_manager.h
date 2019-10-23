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
#ifndef BLOOMBERG_COROKAFKA_CONSUMER_MANAGER_H
#define BLOOMBERG_COROKAFKA_CONSUMER_MANAGER_H

#include <vector>
#include <map>
#include <chrono>
#include <corokafka/corokafka_utils.h>
#include <corokafka/corokafka_metadata.h>
#include <corokafka/corokafka_configuration_builder.h>
#include <quantum/quantum.h>

namespace Bloomberg {
namespace corokafka {

class ConsumerManagerImpl;

/**
 * @brief The ConsumerManager is the object through which consumers commit messages as well
 *        as control the behavior of the message processing by pausing, resuming, etc.
 *        Unlike the ProducerManager, the consumers receive messages asynchronously via the
 *        receiver callback, which means they don't need to interface with this class.
 * @note Committing messages can also be done via the message object itself.
 */
class ConsumerManager
{
public:
    /**
     * @brief Pause all consumption from this topic.
     * @param topic The topic name. If the topic is not specified, the function will apply to all topics.
     */
    void pause(const std::string& topic = {});
    
    /**
     * @brief Resume all consumption from this topic.
     * @param topic The topic name. If the topic is not specified, the function will apply to all topics.
     */
    void resume(const std::string& topic = {});
    
    /**
     * @brief Subscribe a previously unsubscribed consumer.
     * @param topic The topic name. If the topic is not specified, the function will apply to all topics.
     * @param partitionList The optional partition list assignment.
     * @note This method will only work if the consumer was been previously 'unsubscribed'. All the original
     *       configuration settings will remain the same, including PartitionStrategy (Static or Dynamic).
     *       If a partitionList is not provided, the values specified via ConsumerConfiguration::assignInitialPartitions()
     *       shall be used with offsets set to RD_KAFKA_OFFSET_STORED.
     */
    void subscribe(const std::string& topic,
                   cppkafka::TopicPartitionList partitionList = {});
    
    /**
     * @brief Unsubscribe from this topic.
     * @param topic The topic name. If the topic is not specified, the function will apply to all topics.
     */
    void unsubscribe(const std::string& topic = {});
    
    /**
     * @brief Commits an offset. The behavior of this function depends on the 'internal.consumer.offset.persist.strategy' value.
     * @param topicPartition The offset to commit. Must have a valid topic, partition and offset or just a topic (see note).
     * @param opaque Pointer which will be passed as-is via the 'OffsetCommitCallback'.
     * @param forceSync If true, run the commit synchronously. Otherwise run it according to the
     *                  'internal.consumer.commit.exec' setting.
     * @return Error object. If the number of retries reach 0, error contains RD_KAFKA_RESP_ERR__FAIL.
     * @note If only the topic is supplied, this API will commit all offsets in the current partition assignment.
     *       This is only valid if 'internal.consumer.offset.persist.strategy=commit'.
     * @warning If this method is used, 'internal.consumer.auto.offset.persist' must be set to 'false' and NO commits
     *          should be made via the ReceivedMessage::commit() API.
     */
    cppkafka::Error commit(const cppkafka::TopicPartition& topicPartition,
                 const void* opaque = nullptr,
                 bool forceSync = false);
    
    /**
     * @brief Similar to the above commit() but supporting a list of partitions.
     * @param topicPartitions Partitions on the *same* topic. Each TopicPartition must have a valid topic, partition and offset.
     * @param opaque Pointer which will be passed as-is via the 'OffsetCommitCallback'.
     * @param forceSync If true, run the commit synchronously. Otherwise run it according to the
     *                  'internal.consumer.commit.exec' setting.
     * @return Error object. If the number of retries reach 0, error contains RD_KAFKA_RESP_ERR__FAIL.
     */
    cppkafka::Error commit(const cppkafka::TopicPartitionList& topicPartitions,
                 const void* opaque = nullptr,
                 bool forceSync = false);
    
    /**
     * @brief Gracefully shut down all consumers and unsubscribe from all topics.
     * @remark Note that this method is automatically called in the destructor.
     */
    void shutdown();
    
    /**
     * @brief Get Kafka metadata associated with this topic
     * @param topic The topic to query
     * @return The metadata object
     */
    ConsumerMetadata getMetadata(const std::string& topic);
    
    /**
     * @brief Enables or disables the preprocessor callback (if registered)
     * @param enable True to enable, false to disable
     * @param topic The topic name. If not set, this operation will apply to all topics.
     * @remark Note that the preprocessor is enabled by default
     * @remark The overload with no topic will act on all topics.
     */
    void preprocess(bool enable, const std::string& topic = {});
    
    /**
     * @brief Get the configuration associated with this topic.
     * @param topic The topic.
     * @return A reference to the configuration.
     */
    const ConsumerConfiguration& getConfiguration(const std::string& topic) const;
    
    /**
     * @brief Get all the managed topics
     * @return The topic list.
     */
    std::vector<std::string> getTopics() const;
    
protected:
    using ConfigMap = ConfigurationBuilder::ConfigMap<ConsumerConfiguration>;
    ConsumerManager(quantum::Dispatcher& dispatcher,
                    const ConnectorConfiguration& connectorConfiguration,
                    const ConfigMap& config);
    
    ConsumerManager(quantum::Dispatcher& dispatcher,
                    const ConnectorConfiguration& connectorConfiguration,
                    ConfigMap&& config);
    
    virtual ~ConsumerManager();
    
    void poll();
    
private:
    std::unique_ptr<ConsumerManagerImpl>  _impl;
};

}}

#endif //BLOOMBERG_COROKAFKA_CONSUMER_MANAGER_H

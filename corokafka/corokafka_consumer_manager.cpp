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
#include <corokafka/corokafka_consumer_manager.h>
#include <corokafka/impl/corokafka_consumer_manager_impl.h>

namespace Bloomberg {
namespace corokafka {

ConsumerManager::ConsumerManager(quantum::Dispatcher& dispatcher,
                                 const ConnectorConfiguration& connectorConfiguration,
                                 const ConfigMap& config) :
    _impl(new ConsumerManagerImpl(dispatcher, connectorConfiguration, config))
{

}

ConsumerManager::ConsumerManager(quantum::Dispatcher& dispatcher,
                                 const ConnectorConfiguration& connectorConfiguration,
                                 ConfigMap&& config) :
    _impl(new ConsumerManagerImpl(dispatcher, connectorConfiguration, std::move(config)))
{

}

ConsumerManager::~ConsumerManager()
{

}

ConsumerMetadata ConsumerManager::getMetadata(const std::string& topic)
{
    return _impl->getMetadata(topic);
}

void ConsumerManager::preprocess(bool enable, const std::string& topic)
{
    _impl->preprocess(enable, topic);
}

void ConsumerManager::pause(const std::string& topic)
{
    _impl->pause(topic);
}

void ConsumerManager::resume(const std::string& topic)
{
    _impl->resume(topic);
}

void ConsumerManager::subscribe(const std::string& topic,
                                cppkafka::TopicPartitionList partitionList)
{
    _impl->subscribe(topic, std::move(partitionList));
}

void ConsumerManager::unsubscribe(const std::string& topic)
{
    _impl->unsubscribe(topic);
}

cppkafka::Error ConsumerManager::commit(const cppkafka::TopicPartition& topicPartition,
                                          const void* opaque,
                                          bool forceSync)
{
    return _impl->commit(topicPartition, opaque, forceSync);
}

cppkafka::Error ConsumerManager::commit(const cppkafka::TopicPartitionList& topicPartitions,
                                          const void* opaque,
                                          bool forceSync)
{
    return _impl->commit(topicPartitions, opaque, forceSync);
}

void ConsumerManager::shutdown()
{
    _impl->shutdown();
}

void ConsumerManager::poll()
{
    _impl->poll();
}

const ConsumerConfiguration& ConsumerManager::getConfiguration(const std::string& topic) const
{
    return _impl->getConfiguration(topic);
}

std::vector<std::string> ConsumerManager::getTopics() const
{
    return _impl->getTopics();
}

}
}

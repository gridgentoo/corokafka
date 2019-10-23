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
#ifndef BLOOMBERG_COROKAFKA_SENT_MESSAGE_H
#define BLOOMBERG_COROKAFKA_SENT_MESSAGE_H

#include <corokafka/corokafka_message.h>
#include <cppkafka/macros.h>

namespace Bloomberg {
namespace corokafka {

class SentMessage : public IMessage
{
    friend class ProducerManagerImpl;
public:    
    /**
     * @sa IMessage::getKeyBuffer
     */
    const cppkafka::Buffer& getKeyBuffer() const final;
    /**
     * @sa IMessage::getHeaderList
     */
    const HeaderListType& getHeaderList() const final;
    /**
     * @sa IMessage::getPayloadBuffer
     */
    const cppkafka::Buffer& getPayloadBuffer() const final;
    /**
     * @sa IMessage::getHandle
     */
    uint64_t getHandle() const final;
    /**
     * @sa IMessage::getError
     */
    cppkafka::Error getError() const final;
    /**
     * @sa IMessage::getTopic
     */
    std::string getTopic() const final;
    /**
     * @sa IMessage::getPartition
     */
    int getPartition() const final;
    /**
     * @sa IMessage::getOffset
     */
    int64_t getOffset() const final;
    /**
     * @sa IMessage::getTimestamp
     */
    std::chrono::milliseconds getTimestamp() const final;
    /**
     * @sa IMessage::operator bool
     */
    explicit operator bool() const final;
    /**
     * @brief Return the opaque application-specific pointer set when send() or sendAsync() were called.
     * @return The opaque pointer.
     */
    void* getOpaque() const;
    
#if (RD_KAFKA_VERSION >= RD_KAFKA_MESSAGE_STATUS_SUPPORT_VERSION)
    /**
     * @brief Gets the message persistence status.
     * @note Only available if SentMessage was build with a Message type.
     */
    rd_kafka_msg_status_t getStatus() const;
#endif

private:
    SentMessage(const cppkafka::Message& kafkaMessage, void* opaque);
    SentMessage(const cppkafka::MessageBuilder& builder, cppkafka::Error error, void* opaque);
    
    const cppkafka::Message*          _message;
    const cppkafka::MessageBuilder*   _builder;
    cppkafka::Error                   _error;
    void*                   _opaque;
};

}}

#endif //BLOOMBERG_COROKAFKA_SENT_MESSAGE_H

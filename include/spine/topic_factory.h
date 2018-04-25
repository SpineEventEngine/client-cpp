/*
 * Copyright 2017, TeamDev Ltd. All rights reserved.
 *
 * Redistribution and use in source and/or binary forms, with or without
 * modification, must retain the above copyright notice and the following
 * disclaimer.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef SPINE_TOPICFACTORY_H
#define SPINE_TOPICFACTORY_H

#include <string>
#include <vector>
#include <Poco/UUIDGenerator.h>

#include "types.h"
#include "spine/util/message_utils.hpp"

#include <spine/client/entities.pb.h>
#include <spine/client/subscription.pb.h>

namespace spine {

namespace core
{
    class ActorContext;
}

namespace client {

/**
 * Public API for creating \b Topic instances, using the ActorRequestFactory.
 * configuration.
 *
 * @see ActorRequestFactory::topic_factory()
 *
 * @author Vladimir Moiseiev
 */

class TopicFactory
{
public:
    TopicFactory(std::unique_ptr<core::ActorContext>&& actor_context);

public:
    /**
     * Creates a \b Topic for all of the specified entity states.
     *
     * @tparam T Protobuf Message type of a target entity.
     * @return the instance of assembled according to the parameters.
     */
    template <typename T, typename = enable_param_if_protobuf_message<T>>
    TopicPtr all()
    {
        return make_topic(
                        T::descriptor()->file()->options().GetExtension(type_url_prefix),
                        T::descriptor()->full_name()
                );
    };
    template <typename T, typename = enable_param_if_protobuf_message<T>,
              typename I, typename = enable_param_if_protobuf_message<I>>
    TopicPtr some(const std::vector<std::unique_ptr<I>>& ids)
    {
        return make_topic(
                        T::descriptor()->file()->options().GetExtension(type_url_prefix),
                        T::descriptor()->full_name(),
                        ids
                );
    };

private:
    TopicPtr make_topic(const std::string& prefix, const std::string& type);
    template <typename T, typename = enable_param_if_protobuf_message<T>>
    TopicPtr make_topic(const std::string& prefix, const std::string& type,
                        const std::vector<std::unique_ptr<T>>& ids)
    {
        return from_target(std::move(compose_target(prefix, type, ids)));
    }
    TopicPtr from_target(std::unique_ptr<Target>&&);

private:
    std::unique_ptr<core::ActorContext> actor_context_;
    Poco::UUIDGenerator uuid_generator_;
};

}} //namespace

#endif //SPINE_TOPICFACTORY_H

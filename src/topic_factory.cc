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

#include "spine/topic_factory.h"

#include "spine/message_utils.hpp"

using namespace spine::client;

TopicFactory::TopicFactory(const ActorRequestFactory& actor_request_factory)
{
    actor_context_ = actor_request_factory.actor_context();
}

std::unique_ptr<Topic> TopicFactory::all(const type::TypeUrl& type_url)
{
    std::unique_ptr<Target> target { create_with_value<Target>(type_url.value()) };
    return for_target(std::move(target));
}

std::unique_ptr<Topic> TopicFactory::for_target(std::unique_ptr<Target>&& target)
{
    TopicId* topic_id = TopicId::default_instance().New();
    topic_id->set_value(uuid_generator_.createRandom().toString());

    Topic* topic = Topic::default_instance().New();
    topic->set_allocated_id(topic_id);
    topic->set_allocated_target(target.release());
    topic->set_allocated_context(clone(actor_context_));

    return std::unique_ptr<Topic>{topic};
}

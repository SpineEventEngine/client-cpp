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

#include <google/protobuf/field_mask.pb.h>
#include <spine/core/actor_context.pb.h>

#include "spine/topic_factory.h"
#include "spine/util/any_utils.h"
#include "spine/util/target_utils.h"

using namespace spine::core;

namespace spine {
namespace client {

TopicFactory::TopicFactory(std::unique_ptr<core::ActorContext> &&actor_context)
{
    actor_context_ = std::move(actor_context);
}

TopicPtr TopicFactory::from_target(std::unique_ptr<Target>&& target)
{
    std::unique_ptr<TopicId> topic_id = std::unique_ptr<TopicId> {TopicId::default_instance().New() };
    topic_id->set_value(uuid_generator_.createRandom().toString());

    Topic* topic = Topic::default_instance().New();
    topic->set_allocated_id(topic_id.release());
    topic->set_allocated_target(target.release());
    topic->set_allocated_context(clone(actor_context_));
    topic->set_allocated_field_mask(clone(google::protobuf::FieldMask::default_instance()));

    return std::unique_ptr<Topic>{topic};
}

TopicPtr TopicFactory::make_topic(const std::string& prefix, const std::string& type)
{
    return from_target(std::move(compose_target(prefix, type)));
}

}}

/*
 * Copyright 2018, TeamDev. All rights reserved.
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

#include "spine/actor_request_factory.h"

#include "spine/topic_factory.h"
#include "spine/command_factory.h"
#include "spine/query_factory.h"
#include "spine/util/message_utils.hpp"

#include <google/protobuf/util/time_util.h>

using namespace spine;
using namespace spine::time;
using namespace google::protobuf;
using namespace google::protobuf::util;

namespace spine {
namespace client {

ActorContext* create_actor_context(UserId* actor,
                                    ZoneOffset* offset,
                                    TenantId* tenant_id,
                                    Timestamp* timestamp)
{
    ActorContext *actor_context = ActorContext::default_instance().New();
    actor_context->set_allocated_timestamp(timestamp);
    actor_context->set_allocated_actor(actor);
    actor_context->set_allocated_zone_offset(offset);
    actor_context->set_allocated_tenant_id(tenant_id);
    return actor_context;
}

ActorRequestFactory::ActorRequestFactory(const ActorRequestFactoryParams& params)
        : params_(params)
{
    if (!params.zone_offset())
    {
        params_.set_zone_offset(std::make_unique<ZoneOffset>(ZoneOffset::default_instance()));
    }
}

CommandFactoryPtr ActorRequestFactory::command_factory()
{
    return std::make_unique<CommandFactory>(actor_context());
}

TopicFactoryPtr ActorRequestFactory::topic_factory()
{
    return std::make_unique<TopicFactory>(actor_context());
}

QueryFactoryPtr ActorRequestFactory::query_factory()
{
    return std::make_unique<QueryFactory>(actor_context());
}

std::unique_ptr<ActorContext> ActorRequestFactory::actor_context() const
{
    Timestamp* timestamp_ptr = Timestamp::default_instance().New();
    timestamp_ptr->CopyFrom(TimeUtil::GetCurrentTime());

    std::unique_ptr<ActorContext> actor_context{
            create_actor_context(clone(params_.actor()),
                                 clone(params_.zone_offset()),
                                 clone(params_.tenant_id()),
                                 timestamp_ptr)
    };
    return actor_context;
}

ActorRequestFactory ActorRequestFactory::create(const ActorRequestFactoryParams& params)
{
    ActorRequestFactory factory = ActorRequestFactory(params);
    return factory;
}

const std::unique_ptr<UserId>& ActorRequestFactory::actor() const { return params_.actor(); }

const std::unique_ptr<TenantId>& ActorRequestFactory::tenant_id() const { return params_.tenant_id(); }

const std::unique_ptr<ZoneOffset>& ActorRequestFactory::zone_offset() const { return params_.zone_offset(); }

}}

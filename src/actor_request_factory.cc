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

#include "spine/actor_request_factory.h"

#include "spine/topic_factory.h"
#include "spine/command_factory.h"
#include "spine/query_factory.h"

#include <google/protobuf/util/time_util.h>

using namespace spine;
using namespace spine::client;
using namespace google::protobuf;
using namespace google::protobuf::util;

spine::core::ActorContext *
create_actor_context(spine::core::UserId* actor, spine::time::ZoneOffset* offset, spine::core::TenantId* tenant_id,
                     google::protobuf::Timestamp* timestamp)
{
    spine::core::ActorContext *actor_context = spine::core::ActorContext::default_instance().New();
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
        params_.set_zone_offset(std::make_unique<spine::time::ZoneOffset>(spine::time::ZoneOffset::default_instance()));
    }
}

std::unique_ptr<CommandFactory> ActorRequestFactory::command_factory()
{
    return std::make_unique<CommandFactory>(*this);
}

std::unique_ptr<TopicFactory> ActorRequestFactory::topic_factory()
{
    return std::make_unique<TopicFactory>(*this);
}

std::unique_ptr<QueryFactory> ActorRequestFactory::query_factory()
{
    return std::make_unique<QueryFactory>(*this);
}

std::unique_ptr<core::ActorContext> ActorRequestFactory::actor_context() const
{
    Timestamp* timestamp_ptr = Timestamp::default_instance().New();
    timestamp_ptr->CopyFrom(TimeUtil::GetCurrentTime());
    std::unique_ptr<core::ActorContext> actor_context{
            create_actor_context(new core::UserId(*params_.actor()),
                                 new time::ZoneOffset(*params_.zone_offset()),
                                 new core::TenantId(*params_.tenant_id()),
                                 timestamp_ptr)
    };
    return actor_context;
}

ActorRequestFactory ActorRequestFactory::create(const ActorRequestFactoryParams& params)
{
    ActorRequestFactory factory = ActorRequestFactory(params);
    return factory;
}

const std::unique_ptr<core::UserId>& ActorRequestFactory::actor() const { return params_.actor(); }

const std::unique_ptr<core::TenantId>& ActorRequestFactory::tenant_id() const { return params_.tenant_id(); }

const std::unique_ptr<time::ZoneOffset>& ActorRequestFactory::zone_offset() const { return params_.zone_offset(); }


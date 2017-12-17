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

#include "actor_request_factory.h"

#include "common.h"
#include "topic_factory.h"
#include "command_factory.h"
#include "query_factory.h"

using namespace spine;
using namespace spine::client;

ActorRequestFactory::ActorRequestFactory(const ActorRequestFactoryParams& params)
        : params_(params)
{
    if (!params.zone_offset())
    {
        params_.set_zone_offset(std::make_unique<spine::time::ZoneOffset>(spine::time::ZoneOffset::default_instance()));
    }
}

std::unique_ptr<CommandFactory> ActorRequestFactory::command()
{
    return std::make_unique<CommandFactory>(*this);
}

std::unique_ptr<TopicFactory> ActorRequestFactory::topic()
{
    return std::make_unique<TopicFactory>(*this);
}

std::unique_ptr<QueryFactory> ActorRequestFactory::query()
{
    return std::make_unique<QueryFactory>(*this);
}

std::unique_ptr<core::ActorContext> ActorRequestFactory::actor_context() const
{
    std::unique_ptr<core::ActorContext> actor_context{
            get_actor_context(new core::UserId(*params_.actor()),
                              new time::ZoneOffset(*params_.zone_offset()),
                              new core::TenantId(*params_.tenant_id()),
                              get_timestamp())
    };
    return actor_context;
}

ActorRequestFactory ActorRequestFactory::create(const ActorRequestFactoryParams& params)
{
    return ActorRequestFactory(params);
}

const std::unique_ptr<core::UserId>& ActorRequestFactory::actor() const { return params_.actor(); }

const std::unique_ptr<core::TenantId>& ActorRequestFactory::tenant_id() const { return params_.tenant_id(); }

const std::unique_ptr<time::ZoneOffset>& ActorRequestFactory::zone_offset() const { return params_.zone_offset(); }


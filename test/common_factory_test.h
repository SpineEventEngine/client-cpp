/*
 * Copyright 2018, TeamDev Ltd. All rights reserved.
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

#ifndef SPINE_COMMONFACTORYTEST_H
#define SPINE_COMMONFACTORYTEST_H

#include <gtest/gtest.h>

#include "spine/command_factory.h"
#include "spine/query_factory.h"
#include "spine/topic_factory.h"
#include "spine/actor_request_factory.h"

using namespace spine::client;
using namespace spine::core;
using namespace spine::time;

class CommonFactoryTest : public ::testing::Test
{
    const std::string USER_ID   { "user@example.com" };
    const std::string TENANT_ID { "example.com" };
    const std::string ZONE_ID   { "UTC" };
protected:
    virtual void SetUp() override
    {
        ActorRequestFactoryParams params;
        auto actor = std::make_unique<UserId>();
        actor->set_value(USER_ID);

        auto tenant_id = std::make_unique<TenantId>();
        tenant_id->set_value(TENANT_ID);

        auto zone_offset = std::make_unique<ZoneOffset>();
        ZoneId* zone_id = ZoneId::default_instance().New();
        zone_id->set_value(ZONE_ID);
        zone_offset->set_allocated_id(zone_id);
        zone_offset->set_amount_seconds(42);

        params.set_actor(actor)
                .set_tenant_id(tenant_id)
                .set_zone_offset(zone_offset);

        query_factory_ = ActorRequestFactory::create(params).query_factory();
        command_factory_ = ActorRequestFactory::create(params).command_factory();
        topic_factory_ = ActorRequestFactory::create(params).topic_factory();
    }

    QueryFactoryPtr query_factory_;
    TopicFactoryPtr topic_factory_;
    CommandFactoryPtr command_factory_;
};

#endif //SPINE_COMMONFACTORYTEST_H

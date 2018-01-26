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


#include <gtest/gtest.h>

#include <boost/algorithm/string.hpp>

#include "spine/query_factory.h"
#include "spine/actor_request_factory.h"

using namespace spine::client;
using namespace spine::core;
using namespace spine::time;

class QueryFactoryShould : public ::testing::Test
{
    const std::string USER_ID {"user_id_123" };
    const std::string TENANT_ID { "tenant_id_123" };
    const std::string ZONE_ID { "zone_id_123" };
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
        zone_offset->set_amountseconds(42);

        params.set_actor(actor)
                .set_tenant_id(tenant_id)
                .set_zone_offset(zone_offset);

        query_factory_ = ActorRequestFactory::create(params).query_factory();
    }

    QueryFactoryPtr query_factory_;
    const ZoneId zone_id_message;
};

TEST_F(QueryFactoryShould, Create)
{
    QueryPtr query = query_factory_->all<ZoneId>();

    std::string type = query->target().type();
    ASSERT_TRUE(query);
    ASSERT_TRUE(query->has_id());
    ASSERT_FALSE(query->id().value().empty());
    ASSERT_TRUE(query->has_target());
    ASSERT_EQ(query->target().type(), ZoneId::descriptor()->full_name());


}
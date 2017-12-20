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

#include "command_factory.h"
#include "actor_request_factory.h"

#include <spine/core/user_id.pb.h>
#include <spine/core/tenant_id.pb.h>
#include <spine/people/person_name.pb.h>
#include <spine/core/command.pb.h>

using namespace spine::client;
using namespace spine::core;
using namespace spine::time;

class ActorRequestFactoryShould : public ::testing::Test
{
protected:
    virtual void SetUp() override
    {

    }
    virtual void TearDown() override
    {

    }
};

TEST_F(ActorRequestFactoryShould, BeEmpty)
{
    ActorRequestFactoryParams params;

    ASSERT_FALSE(params.actor());
    ASSERT_FALSE(params.tenant_id());
    ASSERT_FALSE(params.zone_offset());
}
TEST_F(ActorRequestFactoryShould, BeEmptyWithFactoryMethod)
{
    ActorRequestFactoryParams params;

    ASSERT_FALSE(params.actor());
    ASSERT_FALSE(params.tenant_id());
    ASSERT_FALSE(params.zone_offset());
}

static const char* const USER_ID = "user_id_123";
static const char* const TENANT_ID = "tenant_id_123";
static const char* const ZONE_ID = "zone_id_123";

TEST_F(ActorRequestFactoryShould, HaveValidParams)
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

    params.set_actor(actor);
    params.set_tenant_id(tenant_id);
    params.set_zone_offset(zone_offset);

    ASSERT_TRUE(params.actor());
    ASSERT_TRUE(params.tenant_id());
    ASSERT_TRUE(params.zone_offset());

    ActorRequestFactory factory = ActorRequestFactory::create(params);

    ASSERT_EQ(params.actor()->value(),factory.actor()->value());
    ASSERT_EQ(params.tenant_id()->value(),factory.tenant_id()->value());
    ASSERT_EQ(params.zone_offset()->id().value(),factory.zone_offset()->id().value());
    ASSERT_EQ(params.zone_offset()->amountseconds(),factory.zone_offset()->amountseconds());

    std::unique_ptr<CommandFactory> command_factory = factory.command_factory();
    spine::people::PersonName message;
    message.set_family_name("asdasdasd");
    std::unique_ptr<Command> command = command_factory->create(message);
    int x = 1;
}



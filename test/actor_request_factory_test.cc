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

#include "actor_request_factory.h"

#include <spine/core/user_id.pb.h>
#include <spine/core/tenant_id.pb.h>

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
    auto params = ActorRequestFactoryParams::create();

    ASSERT_FALSE(params.actor());
    ASSERT_FALSE(params.tenant_id());
    ASSERT_FALSE(params.zone_offset());
}

TEST_F(ActorRequestFactoryShould, BeFilled)
{
    ActorRequestFactoryParams params;
    params.set_actor(std::make_unique<UserId>());
    params.set_tenant_id(std::make_unique<TenantId>());
    params.set_zone_offset(std::make_unique<ZoneOffset>());


    ASSERT_TRUE(params.actor());
    ASSERT_TRUE(params.tenant_id());
    ASSERT_TRUE(params.zone_offset());
}

TEST_F(ActorRequestFactoryShould, BeFilledWithFactoryMethod)
{
    ActorRequestFactoryParams params = (ActorRequestFactoryParams::create()
                .with_actor(std::make_unique<UserId>())
                .with_tenant_id(std::make_unique<TenantId>())
                .with_zone_offset(std::make_unique<ZoneOffset>()));


    ASSERT_TRUE(params.actor());
    ASSERT_TRUE(params.tenant_id());
    ASSERT_TRUE(params.zone_offset());
}


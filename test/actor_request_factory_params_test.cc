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

#include <gtest/gtest.h>

#include "spine/actor_request_factory_params.h"

#include <google/protobuf/timestamp.pb.h>
#include <spine/core/user_id.pb.h>
#include <spine/core/tenant_id.pb.h>
#include <spine/time/zone.pb.h>

using namespace spine::client;
using namespace spine::core;
using namespace spine::time;

static const char* const USER_ID = "user@example.com";
static const char* const TENANT_ID = "example.com";
static const char* const ZONE_ID = "UTC";

class ActorRequestFactoryParamsShould : public ::testing::Test
{
protected:
    virtual void SetUp() override
    {
        actor_ = std::make_unique<UserId>();
        actor_->set_value(USER_ID);

        tenant_id_ = std::make_unique<TenantId>();
        tenant_id_->set_value(TENANT_ID);

        zone_offset_ = std::make_unique<ZoneOffset>();
        ZoneId* zone_id = ZoneId::default_instance().New();
        zone_id->set_value(ZONE_ID);
        zone_offset_->set_allocated_id(zone_id);
        zone_offset_->set_amount_seconds(42);
    }
    virtual void TearDown() override
    {

    }
    std::unique_ptr<UserId> actor_;
    std::unique_ptr<TenantId> tenant_id_;
    std::unique_ptr<ZoneOffset> zone_offset_;
};

TEST_F(ActorRequestFactoryParamsShould, CreateWithEmptyValues)
{
    ActorRequestFactoryParams params;

    ASSERT_FALSE(params.actor());
    ASSERT_FALSE(params.tenant_id());
    ASSERT_FALSE(params.zone_offset());
}

TEST_F(ActorRequestFactoryParamsShould, SetParams)
{
    ActorRequestFactoryParams params;

    params.set_actor(actor_)
            .set_tenant_id(tenant_id_)
            .set_zone_offset(zone_offset_);

    ASSERT_TRUE(params.actor());
    ASSERT_TRUE(params.tenant_id());
    ASSERT_TRUE(params.zone_offset());
}

TEST_F(ActorRequestFactoryParamsShould, Copy)
{
    ActorRequestFactoryParams params;

    params.set_actor(actor_)
            .set_tenant_id(tenant_id_)
            .set_zone_offset(zone_offset_);


    ActorRequestFactoryParams params_copy;
    params_copy = params;

    ASSERT_TRUE(params_copy.actor());
    ASSERT_TRUE(params_copy.tenant_id());
    ASSERT_TRUE(params_copy.zone_offset());

    ASSERT_EQ(params_copy.actor()->value(),params.actor()->value());
    ASSERT_EQ(params_copy.tenant_id()->value(),params.tenant_id()->value());
    ASSERT_EQ(params_copy.zone_offset()->id().value(),params.zone_offset()->id().value());
    ASSERT_EQ(params_copy.zone_offset()->amount_seconds(),params.zone_offset()->amount_seconds());
}

TEST_F(ActorRequestFactoryParamsShould, CopyOnConstruct)
{
    ActorRequestFactoryParams params;

    params.set_actor(actor_)
            .set_tenant_id(tenant_id_)
            .set_zone_offset(zone_offset_);


    ActorRequestFactoryParams params_copy{ params };

    ASSERT_TRUE(params_copy.actor());
    ASSERT_TRUE(params_copy.tenant_id());
    ASSERT_TRUE(params_copy.zone_offset());

    ASSERT_EQ(params_copy.actor()->value(),params.actor()->value());
    ASSERT_EQ(params_copy.tenant_id()->value(),params.tenant_id()->value());
    ASSERT_EQ(params_copy.zone_offset()->id().value(),params.zone_offset()->id().value());
    ASSERT_EQ(params_copy.zone_offset()->amount_seconds(),params.zone_offset()->amount_seconds());
}

TEST_F(ActorRequestFactoryParamsShould, Move)
{
    ActorRequestFactoryParams params;

    params.set_actor(actor_)
            .set_tenant_id(tenant_id_)
            .set_zone_offset(zone_offset_);

    ActorRequestFactoryParams params_copy { std::move(params) };

    ASSERT_TRUE(params_copy.actor());
    ASSERT_TRUE(params_copy.tenant_id());
    ASSERT_TRUE(params_copy.zone_offset());

    ASSERT_FALSE(params.actor());
    ASSERT_FALSE(params.tenant_id());
    ASSERT_FALSE(params.zone_offset());
}

TEST_F(ActorRequestFactoryParamsShould, MoveAssignment)
{
    ActorRequestFactoryParams params;

    params.set_actor(actor_)
            .set_tenant_id(tenant_id_)
            .set_zone_offset(zone_offset_);

    ActorRequestFactoryParams params_copy;
    params_copy = std::move(params);

    ASSERT_TRUE(params_copy.actor());
    ASSERT_TRUE(params_copy.tenant_id());
    ASSERT_TRUE(params_copy.zone_offset());

    ASSERT_FALSE(params.actor());
    ASSERT_FALSE(params.tenant_id());
    ASSERT_FALSE(params.zone_offset());
}

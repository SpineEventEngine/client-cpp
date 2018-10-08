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

#ifndef SPINE_COMMONFACTORYTEST_H
#define SPINE_COMMONFACTORYTEST_H

#include <gtest/gtest.h>

#include <google/protobuf/util/field_comparator.h>
#include <google/protobuf/util/message_differencer.h>

#include "spine/command_factory.h"
#include "spine/query_factory.h"
#include "spine/topic_factory.h"
#include "spine/actor_request_factory.h"

#include "unit_tests.pb.h"
#include "unit_tests_no_prefix.pb.h"

using namespace spine::client;
using namespace spine::core;
using namespace spine::time;
using namespace spine::test;
using namespace google::protobuf::util;

class CommonFactoryTest : public ::testing::Test
{
    const std::string USER_ID   { "user@example.com" };
    const std::string TENANT_ID { "example.com" };
protected:
    virtual void SetUp() override
    {
        auto actor = std::make_unique<UserId>();
        actor->set_value(USER_ID);

        auto tenant_id = std::make_unique<TenantId>();
        tenant_id->set_value(TENANT_ID);

        auto zone_offset = std::make_unique<ZoneOffset>();
        zone_offset->set_amount_seconds(42);

        params_.set_actor(actor)
                .set_tenant_id(tenant_id)
                .set_zone_offset(zone_offset);

        query_factory_ = ActorRequestFactory::create(params_).query_factory();
        command_factory_ = ActorRequestFactory::create(params_).command_factory();
        topic_factory_ = ActorRequestFactory::create(params_).topic_factory();
    }

    std::vector<std::unique_ptr<ProjectId>> make_project_ids()
    {
        std::vector<std::unique_ptr<ProjectId>> project_ids;
        project_ids.emplace_back(std::make_unique<ProjectId>());
        project_ids.emplace_back(std::make_unique<ProjectId>());
        project_ids.emplace_back(std::make_unique<ProjectId>());

        int i = 1;
        for (auto& project_id : project_ids)
        {
            project_id->set_value(i++);
        }
        return project_ids;
    }

    void check_filters_are_empty(const Target& target)
    {
        ASSERT_TRUE(target.has_filters());
        ASSERT_TRUE(MessageDifferencer::Equals(target.filters(), EntityFilters::default_instance()));
        ASSERT_FALSE(target.filters().has_id_filter());
    }
    void check_filters_are_equal(const Target& target, const std::vector<std::unique_ptr<ProjectId>>& ids)
    {
        ASSERT_TRUE(target.has_filters());
        ASSERT_TRUE(target.filters().has_id_filter());

        for (const EntityId &id_filter : target.filters().id_filter().ids())
        {
            ASSERT_TRUE(id_filter.has_id());
            ASSERT_EQ(id_filter.id().type_url(), "type.test.spine.io/spine.test.ProjectId");
            const std::unique_ptr<ProjectId>& entity_id = from_any<ProjectId>(id_filter.id());

            ASSERT_TRUE(std::find_if(std::begin(ids), std::end(ids),
                                     [&] ( const std::unique_ptr<ProjectId>& val) -> bool
                                     {
                                         return MessageDifferencer::Equals(*val, *entity_id);
                                     }
            )
                        != std::end(ids) );
        }
    }

    void verifyContext(const ActorContext& context)
    {
        ASSERT_EQ(params_.actor()->value(), context.actor().value());
        ASSERT_EQ(params_.tenant_id()->value(), context.tenant_id().value());
        ASSERT_EQ(params_.zone_offset()->amount_seconds(), context.zone_offset().amount_seconds());
    }

    QueryFactoryPtr query_factory_;
    TopicFactoryPtr topic_factory_;
    CommandFactoryPtr command_factory_;

private:
    ActorRequestFactoryParams params_;
};

#endif //SPINE_COMMONFACTORYTEST_H

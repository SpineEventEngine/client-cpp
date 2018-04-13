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

#include "common_factory_test.h"
#include "unit_tests.pb.h"
#include "unit_tests_no_prefix.pb.h"
#include <spine/client/query.pb.h>

#include <google/protobuf/util/field_comparator.h>
#include <google/protobuf/util/message_differencer.h>

using namespace spine::client;
using namespace spine::core;
using namespace spine::time;
using namespace spine::test;

class QueryFactoryShould : public CommonFactoryTest
{
public:
    std::vector<std::unique_ptr<ProjectId>> make_project_ids()
    {
        std::vector<std::unique_ptr<ProjectId>> project_ids = {
                std::make_unique<ProjectId>(),
                std::make_unique<ProjectId>(),
                std::make_unique<ProjectId>() };

        int i = 1;
        for (auto& project_id : project_ids)
        {
            project_id->set_value(i++);
        }
        return project_ids;
    }
};

TEST_F(QueryFactoryShould, CreateKnownSpineType)
{
    QueryPtr query = query_factory_->all<ZoneId>();

    std::string type = query->target().type();
    ASSERT_TRUE(query);
    ASSERT_TRUE(query->has_id());
    ASSERT_FALSE(query->id().value().empty());
    ASSERT_TRUE(query->has_target());
    ASSERT_EQ(query->target().type(), "type.spine.io/spine.time.ZoneId");
    ASSERT_TRUE(query->target().include_all());
    ASSERT_FALSE(query->target().has_filters());
    ASSERT_FALSE(query->target().has_filters());
}

TEST_F(QueryFactoryShould, CreateKnownSpineTypeWithMask)
{
    std::vector<std::string> masks {"some", "random", "paths"};
    QueryPtr query = query_factory_->all_with_mask<ZoneId>(masks);

    std::string type = query->target().type();
    ASSERT_TRUE(query);
    ASSERT_TRUE(query->has_id());
    ASSERT_FALSE(query->id().value().empty());
    ASSERT_TRUE(query->has_target());
    ASSERT_EQ(query->target().type(), "type.spine.io/spine.time.ZoneId");
    ASSERT_FALSE(query->target().include_all());
    ASSERT_TRUE(query->target().has_filters());
    ASSERT_FALSE(query->target().filters().has_id_filter());
    //query->target().filters().filter().
}

TEST_F(QueryFactoryShould, QueryKnownSpineById)
{
    std::vector<std::unique_ptr<ProjectId>> project_ids = make_project_ids();

    QueryPtr query = query_factory_->by_ids<CreateProject>(project_ids);

    std::string type = query->target().type();
    ASSERT_TRUE(query);
    ASSERT_TRUE(query->has_id());
    ASSERT_FALSE(query->id().value().empty());
    ASSERT_TRUE(query->has_target());
    ASSERT_EQ(query->target().type(), "type.spine.io/spine.time.ZoneId");
    ASSERT_FALSE(query->target().include_all());
    ASSERT_TRUE(query->target().has_filters());
    ASSERT_TRUE(query->target().filters().has_id_filter());
    ASSERT_EQ(query->target().filters().id_filter().ids_size(), project_ids.size());
}

//TEST_F(QueryFactoryShould, QueryKnownSpineByIdWithMask)
//{
//    QueryPtr query = query_factory_->by_ids_with_masks<ZoneId>();
//
//    std::string type = query->target().type();
//    ASSERT_TRUE(query);
//    ASSERT_TRUE(query->has_id());
//    ASSERT_FALSE(query->id().value().empty());
//    ASSERT_TRUE(query->has_target());
//    ASSERT_EQ(query->target().type(), "type.spine.io/spine.time.ZoneId");
//    ASSERT_FALSE(query->target().include_all());
//    ASSERT_FALSE(query->target().has_filters());
//
//}

TEST_F(QueryFactoryShould, CreateMessageWithPrefix)
{
    QueryPtr query = query_factory_->all<TestMessage>();

    std::string type = query->target().type();
    ASSERT_TRUE(query);
    ASSERT_TRUE(query->has_id());
    ASSERT_FALSE(query->id().value().empty());
    ASSERT_TRUE(query->has_target());
    ASSERT_EQ(query->target().type(), "type.test.spine.io/spine.test.TestMessage");
}

TEST_F(QueryFactoryShould, CreateMessageWithoutPrefix)
{
    QueryPtr query = query_factory_->all<TestMessageNoPrefix>();

    std::string type = query->target().type();
    ASSERT_TRUE(query);
    ASSERT_TRUE(query->has_id());
    ASSERT_FALSE(query->id().value().empty());
    ASSERT_TRUE(query->has_target());
    ASSERT_EQ(query->target().type(), "spine.test.TestMessageNoPrefix");
}




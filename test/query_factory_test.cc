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
using namespace google::protobuf::util;

class QueryFactoryShould : public CommonFactoryTest
{
public:
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
    void check_filters_are_empty(const QueryPtr& query)
    {
        ASSERT_TRUE(query->target().has_filters());
        ASSERT_TRUE(MessageDifferencer::Equals(query->target().filters(), EntityFilters::default_instance()));
        ASSERT_FALSE(query->target().filters().has_id_filter());
    }
    void check_field_mask_is_empty(const QueryPtr& query)
    {
        ASSERT_TRUE(query->has_field_mask());
        ASSERT_TRUE(MessageDifferencer::Equals(query->field_mask(), FieldMask::default_instance()));
    }
    void check_filters_are_equal(const QueryPtr& query, const std::vector<std::unique_ptr<ProjectId>>& ids)
    {
        ASSERT_TRUE(query->target().has_filters());
        ASSERT_TRUE(query->target().filters().has_id_filter());

        for (const EntityId &id_filter : query->target().filters().id_filter().ids())
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
    void check_field_mask_is_equal(const QueryPtr& query, const std::vector<std::string>& masks)
    {
        ASSERT_TRUE(query->has_field_mask());
        ASSERT_EQ(query->field_mask().paths_size(), masks.size());
        ASSERT_TRUE(std::equal(std::begin(masks), std::end(masks),
                               std::begin(query->field_mask().paths()), std::end(query->field_mask().paths())
        ));
    }
};

TEST_F(QueryFactoryShould, CreateKnownSpineType)
{
    QueryPtr query = query_factory_->all<ZoneId>();

    ASSERT_TRUE(query);
    ASSERT_TRUE(query->has_id());
    ASSERT_FALSE(query->id().value().empty());

    ASSERT_TRUE(query->has_target());
    ASSERT_EQ(query->target().type(), "type.spine.io/spine.time.ZoneId");
    ASSERT_FALSE(query->target().include_all());

    check_field_mask_is_empty(query);
    check_filters_are_empty(query);

}

TEST_F(QueryFactoryShould, CreateKnownSpineTypeWithMask)
{
    std::vector<std::string> masks {"some", "random", "paths"};
    QueryPtr query = query_factory_->all_with_mask<ZoneId>(masks);

    ASSERT_TRUE(query);
    ASSERT_TRUE(query->has_id());
    ASSERT_FALSE(query->id().value().empty());

    ASSERT_TRUE(query->has_target());
    ASSERT_EQ(query->target().type(), "type.spine.io/spine.time.ZoneId");
    ASSERT_FALSE(query->target().include_all());

    check_filters_are_empty(query);
    check_field_mask_is_equal(query, masks);
}

TEST_F(QueryFactoryShould, QueryKnownSpineById)
{
    std::vector<std::unique_ptr<ProjectId>> project_ids = make_project_ids();

    QueryPtr query = query_factory_->by_ids<CreateProject>( project_ids );

    ASSERT_TRUE(query);
    ASSERT_TRUE(query->has_id());
    ASSERT_FALSE(query->id().value().empty());

    ASSERT_TRUE(query->has_field_mask());
    ASSERT_TRUE(MessageDifferencer::Equals(query->field_mask(), FieldMask::default_instance()));

    ASSERT_TRUE(query->has_target());
    ASSERT_EQ(query->target().type(), "type.test.spine.io/spine.test.CreateProject");
    ASSERT_FALSE(query->target().include_all());

    check_filters_are_equal(query, project_ids);
}

TEST_F(QueryFactoryShould, QueryKnownSpineByIdWithMask)
{
    std::vector<std::string> masks {"some", "random", "paths"};
    std::vector<std::unique_ptr<ProjectId>> project_ids = make_project_ids();

    QueryPtr query = query_factory_->by_ids_with_masks<CreateProject>( masks, project_ids );

    ASSERT_TRUE(query);
    ASSERT_TRUE(query->has_id());
    ASSERT_FALSE(query->id().value().empty());

    check_field_mask_is_equal(query, masks);

    ASSERT_TRUE(query->has_target());
    ASSERT_EQ(query->target().type(), "type.test.spine.io/spine.test.CreateProject");
    ASSERT_FALSE(query->target().include_all());

    check_filters_are_equal(query, project_ids);
}

TEST_F(QueryFactoryShould, CreateMessageWithPrefix)
{
    QueryPtr query = query_factory_->all<TestMessage>();

    ASSERT_TRUE(query);
    ASSERT_TRUE(query->has_id());
    ASSERT_FALSE(query->id().value().empty());
    ASSERT_TRUE(query->has_target());
    ASSERT_EQ(query->target().type(), "type.test.spine.io/spine.test.TestMessage");
    ASSERT_FALSE(query->target().include_all());

    check_field_mask_is_empty(query);
    check_filters_are_empty(query);
}

TEST_F(QueryFactoryShould, CreateMessageWithoutPrefix)
{
    QueryPtr query = query_factory_->all<TestMessageNoPrefix>();

    ASSERT_TRUE(query);
    ASSERT_TRUE(query->has_id());
    ASSERT_FALSE(query->id().value().empty());
    ASSERT_TRUE(query->has_target());
    ASSERT_EQ(query->target().type(), "spine.test.TestMessageNoPrefix");
    ASSERT_FALSE(query->target().include_all());

    check_field_mask_is_empty(query);
    check_filters_are_empty(query);
}




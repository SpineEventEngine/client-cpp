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


#include <gtest/gtest.h>

#include "common_factory_test.h"
#include "unit_tests.pb.h"
#include "unit_tests_no_prefix.pb.h"
#include <spine/client/query.pb.h>

#include "spine/filters.h"

#include <google/protobuf/wrappers.pb.h>

using namespace spine::client;
using namespace spine::core;
using namespace spine::time;
using namespace spine::test;

class QueryFactoryShould : public CommonFactoryTest
{
public:
    void check_field_mask_is_empty(const QueryPtr& query)
    {
        ASSERT_TRUE(query->has_field_mask());
        ASSERT_TRUE(MessageDifferencer::Equals(query->field_mask(), FieldMask::default_instance()));
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
    check_filters_are_empty(query->target());
    verifyContext(query->context());
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

    check_filters_are_empty(query->target());
    check_field_mask_is_equal(query, masks);
    verifyContext(query->context());
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

    check_filters_are_equal(query->target(), project_ids);
    verifyContext(query->context());
}

TEST_F(QueryFactoryShould, QueryKnownSpineByIdWithMask)
{
    std::vector<std::string> masks {"some", "random", "paths"};
    std::vector<std::unique_ptr<ProjectId>> project_ids = make_project_ids();

    QueryPtr query = query_factory_->by_ids_with_masks<CreateProject>(project_ids, masks);

    ASSERT_TRUE(query);
    ASSERT_TRUE(query->has_id());
    ASSERT_FALSE(query->id().value().empty());

    check_field_mask_is_equal(query, masks);

    ASSERT_TRUE(query->has_target());
    ASSERT_EQ(query->target().type(), "type.test.spine.io/spine.test.CreateProject");
    ASSERT_FALSE(query->target().include_all());

    check_filters_are_equal(query->target(), project_ids);
    verifyContext(query->context());
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
    check_filters_are_empty(query->target());
    verifyContext(query->context());
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
    check_filters_are_empty(query->target());
    verifyContext(query->context());
}

TEST_F(QueryFactoryShould, CreateWithBuilder)
{
    Int32Value pValue1;   pValue1.set_value(15);
    Int32Value pValue2;   pValue2.set_value(42);
    Int32Value pValue3;   pValue3.set_value(17);

    std::unique_ptr<CompositeFilter> all_filter = all(eq("field1", pValue1), ge("field4", pValue2), gt("field16", pValue3));
    std::unique_ptr<CompositeFilter> either_filter = either(eq("dsfdsf", pValue2), ge("field4", pValue3), gt("dfgdf", pValue1));
    int x = 1;

}
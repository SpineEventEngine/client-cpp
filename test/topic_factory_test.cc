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

using namespace spine::client;
using namespace spine::core;
using namespace spine::time;
using namespace spine::test;

class TopicFactoryShould : public CommonFactoryTest
{
public:
    void check_field_mask_is_empty(const TopicPtr& topic)
    {
        ASSERT_TRUE(topic->has_field_mask());
        ASSERT_TRUE(MessageDifferencer::Equals(topic->field_mask(), FieldMask::default_instance()));
    }
};

TEST_F(TopicFactoryShould, CreateKnownSpineType)
{
    TopicPtr topic = topic_factory_->all<ZoneId>();

    ASSERT_TRUE(topic);
    ASSERT_TRUE(topic->has_id());
    ASSERT_FALSE(topic->id().value().empty());
    ASSERT_TRUE(topic->has_target());
    ASSERT_EQ(topic->target().type(), "type.spine.io/spine.time.ZoneId");
    check_filters_are_empty(topic->target());
    check_field_mask_is_empty(topic);
    verifyContext(topic->context());
}

TEST_F(TopicFactoryShould, CreateMessageWithPrefix)
{
    TopicPtr topic = topic_factory_->all<TestMessage>();

    ASSERT_TRUE(topic);
    ASSERT_TRUE(topic->has_id());
    ASSERT_FALSE(topic->id().value().empty());
    ASSERT_TRUE(topic->has_target());
    ASSERT_EQ(topic->target().type(), "type.test.spine.io/spine.test.TestMessage");
    check_filters_are_empty(topic->target());
    check_field_mask_is_empty(topic);
    verifyContext(topic->context());
}

TEST_F(TopicFactoryShould, CreateMessageWithoutPrefix)
{
    TopicPtr topic = topic_factory_->all<TestMessageNoPrefix>();

    ASSERT_TRUE(topic);
    ASSERT_TRUE(topic->has_id());
    ASSERT_FALSE(topic->id().value().empty());
    ASSERT_TRUE(topic->has_target());
    ASSERT_EQ(topic->target().type(), "spine.test.TestMessageNoPrefix");
    check_filters_are_empty(topic->target());
    check_field_mask_is_empty(topic);
    verifyContext(topic->context());
}

TEST_F(TopicFactoryShould, CreateTopicWithIDs)
{
    std::vector<std::unique_ptr<ProjectId>> ids = make_project_ids();
    TopicPtr topic = topic_factory_->some<CreateProject>(ids);

    ASSERT_TRUE(topic);
    ASSERT_TRUE(topic->has_id());
    ASSERT_FALSE(topic->id().value().empty());
    ASSERT_TRUE(topic->has_target());
    ASSERT_EQ(topic->target().type(), "type.test.spine.io/spine.test.CreateProject");
    check_filters_are_equal(topic->target(), ids);
    check_field_mask_is_empty(topic);
    verifyContext(topic->context());
}

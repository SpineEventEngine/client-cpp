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

using namespace spine::client;
using namespace spine::core;
using namespace spine::time;
using namespace spine::test;

class TopicFactoryShould : public CommonFactoryTest
{
};

TEST_F(TopicFactoryShould, CreateKnownSpineType)
{
    TopicPtr topic = topic_factory_->all<ZoneId>();

    std::string type = topic->target().type();
    ASSERT_TRUE(topic);
    ASSERT_TRUE(topic->has_id());
    ASSERT_FALSE(topic->id().value().empty());
    ASSERT_TRUE(topic->has_target());
    ASSERT_EQ(topic->target().type(), "type.spine.io/spine.time.ZoneId");
}

TEST_F(TopicFactoryShould, CreateMessageWithPrefix)
{
    TopicPtr topic = topic_factory_->all<TestMessage>();

    std::string type = topic->target().type();
    ASSERT_TRUE(topic);
    ASSERT_TRUE(topic->has_id());
    ASSERT_FALSE(topic->id().value().empty());
    ASSERT_TRUE(topic->has_target());
    ASSERT_EQ(topic->target().type(), "type.test.spine.io/spine.test.TestMessage");
}

TEST_F(TopicFactoryShould, CreateMessageWithoutPrefix)
{
    TopicPtr topic = topic_factory_->all<TestMessageNoPrefix>();

    std::string type = topic->target().type();
    ASSERT_TRUE(topic);
    ASSERT_TRUE(topic->has_id());
    ASSERT_FALSE(topic->id().value().empty());
    ASSERT_TRUE(topic->has_target());
    ASSERT_EQ(topic->target().type(), "spine.test.TestMessageNoPrefix");
}

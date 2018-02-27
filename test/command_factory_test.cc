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

#include <boost/algorithm/string.hpp>

#include "spine/util/any_utils.h"
#include "common_factory_test.h"
#include "unit_tests.pb.h"
#include "unit_tests_no_prefix.pb.h"

using namespace spine::client;
using namespace spine::core;
using namespace spine::time;
using namespace spine::test;

class CommandFactoryShould : public CommonFactoryTest
{
protected:
    const ZoneId zone_id_;
};

TEST_F(CommandFactoryShould, CreateKnownSpineType)
{
    CommandPtr command = command_factory_->create(zone_id_);
    ASSERT_TRUE(command);
    ASSERT_TRUE(command->has_id());
    ASSERT_FALSE(command->id().uuid().empty());
    ASSERT_TRUE(command->has_message());

    ASSERT_EQ(command->message().type_url(), "type.spine.io/spine.time.ZoneId");
}

TEST_F(CommandFactoryShould, CreateMessageWithPrefix)
{
    TestMessage test_message;
    CommandPtr command = command_factory_->create(test_message);
    ASSERT_TRUE(command);
    ASSERT_TRUE(command->has_id());
    ASSERT_FALSE(command->id().uuid().empty());
    ASSERT_TRUE(command->has_message());

    ASSERT_EQ(command->message().type_url(), "type.test.spine.io/spine.test.TestMessage");
}

TEST_F(CommandFactoryShould, CreateMessageWithoutPrefix)
{
    TestMessageNoPrefix test_message;
    CommandPtr command = command_factory_->create(test_message);
    ASSERT_TRUE(command);
    ASSERT_TRUE(command->has_id());
    ASSERT_FALSE(command->id().uuid().empty());
    ASSERT_TRUE(command->has_message());

    ASSERT_EQ(command->message().type_url(), "type.googleapis.com/spine.test.TestMessageNoPrefix");
}

TEST_F(CommandFactoryShould, CreateWithTargetVersion)
{
    const int target_version = 42;
    CommandPtr command = command_factory_->create(zone_id_, target_version);

    ASSERT_TRUE(command);
    ASSERT_TRUE(command->has_id());
    ASSERT_FALSE(command->id().uuid().empty());
    ASSERT_TRUE(command->has_message());

    ASSERT_EQ(command->message().type_url(), "type.spine.io/spine.time.ZoneId");

    ASSERT_TRUE(command->has_context());
    ASSERT_TRUE(command->context().target_version());
}

TEST_F(CommandFactoryShould, CreateWithAny)
{
    const int target_version = 42;

    StuffId *stuff_id = StuffId::default_instance().New();
    stuff_id->set_value(12);
    
    CreateStuff create_stuff;
    create_stuff.set_allocated_id(stuff_id);
    create_stuff.set_name("cool name");
    create_stuff.set_allocated_cool_field(to_any(zone_id_).release());
    
    CommandPtr command = command_factory_->create(create_stuff, target_version);

    ASSERT_TRUE(command->has_context());
    ASSERT_TRUE(command->context().target_version());

    ASSERT_TRUE(command);
    ASSERT_TRUE(command->has_id());
    ASSERT_FALSE(command->id().uuid().empty());
    ASSERT_TRUE(command->has_message());

    const Any &any = command->message();
    ASSERT_EQ(any.type_url(), "type.test.spine.io/spine.test.CreateStuff");
    std::unique_ptr<CreateStuff> message = from_any<CreateStuff>(any);
    ASSERT_TRUE(message);

    ASSERT_TRUE(message->has_cool_field());
    ASSERT_EQ(message->cool_field().type_url(), "type.spine.io/spine.time.ZoneId");
    std::unique_ptr<ZoneId> zone_id = from_any<ZoneId>(message->cool_field());
    ASSERT_TRUE(zone_id);
}

TEST_F(CommandFactoryShould, FailWithWrongAny)
{
    const int target_version = 42;

    StuffId *stuff_id = StuffId::default_instance().New();
    stuff_id->set_value(12);

    CreateStuff create_stuff;
    create_stuff.set_allocated_id(stuff_id);
    create_stuff.set_name("cool name");
    create_stuff.set_allocated_cool_field(to_any(zone_id_).release());

    CommandPtr command = command_factory_->create(create_stuff, target_version);

    const Any &any = command->message();
    ASSERT_EQ(any.type_url(), "type.test.spine.io/spine.test.CreateStuff");
    std::unique_ptr<CreateStuff> message = from_any<CreateStuff>(any);
    ASSERT_TRUE(message);

    ASSERT_TRUE(message->has_cool_field());
    ASSERT_EQ(message->cool_field().type_url(), "type.spine.io/spine.time.ZoneId");
    std::unique_ptr<UserId> zone_id = from_any<UserId>(message->cool_field());
    ASSERT_FALSE(zone_id);
}

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

#include <boost/algorithm/string.hpp>

#include "spine/command_factory.h"
#include "spine/actor_request_factory.h"

#include "common_factory_test.h"

using namespace spine::client;
using namespace spine::core;
using namespace spine::time;

class CommandFactoryShould : public CommonFactoryTest
{
public:
    void check_type_url(const std::string& type_url)
    {
        std::vector<std::string> split_values;
        boost::split(split_values, type_url, [](char val) { return '/' == val;});
        ASSERT_EQ(2, split_values.size());
        ASSERT_FALSE(split_values[0].empty());
        ASSERT_FALSE(split_values[1].empty());

        ASSERT_EQ(split_values[1], zone_id_message.GetTypeName());
    }

    void check_type_url_with_prefix(const std::string& type_url, const std::string& prefix)
    {
        std::vector<std::string> split_values;
        boost::split(split_values, type_url, [](char val) { return '/' == val;});
        ASSERT_EQ(2, split_values.size());

        ASSERT_EQ(split_values[0], prefix);
        ASSERT_EQ(split_values[1], zone_id_message.GetTypeName());
    }
};



TEST_F(CommandFactoryShould, Create)
{
    CommandPtr command = command_factory_->create(zone_id_message);
    ASSERT_TRUE(command);
    ASSERT_TRUE(command->has_id());
    ASSERT_FALSE(command->id().uuid().empty());
    ASSERT_TRUE(command->has_message());

    check_type_url(command->message().type_url());
}

TEST_F(CommandFactoryShould, CreateWithTypePrefix)
{
    const std::string prefix = "type.com.my.prefix";
    CommandPtr command = command_factory_->create(zone_id_message, prefix);

    ASSERT_TRUE(command);
    ASSERT_TRUE(command->has_id());
    ASSERT_FALSE(command->id().uuid().empty());
    ASSERT_TRUE(command->has_message());

    check_type_url_with_prefix(command->message().type_url(), prefix);
}

TEST_F(CommandFactoryShould, CreateWithTargetVersion)
{
    const int target_version = 42;
    CommandPtr command = command_factory_->create(zone_id_message, target_version);

    ASSERT_TRUE(command);
    ASSERT_TRUE(command->has_id());
    ASSERT_FALSE(command->id().uuid().empty());
    ASSERT_TRUE(command->has_message());

    check_type_url(command->message().type_url());

    ASSERT_TRUE(command->has_context());
    ASSERT_TRUE(command->context().target_version());
}


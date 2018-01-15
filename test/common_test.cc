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

#include <spine/core/command.pb.h>

std::string type_url_or_empty(const google::protobuf::Message& msg)
{
    if ( nullptr == msg.GetDescriptor() ) return "";

    const google::protobuf::FileOptions& fileOptions = msg.GetDescriptor()->file()->options();
    const google::protobuf::RepeatedPtrField<google::protobuf::UninterpretedOption>& options = msg.GetDescriptor()->options().uninterpreted_option();
    auto found = std::find_if(options.begin(), options.end(), [] (const google::protobuf::UninterpretedOption& o)
        {
            return o.name(0).name_part() == "type_url_prefix" && o.has_string_value();
        });

    if( found != options.end())
        return (*found).string_value();
    return "";
}

TEST(CommonShould, ProvideAnyFromMessage)
{
    spine::core::CommandId command_id;
    command_id.set_uuid("123123123");

    const std::string& url_or_empty = type_url_or_empty(command_id);
    google::protobuf::Any* any = to_any(command_id, url_or_empty);
    ASSERT_TRUE(any != nullptr);

    spine::core::CommandId unpacked;
    any->UnpackTo(&unpacked);
    ASSERT_EQ(unpacked.uuid(), command_id.uuid());
    ASSERT_TRUE(unpacked.descriptor() != nullptr);
}

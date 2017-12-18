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

#include "command_factory.h"
#include "actor_request_factory.h"
#include "common.h"

using namespace spine::core;
using namespace spine::client;
using namespace spine::time;

spine::core::CommandContext* get_command_context(const std::unique_ptr<ActorContext>& actor_context);

spine::core::CommandContext* get_command_context(const std::unique_ptr<ActorContext>& actor_context, const int version);
Command* get_command(CommandContext* command_context,google::protobuf::Any* any, CommandId* command_id);
CommandId* get_command_id(const std::string& uuid);


CommandFactory::CommandFactory(const ActorRequestFactory& actor_request_factory)
{
    actor_context_ = actor_request_factory.actor_context();
}

std::unique_ptr<Command> CommandFactory::create(const ::google::protobuf::Message& message)
{
    Command* command = get_command(
            get_command_context(actor_context_),
            to_any(message),
            get_command_id(uuid_generator_.createRandom().toString()));
    return std::unique_ptr<Command>{command};
}

std::unique_ptr<Command> CommandFactory::create(const ::google::protobuf::Message& message, const int target_version)
{
    Command* command = get_command(
            get_command_context(actor_context_, target_version),
            to_any(message),
            get_command_id(uuid_generator_.createRandom().toString()));
    return std::unique_ptr<Command>{command};

}

Command* get_command(CommandContext* command_context, google::protobuf::Any* any, CommandId* command_id)
{
    Command* command = Command::default_instance().New();
    command->set_allocated_id(command_id);
    command->set_allocated_context(command_context);
    command->set_allocated_message(any);
    return command;
}

CommandId* get_command_id(const std::string& uuid)
{
    CommandId* command_id = CommandId::default_instance().New();
    command_id->set_uuid(uuid);
    return command_id;
}


spine::core::CommandContext* get_command_context(const std::unique_ptr<ActorContext>& actor_context)
{
    spine::core::CommandContext *command_context = spine::core::CommandContext::default_instance().New();
    command_context->set_allocated_actor_context(copy_actor_context(*actor_context));

    return command_context;
}

spine::core::CommandContext* get_command_context(const std::unique_ptr<ActorContext>& actor_context, const int version)
{
    CommandContext* context = get_command_context(actor_context);
    context->set_target_version(version);
    return context;
}



//UserId* copy_actor(const UserId& user_id)
//{
//    UserId* new_user_id = UserId::default_instance().New();
//    new_user_id->CopyFrom(user_id);
//    return  new_user_id;
//}
//
//google::protobuf::Timestamp* copy_timestamp(const google::protobuf::Timestamp& timestamp)
//{
//    google::protobuf::Timestamp* new_timestamp = google::protobuf::Timestamp::default_instance().New();
//    new_timestamp->CopyFrom(timestamp);
//    return new_timestamp;
//}
//
//ZoneOffset* copy_zone_offset(const ZoneOffset& zone_offset)
//{
//    ZoneOffset* new_offset = ZoneOffset::default_instance().New();
//    new_offset->CopyFrom(zone_offset);
//    return new_offset;
//}






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

#include "spine/command_factory.h"
#include "spine/actor_request_factory.h"
#include "spine/message_utils.hpp"

using namespace spine::core;
using namespace spine::client;
using namespace spine::time;

spine::core::CommandContext* make_command_context(const std::unique_ptr<ActorContext>& actor_context);

spine::core::CommandContext* make_command_context(const std::unique_ptr<ActorContext>& actor_context, int version);
Command* make_command(CommandContext* command_context, google::protobuf::Any* any, CommandId* command_id);
CommandId* make_command_id(const std::string& uuid);


CommandFactory::CommandFactory(const ActorRequestFactory& actor_request_factory)
{
    actor_context_ = actor_request_factory.actor_context();
}

std::unique_ptr<Command> CommandFactory::create(const ::google::protobuf::Message& message)
{
    Command* command = make_command(
            make_command_context(actor_context_),
            to_any(message),
            make_command_id(uuid_generator_.createRandom().toString()));
    return std::unique_ptr<Command>{command};
}

std::unique_ptr<Command> CommandFactory::create(const ::google::protobuf::Message& message, const std::string& type_url)
{
    Command* command = make_command(
            make_command_context(actor_context_),
            to_any(message, type_url),
            make_command_id(uuid_generator_.createRandom().toString()));
    return std::unique_ptr<Command>{command};
}

std::unique_ptr<Command> CommandFactory::create(const ::google::protobuf::Message& message, const int target_version)
{
    Command* command = make_command(
            make_command_context(actor_context_, target_version),
            to_any(message),
            make_command_id(uuid_generator_.createRandom().toString()));
    return std::unique_ptr<Command>{command};

}
google::protobuf::Any* CommandFactory::to_any(const google::protobuf::Message& message)
{
    google::protobuf::Any* any = google::protobuf::Any::default_instance().New();
    any->PackFrom(message);
    return any;
}

google::protobuf::Any* CommandFactory::to_any(const google::protobuf::Message& message, const std::string& type_url)
{
    google::protobuf::Any* any = google::protobuf::Any::default_instance().New();
    any->PackFrom(message, type_url);
    return any;
}

Command* make_command(CommandContext* command_context, google::protobuf::Any* any, CommandId* command_id)
{
    Command* command = Command::default_instance().New();
    command->set_allocated_id(command_id);
    command->set_allocated_context(command_context);
    command->set_allocated_message(any);
    return command;
}

CommandId* make_command_id(const std::string& uuid)
{
    CommandId* command_id = CommandId::default_instance().New();
    command_id->set_uuid(uuid);
    return command_id;
}


spine::core::CommandContext* make_command_context(const std::unique_ptr<ActorContext>& actor_context)
{
    spine::core::CommandContext *command_context = spine::core::CommandContext::default_instance().New();
    command_context->set_allocated_actor_context(clone(actor_context));

    return command_context;
}

spine::core::CommandContext* make_command_context(const std::unique_ptr<ActorContext>& actor_context, const int version)
{
    CommandContext* context = make_command_context(actor_context);
    context->set_target_version(version);
    return context;
}







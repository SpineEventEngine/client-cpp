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
#include "spine/util/message_utils.hpp"
#include "spine/util/any_utils.hpp"

#include <spine/core/actor_context.pb.h>

using namespace spine;
using namespace spine::core;
using namespace spine::time;

namespace spine {
namespace client {

CommandContext* make_command_context(const std::unique_ptr<ActorContext>& actor_context);
CommandContext* make_command_context(const std::unique_ptr<ActorContext>& actor_context, int version);
Command* make_command(CommandContext* command_context, Any* any, CommandId* command_id);
CommandId* make_command_id(const std::string& uuid);


CommandFactory::CommandFactory(std::unique_ptr<ActorContext>&& actor_context)
{
    actor_context_ = std::move(actor_context);
}

std::unique_ptr<Command> CommandFactory::create(const Message& message)
{
    std::unique_ptr<Any> any = to_any(message);
    Command* command = make_command(
            make_command_context(actor_context_),
            any.release(),
            make_command_id(uuid_generator_.createRandom().toString()));
    return std::unique_ptr<Command>{command};
}

std::unique_ptr<Command> CommandFactory::create(const Message& message, const int target_version)
{
    std::unique_ptr<Any> any = to_any(message);
    Command* command = make_command(
            make_command_context(actor_context_, target_version),
            any.release(),
            make_command_id(uuid_generator_.createRandom().toString()));
    return std::unique_ptr<Command>{command};

}

Command* make_command(CommandContext* command_context, Any* any, CommandId* command_id)
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


CommandContext* make_command_context(const std::unique_ptr<ActorContext>& actor_context)
{
    CommandContext *command_context = CommandContext::default_instance().New();
    command_context->set_allocated_actor_context(clone(actor_context));
    return command_context;
}

CommandContext* make_command_context(const std::unique_ptr<ActorContext>& actor_context, const int version)
{
    CommandContext* context = make_command_context(actor_context);
    context->set_target_version(version);
    return context;
}

}}

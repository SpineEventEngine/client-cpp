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

#ifndef SPINE_COMMANDFACTORY_H
#define SPINE_COMMANDFACTORY_H

#include <memory>
#include <google/protobuf/message.h>
#include <google/protobuf/timestamp.pb.h>
#include <spine/time/zone.pb.h>
#include <Poco/UUIDGenerator.h>
#include <spine/core/command.pb.h>

#include "types.h"

using namespace google::protobuf;
using namespace spine::core;

namespace spine
{
namespace client
{

/**
* Public API for creating \b Command instances, using the ActorRequestFactory
* configuration.
*
* @see ActorRequestFactory::command_factory()
*
* @author Vladimir Moiseiev
*/

class CommandFactory
{
public:
    CommandFactory(std::unique_ptr<ActorContext>&& actor_context);
public:
    /**
     * Creates a command instance with the given message and the context
     * provided during the construction.
     *
     * @param message the command message.
     * @return a new \b Command instance.
     */
    CommandPtr create(const Message& message);
    /**
     * Creates a command instance with the given message and the context
     * provided during the construction.
     *
     * The \b target_version parameter defines the version of the entity which handles
     * the resulting command. Note that the framework performs no validation of the target version
     * before a command is handled. The validation may be performed by the user themselves instead.
     *
     * @param message the command message.
     * @param target_version the version of the entity for which this command is intended.
     * @return a new \b Command instance.
     *
     * @todo add a server side reference, and a link to QueryResponse, once the
     * feature is ready.
     *
     * @note Aggregates and ProcessManagers are the versioned entities, which can handle commands.
     * Each modification of their state leads to the version increment.
     * At the same time the target version number can be used as a parameter for the \b Command,
     * being a way to escape from updating the stale entities (see CommandContext.target_version attribute).
     * I.e. the client may specify the expected version of the target entity,
     * in which as he believes this entity resides. In case the actual entity version differs from the expected
     * version set for the command, the command is rejected — as it clearly
     * has been created with the stale entity state in mind.
     */
    CommandPtr create(const Message& message, int target_version);

private:
    std::unique_ptr<ActorContext> actor_context_;
    Poco::UUIDGenerator uuid_generator_;

};

}} //namespace


#endif //SPINE_COMMANDFACTORY_H

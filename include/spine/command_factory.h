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
namespace core
{
    class CommandContext;
    class UserId;
    class ActorContext;
}
namespace client
{

class CommandFactory
{
public:
    CommandFactory(const ActorRequestFactory & actor_request_factory);
public:
    CommandPtr create(const Message& message);
    CommandPtr create(const Message& message, const std::string& type_url);
    CommandPtr create(const Message& message, int target_version);

private:
    Any* to_any(const Message& message);
    Any* to_any(const Message& message, const std::string& );

private:
    std::unique_ptr<ActorContext> actor_context_;
    Poco::UUIDGenerator uuid_generator_;

};

}} //namespace


#endif //SPINE_COMMANDFACTORY_H

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

#ifndef SPINE_QUERYFACTORY_H
#define SPINE_QUERYFACTORY_H

#include <memory>
#include <Poco/UUIDGenerator.h>
#include <spine/client/query.pb.h>

#include "spine/types.h"
#include "spine/message_utils.hpp"

namespace spine
{

namespace core
{
    class ActorContext;
}

namespace client
{

class QueryFactory
{
public:
    QueryFactory(const ActorRequestFactory & actor_request_factory);

public:

    template <typename T, typename = enable_param_if_protobuf_message<T>>
    QueryPtr all()
    {
        return all(
                T::descriptor()->file()->options().GetExtension(type_url_prefix),
                T::descriptor()->full_name()
        );
    };

private:
    //TODO: naming
    QueryId *createQueryId();
    QueryPtr all(const std::string& prefix, const std::string& type);
private:
    std::unique_ptr<core::ActorContext> actor_context_;
    Poco::UUIDGenerator uuid_generator_;
};

}} //namespace

#endif //SPINE_QUERYFACTORY_H

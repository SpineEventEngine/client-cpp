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

#ifndef SPINE_TYPES_H
#define SPINE_TYPES_H

#include <memory>

/**
 * Forward declarations and aliases for all main types.
 *
 * @author Vladimir Moiseiev
 * @file
 */
namespace spine
{
    namespace client
    {
        class CommandFactory;
        class TopicFactory;
        class QueryFactory;
        class ActorRequestFactory;
        class Topic;
        class Query;

        using CommandFactoryPtr = std::unique_ptr<CommandFactory>;
        using TopicFactoryPtr = std::unique_ptr<TopicFactory>;
        using QueryFactoryPtr = std::unique_ptr<QueryFactory>;
        using ActorRequestFactoryPtr = std::unique_ptr<ActorRequestFactory>;
        using TopicPtr = std::unique_ptr<Topic>;
        using QueryPtr = std::unique_ptr<Query>;

    }
    namespace core
    {
        class Command;

        using CommandPtr = std::unique_ptr<Command>;
    }
}

#endif //SPINE_TYPES_H

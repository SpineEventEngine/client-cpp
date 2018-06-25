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

#ifndef SPINE_ACTORREQUESTFACTORY_H
#define SPINE_ACTORREQUESTFACTORY_H

#include <memory>
#include <spine/time/time.pb.h>
#include "types.h"
#include "actor_request_factory_params.h"

namespace spine
{
namespace client
{
/**
 * A factory for the various requests fired from the client-side by an actor.
 *
 * @author Vladimir Moiseiev
 */
class ActorRequestFactory
{
public:
    /**
     * Creates new ActorRequestFactory based on the provided parameter set.
     *
     * @param params ActorRequestFactoryParams.
     * @return new ActorRequestFactory instance.
     */
    static ActorRequestFactory create(const ActorRequestFactoryParams& params);

public:
    /**
     * Creates new CommandFactory instance.
     *
     * @return unique_ptr with CommandFactory.
     */
    CommandFactoryPtr command_factory();
    /**
     * Creates new TopicFactory instance.
     *
     * @return unique_ptr with TopicFactory.
     */
    TopicFactoryPtr topic_factory();
    /**
     * Creates new QueryFactory instance.
     *
     * @return unique_ptr with QueryFactory.
     */
    QueryFactoryPtr query_factory();

public:
    const std::unique_ptr<core::UserId> &actor() const;
    const std::unique_ptr<core::TenantId> &tenant_id() const;
    const std::unique_ptr<time::ZoneOffset> &zone_offset() const;
    const std::unique_ptr<time::ZoneId> &zone_id() const;

private:
    ActorRequestFactory(const ActorRequestFactoryParams& params);

private:
    std::unique_ptr<core::ActorContext> actor_context() const;

private:
    ActorRequestFactoryParams params_;
};

} //namespace client
} //namespace spine


#endif //SPINE_ACTORREQUESTFACTORY_H

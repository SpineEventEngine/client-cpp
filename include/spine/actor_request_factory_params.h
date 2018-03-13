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

#ifndef SPINE_ACTORREQUESTFACTORYPARAMS_H
#define SPINE_ACTORREQUESTFACTORYPARAMS_H

#include <memory>

namespace spine {

namespace core
{
    class ActorContext;
    class UserId;
    class TenantId;
}
namespace time
{
    class ZoneOffset;
}
namespace client
{

class CommandFactory;
class TopicFactory;
class QueryFactory;

/**
 * An ActorRequestFactory parameters wrapper.
 *
 * @author Vladimir Moiseiev
 */

class ActorRequestFactoryParams
{
public:
    const std::unique_ptr<core::UserId>& actor() const;
    const std::unique_ptr<core::TenantId>& tenant_id() const;
    const std::unique_ptr<time::ZoneOffset>& zone_offset() const;

    ActorRequestFactoryParams& set_actor(const std::unique_ptr<core::UserId>& actor);
    ActorRequestFactoryParams& set_tenant_id(const std::unique_ptr<core::TenantId>& tenant_id);
    ActorRequestFactoryParams& set_zone_offset(const std::unique_ptr<time::ZoneOffset>& zone_offset);

public:
    ActorRequestFactoryParams() = default;
    ActorRequestFactoryParams(const ActorRequestFactoryParams&);
    ActorRequestFactoryParams& operator=(const ActorRequestFactoryParams&);

    ActorRequestFactoryParams(ActorRequestFactoryParams&&) = default;
    ActorRequestFactoryParams& operator=(ActorRequestFactoryParams&&) = default;

private:
    void set_params(const ActorRequestFactoryParams &that);

private:
    /**
     * The ID for the user generating commands.
     */
    std::unique_ptr<spine::core::UserId> actor_;
    /**
     * The ID of the tenant in a multitenant application.
     *
     * This field is null in a single tenant application.
     */
    std::unique_ptr<spine::core::TenantId> tenant_id_;
    /**<
     * The time zone in which the user works.
     * In case the zone offset is not defined, the current time zone offset value is set by default.
     */
    std::unique_ptr<spine::time::ZoneOffset> zone_offset_;
};

} //namespace client
} //namespace spine


#endif //SPINE_ACTORREQUESTFACTORYPARAMS_H

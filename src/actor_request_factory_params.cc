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

#include "actor_request_factory_params.h"

#include <spine/core/user_id.pb.h>
#include <spine/core/tenant_id.pb.h>
#include <spine/time/zone.pb.h>

using namespace spine::client;

ActorRequestFactoryParams::ActorRequestFactoryParams(const ActorRequestFactoryParams& that)
        : actor_(std::make_unique<spine::core::UserId>(*that.actor())),
          tenant_id_(std::make_unique<spine::core::TenantId>(*that.tenant_id())),
          zone_offset_(std::make_unique<spine::time::ZoneOffset>(*that.zone_offset()))
{
}

ActorRequestFactoryParams::ActorRequestFactoryParams(ActorRequestFactoryParams&& that)
        : actor_(std::move(that.actor_)),
          tenant_id_(std::move(that.tenant_id_)),
          zone_offset_(std::move(that.zone_offset_))
{

}

ActorRequestFactoryParams& ActorRequestFactoryParams::operator=(const ActorRequestFactoryParams& that)
{
    return *this;
}

ActorRequestFactoryParams& ActorRequestFactoryParams::operator=(ActorRequestFactoryParams&& that)
{
    actor_.swap(that.actor_);
    tenant_id_.swap(that.tenant_id_);
    zone_offset_.swap(that.zone_offset_);
    return *this;
}

ActorRequestFactoryParams ActorRequestFactoryParams::create()
{
    ActorRequestFactoryParams params;
    return params;
}

const std::unique_ptr<spine::core::UserId>& ActorRequestFactoryParams::actor() const
{
    return actor_;
}

const std::unique_ptr<spine::core::TenantId>& ActorRequestFactoryParams::tenant_id() const
{
    return tenant_id_;
}

const std::unique_ptr<spine::time::ZoneOffset>& ActorRequestFactoryParams::zone_offset() const
{
    return zone_offset_;
}

void ActorRequestFactoryParams::set_actor(const std::unique_ptr<spine::core::UserId>& actor)
{
    actor_ = std::make_unique<spine::core::UserId>(*actor);
}

void ActorRequestFactoryParams::set_tenant_id(const std::unique_ptr<spine::core::TenantId>& tenant_id)
{
    tenant_id_ = std::make_unique<spine::core::TenantId>(*tenant_id);
}

void ActorRequestFactoryParams::set_zone_offset(const std::unique_ptr<spine::time::ZoneOffset>& zone_offset)
{
    zone_offset_ = std::make_unique<spine::time::ZoneOffset>(*zone_offset);
}

ActorRequestFactoryParams&
ActorRequestFactoryParams::with_tenant_id(const std::unique_ptr<spine::core::TenantId>& tenant_id)
{
    set_tenant_id(tenant_id);
    return *this;
}

ActorRequestFactoryParams& ActorRequestFactoryParams::with_actor(const std::unique_ptr<spine::core::UserId>& actor)
{
    set_actor(actor);
    return *this;
}

ActorRequestFactoryParams&
spine::client::ActorRequestFactoryParams::with_zone_offset(const std::unique_ptr<spine::time::ZoneOffset>& zone_offset)
{
    set_zone_offset(zone_offset);
    return *this;
}









//
// Created by Vladimir Moiseiev on 12/11/17.
//

#include "actor_request_factory.h"

#include "common.h"
#include "topic_factory.h"
#include "command_factory.h"
#include "query_factory.h"

using namespace spine;
using namespace spine::client;

ActorRequestFactory::ActorRequestFactory(const ActorRequestFactory::Builder& builder)
    : actor_( new core::UserId(builder.get_actor()))
    , tenant_id_(new core::TenantId(builder.get_tenant_id()))
    , zone_offset_(new time::ZoneOffset(builder.get_zone_offset()))
{
}

std::unique_ptr<CommandFactory> ActorRequestFactory::command()
{
    return std::unique_ptr<CommandFactory>();
}

std::unique_ptr<TopicFactory> ActorRequestFactory::topic()
{
    return std::unique_ptr<TopicFactory>();
}

std::unique_ptr<QueryFactory> ActorRequestFactory::query()
{
    return std::unique_ptr<QueryFactory>();
}

std::unique_ptr<core::ActorContext> ActorRequestFactory::actor_context() const
{
    std::unique_ptr<core::ActorContext> actor_context {
            get_actor_context(new core::UserId(*actor_),
                              new time::ZoneOffset(*zone_offset_),
                              new core::TenantId(*tenant_id_),
                              get_timestamp())
    };
    return actor_context;
}

ActorRequestFactory::Builder &ActorRequestFactory::Builder::set_actor(const spine::core::UserId &actor)
{
    Builder::actor_.reset(spine::core::UserId::default_instance().New());
    Builder::actor_->CopyFrom(actor);
    return *this;
}

ActorRequestFactory::Builder &ActorRequestFactory::Builder::set_tenant_id(const spine::core::TenantId &tenant_id)
{
    Builder::tenant_id_.reset(spine::core::TenantId::default_instance().New());
    Builder::tenant_id_->CopyFrom(tenant_id);
    return *this;
}

ActorRequestFactory::Builder &ActorRequestFactory::Builder::set_zone_offset(const spine::time::ZoneOffset &zone_offset)
{
    Builder::zone_offset_.reset(spine::time::ZoneOffset::default_instance().New());
    Builder::zone_offset_->CopyFrom(zone_offset);
    return *this;
}

const spine::core::UserId &ActorRequestFactory::Builder::get_actor() const
{
    return *actor_;
}

const spine::core::TenantId &ActorRequestFactory::Builder::get_tenant_id() const
{
    return *tenant_id_;
}

const spine::time::ZoneOffset &ActorRequestFactory::Builder::get_zone_offset() const
{
    return *zone_offset_;
}

std::unique_ptr<ActorRequestFactory> ActorRequestFactory::Builder::build()
{
    if( !zone_offset_ )
    {
        set_zone_offset( spine::time::ZoneOffset::default_instance() );
    }


    return std::unique_ptr<ActorRequestFactory> { new ActorRequestFactory(*this) };
}

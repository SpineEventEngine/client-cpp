//
// Created by Vladimir Moiseiev on 12/11/17.
//

#include "actor_request_factory.h"

using namespace spine::client;

ActorRequestFactory::ActorRequestFactory(const ActorRequestFactory::Builder& builder)
    : actor_( spine::core::UserId::default_instance().New())
    , tenant_id_(spine::core::TenantId::default_instance().New())
    , zone_offset_(spine::time::ZoneOffset::default_instance().New())
{
    actor_->CopyFrom(builder.get_actor());
    tenant_id_->CopyFrom(builder.get_tenant_id());
    zone_offset_->CopyFrom(builder.get_zone_offset());
}

std::unique_ptr<CommandFactory> ActorRequestFactory::command() {
    return std::unique_ptr<CommandFactory>();
}

std::unique_ptr<TopicFactory> ActorRequestFactory::topic() {
    return std::unique_ptr<TopicFactory>();
}

std::unique_ptr<QueryFactory> ActorRequestFactory::query() {
    return std::unique_ptr<QueryFactory>();
}

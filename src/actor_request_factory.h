//
// Created by Vladimir Moiseiev on 12/11/17.
//

#ifndef SPINE_ACTORREQUESTFACTORY_H
#define SPINE_ACTORREQUESTFACTORY_H


#include <memory>

#include "spine/core/user_id.pb.h"
#include "spine/time/zone.pb.h"
#include "spine/core/tenant_id.pb.h"

namespace spine {
namespace client {

class CommandFactory;
class TopicFactory;
class QueryFactory;

class ActorRequestFactory
{
public:

    class Builder
    {
    public:
        std::unique_ptr<ActorRequestFactory> build()
        {
            if( !zone_offset_ )
            {
                set_zone_offset( spine::time::ZoneOffset::default_instance() );
            }


            return std::unique_ptr<ActorRequestFactory> { new ActorRequestFactory(*this) };
        }

        Builder& set_actor(const spine::core::UserId &actor) {
            Builder::actor_.reset(spine::core::UserId::default_instance().New());
            Builder::actor_->CopyFrom(actor);
            return *this;
        }

        Builder& set_tenant_id(const spine::core::TenantId& tenant_id) {
            Builder::tenant_id_.reset(spine::core::TenantId::default_instance().New());
            Builder::tenant_id_->CopyFrom(tenant_id);
            return *this;
        }

        Builder& set_zone_offset(const spine::time::ZoneOffset& zone_offset) {
            Builder::zone_offset_.reset(spine::time::ZoneOffset::default_instance().New());
            Builder::zone_offset_->CopyFrom(zone_offset);
            return *this;
        }

        const spine::core::UserId& get_actor() const {
            return *actor_;
        }

        const spine::core::TenantId& get_tenant_id() const {
            return *tenant_id_;
        }

        const spine::time::ZoneOffset& get_zone_offset() const {
            return *zone_offset_;
        }

    private:
        std::unique_ptr<spine::core::UserId> actor_;
        std::unique_ptr<spine::core::TenantId> tenant_id_;
        std::unique_ptr<spine::time::ZoneOffset> zone_offset_;
    };

public:
    std::unique_ptr<CommandFactory> command();
    std::unique_ptr<TopicFactory> topic();
    std::unique_ptr<QueryFactory> query();

public:
    const std::unique_ptr<core::UserId> &actor() const { return actor_; }
    const std::unique_ptr<core::TenantId> &tenant_id() const {return tenant_id_; }
    const std::unique_ptr<time::ZoneOffset> &zone_offset() const { return zone_offset_; }

private:
    ActorRequestFactory(const Builder& builder);

private:
    std::unique_ptr<spine::core::UserId> actor_;
    std::unique_ptr<spine::core::TenantId> tenant_id_;
    std::unique_ptr<spine::time::ZoneOffset> zone_offset_;

};

} //namespace client
} //namespace spine


#endif //SPINE_ACTORREQUESTFACTORY_H

//
// Created by Vladimir Moiseiev on 12/11/17.
//

#ifndef SPINE_ACTORREQUESTFACTORY_H
#define SPINE_ACTORREQUESTFACTORY_H


#include <memory>
#include <spine/time/zone.pb.h>

namespace spine {

namespace core{
    class ActorContext;
    class UserId;
    class TenantId;
}
namespace time {
    class ZoneOffset;
}
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
        std::unique_ptr<ActorRequestFactory> build();

        Builder& set_actor(const spine::core::UserId &actor);
        Builder& set_tenant_id(const spine::core::TenantId& tenant_id);
        Builder& set_zone_offset(const spine::time::ZoneOffset& zone_offset);

        const spine::core::UserId& get_actor() const;
        const spine::core::TenantId& get_tenant_id() const;
        const spine::time::ZoneOffset& get_zone_offset() const;

    private:
        std::unique_ptr<spine::core::UserId> actor_;
        std::unique_ptr<spine::core::TenantId> tenant_id_;
        std::unique_ptr<spine::time::ZoneOffset> zone_offset_;
    };

public:
    std::unique_ptr<CommandFactory> command();
    std::unique_ptr<TopicFactory> topic();
    std::unique_ptr<QueryFactory> query();
    std::unique_ptr<core::ActorContext> actor_context() const;

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

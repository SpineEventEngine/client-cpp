//
// Created by Vladimir Moiseiev on 4/10/17.
//

#include <sstream>
#include "query_factory.h"
#include "common.h"


using namespace spine::client;
using namespace google::protobuf;

google::protobuf::Timestamp *get_timestamp() { return google::protobuf::Timestamp::default_instance().New(); }

spine::core::EventContext *get_event_conext(google::protobuf::Any *producer_id) {
    spine::core::EventContext *event_context = spine::core::EventContext::default_instance().New();
    event_context->set_allocated_timestamp(get_timestamp());
    event_context->set_allocated_producer_id(producer_id);
    return event_context;
}

google::protobuf::Any *get_producer_id(const google::protobuf::Message &message) {
    google::protobuf::Any *producerId = google::protobuf::Any::default_instance().New();
    producerId->PackFrom(message);
    return producerId;
}

spine::core::EventId *get_event_id(const char *value) {
    spine::core::EventId *event_id = spine::core::EventId::default_instance().New();
    event_id->set_value(value);
    return event_id;
}



spine::core::CommandId *get_command_id(const char *value) {
    spine::core::CommandId *commandId = spine::core::CommandId::default_instance().New();
    commandId->set_uuid(value);
    return commandId;
}

spine::core::ActorContext *
get_actor_context(spine::core::UserId *actor, spine::time::ZoneOffset *offset, spine::core::TenantId *tenant_id,
                  google::protobuf::Timestamp *timestamp) {
    spine::core::ActorContext *actor_context = spine::core::ActorContext::default_instance().New();
    actor_context->set_allocated_timestamp(timestamp);
    actor_context->set_allocated_actor(actor);
    actor_context->set_allocated_zone_offset(offset);
    actor_context->set_allocated_tenant_id(tenant_id);
    return actor_context;
}

//spine::core::CommandContext *
//get_command_context(google::protobuf::Timestamp *timestamp, spine::core::UserId *actor, spine::time::ZoneOffset *offset,
//                    int version) {
//    spine::core::CommandContext *command_context = spine::core::CommandContext::default_instance().New();
//    command_context->set_allocated_actor_context(
//            get_actor_context(actor, offset, tenant_id, timestamp));
//    command_context->set_target_version(version);
//    return command_context;
//}

spine::core::UserId *get_user_id(const std::string &value) {
    spine::core::UserId *userId = spine::core::UserId::default_instance().New();
    userId->set_value(value);
    return userId;
}

spine::time::ZoneId *get_zone_id() {
    spine::time::ZoneId *zone_id = spine::time::ZoneId::default_instance().New();
    zone_id->set_value("UTC");
    return zone_id;
}

spine::time::ZoneOffset *get_zone_offset(spine::time::ZoneId *zone_id) {
    spine::time::ZoneOffset *zone_offset = spine::time::ZoneOffset::default_instance().New();
    zone_offset->set_amountseconds(0);
    zone_offset->set_allocated_id(zone_id);
    return zone_offset;
}

Target* create_target(const string& type_url)
{
    Target *target = Target::default_instance().New();
    target->set_type(type_url);
    return target;
}

spine::core::ActorContext* copy_actor_context(const spine::core::ActorContext& actor_context)
{
    spine::core::ActorContext* new_actor_context = spine::core::ActorContext::default_instance().New();
    new_actor_context->CopyFrom(actor_context);

    return new_actor_context;
}

google::protobuf::Any* to_any(const google::protobuf::Message& message)
{
    google::protobuf::Any* any = google::protobuf::Any::default_instance().New();
    any->PackFrom(message);
    return any;
}


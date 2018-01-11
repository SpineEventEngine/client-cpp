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

#include <sstream>
#include "query_factory.h"
#include "common.h"


using namespace spine::client;
using namespace google::protobuf;

google::protobuf::Timestamp *get_timestamp() 
{
    Timestamp* timestamp = google::protobuf::Timestamp::default_instance().New();
    timestamp->set_seconds(time(nullptr));
    return timestamp;
}

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

std::unique_ptr<spine::core::UserId> make_user_id(const std::string &value)
{
    auto actor = std::make_unique<spine::core::UserId>();
    actor->set_value(value);
    return actor;
}

std::unique_ptr<spine::core::TenantId> make_tenant_id(const std::string &value)
{
    auto tenant_id = std::make_unique<spine::core::TenantId>();
    tenant_id->set_value(value);
    return tenant_id;
}

std::unique_ptr<spine::time::ZoneOffset> make_zone_offset(const std::string &zone_id, int amount)
{
    spine::time::ZoneId* zone_id_ptr = spine::time::ZoneId::default_instance().New();
    zone_id_ptr->set_value(zone_id);

    std::unique_ptr<spine::time::ZoneOffset> zone_offset = std::make_unique<spine::time::ZoneOffset>();
    zone_offset->set_allocated_id(zone_id_ptr);
    zone_offset->set_amountseconds(amount);
    return zone_offset;
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

google::protobuf::Any* to_any(const google::protobuf::Message& message, const std::string& type_url)
{
    google::protobuf::Any* any = google::protobuf::Any::default_instance().New();
    any->PackFrom(message, type_url);
    return any;
}


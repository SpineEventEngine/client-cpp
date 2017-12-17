//
// Created by Vladimir Moiseiev on 4/10/17.
//

#ifndef POC_CLIENT_COMMON_H
#define POC_CLIENT_COMMON_H

#include <iostream>
#include <fstream>
#include <string>
#include "grpc++/grpc++.h"

#include "spine/core/event.pb.h"
#include "spine/client/command_service.grpc.pb.h"
#include "spine/client/entities.pb.h"


google::protobuf::Timestamp *get_timestamp();

spine::core::EventContext *get_event_conext(google::protobuf::Any *producer_id);
google::protobuf::Any *get_producer_id(const google::protobuf::Message &message);

spine::core::EventId *get_event_id(const char *value);


spine::core::CommandId *get_command_id(const char *value);

spine::core::ActorContext *
get_actor_context(spine::core::UserId *actor, spine::time::ZoneOffset *offset, spine::core::TenantId *timestamp,
                  google::protobuf::Timestamp *pTimestamp);

spine::core::CommandContext *
get_command_context(google::protobuf::Timestamp *timestamp, spine::core::UserId *actor, spine::time::ZoneOffset *offset,
                    int version);



spine::core::UserId *get_user_id(const std::string &value);

spine::time::ZoneId *get_zone_id();

spine::time::ZoneOffset *get_zone_offset(spine::time::ZoneId *zone_id);

spine::client::Target* create_target(const std::string& type_url);

spine::core::ActorContext* copy_actor_context(const spine::core::ActorContext&);

#endif //POC_CLIENT_COMMON_H

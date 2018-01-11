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
std::unique_ptr<spine::core::UserId> make_user_id(const std::string &value);
std::unique_ptr<spine::core::TenantId> make_tenant_id(const std::string &value);
std::unique_ptr<spine::time::ZoneOffset> make_zone_offset(const std::string &zone_id, int amount);


spine::time::ZoneId *get_zone_id();

spine::time::ZoneOffset *get_zone_offset(spine::time::ZoneId *zone_id);

spine::client::Target* create_target(const std::string& type_url);

spine::core::ActorContext* copy_actor_context(const spine::core::ActorContext&);

google::protobuf::Any* to_any(const google::protobuf::Message& message);
google::protobuf::Any* to_any(const google::protobuf::Message& message, const std::string& );

#endif //POC_CLIENT_COMMON_H

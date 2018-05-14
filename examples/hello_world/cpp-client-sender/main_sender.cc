/*
 * Copyright 2018, TeamDev. All rights reserved.
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

#include "grpc++/grpc++.h"
#include "spine/client/command_service.grpc.pb.h"

#include "hello.pb.h"

#include <spine/types.h>
#include <spine/command_factory.h>
#include <spine/actor_request_factory_params.h>
#include <spine/actor_request_factory.h>
#include <spine/client/query.pb.h>

using namespace spine::client;
//using namespace spine::core;

std::unique_ptr<spine::core::UserId> make_user_id(const std::string &value)
{
    auto actor = std::make_unique<spine::core::UserId>();
    actor->set_value(value);
    return actor;
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

int main(int argc, char *argv[])
{
    std::shared_ptr<grpc::Channel> channel = ::grpc::CreateChannel("localhost:8484", grpc::InsecureChannelCredentials());

    Poco::UUIDGenerator generator;

    helloworld::SayHello say_hello;
    helloworld::HelloId* id = ::helloworld::HelloId::default_instance().New();
    id->set_value(generator.createRandom().toString());
    say_hello.set_allocated_id(id);
    say_hello.set_user_id("asdads");
    say_hello.set_username("user1" + generator.createRandom().toString());

    auto tenant = std::unique_ptr<TenantId>(TenantId::default_instance().New());

    ActorRequestFactoryParams params;
    params
        .set_tenant_id(tenant)
        .set_actor(make_user_id("user"))
        .set_zone_offset(make_zone_offset("UTC", 0));

    CommandFactoryPtr command_factory = ActorRequestFactory::create(params).command_factory();

    CommandPtr command = command_factory->create(say_hello, "type.spine.io");

    std::unique_ptr<CommandService::Stub> stub = CommandService::NewStub(channel);

    spine::core::Ack response;
    grpc::ClientContext client_context;
    stub->Post(&client_context, *command, &response);

    return 0;
}

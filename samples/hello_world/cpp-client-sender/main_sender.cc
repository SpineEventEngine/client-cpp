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

#include "grpc++/grpc++.h"
#include "spine/client/command_service.grpc.pb.h"

#include "hello.pb.h"

#include <command_factory.h>
#include <actor_request_factory_params.h>
#include <common.h>
#include <actor_request_factory.h>
#include <spine/client/query.pb.h>

using namespace spine::client;

int main(int argc, char *argv[])
{
    std::shared_ptr<grpc::Channel> channel = ::grpc::CreateChannel("localhost:8484", grpc::InsecureChannelCredentials());


    helloworld::SayHello say_hello;
    helloworld::HelloId* id = ::helloworld::HelloId::default_instance().New();
    Poco::UUIDGenerator generator;
    id->set_value(generator.createRandom().toString());
    say_hello.set_allocated_id(id);
    say_hello.set_user_id("asdads");
    say_hello.set_username("user1" + generator.createRandom().toString());

    auto tenant = std::unique_ptr<spine::core::TenantId>(TenantId::default_instance().New());

    ActorRequestFactoryParams params;
    params
        .set_tenant_id(tenant)
        .set_actor(make_user_id("user"))
        .set_zone_offset(make_zone_offset("UTC", 0));

    command_factory_t command_factory = ActorRequestFactory::create(params).command_factory();

    spine::core::command_t command = command_factory->create(say_hello, "type.spine.io");

    std::unique_ptr<CommandService::Stub> stub = CommandService::NewStub(channel);

    spine::core::Ack response;
    grpc::ClientContext client_context;
    stub->Post(&client_context, *command, &response);

    return 0;
}


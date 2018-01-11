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
#include "spine/client/query_service.grpc.pb.h"

#include "hello.pb.h"

#include <types.h>
#include <query_factory.h>
#include <actor_request_factory_params.h>
#include <common.h>
#include <actor_request_factory.h>
#include <type_url.h>

using namespace spine::client;

int main ()
{
    std::shared_ptr<grpc::Channel> channel = ::grpc::CreateChannel("localhost:8484", grpc::InsecureChannelCredentials());


    helloworld::LastHello lastHello;


    auto tenant = std::unique_ptr<spine::core::TenantId>(spine::core::TenantId::default_instance().New());

    ActorRequestFactoryParams params;
    params
            .set_tenant_id(tenant)
            .set_actor(make_user_id("user"))
            .set_zone_offset(make_zone_offset("UTC", 0));

    ActorRequestFactory factory = ActorRequestFactory::create(params);

    query_t query = factory.query_factory()->all("helloworld.LastHello");

    std::unique_ptr<QueryService::Stub> query_service = QueryService::NewStub(channel);

    QueryResponse response;
    grpc::ClientContext client_context;
    query_service->Read(&client_context, *query, &response);

    if (response.messages_size() > 0)
    {
        const google::protobuf::Any& any = response.messages(0);
        ::helloworld::LastHello last_hello;
        any.UnpackTo(&last_hello);
        std::string username = last_hello.username();
    }
    return 0;
}


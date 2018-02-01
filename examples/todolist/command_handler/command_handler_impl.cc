/*
* Copyright 2018, TeamDev Ltd. All rights reserved.
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


#include "command_handler_impl.h"

#include "spine/client/query_service.grpc.pb.h"

#define CHANNEL "localhost:50051"

CommandHandlerImpl::CommandHandlerImpl()
{
	channel_ = ::grpc::CreateChannel(CHANNEL, grpc::InsecureChannelCredentials());
	auto tenant = std::unique_ptr<TenantId>(TenantId::default_instance().New());

	parameters_
		.set_tenant_id(tenant)
		.set_actor(make_user_id("user"))
		.set_zone_offset(make_zone_offset("UTC", 0));

	command_factory_ = ActorRequestFactory::create(parameters_).command_factory();
	stub_ = CommandService::NewStub(channel_);
}

void CommandHandlerImpl::post_command(spine::examples::todolist::CreateBasicTask & client_task)
{
	CommandPtr command = command_factory_->create(client_task);
	spine::core::Ack response;
	grpc::ClientContext client_context;
	if (!stub_->Post(&client_context, *command, &response).ok()) {
		throw exception::exception("Invalid server status...");
	}
}

spine::examples::todolist::TaskListView const &
CommandHandlerImpl::get_tasks()
{
	ActorRequestFactory factory = ActorRequestFactory::create(parameters_);

	QueryPtr query = factory.query_factory()->all<::spine::examples::todolist::MyListView>();

	std::unique_ptr<QueryService::Stub> query_service = QueryService::NewStub(channel_);

	QueryResponse response;
	grpc::ClientContext client_context;

	if (!query_service->Read(&client_context, *query, &response).ok()) {
		throw exception::exception("Invalid response....");
	}

	spine::examples::todolist::MyListView * taskListsView
		= spine::examples::todolist::MyListView::default_instance().New();

	if (response.messages_size() > 0)
	{
		const Any& any = response.messages(0);
		any.UnpackTo(taskListsView);
	}

	return taskListsView->my_list();
}

std::unique_ptr<spine::core::UserId>
CommandHandlerImpl::make_user_id(const std::string & value)
{
	auto actor = std::make_unique<spine::core::UserId>();
	actor->set_value(value);
	return actor;
}

std::unique_ptr<spine::time::ZoneOffset>
CommandHandlerImpl::make_zone_offset(const std::string &zone_id, int amount)
{
	spine::time::ZoneId* zone_id_ptr = spine::time::ZoneId::default_instance().New();
	zone_id_ptr->set_value(zone_id);

	std::unique_ptr<spine::time::ZoneOffset> zone_offset
		= std::make_unique<spine::time::ZoneOffset>();

	zone_offset->set_allocated_id(zone_id_ptr);
	zone_offset->set_amountseconds(amount);
	return zone_offset;
}

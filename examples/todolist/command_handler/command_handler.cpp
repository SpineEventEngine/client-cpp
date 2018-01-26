#include "command_handler.hpp"

#include "spine/client/query_service.grpc.pb.h"

#define CHANNEL "localhost:50051"

CommandHandler::CommandHandler()
{
	m_channel = ::grpc::CreateChannel(CHANNEL, grpc::InsecureChannelCredentials());
	auto tenant = std::unique_ptr<TenantId>(TenantId::default_instance().New());

	m_parameters
		.set_tenant_id(tenant)
		.set_actor(make_user_id("user"))
		.set_zone_offset(make_zone_offset("UTC", 0));

	m_command_factory = ActorRequestFactory::create(m_parameters).command_factory();
	m_stub = CommandService::NewStub(m_channel);
}

void CommandHandler::postCommand(spine::examples::todolist::CreateBasicTask & _clientTask)
{
	CommandPtr command = m_command_factory->create(_clientTask, "type.spine.examples.todolist");
	spine::core::Ack response;
	grpc::ClientContext client_context;
	if (!m_stub->Post(&client_context, *command, &response).ok()) {
		throw exception::exception("Invalid server status...");
	}
}

spine::examples::todolist::TaskListView const &
CommandHandler::getTasks()
{
	ActorRequestFactory factory = ActorRequestFactory::create(m_parameters);

	QueryPtr query = factory.query_factory()->all<::spine::examples::todolist::MyListView>();

	std::unique_ptr<QueryService::Stub> query_service = QueryService::NewStub(m_channel);

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
CommandHandler::make_user_id(const std::string &value)
{
	auto actor = std::make_unique<spine::core::UserId>();
	actor->set_value(value);
	return actor;
}

std::unique_ptr<spine::time::ZoneOffset>
CommandHandler::make_zone_offset(const std::string &zone_id, int amount)
{
	spine::time::ZoneId* zone_id_ptr = spine::time::ZoneId::default_instance().New();
	zone_id_ptr->set_value(zone_id);

	std::unique_ptr<spine::time::ZoneOffset> zone_offset
		= std::make_unique<spine::time::ZoneOffset>();

	zone_offset->set_allocated_id(zone_id_ptr);
	zone_offset->set_amountseconds(amount);
	return zone_offset;
}

CommandHandler &
CommandHandler::getCommandHandler()
{
	static CommandHandler commandHandler;
	return commandHandler;
}

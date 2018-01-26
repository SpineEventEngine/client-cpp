#pragma once

#include "grpc++/grpc++.h"
#include "spine/client/command_service.grpc.pb.h"
#include <spine/client/query.pb.h>

#include "spine/types.h"
#include "spine/command_factory.h"
#include "spine/actor_request_factory_params.h"
#include "spine/actor_request_factory.h"
#include "spine/query_factory.h"

#include "todolist/c/commands.pb.h"
#include "todolist/q/projections.pb.h"

#include <memory>

using namespace spine::client;

class CommandHandler
{
	
public:

	CommandHandler();
	~CommandHandler() = default;

	void postCommand(spine::examples::todolist::CreateBasicTask & _clientTask);
	spine::examples::todolist::TaskListView const & getTasks();

	static CommandHandler & getCommandHandler();

	static std::unique_ptr<spine::core::UserId> make_user_id(const std::string &value);
	static std::unique_ptr<spine::time::ZoneOffset> make_zone_offset(const std::string &zone_id, int amount);

private:

	std::shared_ptr<grpc::Channel> m_channel;
	std::unique_ptr<CommandService::Stub> m_stub;

	ActorRequestFactoryParams m_parameters;
	CommandFactoryPtr m_command_factory;
};
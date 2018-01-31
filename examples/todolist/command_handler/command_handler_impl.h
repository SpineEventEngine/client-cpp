#pragma once

#include "grpc++/grpc++.h"
#include "spine/client/command_service.grpc.pb.h"
#include <spine/client/query.pb.h>

#include "spine/types.h"
#include "spine/command_factory.h"
#include "spine/actor_request_factory_params.h"
#include "spine/actor_request_factory.h"
#include "spine/query_factory.h"

#include "command_handler.h"

#include <memory>

using namespace spine::client;

class CommandHandlerImpl
	:	public CommandHandler
{
	
public:

	CommandHandlerImpl();

	void post_command(spine::examples::todolist::CreateBasicTask & client_task);
	spine::examples::todolist::TaskListView const & get_tasks();

private:

	std::unique_ptr<spine::core::UserId> make_user_id(const std::string & value);
	std::unique_ptr<spine::time::ZoneOffset> make_zone_offset(const std::string &zone_id, int amount);

	std::shared_ptr<grpc::Channel> m_channel;
	std::unique_ptr<CommandService::Stub> m_stub;

	ActorRequestFactoryParams m_parameters;
	CommandFactoryPtr m_command_factory;
};
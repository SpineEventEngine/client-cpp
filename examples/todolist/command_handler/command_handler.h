#pragma once

#include "todolist/c/commands.pb.h"
#include "todolist/q/projections.pb.h"

class CommandHandler
{
	virtual ~CommandHandler() {}

	virtual void post_command(spine::examples::todolist::CreateBasicTask & client_task) = 0;

	virtual spine::examples::todolist::TaskListView const & get_tasks() = 0;
};
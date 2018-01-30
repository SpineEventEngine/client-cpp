#pragma once

#include <memory>
#include <string>

#include "todolist/model.pb.h"
#include "todolist/c/commands.pb.h"

class CommandHandler;

class CreateTask
{
public:

	CreateTask(std::shared_ptr<CommandHandler> command_handler);

	void post(std::string const & task_identifier, std::string const & _description);

private:

	std::shared_ptr<CommandHandler> command_handler_;
};
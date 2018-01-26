#include "create_task.hpp"
#include "Poco/UUIDGenerator.h"

#include "command_handler/command_handler.hpp"

void CreateTask::post(std::string const & _description)
{
	Poco::UUIDGenerator generator;

	spine::examples::todolist::TaskId * taskId = spine::examples::todolist::TaskId::default_instance().New();
	taskId->set_value(generator.createRandom().toString());

	spine::examples::todolist::TaskDescription * taskDescription = spine::examples::todolist::TaskDescription::default_instance().New();
	taskDescription->set_value(_description);

	spine::examples::todolist::CreateBasicTask task;

	task.set_allocated_id(taskId);
	task.set_allocated_description(taskDescription);

	CommandHandler::getCommandHandler().postCommand(task);
}

std::shared_ptr<CreateTask>
CreateTask::createTask()
{
	return std::make_shared<CreateTask>(*new CreateTask());
}
#include "create_task.h"

#include "command_handler/command_handler.h"

CreateTask::CreateTask(std::shared_ptr<CommandHandler> command_handler)
	: command_handler_(command_handler)
{

}

void CreateTask::post(std::string const & task_identifier, std::string const & _description)
{
	spine::examples::todolist::TaskId * taskId = spine::examples::todolist::TaskId::default_instance().New();
	taskId->set_value(task_identifier);

	spine::examples::todolist::TaskDescription * taskDescription = spine::examples::todolist::TaskDescription::default_instance().New();
	taskDescription->set_value(_description);

	spine::examples::todolist::CreateBasicTask task;

	task.set_allocated_id(taskId);
	task.set_allocated_description(taskDescription);

	command_handler_->post_command(task);
}
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

#include "create_task.h"
#include "command_handler/command_handler.h"

namespace spine {
namespace examples {
namespace todolist {

CreateTask::CreateTask(std::shared_ptr<CommandHandler> command_handler)
	: command_handler_(command_handler)
{
}

void CreateTask::post(const std::string & task_identifier, const std::string & _description)
{
	TaskId * taskId = TaskId::default_instance().New();
	taskId->set_value(task_identifier);

	TaskDescription * taskDescription = TaskDescription::default_instance().New();
	taskDescription->set_value(_description);

	CreateBasicTask task;

	task.set_allocated_id(taskId);
	task.set_allocated_description(taskDescription);

	command_handler_->post_command(task);
}

} // namespace todolist
} // namespace examples
} // namespace spine

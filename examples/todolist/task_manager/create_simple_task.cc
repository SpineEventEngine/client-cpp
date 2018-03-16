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

#include <command_handler/command_handler.h>
#include <console_view/console_view.h>
#include "create_task.h"
#include "create_simple_task.h"

namespace spine {
namespace examples {
namespace todolist {

CreateSimpleTask::CreateSimpleTask(
    std::shared_ptr<ConsoleView> console_view,
    std::shared_ptr<CommandHandler> command_handler
)
    : BaseTask(console_view, command_handler)
{
}

void CreateSimpleTask::RunSimpleTaskCreation()
{
    std::cout << "Please enter the task description\n";
    std::string description;
    std::getline(std::cin, description);

    std::string task_identifier = BaseTask::GenerateUniqueId();
    TaskId * task_id = TaskId::default_instance().New();
    task_id->set_value(task_identifier);

    TaskDescription * task_description = TaskDescription::default_instance().New();
    task_description->set_value(description);

    CreateBasicTask task;

    task.set_allocated_id(task_id);
    task.set_allocated_description(task_description);

    command_handler_->PostCommand(task);
}

} // namespace todolist
} // namespace examples
} // namespace spine

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

#include "main_task.h"
#include "resources/resources.h"
#include "console_view/console_writer.h"
#include "create_task.h"
#include "list_task.h"
#include "create_simple_task.h"

namespace spine {
namespace examples {
namespace todolist {

MainTask::MainTask(
    std::shared_ptr<ConsoleView> console_view,
    std::shared_ptr<CommandHandler> command_handler
)
    : BaseTask(console_view, command_handler)
{
}

void MainTask::StartMenu() {
    console_view_->ActivateConsole([&]() {
        std::cout << resources::messages::MAIN_MENU << std::endl;
        std::cout << resources::command_line::LINE_SEPARATOR << std::endl;

        InitializeCommands();
        return ProcessCommand();
    });
}

void MainTask::InitializeCommands() {
    console_view_->AddSimpleCommand(
            ConsoleCommandType::CREATE_TASK,
            resources::tasks_menu::CREATE_TASK_SHORTCUT,
            resources::tasks_menu::CREATE_TASK_COMMAND,
            resources::tasks_menu::CREATE_TASK_INFO
    );

    console_view_->AddSimpleCommand(
            ConsoleCommandType::START_WIZARD_TASK_CREATION,
            resources::tasks_menu::START_WIZARD_TASK_CREATION_SHORTCUT,
            resources::tasks_menu::START_WIZARD_TASK_CREATION_COMMAND,
            resources::tasks_menu::START_WIZARD_TASK_CREATION_INFO
    );

    console_view_->AddSimpleCommand(
            ConsoleCommandType::LIST_TASK,
            resources::tasks_menu::LIST_TASK_SHORTCUT,
            resources::tasks_menu::LIST_TASK_COMMAND,
            resources::tasks_menu::LIST_TASK_INFO
    );

    console_view_->AddSimpleCommand(
            ConsoleCommandType::QUIT_PROGRAM,
            resources::tasks_menu::QUIT_TASK_SHORTCUT,
            resources::tasks_menu::QUIT_TASK_COMMAND,
            resources::tasks_menu::QUIT_TASK_INFO
    );
}

bool MainTask::ProcessCommand() {
    console_view_->RunCommandInput();
    switch (console_view_->GetActiveTask()) {
        case ConsoleCommandType::CREATE_TASK:
        {
            AddBasicTask();
            break;
        }
        case ConsoleCommandType::START_WIZARD_TASK_CREATION:
        {
            StartWizardTaskCreation();
            break;
        }
        case ConsoleCommandType::LIST_TASK:
        {
            ListTasks();
            break;
        }
        case ConsoleCommandType::QUIT_PROGRAM:
            return false;
        default:
            ConsoleWriter::PrintUndefinedActionMessage();
    }

    return true;
}

void MainTask::AddBasicTask()
{
    auto create_task_command = std::make_unique<CreateSimpleTask>(console_view_, command_handler_);
    try
    {
        create_task_command->RunSimpleTaskCreation();
        std::cout << resources::messages::TASK_CREATED_MESSAGE;
    }
    catch (std::exception &_exception)
    {
        std::cout << _exception.what() << std::endl;
    }
}

void MainTask::StartWizardTaskCreation() {
    auto create_task_command = std::make_unique<CreateTask>(console_view_, command_handler_);
    try
    {
        create_task_command->RunTaskCreation();
        std::cout << resources::messages::TASK_CREATED_MESSAGE;
    }
    catch (std::exception &_exception)
    {
        std::cout << _exception.what() << std::endl;
    }
}

void MainTask::ListTasks() const {

    auto list_task_command = std::make_unique<ListTask>(console_view_, command_handler_);
    try
    {
        list_task_command->LoadTaskMenu();
    }
    catch (std::exception &_exception)
    {
        std::cout << _exception.what() << std::endl;
    }
}

} // namespace todolist
} // namespace examples
} // namespace spine

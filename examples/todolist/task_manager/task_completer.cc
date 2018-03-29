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

#include "task_runner.h"
#include "task_completer.h"
#include "command_handler/command_handler_impl.h"
#include "resources/resources.h"

namespace spine {
namespace examples {
namespace todolist {

TaskCompleter::TaskCompleter(
    std::shared_ptr<ConsoleView> console_view,
    std::shared_ptr<CommandHandler> command_handler,
    std::shared_ptr<TaskCreationId> wizard_id
)
    : TodoTask(console_view, command_handler)
    , wizard_id_(wizard_id)
{
}

MenuResult TaskCompleter::RunCompleteMenu()
{
    MenuResult menu_result = MenuResult ::UNKNOWN;
    console_view_->ActivateConsole([&]() {
        std::cout << resources::messages::kTaskCompletionMenu << std::endl;
        std::cout << resources::command_line::kLineSeparator << std::endl;

        InitializeCommands();
        menu_result = ProcessCommand();
        return ConvertMenuResultTooBool(menu_result);
    });

    return menu_result;
}

void TaskCompleter::InitializeCommands()
{
    console_view_->AddSimpleCommand(
        ConsoleCommandType::FINISH_TASK,
        resources::tasks_menu::kFinishTaskShortcut,
        resources::tasks_menu::kFinishTaskCommand,
        resources::tasks_menu::kFinishTaskInfo
    );

    console_view_->AddSimpleCommand(
        ConsoleCommandType::CANCEL_TASK,
        resources::tasks_menu::kCancelShortcut,
        resources::tasks_menu::kCancelCommand,
        resources::tasks_menu::kCancelInfo
    );

    console_view_->AddSimpleCommand(
        ConsoleCommandType::BACK_TO_PREVIOUS_MENU,
        resources::tasks_menu::kBackShortcut,
        resources::tasks_menu::kBackCommand,
        resources::tasks_menu::kBackInfo
    );
}

MenuResult TaskCompleter::ProcessCommand()
{
    console_view_->RunCommandInput();
    switch (console_view_->GetActiveTask())
    {
        case ConsoleCommandType::FINISH_TASK:
        {
            FinishTask();
            return MenuResult::FINISH_MENU;
        }
        case ConsoleCommandType::CANCEL_TASK:
        {
            CancelTask();
            return MenuResult::FINISH_MENU;
        }
        case ConsoleCommandType::BACK_TO_PREVIOUS_MENU:
        {
            return MenuResult::BACK_TO_PREVIOUS_MENU;
        }
        default:
            return MenuResult::REPEAT_MENU;
    }
}

void TaskCompleter::FinishTask()
{
    CompleteTaskCreation complete_task_creation;
    complete_task_creation.set_allocated_id(wizard_id_.get());
    command_handler_->PostCommand(complete_task_creation);
    complete_task_creation.release_id();
}

void TaskCompleter::CancelTask()
{
    CancelTaskCreation cancel_task_creation;
    cancel_task_creation.set_allocated_id(wizard_id_.get());
    command_handler_->PostCommand(cancel_task_creation);
    cancel_task_creation.release_id();
}

} // namespace todolist
} // namespace examples
} // namespace spine
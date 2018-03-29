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

#include "list_task.h"
#include "console_view/console_writer.h"
#include "command_handler/command_handler.h"
#include "resources/resources.h"

namespace spine {
namespace examples {
namespace todolist {

ListTask::ListTask(
    std::shared_ptr<ConsoleView> console_view,
    std::shared_ptr<CommandHandler> command_handler
)
    : TodoTask(console_view, command_handler)
{
}

void ListTask::LoadTasks(ConsoleCommandType command_type)
{
    task_items_.clear();
    switch (command_type)
    {
        case ConsoleCommandType::DRAFT_TASKS:
        {
            const auto& task_list_view = command_handler_->GetDraftTasks();
            task_items_.assign(task_list_view.items().begin(), task_list_view.items().end());
            break;
        }
        case ConsoleCommandType::COMPLETED_TASKS:
        {
            const auto& task_list_view = command_handler_->GetCompletedTasks();
            task_items_.assign(task_list_view.items().begin(), task_list_view.items().end());
            break;
        }
        case ConsoleCommandType::ALL_TASKS:
        {
            const auto& completed_task_list_view = command_handler_->GetCompletedTasks();
            const auto& draft_task_list_view = command_handler_->GetDraftTasks();
            const auto& completed_items = completed_task_list_view.items();
            const auto& draft_items = draft_task_list_view.items();

            std::copy(completed_items.begin(), completed_items.end(), std::back_inserter(task_items_));
            std::copy(draft_items.begin(), draft_items.end(), std::back_inserter(task_items_));
            break;
        }
        default:
            break;
    }
}

void ListTask::LoadTaskMenu()
{
    console_view_->ActivateConsole([&]() {
        InitializeCommands();

        MenuResult menu_result = ProcessCommand();
        return ConvertMenuResultTooBool(menu_result);
    });
}

void ListTask::InitializeCommands()
{
    console_view_->AddSimpleCommand(
        ConsoleCommandType::DRAFT_TASKS,
        resources::tasks_menu::kDraftTasksShortcut,
        resources::tasks_menu::kDraftTasksCommand,
        resources::tasks_menu::kDraftTasksInfo
    );
    console_view_->AddSimpleCommand(
        ConsoleCommandType::COMPLETED_TASKS,
        resources::tasks_menu::kCompletedTasksShortcut,
        resources::tasks_menu::kCompletedTasksCommand,
        resources::tasks_menu::kCompletedTasksInfo
    );
    console_view_->AddSimpleCommand(
        ConsoleCommandType::ALL_TASKS,
        resources::tasks_menu::kAllTasksShortcut,
        resources::tasks_menu::kAllTasksCommand,
        resources::tasks_menu::kAllTasksInfo
    );
    console_view_->AddSimpleCommand(
        ConsoleCommandType::BACK_TO_PREVIOUS_MENU,
        resources::tasks_menu::kBackShortcut,
        resources::tasks_menu::kBackCommand,
        resources::tasks_menu::kBackInfo
    );
}

MenuResult ListTask::ProcessCommand()
{
    console_view_->RunCommandInput();
    switch (console_view_->GetActiveTask())
    {
        case ConsoleCommandType::DRAFT_TASKS:
        {
            LoadTaskList(ConsoleCommandType::DRAFT_TASKS);
            break;
        }
        case ConsoleCommandType::COMPLETED_TASKS:
        {
            LoadTaskList(ConsoleCommandType::COMPLETED_TASKS);
            break;
        }
        case ConsoleCommandType::ALL_TASKS:
        {
            LoadTaskList(ConsoleCommandType::ALL_TASKS);
            break;
        }
        case ConsoleCommandType::BACK_TO_PREVIOUS_MENU:
            return MenuResult::BACK_TO_PREVIOUS_MENU;
        default:
            return MenuResult::REPEAT_MENU;
    }
    return MenuResult::REPEAT_MENU;
}

void ListTask::LoadTaskList(ConsoleCommandType command_type)
{
    console_view_->ActivateConsole([&]() {
        LoadTasks(command_type);
        PrintTaskList();

        console_view_->AddSimpleCommand(
                ConsoleCommandType::BACK_TO_PREVIOUS_MENU,
                resources::tasks_menu::kBackShortcut,
                resources::tasks_menu::kBackCommand,
                resources::tasks_menu::kBackInfo
        );

        console_view_->RunCommandInput();
        if (console_view_->IsTaskSet())
        {
            ShowTaskInfo(console_view_->GetActiveTaskIndex());
            return true;
        }
        else if (console_view_->IsCommandSet(ConsoleCommandType::BACK_TO_PREVIOUS_MENU))
        {
            return false;
        }

        console::PrintUndefinedActionMessage();
        return true;
    });
}

void ListTask::PrintTaskList()
{
    std::cout << resources::messages::kMyTasksList << std::endl;
    std::cout << resources::command_line::kLineSeparator << std::endl;

    if (task_items_.empty())
    {
        std::cout << resources::messages::kNoTasks;
        return;
    }

    for (int index = 0; index < task_items_.size(); ++index)
    {
        std::string taskIndex = std::to_string(index + 1);
        std::cout
                << resources::command_line::kLeftBrace
                << std::to_string(index + 1)
                << resources::command_line::kRightBrace
                << task_items_[index].description().value()
                << std::endl;

        auto task_view_command
            = std::make_shared<TCLAP::SwitchArg>(
                    taskIndex,
                    resources::tasks_menu::kTaskNumberCommand + taskIndex,
                    resources::tasks_menu::kTaskNumberInfo + taskIndex,
                    false
                );

        console_view_->AddTaskViewCommand(task_view_command);
    }
}

void ListTask::ShowTaskInfo(int active_task_number)
{
    auto & taskItem = task_items_[active_task_number];
    console::PrintTaskDescription(taskItem);

    console_view_->ActivateConsole([&]() {
        console_view_->AddSimpleCommand(
            ConsoleCommandType::BACK_TO_PREVIOUS_MENU,
            resources::tasks_menu::kBackShortcut,
            resources::tasks_menu::kBackCommand,
            resources::tasks_menu::kBackInfo
        );

        console_view_->RunCommandInput();
        if (console_view_->IsCommandSet(ConsoleCommandType::BACK_TO_PREVIOUS_MENU))
            return false;

        console::PrintUndefinedActionMessage();
        return true;
    });
}

} // namespace todolist
} // namespace examples
} // namespace spine

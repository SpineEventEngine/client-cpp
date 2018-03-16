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
#include "create_task_label.h"
#include "command_handler/command_handler.h"

#include "resources/resources.h"

namespace spine {
namespace examples {
namespace todolist {

CreateTask::CreateTask(
    std::shared_ptr<ConsoleView> console_view,
    std::shared_ptr<CommandHandler> command_handler
)
    : BaseTask(console_view, command_handler)
{
    wizard_id_.reset(TaskCreationId::default_instance().New());
    std::string task_id = GenerateUniqueId();
    wizard_id_->set_value(std::move(task_id));

    task_id_.reset(TaskId::default_instance().New());
    std::string unique_task_id = GenerateUniqueId();
    task_id_->set_value(unique_task_id);

    task_priority_ = TaskPriority::TP_UNDEFINED;
    task_details_is_already_set = false;
}

void CreateTask::RunTaskCreation()
{
    StartTaskCreationProcess();
    console_view_->ActivateConsole([&]() {
        std::cout << resources::messages::CREATE_TASK_MENU << std::endl;
        std::cout << resources::command_line::LINE_SEPARATOR << std::endl;

        InitializeCommands();
        MenuResult menu_result = ProcessCommand();
        return ConvertMenuResultTooBool(menu_result);
    });
}

void CreateTask::StartTaskCreationProcess()
{
    StartTaskCreation start_task_creation;
    start_task_creation.set_allocated_id(wizard_id_.get());
    start_task_creation.set_allocated_task_id(task_id_.get());

    command_handler_->PostCommand(start_task_creation);
    start_task_creation.release_id();
    start_task_creation.release_task_id();
}

void CreateTask::InitializeCommands()
{
    console_view_->AddSimpleCommand(
            ConsoleCommandType::ADD_DESCRIPTION,
            resources::tasks_menu::DESCRIPTION_SHORTCUT,
            resources::tasks_menu::DESCRIPTION_COMMAND,
            resources::tasks_menu::DESCRIPTION_INFO
    );

    console_view_->AddSimpleCommand(
            ConsoleCommandType::ADD_PRIORITY,
            resources::tasks_menu::PRIORITY_SHORTCUT,
            resources::tasks_menu::PRIORITY_COMMAND,
            resources::tasks_menu::PRIORITY_INFO
    );

    console_view_->AddSimpleCommand(
            ConsoleCommandType::NEXT_STAGE,
            resources::tasks_menu::NEXT_STAGE_SHORTCUT,
            resources::tasks_menu::NEXT_STAGE_COMMAND,
            resources::tasks_menu::NEXT_STAGE_INFO
    );

    console_view_->AddSimpleCommand(
            ConsoleCommandType::CANCEL_TASK,
            resources::tasks_menu::CANCEL_SHORTCUT,
            resources::tasks_menu::CANCEL_COMMAND,
            resources::tasks_menu::CANCEL_INFO
    );

    console_view_->AddSimpleCommand(
            ConsoleCommandType::BACK_TO_PREVIOUS_MENU,
            resources::tasks_menu::BACK_SHORTCUT,
            resources::tasks_menu::BACK_COMMAND,
            resources::tasks_menu::BACK_INFO
    );
}

MenuResult CreateTask::ProcessCommand()
{
    console_view_->RunCommandInput();

    switch (console_view_->GetActiveTask())
    {
        case ConsoleCommandType::ADD_DESCRIPTION:
        {
            AddDescription();
            break;
        }
        case ConsoleCommandType::ADD_PRIORITY:
        {
            AddPriority();
            break;
        }
        case ConsoleCommandType::CANCEL_TASK:
        {
            CancelTask();
            return MenuResult::FINISH_MENU;
        }
        case ConsoleCommandType::NEXT_STAGE:
            return MoveToNextStage();
        case ConsoleCommandType::BACK_TO_PREVIOUS_MENU:
            return MenuResult::BACK_TO_PREVIOUS_MENU;
        default:
            return MenuResult::REPEAT_MENU;
    }
    return MenuResult::REPEAT_MENU;
}

void CreateTask::AddDescription()
{
    std::cout << resources::messages::PLEASE_ENTER_THE_TASK_MENU;
    std::string previous_description = task_description_;
    task_description_.clear();
    std::getline(std::cin, task_description_);
    UpdateDescription(previous_description);
    std::cout << resources::messages::TASK_DESCRIPTION_UPDATED;
}

void CreateTask::UpdateDescription(const std::string &previous_description)
{
    if (!task_details_is_already_set)
        return;

    UpdateTaskDescription update_task_description;
    change::StringChange * string_change = change::StringChange::default_instance().New();
    string_change->set_new_value(task_description_);
    string_change->set_previous_value(previous_description);
    update_task_description.set_allocated_description_change(string_change);
    update_task_description.set_allocated_id(task_id_.get());
    command_handler_->PostCommand(update_task_description);
    update_task_description.release_id();
}

void CreateTask::AddPriority()
{
    TaskPriority previous_task_priority = task_priority_;
    task_priority_ = GenerateTaskPriority();
    UpdatePriority(previous_task_priority);
    std::cout << resources::messages::TASK_PRIORITY_UPDATED;
}

void CreateTask::UpdatePriority(TaskPriority previous_task_priority)
{
    if (!task_details_is_already_set)
        return;

    UpdateTaskPriority update_task_priority;
    PriorityChange * priority_change = PriorityChange::default_instance().New();
    priority_change->set_new_value(task_priority_);
    priority_change->set_previous_value(previous_task_priority);
    update_task_priority.set_allocated_priority_change(priority_change);
    update_task_priority.set_allocated_id(task_id_.get());
    command_handler_->PostCommand(update_task_priority);
    update_task_priority.release_id();
}

void CreateTask::CancelTask()
{
    CancelTaskCreation cancel_task_creation;
    cancel_task_creation.set_allocated_id(wizard_id_.get());
    command_handler_->PostCommand(cancel_task_creation);
    cancel_task_creation.release_id();
}

MenuResult CreateTask::MoveToNextStage()
{
    if (task_description_.empty())
    {
        std::cout << resources::messages::TASK_DESCRIPTION_IS_EMPTY;
        return MenuResult::REPEAT_MENU;
    }

    TaskDescription *task_description = TaskDescription::default_instance().New();
    task_description->set_value(task_description_);

    SetTaskDetails task_details;
    task_details.set_allocated_id(wizard_id_.get());
    task_details.set_priority(task_priority_);
    task_details.set_allocated_description(task_description);

    command_handler_->PostCommand(task_details);
    task_details.release_id();
    task_details_is_already_set = true;
    return AssignTaskLabel();
}

MenuResult CreateTask::AssignTaskLabel()
{
    CreateTaskLabel create_task_label(console_view_, command_handler_, wizard_id_.get());
    return (create_task_label.AddTaskLabels() == MenuResult::BACK_TO_PREVIOUS_MENU) ?
           MenuResult::REPEAT_MENU : MenuResult::FINISH_MENU;
}

} // namespace todolist
} // namespace examples
} // namespace spine

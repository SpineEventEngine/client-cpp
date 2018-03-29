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
#include "create_task_label.h"
#include "task_completer.h"
#include "console_view/console_writer.h"
#include "command_handler/command_handler_impl.h"
#include "resources/resources.h"

namespace spine {
namespace examples {
namespace todolist {

constexpr int MIN_TASK_NUMBER = 1;

CreateTaskLabel::CreateTaskLabel(
    std::shared_ptr<ConsoleView> console_view,
    std::shared_ptr<CommandHandler> command_handler,
    std::shared_ptr<TaskCreationId> wizard_id
)
    : TodoTask(console_view, command_handler)
    , wizard_id_(wizard_id)
{
}

MenuResult CreateTaskLabel::AddTaskLabels()
{
    AddLabels add_labels_command;
    add_labels_command.set_allocated_id(wizard_id_.get());
    MenuResult menu_result = MenuResult ::UNKNOWN;
    console_view_->ActivateConsole([&]() {
        std::cout << resources::messages::kTaskLabelMenu << std::endl;
        std::cout << resources::command_line::kLineSeparator << std::endl;

        PrintAssignedLabels(console::PrintTaskLabelInfoForDescription);
        InitializeCommands();

        menu_result = ProcessCommand(&add_labels_command);
        return ConvertMenuResultTooBool(menu_result);
    });

    add_labels_command.release_id();

    return menu_result;
}

void CreateTaskLabel::InitializeCommands()
{
    console_view_->AddSimpleCommand(
        ConsoleCommandType::ASSIGN_NEW_LABEL,
        resources::tasks_menu::kNewLabelShortcut,
        resources::tasks_menu::kNewLabelCommand,
        resources::tasks_menu::kNewLabelInfo
    );
    console_view_->AddSimpleCommand(
        ConsoleCommandType::ASSIGN_EXISTING_LABEL,
        resources::tasks_menu::kExistingLabelShortcut,
        resources::tasks_menu::kExistingLabelCommand,
        resources::tasks_menu::kExistingLabelInfo
    );
    console_view_->AddSimpleCommand(
        ConsoleCommandType::REMOVE_LABEL,
        resources::tasks_menu::kRemoveLabelShortcut,
        resources::tasks_menu::kRemoveLabelCommand,
        resources::tasks_menu::kRemoveLabelInfo
    );
    console_view_->AddSimpleCommand(
        ConsoleCommandType::NEXT_STAGE,
        resources::tasks_menu::kNextStageShortcut,
        resources::tasks_menu::kNextStageCommand,
        resources::tasks_menu::kNextStageInfo
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

MenuResult CreateTaskLabel::ProcessCommand(AddLabels *add_labels_command)
{
    console_view_->RunCommandInput();
    switch (console_view_->GetActiveTask()) {
        case ConsoleCommandType::ASSIGN_NEW_LABEL:
        {
            AssignNewLabel(add_labels_command);
            break;
        }
        case ConsoleCommandType::ASSIGN_EXISTING_LABEL:
        {
            AssignExistingLabel(add_labels_command);
            break;
        }
        case ConsoleCommandType::REMOVE_LABEL:
        {
            RemoveTaskLabel(add_labels_command);
            break;
        }
        case ConsoleCommandType::NEXT_STAGE:
        {
            return FinishLabelAssignment(add_labels_command);
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
    return MenuResult::REPEAT_MENU;
}

void CreateTaskLabel::CancelTask()
{
    CancelTaskCreation cancel_task_creation;
    cancel_task_creation.set_allocated_id(wizard_id_.get());
    command_handler_->PostCommand(cancel_task_creation);
    cancel_task_creation.release_id();
}

void CreateTaskLabel::AssignNewLabel(AddLabels *add_labels_command)
{
    std::cout << resources::messages::kPleaseEnterTheTaskLabel << std::endl;
    std::string label_title;
    std::getline(std::cin, label_title);
    LabelDetails * label_details = add_labels_command->add_new_labels();
    label_details->set_title(label_title);

    LabelColor label_color = GenerateLabelColor();
    label_details->set_color(label_color);

    new_labels_.push_back(label_details);
}


void CreateTaskLabel::AssignExistingLabel(AddLabels *add_labels_command)
{
    auto task_labels = command_handler_->GetLabels();
    std::cout << resources::messages::kExistingLabels;
    if (task_labels.empty())
    {
        std::cout << resources::messages::kNoExistingLabels;
        return;
    }

    for (int i = 0; i < task_labels.size(); ++i)
    {
        std::shared_ptr<TaskLabel> label = task_labels[i];
        console::PrintTaskLabelInfoForMenu(
                std::to_string(i + MIN_TASK_NUMBER),
                label->title(),
                LabelColorToString(label->color())
        );
    }

    while (true)
    {
        std::cout << resources::messages::kPleaseChooseTheLabelNumber;
        int label_number = 0;
        std::cin >> label_number;
        std::cin.ignore();
        if (MIN_TASK_NUMBER <= label_number && label_number <= task_labels.size())
        {
            auto * existing_label = add_labels_command->add_existing_labels();
            std::shared_ptr<TaskLabel> task_label = task_labels[label_number - MIN_TASK_NUMBER];
            if(existing_labels_filter_.find(task_label) == existing_labels_filter_.end())
            {
                existing_label->set_value(task_label->id().value());
                existing_labels_.push_back(task_label);
                existing_labels_filter_.insert(task_label);
            } else
            {
                std::cout << resources::messages::kLabelHasAlreadyBeenSetToThisTask;
            }

            return;
        }
        else
        {
            std::cout << resources::messages::kLabelNumberIsIncorrect;
        }
    }
}

void CreateTaskLabel::RemoveTaskLabel(AddLabels *add_labels_command)
{
    if (NoAssignedLabels())
    {
        std::cout << resources::messages::kNoLabelsOnThisTask << std::endl;
        return;
    }

    PrintAssignedLabels(console::PrintTaskLabelInfoForMenu);
    unsigned long task_labels_count = existing_labels_.size() + new_labels_.size();

    while (true)
    {
        std::cout << resources::messages::kPleaseSelectNumberYouWantToRemove;
        int label_number;
        std::cin >> label_number;
        std::cin.ignore();
        if (MIN_TASK_NUMBER <= label_number && label_number <= task_labels_count)
        {
            --label_number;
            RemoveLabelFromList(add_labels_command, label_number);
            return;
        }
        else
        {
            std::cout << resources::messages::kLabelNumberIsIncorrect << std::endl;
        }
    }
}

void CreateTaskLabel::RemoveLabelFromList(AddLabels *add_labels_command, int label_number)
{
    if (label_number < new_labels_.size())
    {
        new_labels_.erase(new_labels_.begin() + label_number);
        UpdateNewLabels(add_labels_command);
    }
    else
    {
        label_number -= new_labels_.size();
        auto current_iterator = existing_labels_.begin() + label_number;
        existing_labels_filter_.erase(* current_iterator);
        existing_labels_.erase(current_iterator);
        UpdateExistingLabels(add_labels_command);
    }

    console::PrintLabelRemovedFromTaskMessage(std::to_string(++label_number));
}

void CreateTaskLabel::UpdateNewLabels(AddLabels *add_labels_command)
{
    add_labels_command->clear_new_labels();
    std::for_each(new_labels_.begin(), new_labels_.end(), [&](LabelDetails * label_details)
    {
        LabelDetails * updated_label_details = add_labels_command->add_new_labels();
        updated_label_details->set_color(label_details->color());
        updated_label_details->set_title(label_details->title());
    });
}

void CreateTaskLabel::UpdateExistingLabels(AddLabels *add_labels_command)
{
    add_labels_command->clear_existing_labels();
    std::for_each(existing_labels_.begin(), existing_labels_.end(), [&](std::shared_ptr<TaskLabel> task_label)
    {
        LabelId * updated_task_label = add_labels_command->add_existing_labels();
        updated_task_label->set_value(task_label->id().value());
    });
}

MenuResult CreateTaskLabel::FinishLabelAssignment(AddLabels *add_labels_command)
{
    command_handler_->PostCommand(*add_labels_command);
    TaskCompleter task_completer(console_view_, command_handler_, wizard_id_);
    MenuResult menu_result = task_completer.RunCompleteMenu();
    return (menu_result == MenuResult::BACK_TO_PREVIOUS_MENU) ?
           MenuResult::REPEAT_MENU : MenuResult::FINISH_MENU;
}

void CreateTaskLabel::PrintAssignedLabels(PrintCallback callback)
{
    std::cout << resources::messages::kAssignedLabels;
    if (NoAssignedLabels())
    {
        std::cout << resources::messages::kNoAssignedLabels << std::endl;
        return;
    }
    unsigned int label_index = 0;
    for (int i = 0; i < new_labels_.size();++i)
    {
        ++label_index;
        LabelDetails * label_detail = new_labels_[i];
        callback(
            std::to_string(label_index),
            label_detail->title(),
            LabelColorToString(label_detail->color())
        );
    }

    for (int i = 0; i < existing_labels_.size(); ++i)
    {
        ++label_index;
        std::shared_ptr<TaskLabel> task_label = existing_labels_[i];
        callback(
            std::to_string(label_index),
            task_label->title(),
            LabelColorToString(task_label->color()));
    }
}

bool CreateTaskLabel::NoAssignedLabels()
{
    return new_labels_.empty() && existing_labels_.empty();
}

} // namespace todolist
} // namespace examples
} // namespace spine
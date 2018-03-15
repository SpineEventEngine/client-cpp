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

#include "task_manager.h"
#include "task_completer.h"
#include "console_view/console_writer.h"
#include "console_view/console_view_impl.h"
#include "command_handler/command_handler_impl.h"
#include "resources/resources.h"

namespace spine {
namespace examples {
namespace todolist {

TaskCompleter::TaskCompleter(
    std::shared_ptr<ConsoleView> console_view,
    std::shared_ptr<CommandHandler> command_handler,
    TaskCreationId * wizard_id
)
    : BaseTask(console_view, command_handler)
    , wizard_id_(wizard_id)
{
}

MenuResult TaskCompleter::run_complete_menu()
{
    MenuResult menu_result = MenuResult ::UNKNOWN;
    console_view_->activate_console([&]()
    {
        std::cout << resources::messages::TASK_COMPLETION_MENU << std::endl;
        std::cout << resources::command_line::LINE_SEPARATOR << std::endl;

        initialize_commands();
        menu_result = process_command();
        return convert_menu_result_too_bool(menu_result);
    });

    return menu_result;
}

void TaskCompleter::initialize_commands()
{
    console_view_->add_simple_command(
        ConsoleCommandType::FINISH_TASK,
        resources::tasks_menu::FINISH_TASK_SHORTCUT,
        resources::tasks_menu::FINISH_TASK_COMMAND,
        resources::tasks_menu::FINSH_TASK_INFO
    );

    console_view_->add_simple_command(
        ConsoleCommandType::CANCEL_TASK,
        resources::tasks_menu::CANCEL_SHORTCUT,
        resources::tasks_menu::CANCEL_COMMAND,
        resources::tasks_menu::CANCEL_INFO
    );

    console_view_->add_simple_command(
        ConsoleCommandType::BACK_TO_PREVIOUS_MENU,
        resources::tasks_menu::BACK_SHORTCUT,
        resources::tasks_menu::BACK_COMMAND,
        resources::tasks_menu::BACK_INFO
    );
}

MenuResult TaskCompleter::process_command()
{
    console_view_->run_command_input();
    switch (console_view_->get_active_task())
    {
        case ConsoleCommandType::FINISH_TASK:
        {
            finish_task();
            return MenuResult::FINISH_MENU;
        }
        case ConsoleCommandType::CANCEL_TASK:
        {
            cancel_task();
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

void TaskCompleter::finish_task()
{
    CompleteTaskCreation complete_task_creation;
    complete_task_creation.set_allocated_id(wizard_id_);
    command_handler_->post_command(complete_task_creation);
}

void TaskCompleter::cancel_task()
{
    CancelTaskCreation cancel_task_creation;
    cancel_task_creation.set_allocated_id(wizard_id_);
    command_handler_->post_command(cancel_task_creation);
}

} // namespace todolist
} // namespace examples
} // namespace spine
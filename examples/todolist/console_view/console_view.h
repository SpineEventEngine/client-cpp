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

#ifndef TODOLIST_CONSOLE_VIEW
#define TODOLIST_CONSOLE_VIEW

#include "tclap/SwitchArg.h"

#include <functional>
#include <memory>

namespace spine {
namespace examples {
namespace todolist {

enum ConsoleCommandType
{
    CREATE_TASK,
    LIST_TASK,
    VIEW_TASK,
    ADD_DESCRIPTION,
    ADD_PRIORITY,
    ASSIGN_TASK_LABEL,
    ASSIGN_EXISTING_LABEL,
    ASSIGN_NEW_LABEL,
    REMOVE_LABEL,
    FINISH_LABEL_ASSIGNMENT,
    FINISH_TASK,
    CANCEL_TASK,
    NEXT_STAGE,
    BACK_TO_PREVIOUS_MENU,
    DRAFT_TASKS,
    COMPLETED_TASKS,
    ALL_TASKS = (DRAFT_TASKS | COMPLETED_TASKS) << 1,
    QUIT_PROGRAM,
    UNKNOWN
};

class ConsoleView
{
public:

    virtual ~ConsoleView() {}

    virtual void AddSimpleCommand(
        ConsoleCommandType command_type,
        std::string const &command_shortcut,
        std::string const &command_name,
        std::string const &command_description) = 0;

    virtual void AddTaskViewCommand(std::shared_ptr<TCLAP::SwitchArg> command_args) = 0;
    virtual void RunCommandInput() = 0;
    virtual void ActivateConsole(std::function<bool()> callback) = 0;
    virtual void ResetTasks() = 0;

    virtual ConsoleCommandType GetActiveTask() = 0;

    virtual bool IsCommandSet(ConsoleCommandType command_type) = 0;
    virtual bool IsTaskSet() const = 0;

    virtual int GetActiveTaskIndex() const = 0;
};

} // namespace todolist
} // namespace examples
} // namespace spine

#endif // TODOLIST_CONSOLE_VIEW_IMPL_H

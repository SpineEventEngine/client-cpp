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

#ifndef TODOLIST_MAIN_TASK_H
#define TODOLIST_MAIN_TASK_H

#include <string>
#include <memory>
#include "base_task.h"

namespace spine {
namespace examples {
namespace todolist {

class ConsoleView;
class CommandHandler;

class MainTask : public BaseTask
{
public:
    MainTask(
        std::shared_ptr<ConsoleView> console_view,
        std::shared_ptr<CommandHandler> command_handler);

public:
    void StartMenu();

protected:
    void InitializeCommands() override;

private:
    void AddBasicTask();
    void StartWizardTaskCreation();
    void ListTasks() const;

    bool ProcessCommand();
};

} // namespace todolist
} // namespace examples
} // namespace spine

#endif // TODOLIST_MAIN_TASK_H

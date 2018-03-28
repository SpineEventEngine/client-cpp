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

#ifndef TODOLIST_BASE_TASK_H
#define TODOLIST_BASE_TASK_H

#include <memory>
#include <string>

#include "todolist/model.pb.h"
#include "todolist/c/commands.pb.h"

#include "console_view/console_view_impl.h"

namespace spine {
namespace examples {
namespace todolist {

class ConsoleView;
class CommandHandler;

enum class MenuResult {
    REPEAT_MENU,
    FINISH_MENU,
    BACK_TO_PREVIOUS_MENU,
    UNKNOWN
};

class BaseTask //TODO BaseTask -> Task. Or SpineTask, or TODoTask
{
public:
    //TODO task knows too much about the UI. Try to design this as MVC, with a good separation for M,V,and C
    //TODO your tasks are actions, but do much with the ui. you need to make task creation as a separate process, sending commands
    // a separate process. UI update a separate process.
    //You should have a model classes for a task, and a processor in it or a separate, that would do some actions.
    // You can use protobuf classes for a model
    BaseTask(
        std::shared_ptr<ConsoleView> console_view, //TODO const std::shared_ptr<T>&
        std::shared_ptr<CommandHandler> command_handler);

    static TaskPriority GenerateTaskPriority();
    static LabelColor GenerateLabelColor();

    static std::string GenerateUniqueId();
    static std::string LabelColorToString(LabelColor label_color);

protected:
    virtual void InitializeCommands() = 0;

    bool ConvertMenuResultTooBool(MenuResult result) const;

protected:
    std::shared_ptr<ConsoleView> console_view_;
    std::shared_ptr<CommandHandler> command_handler_;
};

} // namespace todolist
} // namespace examples
} // namespace spine

#endif // TODOLIST_BASE_TASK_H

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

#ifndef TODOLIST_CONSOLE_VIEW_IMPL_H
#define TODOLIST_CONSOLE_VIEW_IMPL_H

#include "console_view.h"
#include "tclap/CmdLine.h"

#include <vector>
#include <memory>
#include <unordered_map>
#include <utility>
#include <map>

namespace spine {
namespace examples {
namespace todolist {

//TODO general. const std::string& <- put & to type, not variable names. you have different styles accross source code
class ConsoleViewImpl: public ConsoleView
{
public:
    ConsoleViewImpl(std::string const & path_to_exec_file);

public:
    void AddSimpleCommand(
        ConsoleCommandType command_type,
        const std::string & command_shortcut,
        const std::string & command_name,
        const std::string & command_description) override final;

    void AddTaskViewCommand(std::shared_ptr<TCLAP::SwitchArg> command_args) override final;
    void RunCommandInput() override final;
    void ResetTasks() override final;
    void ActivateConsole(std::function<bool()> callback) override final;

    ConsoleCommandType GetActiveTask() override final;

    bool IsTaskSet() const override final;
    bool IsCommandSet(ConsoleCommandType command_type) override final;

    int GetActiveTaskIndex() const override final;

private:
    std::unique_ptr<TCLAP::CmdLine> command_handler_;
    std::map<ConsoleCommandType, std::shared_ptr<TCLAP::SwitchArg> > commands_;
    std::vector<std::shared_ptr<TCLAP::SwitchArg>> task_commands_;

    const std::string path_to_exec_file_;
};

} // namespace todolist
} // namespace examples
} // namespace spine

#endif // TODOLIST_CONSOLE_VIEW_IMPL_H

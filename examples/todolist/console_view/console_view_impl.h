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


class ConsoleViewImpl: public ConsoleView
{
public:
	ConsoleViewImpl(std::string const & path_to_exec_file);

public:
	void add_simple_command(
		ConsoleCommandType command_type,
		std::string const & command_shortcut,
		std::string const & command_name,
		std::string const & command_description) override final;

	void add_task_view_command(std::shared_ptr<TCLAP::SwitchArg> command_args) override final;
	void run_command_input() override final;
	void reset_tasks() override final;
	void activate_console(std::function<bool()> callback) override final;

	ConsoleCommandType get_active_task() override final;

	bool is_task_set() const override final;
	bool is_command_set(ConsoleCommandType command_type) override final;

	int get_active_task_index() const override final;

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

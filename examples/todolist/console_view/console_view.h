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

enum class ConsoleCommandType
{
	CREATE_TASK,
	LIST_TASK,
	VIEW_TASK,
	BACK_TO_PREVIOUS_MENU,
	QUIT_PROGRAM
};

class ConsoleView
{
public:

	virtual ~ConsoleView() {}

	virtual void add_simple_command(ConsoleCommandType command_type, std::shared_ptr<TCLAP::SwitchArg> command_args) = 0;
	virtual void add_task_view_command(std::shared_ptr<TCLAP::SwitchArg> command_args) = 0;
	virtual void run_command_input() = 0;
	virtual void activate_console(std::function<bool()> callback) = 0;
	virtual void reset_tasks() = 0;

	virtual bool is_command_set(ConsoleCommandType command_type) = 0;
	virtual bool is_task_set() const = 0;
	
	virtual int get_active_task_index() const = 0;
};

} // namespace todolist
} // namespace examples
} // namespace spine

#endif // TODOLIST_CONSOLE_VIEW_IMPL_H

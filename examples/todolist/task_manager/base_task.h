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

enum class TaskCreationResult {
	REPEAT_MENU,
	FINISH_MENU,
	BACK_TO_PREVIOUS_MENU,
	UNKNOWN
};

class BaseTask
{
public:
	BaseTask(
		std::shared_ptr<ConsoleView> console_view,
		std::shared_ptr<CommandHandler> command_handler);

	static TaskPriority generate_task_priority();
	static LabelColor generate_label_color();

	static std::string generate_unique_id();
	static std::string label_color_to_string(LabelColor label_color);

protected:
	bool task_creation_result_to_bool(TaskCreationResult result) const;

protected:
	std::shared_ptr<ConsoleView> console_view_;
	std::shared_ptr<CommandHandler> command_handler_;
};

} // namespace todolist
} // namespace examples
} // namespace spine

#endif // TODOLIST_BASE_TASK_H

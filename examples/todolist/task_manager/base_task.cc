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

#include "base_task.h"
#include "command_handler/command_handler_impl.h"
#include "resources/resources.h"

namespace spine {
namespace examples {
namespace todolist {

BaseTask::BaseTask(
	std::shared_ptr<ConsoleView> console_view,
	std::shared_ptr<CommandHandler> command_handler
)
	: console_view_(console_view)
	, command_handler_(command_handler)
{
}

bool BaseTask::task_creation_result_to_bool(TaskCreationResult result) const
{
	switch (result)
	{
		case TaskCreationResult::REPEAT_MENU:
			return true;
		case TaskCreationResult::FINISH_MENU:
		case TaskCreationResult::BACK_TO_PREVIOUS_MENU:
			return false;

		default:
			assert(false);
	}
}

TaskPriority BaseTask::generate_task_priority()
{
	std::cout << resources::messages::PLEASE_ENTER_THE_TASK_PRIORITY;
	while (true)
	{
		std::cout << resources::messages::TASK_PRIORITY_VALUES;
		int task_priority;
		std::cin >> task_priority;
		std::cin.ignore();
		if (TaskPriority::HIGH <= task_priority <= TaskPriority::LOW)
			return static_cast<TaskPriority>(task_priority);
		else
			std::cout << resources::messages::TASK_PRIORITY_VALUE_IS_INCORRECT;
	}
}

LabelColor BaseTask::generate_label_color()
{
	std::cout << resources::messages::PLEASE_ENTER_THE_LABEL_COLOR;
	while (true)
	{
		std::cout << resources::messages::LABEL_VALUES;

		int label_color = 0;
		std::cin >> label_color;
		std::cin.ignore();
		if (LabelColor::RED <= label_color <= LabelColor::GRAY)
			return static_cast<LabelColor>(label_color);
		else
			std::cout << resources::messages::LABEL_COLOR_IS_INCORRECT;
	}
}

std::string BaseTask::label_color_to_string(LabelColor label_color)
{
	switch (label_color)
	{
		case LabelColor::BLUE:
			return std::string("BLUE");
		case LabelColor::RED:
			return std::string("RED");
		case LabelColor::GRAY:
			return std::string("GRAY");
		case LabelColor::GREEN:
			return std::string("GREEN");
		default:
			assert(false);
	}
}

std::string BaseTask::generate_unique_id()
{
	Poco::UUIDGenerator generator;
	return generator.createRandom().toString();
}

} // namespace todolist
} // namespace examples
} // namespace spine
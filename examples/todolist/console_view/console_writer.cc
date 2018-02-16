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

#include "console_writer.h"
#include <iostream>

namespace spine {
namespace examples {
namespace todolist {

void ConsoleWriter::print_main_menu_help()
{
	std::cout << "----------------" << std::endl;
	std::cout
		<< "(c) Create a task.\n"
		<< "(l) List tasks.\n"
		<< "(q) Quit.\n";

	std::cout << "----------------" << std::endl;
}

void ConsoleWriter::print_back_option()
{
	std::cout << "(b) " << "Back." << std::endl;
	std::cout << "----------------" << std::endl;
}

void ConsoleWriter::print_task_description(TaskItem & task_item)
{
	std::cout << "My task details:\n";
	std::cout << "----------------" << std::endl;

	std::cout << "Description: " << task_item.description().value() << std::endl;
	std::cout << "Priority: " << TaskPriority_Name(task_item.priority()) << std::endl;
	std::cout << "Due date: " << "default" << std::endl;
}

void ConsoleWriter::print_undefined_action_message()
{
	std::cout << "There is no action with specified shortcut or argument is invalid.\n";
}

void ConsoleWriter::print_select_an_action_prompt()
{
	std::cout << "Select an action (?)" << std::endl;
}

} // namespace todolist
} // namespace examples
} // namespace spine

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

#ifndef TODOLIST_CONSOLE_WRITER_H
#define TODOLIST_CONSOLE_WRITER_H

#include "todolist/model.pb.h"
#include "todolist/q/projections.pb.h"
#include "todolist/attributes.pb.h"

namespace spine {
namespace examples {
namespace todolist {

class ConsoleWriter
{
public:
	static void print_task_description(TaskItem & task_item);
	static void print_undefined_action_message();
	static void print_select_an_action_prompt();

	static void print_existing_task_label_info(
		const std::string & index,
		const std::string & title,
		const std::string & color
	);

	static void print_label_removed_from_task_message(
		const std::string & label_number
	);

	static void print_label_number(const std::string & label_number);

	static void print_label_info(
		const std::string & label_title,
		const std::string & label_color
	);
};

} // namespace todolist
} // namespace examples
} // namespace spine

#endif // TODOLIST_CONSOLE_WRITER_H
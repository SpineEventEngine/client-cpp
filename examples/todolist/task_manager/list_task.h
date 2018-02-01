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

#ifndef TODOLIST_LIST_TASK_H
#define TODOLIST_LIST_TASK_H

#include "todolist/q/projections.pb.h"
#include "todolist/attributes.pb.h"
#include "tclap/CmdLine.h"

#include <memory>
#include <functional>

class ConsoleView;
class CommandHandler;

class ListTask
{

public:

	void load_task_menu();

	ListTask(
			std::shared_ptr<ConsoleView> console_view
		,	std::shared_ptr<CommandHandler> command_handler
	);

private:

	void show_task_info(int taskId);
	void load_tasks();
	void add_back_task();

private:

	std::vector<spine::examples::todolist::TaskItem> task_items_;

	std::shared_ptr<ConsoleView> console_view_;
	std::shared_ptr<CommandHandler> command_handler_;
};

#endif // TODOLIST_LIST_TASK_H
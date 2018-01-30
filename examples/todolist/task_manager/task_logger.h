#pragma once

#include "todolist/model.pb.h"

class TaskLogger
{

public:

	static void print_main_menu_help();
	static void print_back_option();
	static void print_task_description(spine::examples::todolist::TaskItem & task_item);
	static void print_undefined_action_message();
	static void print_select_an_action_prompt();

};
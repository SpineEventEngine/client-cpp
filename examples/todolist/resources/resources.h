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

#ifndef TODOLIST_RESOURCES_H
#define TODOLIST_RESOURCES_H

namespace spine {
namespace examples {
namespace todolist {
namespace resources {

namespace tasks_menu {
	constexpr char * DESCRIPTION_SHORTCUT = "d";
	constexpr char * DESCRIPTION_COMMAND = "Description";
	constexpr char * DESCRIPTION_INFO = "Add/Edit description";

	constexpr char * PRIORITY_SHORTCUT = "p";
	constexpr char * PRIORITY_COMMAND = "Priority";
	constexpr char * PRIORITY_INFO = "Add/Edit Priority";

	constexpr char * NEXT_STAGE_SHORTCUT = "n";
	constexpr char * NEXT_STAGE_COMMAND = "next_stage";
	constexpr char * NEXT_STAGE_INFO = "Next stage";

	constexpr char * CANCEL_SHORTCUT = "c";
	constexpr char * CANCEL_COMMAND = "Cancel";
	constexpr char * CANCEL_INFO = "Cancel Task";

	constexpr char * BACK_SHORTCUT = "b";
	constexpr char * BACK_COMMAND = "Back";
	constexpr char * BACK_INFO = "Go to previous menu";

	constexpr char * NEW_LABEL_SHORTCUT = "a";
	constexpr char * NEW_LABEL_COMMAND = "assign_new_label";
	constexpr char * NEW_LABEL_INFO = "Assign new label";

	constexpr char * EXISTING_LABEL_SHORTCUT = "e";
	constexpr char * EXISTING_LABEL_COMMAND = "assign_existing_label";
	constexpr char * EXISTING_LABEL_INFO = "Assign existing label";

	constexpr char * REMOVE_LABEL_SHORTCUT = "r";
	constexpr char * REMOVE_LABEL_COMMAND = "remove_label";
	constexpr char * REMOVE_LABEL_INFO = "Remove label from task";

	constexpr char * DRAFT_TASK_SHORTCUT = "d";
	constexpr char * DRAFT_TASK_COMMAND = "draft_tasks";
	constexpr char * DRAFT_TASK_INFO = "Draft Tasks";

	constexpr char * COMPLETED_TASK_SHORTCUT = "c";
	constexpr char * COMPLETED_TASK_COMMAND = "completed_tasks";
	constexpr char * COMPLETED_TASK_INFO = "Completed Tasks";

	constexpr char * ALL_TASKS_SHORTCUT = "c";
	constexpr char * ALL_TASKS_COMMAND = "completed_tasks";
	constexpr char * ALL_TASKS_INFO = "Completed Tasks";

	constexpr char * FINISH_TASK_SHORTCUT = "f";
	constexpr char * FINISH_TASK_COMMAND = "finish_task";
	constexpr char * FINSH_TASK_INFO = "Finish task";

	constexpr char * CREATE_TASK_SHORTCUT = "c";
	constexpr char * CREATE_TASK_COMMAND = "create_task";
	constexpr char * CREATE_TASK_INFO = "Create a task";

	constexpr char * LIST_TASK_SHORTCUT = "l";
	constexpr char * LIST_TASK_COMMAND = "list_tasks";
	constexpr char * LIST_TASK_INFO = "List tasks";

	constexpr char * QUIT_TASK_SHORTCUT = "q";
	constexpr char * QUIT_TASK_COMMAND = "quit";
	constexpr char * QUIT_TASK_INFO = "Quit";

	constexpr char * TASK_NUMBER_COMMAND = "task_number";
	constexpr char * TASK_NUBMER_INFO = "Choose task";

} // namespace task_menu

namespace task_info {
	constexpr char * TITLE = "Title";
	constexpr char * COLOR = "Color";
	constexpr char * LABEL = "Label";
	constexpr char * TASK_DETAILS = "My task details:\n";
	constexpr char * TASK_DESCRIPTION = "Description";
	constexpr char * TASK_PRIORITY = "Priority";
	constexpr char * TASK_DUE_DATE = "Due date";
	constexpr char * DEFAULT = "default";

} // namespace task_info

namespace server_info {
	constexpr char * INVALID_SERVER_STATUS = "Invalid server status...";
	constexpr char * INVALID_SERVER_RESPONSE = "Invalid response....";

	constexpr char * USER_ID = "user";
	constexpr char * ZONE_ID = "UTC";

	constexpr char * CHANNEL = "localhost:50051";

} // namespace server_info

namespace command_line
{
	constexpr char * COMMAND_DESCRIPTION_MESSAGE = "Command description message";
	constexpr char * COMMAND_LINE_VERSION = "0.9";

	constexpr char * LEFT_BRACE = "(";
	constexpr char * RIGHT_BRACE = ")";
	constexpr char * LEFT_BRACKET = "[";
	constexpr char * RIGHT_BRACKET = "]";
	constexpr char * COLON = ":";
	constexpr char * DASH = "-";
	constexpr char * COMMA = ",";
	constexpr char * SHARP = "#";
	constexpr char * LINE_SEPARATOR = "----------------";

	char  WHITE_SPACE_DELIMETER = ' ';

} // namespace command_line

namespace messages {

	constexpr char * PLEASE_ENTER_THE_TASK_MENU = "Please enter the task description:\n";
	constexpr char * PLEASE_ENTER_THE_TASK_PRIORITY = "Please enter the task priority:\n";

	constexpr char * TASK_DESCRIPTION_UPDATED = "Task description updated.\n";
	constexpr char * TASK_PRIORITY_UPDATED = "Task priority updated.\n";
	constexpr char * TASK_DESCRIPTION_IS_EMPTY = "Task description is not add.\n Please add task description.\n";

	constexpr char * TASK_PRIORITY_VALUES = "(1) - HIGH\n (2) - NORMAL\n (3) - LOW\n";
	constexpr char * TASK_PRIORITY_VALUE_IS_INCORRECT = "The value is incorrect. Please choose the proper task priority.\n";

	constexpr char * PLEASE_ENTER_THE_TASK_LABEL = "Please enter the label title";
	constexpr char * PLEASE_ENTER_THE_LABEL_COLOR = "Please enter the label color:\n";
	constexpr char * LABEL_VALUES = "(1) - RED \n(2) - GREEN \n(3) - BLUE    \n(4) - GRAY   \n";
	constexpr char * LABEL_COLOR_IS_INCORRECT = "The value is incorrect. Please choose the label color.\n";
	constexpr char * LABEL_NUMBER_IS_INCORRECT = "The value is incorrect. Please choose the label number.\n";

	constexpr char * EXISTING_LABELS = "Existing labels :\n";
	constexpr char * NO_EXISTING_LABELS = "<No existing labels.>\n";

	constexpr char * ASSIGNED_LABELS = "Assigned labels:\n";
	constexpr char * NO_ASSIGNED_LABELS = "<No assigned labels>";
	constexpr char * PLEASE_CHOOSE_THE_LABEL_NUMBER = "Please choose a number of existing label:\n";

	constexpr char * NO_LABELS_ON_THIS_TASK = "You did not assign any label to this task.\n";
	constexpr char * PLEASE_SELECT_NUMBER_YOU_WANT_TO_REMOVE = "Please select label number you want to remove.\n";

	constexpr char * REMOVED_FROM_TASK = "removed from task.\n";

	constexpr char * MY_TASKS_LIST = "My tasks list:";
	constexpr char * NO_TASKS = "<no tasks>\n";

	constexpr char * TASK_COMPLETION_MENU = "Task completion menu";
	constexpr char * MAIN_MENU = "Main menu";

	constexpr char * CREATE_TASK_MENU = "Create task menu";
	constexpr char * TASK_LABEL_MENU = "Task Labels menu";

	constexpr char * NO_SPECIFIED_SHORTCUT = "There is no action with specified shortcut or argument is invalid.\n";
	constexpr char * SELECT_AN_ACTION = "Select an action (?)";

} // namespace messages
} // namespace resources
} // namespace todolist
} // namespace examples
} // namespace spine

#endif
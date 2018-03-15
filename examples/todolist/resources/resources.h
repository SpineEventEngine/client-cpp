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
    static const char * DESCRIPTION_SHORTCUT = "d";
    static const char * DESCRIPTION_COMMAND = "Description";
    static const char * DESCRIPTION_INFO = "Add/Edit description";

    static const char * PRIORITY_SHORTCUT = "p";
    static const char * PRIORITY_COMMAND = "Priority";
    static const char * PRIORITY_INFO = "Add/Edit Priority";

    static const char * NEXT_STAGE_SHORTCUT = "n";
    static const char * NEXT_STAGE_COMMAND = "next_stage";
    static const char * NEXT_STAGE_INFO = "Next stage";

    static const char * CANCEL_SHORTCUT = "c";
    static const char * CANCEL_COMMAND = "Cancel";
    static const char * CANCEL_INFO = "Cancel Task";

    static const char * BACK_SHORTCUT = "b";
    static const char * BACK_COMMAND = "Back";
    static const char * BACK_INFO = "Back to previous menu";

    static const char * NEW_LABEL_SHORTCUT = "a";
    static const char * NEW_LABEL_COMMAND = "assign_new_label";
    static const char * NEW_LABEL_INFO = "Assign new label";

    static const char * EXISTING_LABEL_SHORTCUT = "e";
    static const char * EXISTING_LABEL_COMMAND = "assign_existing_label";
    static const char * EXISTING_LABEL_INFO = "Assign existing label";

    static const char * REMOVE_LABEL_SHORTCUT = "r";
    static const char * REMOVE_LABEL_COMMAND = "remove_label";
    static const char * REMOVE_LABEL_INFO = "Remove label from task";

    static const char * DRAFT_TASK_SHORTCUT = "d";
    static const char * DRAFT_TASK_COMMAND = "draft_tasks";
    static const char * DRAFT_TASK_INFO = "Draft Tasks";

    static const char * COMPLETED_TASK_SHORTCUT = "c";
    static const char * COMPLETED_TASK_COMMAND = "completed_tasks";
    static const char * COMPLETED_TASK_INFO = "Completed Tasks";

    static const char * ALL_TASKS_SHORTCUT = "a";
    static const char * ALL_TASKS_COMMAND = "all_tasks";
    static const char * ALL_TASKS_INFO = "All Tasks";

    static const char * FINISH_TASK_SHORTCUT = "f";
    static const char * FINISH_TASK_COMMAND = "finish_task";
    static const char * FINSH_TASK_INFO = "Finish task";

    static const char * CREATE_TASK_SHORTCUT = "c";
    static const char * CREATE_TASK_COMMAND = "create_task";
    static const char * CREATE_TASK_INFO = "Create a task";

    static const char * LIST_TASK_SHORTCUT = "l";
    static const char * LIST_TASK_COMMAND = "list_tasks";
    static const char * LIST_TASK_INFO = "List tasks";

    static const char * QUIT_TASK_SHORTCUT = "q";
    static const char * QUIT_TASK_COMMAND = "quit";
    static const char * QUIT_TASK_INFO = "Quit";

    static const char * TASK_NUMBER_COMMAND = "task_number";
    static const char * TASK_NUBMER_INFO = "Choose task";

} // namespace task_menu

namespace task_info {
    static const char * TITLE = "Title";
    static const char * COLOR = "Color";
    static const char * LABEL = "Label";
    static const char * TASK_DETAILS = "My task details:\n";
    static const char * TASK_DESCRIPTION = "Description";
    static const char * TASK_PRIORITY = "Priority";
    static const char * TASK_DUE_DATE = "Due date";
    static const char * DEFAULT = "default";

} // namespace task_info

namespace server_info {
    static const char * INVALID_SERVER_STATUS = "Invalid server status...";
    static const char * INVALID_SERVER_RESPONSE = "Invalid response....";

    static const char * USER_ID = "user";
    static const char * ZONE_ID = "UTC";

    static const char * CHANNEL = "localhost:50051";

} // namespace server_info

namespace command_line
{
    static const char * COMMAND_DESCRIPTION_MESSAGE = "Command description message";
    static const char * COMMAND_LINE_VERSION = "0.9";

    static const char * LEFT_BRACE = "(";
    static const char * RIGHT_BRACE = ")";
    static const char * LEFT_BRACKET = "[";
    static const char * RIGHT_BRACKET = "]";
    static const char * COLON = ":";
    static const char * DASH = "-";
    static const char * COMMA = ",";
    static const char * SHARP = "#";
    static const char * LINE_SEPARATOR = "----------------";

    static const char  WHITE_SPACE_DELIMETER = ' ';

} // namespace command_line

namespace messages {

    static const char * PLEASE_ENTER_THE_TASK_MENU = "Please enter the task description:\n";
    static const char * PLEASE_ENTER_THE_TASK_PRIORITY = "Please enter the task priority:\n";

    static const char * TASK_DESCRIPTION_UPDATED = "Task description updated.\n";
    static const char * TASK_PRIORITY_UPDATED = "Task priority updated.\n";
    static const char * TASK_DESCRIPTION_IS_EMPTY = "Task description is not add.\nPlease add task description.\n";

    static const char * TASK_PRIORITY_VALUES = "(1) - HIGH\n(2) - NORMAL\n(3) - LOW\n";
    static const char * TASK_PRIORITY_VALUE_IS_INCORRECT = "The value is incorrect. Please choose the proper task priority.\n";

    static const char * PLEASE_ENTER_THE_TASK_LABEL = "Please enter the label title";
    static const char * PLEASE_ENTER_THE_LABEL_COLOR = "Please enter the label color:\n";
    static const char * LABEL_VALUES = "(1) - RED \n(2) - GREEN \n(3) - BLUE    \n(4) - GRAY   \n";
    static const char * LABEL_COLOR_IS_INCORRECT = "The value is incorrect. Please choose the label color.\n";
    static const char * LABEL_NUMBER_IS_INCORRECT = "The value is incorrect. Please choose the label number.\n";

    static const char * EXISTING_LABELS = "Existing labels :\n";
    static const char * NO_EXISTING_LABELS = "<No existing labels.>\n";

    static const char * ASSIGNED_LABELS = "Assigned labels:\n";
    static const char * NO_ASSIGNED_LABELS = "<No assigned labels>";
    static const char * PLEASE_CHOOSE_THE_LABEL_NUMBER = "Please choose a number of existing label:\n";

    static const char * NO_LABELS_ON_THIS_TASK = "You did not assign any label to this task.\n";
    static const char * PLEASE_SELECT_NUMBER_YOU_WANT_TO_REMOVE = "Please select label number you want to remove.\n";

    static const char * REMOVED_FROM_TASK = "removed from task.\n";

    static const char * MY_TASKS_LIST = "My tasks list:";
    static const char * NO_TASKS = "<no tasks>\n";

    static const char * TASK_COMPLETION_MENU = "Task completion menu";
    static const char * MAIN_MENU = "Main menu";

    static const char * CREATE_TASK_MENU = "Create task menu";
    static const char * TASK_LABEL_MENU = "Task Labels menu";

    static const char * NO_SPECIFIED_SHORTCUT = "There is no action with specified shortcut or argument is invalid.\n";
    static const char * SELECT_AN_ACTION = "Select an action (?)";

} // namespace messages
} // namespace resources
} // namespace todolist
} // namespace examples
} // namespace spine

#endif
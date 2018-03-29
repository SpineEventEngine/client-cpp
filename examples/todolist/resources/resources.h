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
    static const char * kDescriptionShortcut = "d";
    static const char * kDescriptionCommand = "Description";
    static const char * kDescriptionInfo = "Add/Edit description";

    static const char * kPriorityShortcut = "p";
    static const char * kPriorityCommand = "Priority";
    static const char * kPriorityInfo = "Add/Edit Priority";

    static const char * kNextStageShortcut = "n";
    static const char * kNextStageCommand = "next_stage";
    static const char * kNextStageInfo = "Next stage";

    static const char * kCancelShortcut = "c";
    static const char * kCancelCommand = "Cancel";
    static const char * kCancelInfo = "Cancel Task";

    static const char * kBackShortcut = "b";
    static const char * kBackCommand = "Back";
    static const char * kBackInfo = "Back to previous menu";

    static const char * kNewLabelShortcut = "a";
    static const char * kNewLabelCommand = "assign_new_label";
    static const char * kNewLabelInfo = "Assign new label";

    static const char * kExistingLabelShortcut = "e";
    static const char * kExistingLabelCommand = "assign_existing_label";
    static const char * kExistingLabelInfo = "Assign existing label";

    static const char * kRemoveLabelShortcut = "r";
    static const char * kRemoveLabelCommand = "remove_label";
    static const char * kRemoveLabelInfo = "Remove label from task";

    static const char * kDraftTasksShortcut = "d";
    static const char * kDraftTasksCommand = "draft_tasks";
    static const char * kDraftTasksInfo = "Draft Tasks";

    static const char * kCompletedTasksShortcut = "c";
    static const char * kCompletedTasksCommand = "completed_tasks";
    static const char * kCompletedTasksInfo = "Completed Tasks";

    static const char * kAllTasksShortcut = "a";
    static const char * kAllTasksCommand = "all_tasks";
    static const char * kAllTasksInfo = "All Tasks";

    static const char * kFinishTaskShortcut = "f";
    static const char * kFinishTaskCommand = "finish_task";
    static const char * kFinishTaskInfo = "Finish task";

    static const char * kCreateTaskShortcut = "c";
    static const char * kCreateTaskCommand = "create_task";
    static const char * kCreateTaskInfo = "Create a basic task";

    static const char * kStartWizardTaskCreationShortcut = "s";
    static const char * kStartWizardTaskCreationCommand = "create_wizard_task";
    static const char * kStartWizardTaskCreationInfo = "Start wizard task creation";

    static const char * kListTasksShortcut = "l";
    static const char * kListTasksCommand = "list_tasks";
    static const char * kListTasksInfo = "List tasks";

    static const char * kQuitTaskShortcut = "q";
    static const char * kQuitTaskCommand = "quit";
    static const char * kQuitTaskInfo = "Quit";

    static const char * kTaskNumberCommand = "task_number";
    static const char * kTaskNumberInfo = "Choose task";

} // namespace task_menu

namespace task_info {
    static const char * kTitle = "Title";
    static const char * kColor = "Color";
    static const char * kLabel = "Label";
    static const char * kTaskDetails = "My task details:\n";
    static const char * kTaskDescription = "Description";
    static const char * kTaskPriority = "Priority";
    static const char * kTaskDueDate = "Due date";
    static const char * kDefault = "default";

} // namespace task_info

namespace server_info {
    static const char * kInvalidServerStatus = "Invalid server status...";
    static const char * kInvalidServerResponse = "Invalid response....";

    static const char * kUserId = "user";
    static const char * kZoneId = "UTC";

    static const char * kChannel = "localhost:50051";

} // namespace server_info

namespace command_line
{
    static const char * kCommandDescriptionMessage = "Command description message";
    static const char * kCommandLineVersion = "0.9";

    static const char * kLeftBrace = "(";
    static const char * kRightBrace = ")";
    static const char * kLeftBracket = "[";
    static const char * kRightBracket = "]";
    static const char * kColon = ":";
    static const char * kDash = "-";
    static const char * kComma = ",";
    static const char * kSharp = "#";
    static const char * kLineSeparator = "----------------";

    static const char  kWhiteSpaceDelimiter = ' ';

} // namespace command_line

namespace messages {

    static const char * kPleaseEnterTheTaskDescription = "Please enter the task description:\n";
    static const char * kPleaseEnterTheTaskPriority = "Please enter the task priority:\n";

    static const char * kTaskDescriptionUpdated = "Task description updated.\n";
    static const char * kTaskPriorityUpdated = "Task priority updated.\n";
    static const char * kTaskDescriptionIsEmpty = "Task description is not add.\nPlease add task description.\n";

    static const char * kTaskPriorityValues = "(1) - HIGH\n(2) - NORMAL\n(3) - LOW\n";
    static const char * kTaskPriorityValueIsIncorrect = "The value is incorrect. Please choose the proper task priority.\n";

    static const char * kPleaseEnterTheTaskLabel = "Please enter the label title";
    static const char * kPleaseEnterTheLabelColor = "Please enter the label color:\n";
    static const char * kLabelValues = "(1) - RED \n(2) - GREEN \n(3) - BLUE    \n(4) - GRAY   \n";
    static const char * kLabelColorIsIncorrect = "The value is incorrect. Please choose the label color.\n";
    static const char * kLabelNumberIsIncorrect = "The value is incorrect. Please choose the label number.\n";

    static const char * kExistingLabels = "Existing labels :\n";
    static const char * kNoExistingLabels = "<No existing labels.>\n";

    static const char * kAssignedLabels = "Assigned labels:\n";
    static const char * kNoAssignedLabels = "<No assigned labels>";
    static const char * kPleaseChooseTheLabelNumber = "Please choose a number of existing label:\n";

    static const char * kNoLabelsOnThisTask = "You did not assign any label to this task.\n";
    static const char * kPleaseSelectNumberYouWantToRemove = "Please select label number you want to remove.\n";

    static const char * kRemoveFromTask = "removed from task.\n";

    static const char * kMyTasksList = "My tasks list:";
    static const char * kNoTasks = "<no tasks>\n";

    static const char * kTaskCompletionMenu = "Task completion menu";
    static const char * kMainMenu = "Main menu";

    static const char * kCreateTaskMenu = "Create task menu";
    static const char * kTaskLabelMenu = "Task Labels menu";

    static const char * kNoSpecifiedShortcut = "There is no action with specified shortcut or argument is invalid.\n";
    static const char * kSelectAnAction = "Select an action (?)";

    static const char * kTaskCreatedMessage = "Task successfully created.\n";
    static const char * kLabelHasAlreadyBeenSetToThisTask = "Label has been already set to this task.\n";

} // namespace messages
} // namespace resources
} // namespace todolist
} // namespace examples
} // namespace spine

#endif
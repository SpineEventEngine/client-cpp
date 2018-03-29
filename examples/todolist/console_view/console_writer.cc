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
#include "resources/resources.h"

namespace spine {
namespace examples {
namespace todolist {
namespace console {

void PrintTaskDescription(const TaskItem& task_item)
{
    std::cout << resources::task_info::kTaskDetails;
    std::cout << resources::command_line::kLineSeparator << std::endl;

    std::cout
            << resources::task_info::kTaskDescription
            << resources::command_line::kColon
            << resources::command_line::kWhiteSpaceDelimiter
            << task_item.description().value()
            << std::endl;

    std::cout
            << resources::task_info::kTaskPriority
            << resources::command_line::kColon
            << resources::command_line::kWhiteSpaceDelimiter
            << TaskPriority_Name(task_item.priority())
            << std::endl;

    std::cout
            << resources::task_info::kTaskDueDate
            << resources::command_line::kColon
            << resources::command_line::kWhiteSpaceDelimiter
            << resources::task_info::kDefault
            << std::endl;
}

void PrintUndefinedActionMessage()
{
    std::cout << resources::messages::kNoSpecifiedShortcut;
}

void PrintSelectAnActionPrompt()
{
    std::cout << resources::messages::kSelectAnAction << std::endl;
}

void PrintTaskLabelInfoForMenu(
    const std::string& index,
    const std::string& title,
    const std::string& color
)
{
    std::cout
        << resources::command_line::kLeftBrace
        << index
        << resources::command_line::kRightBrace
        << resources::command_line::kWhiteSpaceDelimiter
        << resources::command_line::kDash
        << resources::command_line::kWhiteSpaceDelimiter
        << resources::command_line::kLeftBracket
        << resources::task_info::kTitle
        << resources::command_line::kWhiteSpaceDelimiter
        << resources::command_line::kColon
        << title
        << resources::command_line::kComma
        << resources::command_line::kWhiteSpaceDelimiter
        << resources::task_info::kColor
        << resources::command_line::kWhiteSpaceDelimiter
        << resources::command_line::kColon
        << resources::command_line::kWhiteSpaceDelimiter
        << color
        << resources::command_line::kRightBracket
        << std::endl;
}

void PrintLabelRemovedFromTaskMessage(const std::string& label_number)
{
    PrintLabelNumber(label_number);
    std::cout << resources::messages::kRemoveFromTask;
}

void PrintLabelNumber(const std::string& label_number)
{
    std::cout
        << resources::task_info::kLabel
        << resources::command_line::kWhiteSpaceDelimiter
        << resources::command_line::kSharp
        << resources::command_line::kWhiteSpaceDelimiter
        << label_number
        << resources::command_line::kWhiteSpaceDelimiter
        << resources::command_line::kColon
        << resources::command_line::kWhiteSpaceDelimiter;
}

void PrintTaskLabelInfoForDescription(
    const std::string& label_number,
    const std::string& label_title,
    const std::string& label_color
)
{
    std::cout
        << resources::task_info::kLabel
        << resources::command_line::kWhiteSpaceDelimiter
        << resources::command_line::kSharp
        << resources::command_line::kWhiteSpaceDelimiter
        << label_number
        << resources::command_line::kWhiteSpaceDelimiter
        << resources::command_line::kColon
        << resources::command_line::kWhiteSpaceDelimiter
        << resources::command_line::kLeftBracket
        << resources::task_info::kTitle
        << resources::command_line::kWhiteSpaceDelimiter
        << resources::command_line::kColon
        << label_title
        << resources::command_line::kComma
        << resources::command_line::kWhiteSpaceDelimiter
        << resources::task_info::kColor
        << resources::command_line::kWhiteSpaceDelimiter
        << resources::command_line::kColon
        << resources::command_line::kWhiteSpaceDelimiter
        << label_color
        << resources::command_line::kRightBracket
        << std::endl;
}

} // namespace console
} // namespace todolist
} // namespace examples
} // namespace spine

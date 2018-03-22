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

void ConsoleWriter::PrintTaskDescription(TaskItem &task_item)
{
    std::cout << resources::task_info::TASK_DETAILS;
    std::cout << resources::command_line::LINE_SEPARATOR << std::endl;

    std::cout
            << resources::task_info::TASK_DESCRIPTION
            << resources::command_line::COLON
            << resources::command_line::WHITE_SPACE_DELIMETER
            << task_item.description().value()
            << std::endl;

    std::cout
            << resources::task_info::TASK_PRIORITY
            << resources::command_line::COLON
            << resources::command_line::WHITE_SPACE_DELIMETER
            << TaskPriority_Name(task_item.priority())
            << std::endl;

    std::cout
            << resources::task_info::TASK_DUE_DATE
            << resources::command_line::COLON
            << resources::command_line::WHITE_SPACE_DELIMETER
            << resources::task_info::DEFAULT
            << std::endl;
}

void ConsoleWriter::PrintUndefinedActionMessage()
{
    std::cout << resources::messages::NO_SPECIFIED_SHORTCUT;
}

void ConsoleWriter::PrintSelectAnActionPrompt()
{
    std::cout << resources::messages::SELECT_AN_ACTION << std::endl;
}

void ConsoleWriter::PrintTaskLabelInfoForMenu(
    const std::string & index,
    const std::string & title,
    const std::string & color
)
{
    std::cout
        << resources::command_line::LEFT_BRACE
        << index
        << resources::command_line::RIGHT_BRACE
        << resources::command_line::WHITE_SPACE_DELIMETER
        << resources::command_line::DASH
        << resources::command_line::WHITE_SPACE_DELIMETER
        << resources::command_line::LEFT_BRACKET
        << resources::task_info::TITLE
        << resources::command_line::WHITE_SPACE_DELIMETER
        << resources::command_line::COLON
        << title
        << resources::command_line::COMMA
        << resources::command_line::WHITE_SPACE_DELIMETER
        << resources::task_info::COLOR
        << resources::command_line::WHITE_SPACE_DELIMETER
        << resources::command_line::COLON
        << resources::command_line::WHITE_SPACE_DELIMETER
        << color
        << resources::command_line::RIGHT_BRACKET
        << std::endl;
}

void ConsoleWriter::PrintLabelRemovedFromTaskMessage(const std::string &label_number)
{
    PrintLabelNumber(label_number);
    std::cout << resources::messages::REMOVED_FROM_TASK;
}

void ConsoleWriter::PrintLabelNumber(const std::string &label_number)
{
    std::cout
        << resources::task_info::LABEL
        << resources::command_line::WHITE_SPACE_DELIMETER
        << resources::command_line::SHARP
        << resources::command_line::WHITE_SPACE_DELIMETER
        << label_number
        << resources::command_line::WHITE_SPACE_DELIMETER
        << resources::command_line::COLON
        << resources::command_line::WHITE_SPACE_DELIMETER;
}

void ConsoleWriter::PrintTaskLabelInfoForDescription(
    const std::string & label_number,
    const std::string & label_title,
    const std::string & label_color
)
{
    std::cout
        << resources::task_info::LABEL
        << resources::command_line::WHITE_SPACE_DELIMETER
        << resources::command_line::SHARP
        << resources::command_line::WHITE_SPACE_DELIMETER
        << label_number
        << resources::command_line::WHITE_SPACE_DELIMETER
        << resources::command_line::COLON
        << resources::command_line::WHITE_SPACE_DELIMETER
        << resources::command_line::LEFT_BRACKET
        << resources::task_info::TITLE
        << resources::command_line::WHITE_SPACE_DELIMETER
        << resources::command_line::COLON
        << label_title
        << resources::command_line::COMMA
        << resources::command_line::WHITE_SPACE_DELIMETER
        << resources::task_info::COLOR
        << resources::command_line::WHITE_SPACE_DELIMETER
        << resources::command_line::COLON
        << resources::command_line::WHITE_SPACE_DELIMETER
        << label_color
        << resources::command_line::RIGHT_BRACKET
        << std::endl;
}

} // namespace todolist
} // namespace examples
} // namespace spine

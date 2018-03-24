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

//TODO don't need a class if everything is public and static.
class ConsoleWriter
{
public:
    static void PrintTaskDescription(TaskItem &task_item);
    static void PrintUndefinedActionMessage();
    static void PrintSelectAnActionPrompt();

    static void PrintTaskLabelInfoForMenu(
        const std::string &index,
        const std::string &title,
        const std::string &color);

    static void PrintLabelRemovedFromTaskMessage(const std::string &label_number);

    static void PrintLabelNumber(const std::string &label_number);

    static void PrintTaskLabelInfoForDescription(
        const std::string &index,
        const std::string &label_title,
        const std::string &label_color);
};

} // namespace todolist
} // namespace examples
} // namespace spine

#endif // TODOLIST_CONSOLE_WRITER_H

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


#ifndef TODOLIST_COMMAND_HANDLER_H
#define TODOLIST_COMMAND_HANDLER_H

#include "google/protobuf/message.h"

#include "todolist/c/commands.pb.h"
#include "todolist/q/projections.pb.h"
#include "todolist/model.pb.h"

namespace spine {
namespace examples {
namespace todolist {

class CommandHandler
{
public:
    virtual ~CommandHandler() {}

    virtual void PostCommand(google::protobuf::Message &client_task) = 0;

    virtual TaskListView const & GetCompletedTasks() = 0;
    virtual TaskListView const & GetDraftTasks() = 0;

    virtual std::vector<TaskLabel *> GetLabels() = 0;
};

} // namespace todolist
} // namespace examples
} // namespace spine

#endif // TODOLIST_COMMAND_HANDLER_H

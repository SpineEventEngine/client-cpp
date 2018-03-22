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

#include "command_handler_impl.h"
#include "spine/client/query_service.grpc.pb.h"
#include "resources/resources.h"

namespace spine {
namespace examples {
namespace todolist {

constexpr int AMOUNT_SECONDS = 0;

CommandHandlerImpl::CommandHandlerImpl(const std::string & channel)
{
    channel_ = ::grpc::CreateChannel(channel, grpc::InsecureChannelCredentials());
    auto tenant = std::unique_ptr<TenantId>(TenantId::default_instance().New());

    parameters_
        .set_tenant_id(tenant)
        .set_actor(MakeUserId(resources::server_info::USER_ID))
        .set_zone_offset(MakeZoneOffset(resources::server_info::ZONE_ID, AMOUNT_SECONDS));

    command_factory_ = ActorRequestFactory::create(parameters_).command_factory();
    stub_ = CommandService::NewStub(channel_);
}

void CommandHandlerImpl::PostCommand(Message &client_task)
{
    CommandPtr command = command_factory_->create(client_task);
    core::Ack response;
    grpc::ClientContext client_context;
    if (!stub_->Post(&client_context, *command, &response).ok()) {
        throw std::runtime_error(resources::server_info::INVALID_SERVER_STATUS);
    }
}

TaskListView const &CommandHandlerImpl::GetCompletedTasks()
{
    return GetTasks<MyListView>()->my_list();
}

TaskListView const & CommandHandlerImpl::GetDraftTasks()
{
    return GetTasks<DraftTasksView>()->draft_tasks();
}

template <typename T>
T * CommandHandlerImpl::GetTasks()
{
    ActorRequestFactory factory = ActorRequestFactory::create(parameters_);
    QueryPtr query = factory.query_factory()->all<T>();
    std::unique_ptr<QueryService::Stub> query_service = QueryService::NewStub(channel_);

    QueryResponse response;
    grpc::ClientContext client_context;

    if (!query_service->Read(&client_context, *query, &response).ok()) {
        throw std::runtime_error(resources::server_info::INVALID_SERVER_RESPONSE);
    }

    T * task_list_view = T::default_instance().New();
    if (response.messages_size() > 0) {
        const Any& any = response.messages(0);
        any.UnpackTo(task_list_view);
    }

    return task_list_view;
}

std::vector<std::shared_ptr<TaskLabel>> CommandHandlerImpl::GetLabels()
{
    ActorRequestFactory factory = ActorRequestFactory::create(parameters_);
    QueryPtr query = factory.query_factory()->all<TaskLabel>();
    std::unique_ptr<QueryService::Stub> query_service = QueryService::NewStub(channel_);

    QueryResponse response;
    grpc::ClientContext client_context;

    if (!query_service->Read(&client_context, *query, &response).ok()) {
        throw std::runtime_error(resources::server_info::INVALID_SERVER_RESPONSE);
    }

    std::vector<std::shared_ptr<TaskLabel>> label_tasks;
    int messages_count = response.messages_size();
    for (int i = 0; i < messages_count; ++i) {
        std::shared_ptr<TaskLabel> task_label(TaskLabel::default_instance().New());
        const Any& any = response.messages(i);
        any.UnpackTo(task_label.get());
        label_tasks.push_back(task_label);
    }

    return std::move(label_tasks);
}

std::unique_ptr<core::UserId>
CommandHandlerImpl::MakeUserId(const std::string & value)
{
    auto actor = std::make_unique<core::UserId>();
    actor->set_value(value);
    return actor;
}

std::unique_ptr<time::ZoneOffset>
CommandHandlerImpl::MakeZoneOffset(const std::string &zone_id, int amount)
{
    time::ZoneId* zone_id_ptr = time::ZoneId::default_instance().New();
    zone_id_ptr->set_value(zone_id);

    std::unique_ptr<spine::time::ZoneOffset> zone_offset
        = std::make_unique<time::ZoneOffset>();

    zone_offset->set_allocated_id(zone_id_ptr);
    zone_offset->set_amountseconds(amount);
    return zone_offset;
}

} // namespace todolist
} // namespace examples
} // namespace spine

#include "list_task.hpp"
#include "todolist/model.pb.h"

#include "command_handler/command_handler.hpp"

std::shared_ptr<ListTask>
ListTask::createListTask()
{
	return std::make_shared<ListTask>(*new ListTask());
}

void ListTask::loadTasks()
{
	auto const & taskListView = CommandHandler::getCommandHandler().getTasks();

	for (int i = 0; i < taskListView.items_size(); i++)
		m_taskItems.push_back(taskListView.items(i));
}

void ListTask::forEachTask(std::function<void(std::string const &)> _callback)
{
	for (int index = 0; index < m_taskItems.size(); ++index)
	{
		_callback(m_taskItems[index].description().value());
	}
}
#pragma once

#include "todolist/q/projections.pb.h"

#include <memory>
#include <functional>

class ListTask
{

public:

	ListTask() = default;
	~ListTask() = default;

	static std::shared_ptr<ListTask> createListTask();

	void loadTasks();

	void forEachTask(std::function<void(std::string const &)> _callback);

private:

	std::vector<spine::examples::todolist::TaskItem> m_taskItems;
};
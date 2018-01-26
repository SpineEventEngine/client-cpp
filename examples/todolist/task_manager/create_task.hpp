#pragma once

#include <memory>
#include <string>

#include "todolist/model.pb.h"
#include "todolist/c/commands.pb.h"

class CreateTask
{
public:

	CreateTask() = default;
	~CreateTask() = default;

	void post(std::string const & _description);

	static std::shared_ptr<CreateTask> createTask();

};
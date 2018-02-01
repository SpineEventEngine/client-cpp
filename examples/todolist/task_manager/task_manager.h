#pragma once

#include <string>
#include <memory>

class ConsoleView;
class CommandHandler;

class TaskManager
{

public:

	TaskManager(std::string const & path_to_exec_file);

	void start();

private:

	void initialize_tasks() noexcept;

	void add_task();
	void list_tasks() const;

	static std::string generate_task_id();

private:

	std::shared_ptr<ConsoleView> console_view_;
	std::shared_ptr<CommandHandler> command_handler_;
};
#include <string>
#include <iostream>
#include <algorithm>

#include "task_manager/task_manager.hpp"

using namespace std;

int main(int argc, char** argv)
{
	TaskManager taskManager;

	taskManager.init();
	taskManager.start(argv[0]);
}

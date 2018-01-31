#include <string>
#include <iostream>
#include <algorithm>

#include "task_manager/task_manager.h"

using namespace std;

int main(int argc, char** argv)
{
	TaskManager taskManager(argv[0]);
	taskManager.start();
}

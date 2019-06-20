#include <octoon/octoon-c.h>
#include <iostream>
#include <octoon/process/command.h>
#include "main_controller.h"

int main(int argc, const char* argv[])
{
	std::cout << octoon::process::Command::run("dir").status();
	if (!::OctoonInit(argv[0], ""))
		return 1;

	if (::OctoonOpenWindow("Octoon Studio", 1376, 768))
	{
		auto object = octoon::GameObject::create();
		object->addComponent<octoon::editor::MainController>();

		::OctoonMainLoop();
	}

	::OctoonTerminate();
	return 0;
}
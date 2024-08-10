
#define CONSOLE_APP

#ifdef CONSOLE_APP
#pragma comment(linker,"/SUBSYSTEM:CONSOLE")
#else
#pragma comment(linker,"/SUBSYSTEM:WINDOWS")
#endif

#include <iostream>
#include "Application.h"
#include "Tools/Timer.h"
#include <SFML/Graphics.hpp>



int main(int argc, char** argv) {

	// TODO: process command line arguments

	Application& app = Application::instance();
	app.init();
	app.run();

	return 0;
}
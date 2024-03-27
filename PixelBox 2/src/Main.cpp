
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

	// process command line arguments
	// ...


	Application app;
	app.run();


	return 0;
}
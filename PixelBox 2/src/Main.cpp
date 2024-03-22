
#ifdef CONSOLE_APP
#pragma comment(linker,"/SUBSYSTEM:CONSOLE")
#else
#pragma comment(linker,"/SUBSYSTEM:WINDOWS")
#endif

#include <iostream>
#include "Application.h"
#include "Tools/Timer.h"
#include <SFML/Graphics.hpp>
#include <thread>
#include <mutex>

std::mutex mtx;

void func(uint8_t* data, int w, int h) {

	mtx.lock();
	std::this_thread::sleep_for(std::chrono::milliseconds(2));
	memset(data, 255, w * h * 4);
	mtx.unlock();

}


int main(int argc, char** argv) {

	// process command line arguments
	// ...

	//Timer timer;

	////2048 -> 4.5ms

	//int width = 4096; // 4096 -> 15ms, 2048 -> 14ms, 1024 -> 18ms (half: 10ms), 512 -> 19ms (half: 11ms), 256 -> ~40ms
	//int height = width;
	//int num = 1;

	//sf::Texture tex;
	//tex.create(width, height);

	//uint8_t* data = new uint8_t[width * height * 4];
	//uint8_t* back_buf = new uint8_t[width * height * 4];
	//int n = 1000;

	//memset(data, 0, width * height * 4);


	//tex.update(data);
	//double time = 0;
	//double t = 0;

	//for (int i = 0; i < n; i++) {
	//	data[0] = rand() % 256;
	//	data[width * height * 4 - 1] = rand() % 256;

	//	timer.start();
	//	memcpy(back_buf, data, width * height * 4);
	//	//for(int m=0;m<num;m++)
	//		//tex.update(data);
	//	timer.stop();

	//	std::cout << timer.get_duration() << std::endl;
	//	time += timer.get_duration();

	//}
	//std::cout << "\n" << time / n << std::endl;



	//delete[] data;
	//delete[] back_buf;

	Application app;
	app.run();

#ifdef CONSOLE_APP
	std::cin.get();
#endif
	return 0;

}
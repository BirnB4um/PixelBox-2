#include "Application.h"


Application::Application() {
	Screen::app = this;

	homescreen.init();
	settingsscreen.init();
	screens.push_back(&homescreen);
	current_screen = &homescreen;

	create_window(800, 600, false, 60, "CircuitGrid");

	ImGui::SFML::Init(window);

}

Application::~Application() {
}


void Application::create_window(unsigned int width, unsigned int height, bool fullscreen, int fps, std::string title, bool vsync)
{
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 3;
	settings.minorVersion = 0;

	window_width = width;
	window_height = height;
	this->fps = fps;
	this->fullscreen = fullscreen;

	if (fullscreen) {
		window.create(sf::VideoMode::getFullscreenModes()[0], title, sf::Style::Fullscreen, settings);
	}
	else {
		windowed_width = width;
		windowed_height = height;
		window.create(sf::VideoMode(width, height), title, sf::Style::Close | sf::Style::Resize, settings);
	}
	window.setFramerateLimit(fps);
	window.setVerticalSyncEnabled(vsync);

	on_resize();
}

void Application::close_current_screen() {
	if (screens.size() > 1)
		screens.pop_back();
}

void Application::open_screen(SCREEN_ID id) {
	switch (id)
	{
	case HOME:
		screens.push_back(&homescreen);
		break;
	case SETTINGS:
		screens.push_back(&settingsscreen);
		break;
	default:
		break;
	}
}

void Application::on_closing() {
	homescreen.on_closing();
	settingsscreen.on_closing();

	window.close();
}

void Application::on_resize() {
	window_width = window.getSize().x;
	window_height = window.getSize().y;
	if (!fullscreen) {
		windowed_width = window_width;
		windowed_height = window_height;
	}

	homescreen.on_resize();
	settingsscreen.on_resize();
}

void Application::handle_events() {
	while (window.pollEvent(sf_event)) {
		
		ImGui::SFML::ProcessEvent(window, sf_event);


		switch (sf_event.type)
		{

		case sf::Event::GainedFocus:
			break;

		case sf::Event::LostFocus:
			break;

		case sf::Event::Closed:
			on_closing();
			break;

		case sf::Event::Resized:
			on_resize();
			break;

		case sf::Event::KeyPressed:

			// toggle fullscreen
			if (sf_event.key.code == sf::Keyboard::F10) {
				fullscreen = !fullscreen;
				create_window(windowed_width, windowed_height, fullscreen, fps, "CircuitGrid");
			}

			break;

		default:
			break;
		}

		//if mouse is captured by imgui, don't handle events
		if (ImGui::GetIO().WantCaptureMouse || ImGui::GetIO().WantCaptureKeyboard)
			continue;

		current_screen->handle_events(sf_event);

	}
}

void Application::update() {

	ImGui::SFML::Update(window, deltaTime);

	current_screen->update(deltaTime.asSeconds());

}

void Application::draw() {
	window.clear();

	current_screen->render(window);

	sf::Sprite sprite;

	ImGui::SFML::Render(window);

	window.display();
}

void Application::run() {

	while (window.isOpen())
	{
		deltaTime = deltaClock.restart();

		if (screens.size() == 0)
			screens.push_back(&homescreen);

		current_screen = screens.back();

		handle_events();

		update();

		draw();
	}

	ImGui::SFML::Shutdown();
}
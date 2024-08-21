#include "WorldInteractionManager.h"

#include "../../Application.h"
#include "SimulationScreen.h"

WorldInteractionManager::WorldInteractionManager() {
	m_simulation = nullptr;
	m_isDrawing = false;

	m_linePreview.setFillColor(sf::Color(255, 0, 0));
	m_rectPreview.setFillColor(sf::Color::Transparent);
	m_rectPreview.setOutlineColor(sf::Color(255, 0, 0));
	m_circlePreview.setFillColor(sf::Color::Transparent);
	m_circlePreview.setOutlineColor(sf::Color(255, 0, 0));
}

WorldInteractionManager::~WorldInteractionManager() {
}

void WorldInteractionManager::init(SimulationScreen* simulation) {
	m_simulation = simulation;

	m_pauseSwitch.addState({ 1, {61, 7, 3, 5} }); //paused
	m_pauseSwitch.addState({ 2, {61, 1, 3, 5} }); //unpaused
	m_pauseSwitch.setSpritePadding(5.0f);
	m_pauseSwitch.setFunction([this]() {
		m_simulation->m_isSimulationPaused = m_pauseSwitch.getCurrentState().id == 1 ? true : false;
		});
	m_simulation->addGuiElement(&m_pauseSwitch);

	m_interactionSwitch.addState({ 1, {65, 1, 11, 11} });//drawing
	m_interactionSwitch.addState({ 2, {77, 1, 12, 14} });//interacting
	m_interactionSwitch.setSpritePadding(5.0f);
	m_interactionSwitch.setFunction([this]() {
		});
	m_simulation->addGuiElement(&m_interactionSwitch);

	//Sliders
	m_tpsSlider.setRange(1, 1000);
	m_tpsSlider.setValue(10);
	m_tpsSlider.setFunction([this]() {
		});
	m_simulation->addGuiElement(&m_tpsSlider);

	m_brushSizeSlider.setRange(1, 100);
	m_brushSizeSlider.setValue(1);
	m_brushSizeSlider.setFunction([this]() {
		});
	m_simulation->addGuiElement(&m_brushSizeSlider);

	//Drawtype Buttons
	m_brushSwitch.setActivated(true);
	m_brushSwitch.setBorderWidth(2.0f);
	m_brushSwitch.setSpritePadding(2.0f);
	m_brushSwitch.setTexturePatch({ 90, 1, 20, 20 });
	m_brushSwitch.setFunction([this]() {
		deactivateAllSwitches();
		m_brushSwitch.setActivated(true);
		});
	m_simulation->addGuiElement(&m_brushSwitch);

	m_lineSwitch.setBorderWidth(2.0f);
	m_lineSwitch.setSpritePadding(2.0f);
	m_lineSwitch.setTexturePatch({ 110, 2, 11, 10 });
	m_lineSwitch.setFunction([this]() {
		deactivateAllSwitches();
		m_lineSwitch.setActivated(true);
		});
	m_simulation->addGuiElement(&m_lineSwitch);

	m_rectangleSwitch.setBorderWidth(2.0f);
	m_rectangleSwitch.setSpritePadding(2.0f);
	m_rectangleSwitch.setTexturePatch({ 110, 13, 11, 7 });
	m_rectangleSwitch.setFunction([this]() {
		deactivateAllSwitches();
		m_rectangleSwitch.setActivated(true);
		});
	m_simulation->addGuiElement(&m_rectangleSwitch);

	m_circleSwitch.setBorderWidth(2.0f);
	m_circleSwitch.setSpritePadding(2.0f);
	m_circleSwitch.setTexturePatch({ 110, 21, 15, 15 });
	m_circleSwitch.setFunction([this]() {
		deactivateAllSwitches();
		m_circleSwitch.setActivated(true);
		});
	m_simulation->addGuiElement(&m_circleSwitch);

	m_fillSwitch.setBorderWidth(2.0f);
	m_fillSwitch.setSpritePadding(2.0f);
	m_fillSwitch.setTexturePatch({ 98, 21, 11, 17 });
	m_fillSwitch.setFunction([this]() {
		deactivateAllSwitches();
		m_fillSwitch.setActivated(true);
		});
	m_simulation->addGuiElement(&m_fillSwitch);

	m_selectionSwitch.setBorderWidth(2.0f);
	m_selectionSwitch.setSpritePadding(4.0f);
	m_selectionSwitch.setTexturePatch({ 61, 13, 6, 6 });
	m_selectionSwitch.setFunction([this]() {
		deactivateAllSwitches();
		m_selectionSwitch.setActivated(true);
		});
	m_simulation->addGuiElement(&m_selectionSwitch);

	//Toggle switches

	m_gridSwitch.setBorderWidth(2.0f);
	m_gridSwitch.setSpritePadding(4.0f);
	m_gridSwitch.setTexturePatch({ 68, 13, 7, 7 });
	m_gridSwitch.setFunction([this]() {
		ResourceManager::getPixelShader()->setUniform("drawGrid", m_gridSwitch.isActivated());
		});
	m_simulation->addGuiElement(&m_gridSwitch);


	m_detailSwitch.setBorderWidth(2.0f);
	m_detailSwitch.setSpritePadding(4.0f);
	m_detailSwitch.setTexturePatch({ 61, 20, 4, 6 });
	m_detailSwitch.setFunction([this]() {
		ResourceManager::getPixelShader()->setUniform("detailMode", m_detailSwitch.isActivated());
		});
	m_simulation->addGuiElement(&m_detailSwitch);

	m_resetButton.setBorderWidth(2.0f);
	m_resetButton.setSpritePadding(4.0f);
	m_resetButton.setTexturePatch({ 76, 16, 8, 11 });
	m_resetButton.setFunction([this]() {
		std::cout << "reset" << std::endl;
		});
	m_simulation->addGuiElement(&m_resetButton);

	m_undoButton.setBorderWidth(2.0f);
	m_undoButton.setSpritePadding(4.0f);
	m_undoButton.setTexturePatch({ 66, 21, 6, 6 });
	m_undoButton.setFunction([this]() {
		std::cout << "undo" << std::endl;
		});
	m_simulation->addGuiElement(&m_undoButton);
}

bool WorldInteractionManager::handleEvent(sf::Event& sfEvent) {
	switch (sfEvent.type)
	{
	case sf::Event::KeyReleased:
		if (sfEvent.key.code == sf::Keyboard::R) {
			uint32_t data = 0xff0000ff;
			reinterpret_cast<uint8_t*>(&data)[0] = rand() % 255;
			reinterpret_cast<uint8_t*>(&data)[1] = rand() % 255;
			reinterpret_cast<uint8_t*>(&data)[2] = rand() % 255;
			reinterpret_cast<uint8_t*>(&data)[3] = 255;

			DrawInstruction instruction(
				data,
				{ 0,0 },
				{ static_cast<int>(m_simulation->m_world->getMetaData().width),static_cast<int>(m_simulation->m_world->getMetaData().height) },
				DrawInstruction::Type::RECTANGLE,
				1.0f,
				nullptr);

			std::lock_guard<std::mutex> lock(m_simulation->m_drawingMutex);
			m_simulation->m_collectedDrawInstructions.push_back(instruction);

			return true;
		}
		else if (sfEvent.key.code == sf::Keyboard::F) {
			m_fillSwitch.callFunction();
		}
		break;

	case sf::Event::MouseButtonPressed:
		if (sfEvent.mouseButton.button == sf::Mouse::Left && !sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
			if (m_interactionSwitch.getCurrentState().id == 1) { //drawing
				m_startDrawingPosition = m_simulation->getMouseWorldPos();
				m_isDrawing = true;

				return true;
			}
			else { //interacting
			}
		}
		break;

	case sf::Event::MouseButtonReleased:
	{
		if (m_isDrawing) {
			m_isDrawing = false;

			//create drawing instruction
			//by default draw LINE
			DrawInstruction instruction(
				m_simulation->m_selectedPixelData,
				static_cast<sf::Vector2i>(m_startDrawingPosition),
				static_cast<sf::Vector2i>(m_simulation->getMouseWorldPos()),
				DrawInstruction::Type::LINE,
				m_brushSizeSlider.getValue(),
				nullptr);

			if (m_rectangleSwitch.isActivated()) {
				//draw rectangle
				instruction.type = DrawInstruction::Type::RECTANGLE;
			}
			else if (m_circleSwitch.isActivated()) {
				//draw circle
				instruction.endPos = instruction.startPos;
				instruction.width = std::max(1.0f, Utils::getLength(m_startDrawingPosition - m_simulation->getMouseWorldPos()));
			}
			else if (m_fillSwitch.isActivated()) {
				//draw fill
				instruction.type = DrawInstruction::Type::FILL;
				instruction.startPos = instruction.endPos;
			}

			std::lock_guard<std::mutex> lock(m_simulation->m_drawingMutex);
			m_simulation->m_collectedDrawInstructions.push_back(instruction);

			return true;
		}
	}
	break;

	default:
		break;
	}

	return false;
}

void WorldInteractionManager::update(float dt) {
	//if drawing with brush
	if (m_brushSwitch.isActivated() && m_isDrawing) {
		//if mouse moved relative to board
		if (m_startDrawingPosition != m_simulation->getMouseWorldPos()) {
			//create drawing instruction for brush
			{
				DrawInstruction instruction(
					m_simulation->m_selectedPixelData,
					static_cast<sf::Vector2i>(m_startDrawingPosition),
					static_cast<sf::Vector2i>(m_simulation->getMouseWorldPos()),
					DrawInstruction::Type::LINE,
					m_brushSizeSlider.getValue(),
					nullptr);

				m_startDrawingPosition = m_simulation->getMouseWorldPos();

				std::lock_guard<std::mutex> lock(m_simulation->m_drawingMutex);
				m_simulation->m_collectedDrawInstructions.push_back(instruction);
			}
		}
	}
}

void WorldInteractionManager::render(sf::RenderTarget& window) {
	window.setView(m_simulation->m_pixelView);

	//draw preview on board
	if (m_isDrawing) {
		if (m_brushSwitch.isActivated()) {
			//draw brush preview
		}
		else if (m_lineSwitch.isActivated()) {
			//draw line preview

			m_linePreview.setPosition(m_startDrawingPosition);

			sf::Vector2f distance = m_simulation->getMouseWorldPos() - m_startDrawingPosition;
			m_linePreview.setSize(sf::Vector2f(Utils::getLength(distance), 4.0f / m_simulation->m_zoomLevel));
			m_linePreview.setRotation(atan2(distance.y, distance.x) * 180.0f / Utils::PI);

			window.draw(m_linePreview);
		}
		else if (m_rectangleSwitch.isActivated()) {
			//draw rectangle preview
			m_rectPreview.setPosition(m_startDrawingPosition);
			m_rectPreview.setSize(m_simulation->getMouseWorldPos() - m_startDrawingPosition);
			m_rectPreview.setOutlineThickness(4.0f / m_simulation->m_zoomLevel);
			window.draw(m_rectPreview);
		}
		else if (m_circleSwitch.isActivated()) {
			//draw circle preview
			m_circlePreview.setRadius(Utils::getLength(m_startDrawingPosition - m_simulation->getMouseWorldPos()));
			m_circlePreview.setOrigin(m_circlePreview.getRadius(), m_circlePreview.getRadius());
			m_circlePreview.setPosition(m_startDrawingPosition);
			m_circlePreview.setOutlineThickness(4.0f / m_simulation->m_zoomLevel);
			window.draw(m_circlePreview);
		}
		else if (m_fillSwitch.isActivated()) {
			//draw fill preview
		}
	}

	window.setView(Application::normalView);
}

void WorldInteractionManager::onResize() {
	sf::Vector2i windowSize = Application::instance().getWindowSize();

	m_pauseSwitch.setBounds(10, 10, 50, 50);
	m_interactionSwitch.setBounds(10, 70, 50, 50);

	m_tpsSlider.setBounds(80, 10, 160, 25);
	m_brushSizeSlider.setBounds(80, 70, 160, 25);

	float x = 10.0f;
	float y = 130.0f;
	float w = 40.0f;
	float margin = 4.0f;
	m_brushSwitch.setBounds(x, y, w, w);
	m_lineSwitch.setBounds(x + w + margin, y, w, w);

	y += w + margin;
	m_rectangleSwitch.setBounds(x, y, w, w);
	m_circleSwitch.setBounds(x + w + margin, y, w, w);

	y += w + margin;
	m_fillSwitch.setBounds(x, y, w, w);
	m_selectionSwitch.setBounds(x + w + margin, y, w, w);

	y += w + margin + 10.0f;
	m_gridSwitch.setBounds(x, y, w, w);
	m_detailSwitch.setBounds(x + w + margin, y, w, w);

	y += w + margin;
	m_resetButton.setBounds(x, y, w, w);
	m_undoButton.setBounds(x + w + margin, y, w, w);
}

void WorldInteractionManager::resetAll() {
	m_isDrawing = false;

	m_pauseSwitch.setState(1);
	m_interactionSwitch.setState(1);

	deactivateAllSwitches();
	m_brushSwitch.setActivated(true);

	m_gridSwitch.setActivated(false);
	m_detailSwitch.setActivated(false);
}

void WorldInteractionManager::deactivateAllSwitches() {
	m_brushSwitch.setActivated(false);
	m_lineSwitch.setActivated(false);
	m_rectangleSwitch.setActivated(false);
	m_circleSwitch.setActivated(false);
	m_fillSwitch.setActivated(false);
	m_selectionSwitch.setActivated(false);
}
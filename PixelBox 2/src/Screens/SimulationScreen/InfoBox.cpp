#include "InfoBox.h"
#include "../../Application.h"

InfoBox::InfoBox() {
	m_simulation = nullptr;
	m_hideGui = false;
	m_lastPixelData = 0;
	m_selectedData = 0;
	m_overPixel = false;
}

InfoBox::~InfoBox() {
}

void InfoBox::init(SimulationScreen* simulation) {
	m_simulation = simulation;

	m_hoveredPixelPos = sf::Vector2i(-1, -1);

	m_panel.setBorderWidth(2.0f);
	m_guiElements.push_back(&m_panel);

	m_infoTitle.setText("Info");
	m_infoTitle.setFontSize(25);
	m_infoTitle.setAlignment(TextRect::Alignment::CenterLeft);
	m_panel.addElement(&m_infoTitle);

	m_infoText.setText("Name:\nID:\ndata1:\ndata2:\ndata3:");
	m_infoText.setFontSize(18);
	m_infoText.setAlignment(TextRect::Alignment::TopLeft);
	m_infoText.setLineSpacing(1.4f);
	m_panel.addElement(&m_infoText);

	m_dataText.setText("Air\n0\n0\n0\n0");
	m_dataText.setFontSize(18);
	m_dataText.setAlignment(TextRect::Alignment::TopLeft);
	m_dataText.setLineSpacing(1.4f);
	m_panel.addElement(&m_dataText);

	m_selectedData = 0;
	m_selectedDataRect.setFillColor(sf::Color::Transparent);
	m_selectedDataRect.setOutlineColor(sf::Color(255, 255, 255));
	m_selectedDataRect.setBorderWidth(1.0f);
	m_panel.addElement(&m_selectedDataRect);

	for (GuiElement* element : m_guiElements) {
		element->reloadResources();
	}
	onResize();
}

bool InfoBox::handleEvent(sf::Event& sfEvent) {
	for (GuiElement* element : m_guiElements) {
		if (element->handleEvent(sfEvent))
			return true;
	}

	switch (sfEvent.type)
	{
	case sf::Event::KeyPressed:
		if (sfEvent.key.code == sf::Keyboard::Down) {
			m_selectedData++;
			if (m_selectedData > 3)
				m_selectedData = 0;
			onResize();
			return true;
		}
		else if (sfEvent.key.code == sf::Keyboard::Up) {
			m_selectedData--;
			if (m_selectedData < 0)
				m_selectedData = 3;
			onResize();
			return true;
		}
		else if (sfEvent.key.code == sf::Keyboard::Left) {
			if (m_overPixel) {
				PixelData pixel(m_lastPixelData);
				if (m_selectedData == 0) {
					pixel.id -= sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ? 10 : 1;
				}
				else if (m_selectedData == 1) {
					pixel.data1 -= sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ? 10 : 1;
				}
				else if (m_selectedData == 2) {
					pixel.data2 -= sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ? 10 : 1;
				}
				else if (m_selectedData == 3) {
					pixel.data2 -= sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ? 10 : 1;
				}

				DrawInstruction instruction(
					pixel.toUInt32(),
					m_hoveredPixelPos,
					m_hoveredPixelPos,
					DrawInstruction::Type::LINE,
					1.0f,
					nullptr);

				std::lock_guard<std::mutex> lock(m_simulation->m_drawingMutex);
				m_simulation->m_collectedDrawInstructions.push_back(instruction);

				return true;
			}
		}
		else if (sfEvent.key.code == sf::Keyboard::Right) {
			if (m_overPixel) {
				PixelData pixel(m_lastPixelData);
				if (m_selectedData == 0) {
					pixel.id += sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ? 10 : 1;
				}
				else if (m_selectedData == 1) {
					pixel.data1 += sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ? 10 : 1;
				}
				else if (m_selectedData == 2) {
					pixel.data2 += sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ? 10 : 1;
				}
				else if (m_selectedData == 3) {
					pixel.data2 += sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) ? 10 : 1;
				}

				DrawInstruction instruction(
					pixel.toUInt32(),
					m_hoveredPixelPos,
					m_hoveredPixelPos,
					DrawInstruction::Type::LINE,
					1.0f,
					nullptr);

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

void InfoBox::update(float dt) {
	m_hoveredPixelPos = static_cast<sf::Vector2i>(m_simulation->getMouseWorldPos());

	sf::IntRect worldRect(0, 0, m_simulation->m_world->getMetaData().width,
		m_simulation->m_world->getMetaData().height);

	if (worldRect.contains(m_hoveredPixelPos)) {
		m_overPixel = true;
		uint32_t pixelData = m_simulation->m_world->getPixel(m_hoveredPixelPos.x, m_hoveredPixelPos.y);
		if (m_lastPixelData != pixelData) {
			m_lastPixelData = pixelData;
			PixelData pixel(m_lastPixelData);
			m_simulation->m_world->getMetaData().ruleset->getItemFromID(pixel.id).name;
			m_dataText.setText(
				m_simulation->m_world->getMetaData().ruleset->getItemFromID(pixel.id).name + "\n" +
				std::to_string(pixel.id) + "\n" +
				std::to_string(pixel.data1) + "\n" +
				std::to_string(pixel.data2) + "\n" +
				std::to_string(pixel.data3)
			);
		}
	}
	else {
		m_overPixel = false;
		m_dataText.setText("");
		m_lastPixelData = 0;
	}

	for (GuiElement* element : m_guiElements) {
		element->update(dt);
	}
}

void InfoBox::render(sf::RenderTarget& window) {
	if (!m_hideGui) {
		for (GuiElement* element : m_guiElements) {
			element->render(window);
		}
	}
}

void InfoBox::onResize() {
	sf::Vector2f windowSize = static_cast<sf::Vector2f>(Application::instance().getWindowSize());

	m_panel.setBounds(2, windowSize.y - 2 - 180, 200, 180);

	m_infoTitle.setBounds(8, 8, 170, m_infoTitle.getFontSize());
	m_infoText.setBounds(8, 50, 80, 130);
	m_dataText.setBounds(95, 50, 95, 130);

	m_selectedDataRect.setSize(165, ResourceManager::getPixelFont()->getLineSpacing(m_infoText.getFontSize()) * m_infoText.getLineSpacing());
	m_selectedDataRect.setPosition(4, 46 + (m_selectedData + 1) * m_selectedDataRect.getSize().y);
}

void InfoBox::resetAll() {
	m_selectedData = 0;
	onResize();
}

void InfoBox::setHideGui(bool hide) {
	m_hideGui = hide;
}
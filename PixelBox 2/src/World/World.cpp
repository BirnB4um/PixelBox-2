#include "World.h"

World::World() {
	m_metaData = WorldMetaData();
	m_worldDataFront = nullptr;
	m_worldDataBack = nullptr;
	m_worldRenderBuffer = nullptr;
}

World::World(WorldMetaData& metaData) : World() {
	setMetaData(metaData);
}

World::~World() {
	delete[] reinterpret_cast<uint32_t*>(m_worldDataFront);
	delete[] reinterpret_cast<uint32_t*>(m_worldDataBack);
	delete[] reinterpret_cast<uint32_t*>(m_worldRenderBuffer);
}

const WorldMetaData& World::getMetaData() {
	return m_metaData;
}

void World::clearWorld() {
	if (isCreated()) {
		m_drawInstructionList.clear();
		memset(m_worldDataFront, 0, m_metaData.width * m_metaData.height * 4);
		memset(m_worldDataBack, 0, m_metaData.width * m_metaData.height * 4);
		memset(m_worldRenderBuffer, 0, m_metaData.width * m_metaData.height * 4);
		m_updateList.clear();
		m_updateListNext.clear();
		m_renderUpdates.clear();
	}
}

bool World::save() {
	//TODO:
	return true;
}

bool World::load(WorldMetaData& metaData) {
	//TODO:
	return true;
}

void World::setMetaData(WorldMetaData& metaData) {
	//change world
	if (isCreated()) {
		//TODO:
	}

	m_metaData = metaData;
}

bool World::isCreated() const {
	return m_worldDataFront != nullptr;
}

void World::createWorld() {
	delete[] reinterpret_cast<uint32_t*>(m_worldDataFront);
	delete[] reinterpret_cast<uint32_t*>(m_worldDataBack);
	delete[] reinterpret_cast<uint32_t*>(m_worldRenderBuffer);

	//allocate using uint32_t to ensure 4 byte alignment for faster access and compatability with older systems (ARM & RISC)
	m_worldDataFront = reinterpret_cast<uint8_t*>(new uint32_t[m_metaData.width * m_metaData.height]);
	m_worldDataBack = reinterpret_cast<uint8_t*>(new uint32_t[m_metaData.width * m_metaData.height]);
	m_worldRenderBuffer = reinterpret_cast<uint8_t*>(new uint32_t[m_metaData.width * m_metaData.height]);
	m_updateList.setMaxSize(m_metaData.width * m_metaData.height);
	m_updateListNext.setMaxSize(m_metaData.width * m_metaData.height);
	m_renderUpdates.setMaxSize(m_metaData.width * m_metaData.height);
	clearWorld();

	//DEBUG
	for (size_t i = 0; i < m_metaData.width * m_metaData.height * 4; i += 4) {
		m_worldDataFront[i] = rand() % 255;
		m_worldDataFront[i + 1] = rand() % 255;
		m_worldDataFront[i + 2] = rand() % 255;
		m_worldDataFront[i + 3] = 255;
	}
}

void World::tick() {
	if (!isCreated())
		return;

	//return if no pixels need to be updated
	int numPixelsToUpdate = m_updateList.size();
	if (numPixelsToUpdate == 0)
		return;

	//copy changed pixels
	for (size_t i : m_updateList.getItems()) {
		reinterpret_cast<uint32_t*>(m_worldDataBack)[i] = reinterpret_cast<uint32_t*>(m_worldDataFront)[i];
	}
	m_updateListNext.clear();

	//apply rules
	m_metaData.ruleset->updateAllPixels(this);

	//switch buffers
	m_updateList.swap(m_updateListNext);
	std::swap(m_worldDataFront, m_worldDataBack);
}

void World::drawToWorld() {
	if (!isCreated())
		return;

	if (m_drawInstructionList.size() > 0) {

		//draw to board
		for (DrawInstruction& instruction : m_drawInstructionList) {
			

			if (instruction.type == DrawInstruction::Type::LINE) {

				//FIXME: dont just snap to board edges, find the next position that is inside the board
				//FIXME: optimize the shit out of this, probably by better algorithm + drawing directly to renderBuffer (which causes tearing)

				//constrain positions to board size
				instruction.startPos.x = Utils::constrain(instruction.startPos.x, 0, static_cast<int>(m_metaData.width) - 1);
				instruction.startPos.y = Utils::constrain(instruction.startPos.y, 0, static_cast<int>(m_metaData.height) - 1);

				instruction.endPos.x = Utils::constrain(instruction.endPos.x, 0, static_cast<int>(m_metaData.width) - 1);
				instruction.endPos.y = Utils::constrain(instruction.endPos.y, 0, static_cast<int>(m_metaData.height) - 1);
				instruction.width = std::max(instruction.width, 1.0f);

				//swap positions if needed
				if (instruction.startPos.x > instruction.endPos.x) {
					std::swap(instruction.startPos.x, instruction.endPos.x);
					std::swap(instruction.startPos.y, instruction.endPos.y);
				}

				int dx = instruction.endPos.x - instruction.startPos.x;
				double m = (double(instruction.endPos.y) - instruction.startPos.y) / ((dx == 0) ? 1 : dx);

				int next_y = instruction.startPos.y;
				int last_y = instruction.startPos.y;
				int y;
				for (int x = instruction.startPos.x; x <= instruction.endPos.x; ++x) {

					next_y = instruction.startPos.y + floor(m * (x - instruction.startPos.x + ((dx == 0) ? 1 : 0)));

					for (y = next_y; (next_y >= last_y && y >= last_y) || (next_y < last_y && y <= last_y); y += next_y >= last_y ? -1 : 1) {

						if (y < 0)
							break;

						if (y < m_metaData.height) {

							//brushsize
							for (int _y = y - (instruction.width - 1); _y < y + instruction.width; _y++) {
								for (int _x = x - (instruction.width - 1); _x < int(x + instruction.width); _x++) {

									if (_y >= 0 && _y < m_metaData.height && _x >= 0 && _x < m_metaData.width) {
										if (sqrt((_x - x) * (_x - x) + (_y - y) * (_y - y)) <= instruction.width - 1) {

											reinterpret_cast<uint32_t*>(m_worldDataFront)[_x + _y * m_metaData.width] = instruction.pixelData;
											m_renderUpdates.add(_x + _y * m_metaData.width);

											for (int uy = Utils::constrain(_y - 1, 1, static_cast<int>(m_metaData.height) - 2); uy <= Utils::constrain(_y + 1, 1, static_cast<int>(m_metaData.height) - 2); ++uy) {
												for (int ux = Utils::constrain(_x - 1, 1, static_cast<int>(m_metaData.width) - 2); ux <= Utils::constrain(_x + 1, 1, static_cast<int>(m_metaData.width) - 2); ++ux) {
													m_updateList.add(ux + uy * m_metaData.width);
													//this code runs 7 for loop deep lol
													//TODO: optimize, but i currently don't care
												}
											}

										}
									}
								}
							}

						}
					}
					last_y = next_y;

				}
			}
			else if (instruction.type == DrawInstruction::Type::RECTANGLE) {

				//constrain positions to board size
				instruction.startPos.x = Utils::constrain(instruction.startPos.x, 0, static_cast<int>(m_metaData.width) - 1);
				instruction.startPos.y = Utils::constrain(instruction.startPos.y, 0, static_cast<int>(m_metaData.height) - 1);
				instruction.endPos.x = Utils::constrain(instruction.endPos.x, 0, static_cast<int>(m_metaData.width) - 1);
				instruction.endPos.y = Utils::constrain(instruction.endPos.y, 0, static_cast<int>(m_metaData.height) - 1);

				//swap positions if needed
				if (instruction.startPos.x > instruction.endPos.x) {
					std::swap(instruction.startPos.x, instruction.endPos.x);
				}
				if (instruction.startPos.y > instruction.endPos.y) {
					std::swap(instruction.startPos.y, instruction.endPos.y);
				}

				//copy pixel data to board + add to renderList
				for (size_t y = instruction.startPos.y; y <= instruction.endPos.y; ++y) {
					for (size_t x = instruction.startPos.x; x <= instruction.endPos.x; ++x) {
						reinterpret_cast<uint32_t*>(m_worldDataFront)[x + y * m_metaData.width] = instruction.pixelData;
						m_renderUpdates.add(x + y * m_metaData.width);
					}
				}

				//add to update list
				instruction.startPos.x = Utils::constrain(instruction.startPos.x - 1, 1, static_cast<int>(m_metaData.width) - 2);
				instruction.startPos.y = Utils::constrain(instruction.startPos.y - 1, 1, static_cast<int>(m_metaData.height) - 2);
				instruction.endPos.x = Utils::constrain(instruction.endPos.x + 1, 1, static_cast<int>(m_metaData.width) - 2);
				instruction.endPos.y = Utils::constrain(instruction.endPos.y + 1, 1, static_cast<int>(m_metaData.height) - 2);
				for (size_t y = instruction.startPos.y; y <= instruction.endPos.y; ++y) {
					for (size_t x = instruction.startPos.x; x <= instruction.endPos.x; ++x) {
						m_updateList.add(x + y * m_metaData.width);
					}
				}

			}
			else if (instruction.type == DrawInstruction::Type::FILL) {

				//constrain positions to board size
				instruction.startPos.x = Utils::constrain(instruction.startPos.x, 0, static_cast<int>(m_metaData.width) - 1);
				instruction.startPos.y = Utils::constrain(instruction.startPos.y, 0, static_cast<int>(m_metaData.height) - 1);

				uint8_t itemIDtoOverride = m_worldDataFront[(instruction.startPos.y * m_metaData.width + instruction.startPos.x) * 4];
				uint8_t itemID = *reinterpret_cast<uint8_t*>(&instruction.pixelData);

				if (itemIDtoOverride == itemID)
					continue;

				std::vector<size_t> test_list;
				test_list.reserve(4 * 1000);
				test_list.push_back(instruction.startPos.y * m_metaData.width + instruction.startPos.x);

				size_t next_i;
				while (test_list.size() > 0) {
					next_i = test_list[test_list.size() - 1];
					test_list.pop_back();

					uint8_t id = m_worldDataFront[next_i * 4];
					if (id == itemIDtoOverride) {
						reinterpret_cast<uint32_t*>(m_worldDataFront)[next_i] = instruction.pixelData;
						m_renderUpdates.add(next_i);
						m_updateList.add(next_i);

						if (next_i % m_metaData.width > 0) {
							test_list.push_back(next_i - 1);

						}

						if (next_i % m_metaData.width < m_metaData.width - 1) {
							test_list.push_back(next_i + 1);

						}

						if (next_i <= m_metaData.width * (m_metaData.height - 1)) {
							test_list.push_back(next_i + m_metaData.width);

						}

						if (next_i >= m_metaData.width) {
							test_list.push_back(next_i - m_metaData.width);

						}
					}
				}
			}
			else if (instruction.type == DrawInstruction::Type::STRUCTURE) {

			}

		}

		m_drawInstructionList.clear();
	}
}

void World::addDrawInstruction(DrawInstruction& drawInstruction) {
	if (!isCreated())
		return;

	m_drawInstructionList.push_back(drawInstruction);
}

void World::addDrawInstruction(std::vector<DrawInstruction>& drawInstructionList) {
	if (!isCreated())
		return;

	//extend m_drawInstructionList with drawInstructionList
	m_drawInstructionList.reserve(m_drawInstructionList.size() + drawInstructionList.size());
	m_drawInstructionList.insert(m_drawInstructionList.end(), drawInstructionList.begin(), drawInstructionList.end());
}

void World::updateRenderBuffer() {
	for (size_t item : m_renderUpdates.getItems()) {
		reinterpret_cast<uint32_t*>(m_worldRenderBuffer)[item] = reinterpret_cast<uint32_t*>(m_worldDataFront)[item];
	}
	m_renderUpdates.clear();
}

bool World::renderBufferHasChanges() {
	return m_renderUpdates.size() > 0;
}

uint8_t* World::getRenderBuffer() {
	return m_worldRenderBuffer;
}

void World::updateAllPixels() {
	for (size_t y = 1; y < m_metaData.height - 1; ++y) {
		for (size_t x = 1; x < m_metaData.width - 1; ++x) {
			size_t i = y * m_metaData.width + x;
			m_updateList.add(i);
		}
	}
}

void World::redrawWorld() {
	for (size_t i = 0; i < m_metaData.width * m_metaData.height * 4; ++i) {
		m_worldRenderBuffer[i] = m_worldDataFront[i];
	}
	m_renderUpdates.add(0);
}
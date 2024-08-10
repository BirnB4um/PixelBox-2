#include "Ruleset.h"

Ruleset::Ruleset() {
	m_id = 0;
}

Ruleset::~Ruleset() {

}


uint64_t Ruleset::getID() {
	return m_id;
}
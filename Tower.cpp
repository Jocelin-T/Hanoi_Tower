/*****************************************************************//**
 * @file   Tower.cpp
 * @brief  Class Tower
 * 
 * @author ThJo
 * @date   12 June 2024
 *********************************************************************/
#include "Tower.h"

namespace logic {
	// Construct a Tower with no value
	Tower::Tower(const std::string& tower_name)
	: m_tower_name{ tower_name }
	{}


	// Construct a Tower with value in format from high -> low (3,2,1)
	Tower::Tower(const std::string& tower_name, size_t tower_height)
	: m_tower_name{ tower_name }
	{
		for (size_t i = tower_height; i > 0; i--) {
			m_tower_stack.push_back(i);
		}
	}


	// Return the name of the tower
	std::string Tower::GetTowerName() const {
		return m_tower_name;
	}


	// Check if the vector is empty
	bool Tower::IsTowerEmpty() const {
		return m_tower_stack.empty();
	}


	// Check if the given value is present in the tower
	bool Tower::IsElementPresentInTower(int value) const {
		if (!IsTowerEmpty()) {
			for (int tower_value : m_tower_stack) {
				if (tower_value == value) {
					return true;
				}
			}
		}
		return false;
	}


	// Return a pointer of the vector of this Tower (not used)
	std::vector<int>* Tower::GetTowerStack() const {
		return const_cast<std::vector<int>*>(&m_tower_stack);
	}


	// Return the size of the vector
	int Tower::GetTowerSize() const	{
		return m_tower_stack.size();
	}


	// Return the value at the given index
	int Tower::GetTowerFloor(size_t floor) const {
		if (floor >= m_tower_stack.size() || IsTowerEmpty()) {
			return 0;
		}
		return m_tower_stack[floor];
	}


	// Return the value of the last element of the vector
	int Tower::GetBottomElement() const {
		if (!IsTowerEmpty()) {
			return m_tower_stack.front();
		}
		return 0;
	}


	// Return the value of the 1st element of the vector
	int Tower::GetTopElement() const {
		if (!IsTowerEmpty()) {
			return m_tower_stack.back();
		}
		return 0;
	}


	// Check if the tower is stable, the next value NEED to always be lower
	bool Tower::IsTowerStable() const {
		if (GetTowerSize() > 1) {
			for (size_t i = 0; i < GetTowerSize(); i++) {
				unsigned short int previous_floor = GetTowerFloor(i);
				unsigned short int current_floor = GetTowerFloor(i + 1);

				if (current_floor > previous_floor) {
					return false;
				}
			}
		}
		return true;
	}


	// Add an value at the back of the vector
	void Tower::AddTopElement(size_t value) {
		m_tower_stack.push_back(value);
	}


	// Remove the last value of the vector
	void Tower::RemoveTopElement() {
		if (!IsTowerEmpty()) {
			m_tower_stack.pop_back();
		}
	}


	// Clear the tower
	void Tower::ClearTower() {
		m_tower_stack.clear();
	}

} // namespace logic

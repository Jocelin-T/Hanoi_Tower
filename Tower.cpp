/*****************************************************************//**
 * @file   Tower.cpp
 * @brief  Class Tower
 * 
 * @author ThJo
 * @date   12 June 2024
 *********************************************************************/
#include "Tower.h"

namespace logic {
	
	Tower::Tower(const std::string& tower_name)
	: m_tower_name{ tower_name }
	{}

	// {3,2,1}
	Tower::Tower(const std::string& tower_name, const int tower_height)
	: m_tower_name{ tower_name }
	{
		for (int i = tower_height; i > 0; i--) {
			m_tower_stack.push_back(i);
		}
	}

	// Get the name of the tower
	std::string Tower::GetTowerName() const {
		return m_tower_name;
	}

	// Check if the vector is empty
	bool Tower::IsTowerEmpty() const {
		return m_tower_stack.empty();
	}

	// Check if the given value is present in the tower
	bool Tower::IsElementPresentInTower(const int value) const {
		if (!IsTowerEmpty()) {
			for (int tower_value : m_tower_stack) {
				if (tower_value == value) {
					return true;
				}
			}
		}
		return false;
	}

	// Get a pointer of the vector of this Tower
	std::vector<int>* Tower::GetTowerStack() const {
		return const_cast<std::vector<int>*>(&m_tower_stack);
	}

	// Get the size of the vector
	int Tower::GetTowerSize() const	{
		return m_tower_stack.size();
	}

	// Get the value at the given index
	int Tower::GetTowerFloor(const int floor) const {
		if (floor < 0 || floor >= m_tower_stack.size() || IsTowerEmpty()) {
			return 0;
		}
		return m_tower_stack[floor];
	}

	// Get the value of the last element of the vector
	int Tower::GetBottomElement() const {
		if (!IsTowerEmpty()) {
			return m_tower_stack.front();
		}
		return 0;
	}

	// Get the value of the 1st element of the vector
	int Tower::GetTopElement() const {
		if (!IsTowerEmpty()) {
			return m_tower_stack.back();
		}
		return 0;
	}

	// Check if the tower is stable, the next value NEED to always be lower
	bool Tower::IsTowerStable() const {
		if (GetTowerSize() > 1) {
			//std::cout << "call: "<< GetTowerName() << "\n"; // DEBUG
			for (int i = 0; i < GetTowerSize(); i++) {
				int previous_floor = GetTowerFloor(i);
				int current_floor = GetTowerFloor(i + 1);

				//std::cout  << " current: " << current_floor << " previous: " << previous_floor << "\n"; // DEBUG

				if (current_floor > previous_floor) {
					return false;
				}
			}
		}
		return true;
	}

	// Add an value at the back of the vector
	void Tower::AddTopElement(const int value) {
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

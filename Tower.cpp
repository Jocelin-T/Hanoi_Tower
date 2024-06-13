/*****************************************************************//**
 * @file   Tower.cpp
 * @brief  Class Tower
 * 
 * @author ThJo
 * @date   12 June 2024
 *********************************************************************/
#include "Tower.h"

Tower::Tower(const int tower_height){
	for (int i = tower_height; i > 0; i--) {
		m_tower_stack.push_back(i);
	}
}

bool Tower::IsTowerEmpty(){

	return false;
}

int Tower::GetTowerSize(){
	return m_tower_stack.size();
}

int Tower::GetFirstElement(){

	return 0;
}

int Tower::GetLastElement(){

	return 0;
}

bool Tower::CheckTowerStability(){

	return false;
}

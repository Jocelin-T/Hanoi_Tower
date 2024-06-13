/*****************************************************************//**
 * @file   Tower.h
 * @brief  Class Tower
 * 
 * @author ThJo
 * @date   12 June 2024
 *********************************************************************/
#pragma once
#include <iostream>
#include <stack> // push pop
#include <vector>


class Tower{
public:
	// Default Tower Constructor
	Tower() = default;

	// First Tower Constructor
	Tower(const int tower_height);

	bool IsTowerEmpty();

	int GetTowerSize();

	int GetFirstElement();

	int GetLastElement();

private:
	std::vector<int> m_tower_stack;

	bool CheckTowerStability();

};


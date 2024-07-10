/*****************************************************************//**
 * @file   Tower_Connection.h
 * @brief  This file will manage all interactions and logic between the Towers
 *
 * @author ThJo
 * @date   17 June 2024
 *********************************************************************/
#pragma once
#include <sstream>
#include <string>
#include <vector>

#include "User_Interaction.h"
#include "Tower.h"


namespace logic {
	// Super Global variables
	inline constexpr unsigned short int NBR_TOWER{ 3 };
	inline constexpr unsigned short int MIN_TOWER_HIGH{ 3 };
	inline constexpr unsigned short int MAX_TOWER_HIGH{ 10 };
	inline unsigned short int first_tower_height{ 0 };
	inline std::string general_algo_message{ "" };
	inline std::string general_error_message{ "" };
	inline bool algorithm_done{ false };


	// Struct of static_array, because can't make vector of static_array,
	//	but can make a vector of struct holding a static_array
	struct TowersStep {
		Tower m_array_towers[NBR_TOWER];
		std::string m_step_message{ "" };
		TowersStep(const Tower array_tower[]);
	};

	// Super Global vector (need to be after the struct declaration)
	inline std::vector<TowersStep> vec_steps;

	/** ***************************************** Towers set up *****************************************
	* @brief : Set up the 3 towers.
	*
	* @param value_t1 : int => Height of the 1st Tower, a value is required
	* @param value_t2 : int => Height of the 2nd Tower, default is {0}
	* @param value_t3 : int => Height of the 3th Tower, default is {0}
	*/
	void SetUpTowers(int value_t1, int value_t2 = 0, int value_t3 = 0);

	/** ***************************************** Algorithm *****************************************
	 * @brief : Algorithm for the Hanoi Towers.
	 *
	 */
	void AlgorithmStart();

} // namespace logic

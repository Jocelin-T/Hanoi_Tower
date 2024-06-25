/*****************************************************************//**
 * @file   Tower_Connection.cpp
 * @brief  This file will manage all interactions and logic between the Towers
 * 
 * @author ThJo
 * @date   17 June 2024
 *********************************************************************/
#include "Tower_Connection.h"


namespace logic {
	// Global variable
	int nbr_step{ 0 };

	// Definitions
	Tower array_obj_towers[NBR_TOWER];

	// Implementation of TowersStep constructor
	TowersStep::TowersStep(const Tower array_tower[]) {
		for (int i = 0; i < NBR_TOWER; ++i) {
			m_array_towers[i] = array_tower[i]; // Assuming Tower has a copy constructor
		}
	}

	// Function declaration
	void MoveValueToTower(Tower& from_tower, Tower& to_tower);
	void AlgorithmStop();
	void CreateAlgorithmFirstStep();
	void CreateAlgorithmStep(std::ostringstream& oss);

	// Alias for easier readability
	Tower& t1 = array_obj_towers[0];
	Tower& t2 = array_obj_towers[1];
	Tower& t3 = array_obj_towers[2];

	// Set up the 3 towers.
	void SetUpTowers(int value_t1, int value_t2, int value_t3) {
		// Set the first tower using the parameter constructor
		t1 = Tower("t1", value_t1);
		t2 = Tower("t2", value_t2);
		t3 = Tower("t3", value_t3);

		// Creation of the first step
		CreateAlgorithmFirstStep();
	}

	// ****** THE ALGORITHM ******
	void AlgorithmRunning() {

		while (!algorithm_done) {
			MoveValueToTower(t1, t2);
			MoveValueToTower(t2, t1);

		}
	}

	// Create the first step of the towers stats
	void CreateAlgorithmFirstStep() {
		TowersStep first_step(array_obj_towers);
		vec_steps.push_back(first_step);
	}

	// Create a step of the algorithm 
	void CreateAlgorithmStep(std::ostringstream& oss) {
		TowersStep step(array_obj_towers);
		step.step_message = oss.str();
		vec_steps.push_back(step);
	}

	// Move a value from a tower to another
	void MoveValueToTower(Tower& from_tower, Tower& to_tower) {
		// Check if tower is NOT empty and addresses of the given Towers are NOT the same
		if (!from_tower.IsTowerEmpty() && &from_tower != &to_tower) {
			int temp_value = from_tower.GetTopElement();
			to_tower.AddTopElement(temp_value);
			from_tower.RemoveTopElement();

			// Creation of a message for this step
			std::ostringstream oss;
			oss << from_tower.GetTowerName() << " -- " << temp_value << " -> " << to_tower.GetTowerName() << "\n";

			// Create a step of this move
			CreateAlgorithmStep(oss);

		}
		else {
			general_error_message = "Empty Tower or same Towers selected";
		}
		// Check if the algo is done
		AlgorithmStop();
	}

	// Check if the last tower has the correct result or after x step
	void AlgorithmStop() {
		nbr_step++;
		if (nbr_step == 100) {
			algorithm_done = true;
			general_algo_message = "Algorithm max steps!";
		}
		if (t3.GetTowerSize() == first_tower_height
			&& t3.IsTowerStable()) {
			algorithm_done = true;
			general_algo_message = "Algorithm done!";
		}
	}




} // namespace logic
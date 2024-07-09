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
	const int START_STEP{ 1 };
	const int MAX_STEP{ 1000 };
	const std::string TOWER_1_NAME{ "t1" };
	const std::string TOWER_2_NAME{ "t2" };
	const std::string TOWER_3_NAME{ "t3" };

	int nbr_step{ START_STEP };
	bool final_phase_start{ false };
	bool algorithm_is_even{ false };
	int elements_1_2_phase{ 1 };
	bool ignore_phase_check{ false };


	// Definition
	Tower array_obj_towers[NBR_TOWER];

	// Implementation of TowersStep constructor
	TowersStep::TowersStep(const Tower array_tower[]) {
		for (int i = 0; i < NBR_TOWER; ++i) {
			m_array_towers[i] = array_tower[i]; // Assuming Tower has a copy constructor
		}
	}

	// Function declaration
	void ResetAlgorithm();
	void CreateAlgorithmFirstStep();
	void CreateAlgorithmStep(Tower& from_tower, Tower& to_tower, int temp_value);
	void AlgorithmCheckNextPhase();
	void AlgorithmCheckStepStatus(const Tower& to_tower);
	Tower& FindTowerWithLowestElementAtTop();
	Tower& FindElement(const int value);

	Tower& GetOtherTower(const Tower& tower_a, const Tower& tower_b);
	void MoveFloorToTower(Tower& from_tower, Tower& to_tower, bool ignore_phase_check = false);
	void MoveElements1And2To(Tower& from_tower, Tower& to_tower);
	void LoopElements1And2();
	void FinalAlgorithmPhase();

	// Alias for easier readability
	Tower& t1 = array_obj_towers[0];
	Tower& t2 = array_obj_towers[1];
	Tower& t3 = array_obj_towers[2];

	// Pointers for last movement of elements (1) and (2)
	Tower* p_last_move_elements_1_2 = nullptr;
	Tower* p_before_last_move_elements_1_2 = nullptr;

	// Initialization of ptr
	Tower& tower_a{ t1 };
	Tower* p_tower_b = nullptr;
	Tower* p_tower_c = nullptr;


	// Set up the 3 towers.
	void SetUpTowers(const int value_t1, const int value_t2, const int value_t3) {
		ResetAlgorithm();

		// Set the first tower using the parameter constructor
		t1 = Tower(TOWER_1_NAME, value_t1);
		t2 = Tower(TOWER_2_NAME, value_t2);
		t3 = Tower(TOWER_3_NAME, value_t3);

		// Creation of the first step
		CreateAlgorithmFirstStep();
	}


	// Reset all global variables, Towers
	void ResetAlgorithm() {
		nbr_step = START_STEP;
		algorithm_done = false;
		algorithm_is_even = false;
		final_phase_start = false;
		ignore_phase_check = false;
		elements_1_2_phase = 1;
		general_algo_message = "";
		general_error_message = "";
		vec_steps.clear();

		t1.ClearTower();
		t2.ClearTower();
		t3.ClearTower();

		p_last_move_elements_1_2 = nullptr;
		p_before_last_move_elements_1_2 = nullptr;

		p_tower_b = nullptr;
		p_tower_c = nullptr;
	}


	// Create the first step of the towers stats
	void CreateAlgorithmFirstStep() {
		TowersStep first_step(array_obj_towers);
		first_step.m_step_message = "Step_0\n";
		vec_steps.push_back(first_step);
	}


	// Create a step of the algorithm 
	void CreateAlgorithmStep(Tower& from_tower, Tower& to_tower, int temp_value) {

		// Creation of this step array
		TowersStep step(array_obj_towers);

		// Creation of a message for this step
		std::ostringstream oss;
		oss << "Step_" << nbr_step << " :\t" << from_tower.GetTowerName()
			<< " --(" << temp_value << ")-> " << to_tower.GetTowerName() << "\n";
		step.m_step_message = oss.str();

		std::cout << oss.str(); // DEBUG

		// Add the step in the vector
		vec_steps.push_back(step);
	}


	// ****** THE ALGORITHM ******
	void AlgorithmStart() {
		// Determine if the Tower is even or odd (check if the last bit is 1 or 0)
		if (first_tower_height & 1) { // ODD
			p_last_move_elements_1_2 = &t3;
			LoopElements1And2();
		}
		else { // EVEN
			algorithm_is_even = true;
			p_last_move_elements_1_2 = &t2;
			LoopElements1And2();
		}
	}


	// In case all floors are set on T3 but the 2 last, will find them and move them
	void FinalAlgorithmPhase() {
		std::cout << "FinalAlgorithmPhase ()\n"; // DEBUG

		Tower& tower_elem_1 = FindElement(1);
		Tower& tower_elem_2 = FindElement(2);

		// If the elements (1) and (2) have the same Tower address
		if (&tower_elem_1 == &tower_elem_2) {
			Tower& other_tower = GetOtherTower(tower_elem_1, t3);
			MoveFloorToTower(tower_elem_1, other_tower);
			MoveFloorToTower(tower_elem_1, t3);
			MoveFloorToTower(other_tower, t3);
		}
		// Else move the element (2) on T3, then the element (1)
		else {
			MoveFloorToTower(tower_elem_2, t3);
			MoveFloorToTower(tower_elem_1, t3);
		}
	}


	// Move a value from a tower to another tower
	void MoveFloorToTower(Tower& from_tower, Tower& to_tower, bool ignore_phase_check) {

		std::cout << "MoveFloorToTower (" 
			<< "from_tower: " << from_tower.GetTowerName()
			<< " to_tower: " << to_tower.GetTowerName() 
			<< " ignore: " << ignore_phase_check << ")\n"; // DEBUG

		// Check if the algo is done (probably tower unstable)
		if (!algorithm_done) {

			// Check if from_tower is NOT empty
			if (from_tower.IsTowerEmpty()) {
				algorithm_done = true;
				std::ostringstream oss;
				oss << "Empty Tower: " << from_tower.GetTowerName()
					<< " at step_" << nbr_step << "\n";
				general_error_message = oss.str();
				return;
			}
			// Check if addresses of the given Towers are NOT the same
			if (&from_tower == &to_tower) {
				algorithm_done = true;
				std::ostringstream oss;
				oss << " Same Towers selected: " << from_tower.GetTowerName()
					<< "-" << to_tower.GetTowerName() 
					<< " at step_" << nbr_step << "\n";
				general_error_message = oss.str();
				return;
			}

			// Pass a value from a Tower to another Tower
			int temp_value = from_tower.GetTopElement();
			to_tower.AddTopElement(temp_value);
			from_tower.RemoveTopElement();

			// Create a step of this move
			CreateAlgorithmStep(from_tower, to_tower, temp_value);
			
			// Check if the algo is done
			AlgorithmCheckStepStatus(to_tower);

			std::cout << "move done from_tower: " << from_tower.GetTowerName()
				<< " to_tower: " << to_tower.GetTowerName() << "\n";


			// Check for the next phase
			if (!ignore_phase_check) {
				AlgorithmCheckNextPhase();
			}
			else { // DEBUG
				std::cout << "phase ignored at step_" << nbr_step - 1 << "\n";
			}
		}
	}


	// Move the Elements (1) and (2) from a Tower to another Tower
	void MoveElements1And2To(Tower& from_tower, Tower& to_tower) {
		std::cout << "MoveElements1And2To (" 
			<< "from_tower: " << from_tower.GetTowerName()
			<< " to_tower: " << to_tower.GetTowerName() << ")\n";

		// Set the last movement
		p_before_last_move_elements_1_2 = p_last_move_elements_1_2;
		p_last_move_elements_1_2 = &from_tower;
		
		// Check if pointers are valid
		if (!p_before_last_move_elements_1_2 || !p_last_move_elements_1_2) {
			std::cerr << "Error: p_before_last_move_elements_1_2 or p_last_move_elements_1_2 not set correctly.\n";
			return;
		}

		std::cout << "last: " << p_last_move_elements_1_2->GetTowerName()
			<< " before_last: " << p_before_last_move_elements_1_2->GetTowerName() << "\n";

		// Determine the other_tower
		Tower& other_tower = GetOtherTower(from_tower, to_tower);

		std::cout << "from_tower: " << from_tower.GetTowerName()
			<< " to_tower: " << to_tower.GetTowerName()
			<< " other_tower: " << other_tower.GetTowerName() << "\n";

		// Prepare the phase for the next call
		elements_1_2_phase++;
		std::cout << "prepare for next phase :" << elements_1_2_phase << "\n";
		MoveFloorToTower(from_tower, other_tower, true);
		MoveFloorToTower(from_tower, to_tower, true);
		
		// Don't ignore the next phase to find which element need to be moved
		MoveFloorToTower(other_tower, to_tower);


	}


	// Move the elements (1) and (2) to the next phase
	void LoopElements1And2() {
		std::cout << "LoopElements1And2 ()\n"; // DEBUG

		// Order for ODD of the Elements (1) and (2): T1 -> T2 -> T3 --> T1...
		// Order for EVEN of the Elements (1) and (2): T1 -> T3 -> T2 --> T1...

		std::cout << "initial tower_a: " << tower_a.GetTowerName() << "\n";

		// Set the Towers b and c for odd or even number
		if (!p_tower_b && !p_tower_c) {
			// if ODD
			if (!algorithm_is_even) {
				p_tower_b = &t2;
				p_tower_c = &t3;
				std::cout << "is odd\n";
			}
			// if EVEN
			else {
				p_tower_b = &t3;
				p_tower_c = &t2;
				std::cout << "is even\n";
			}
		}

		// Reset the phase to 1 when too high
		if (elements_1_2_phase > NBR_TOWER) {
			elements_1_2_phase = 1;
			std::cout << "phase reset to 1\n";
		}

		// Check if pointers are valid
		if (!p_tower_b || !p_tower_c) {
			std::cerr << "Error: p_tower_b or p_tower_c not set correctly.\n";
			return;
		}

		std::cout << "loop tower_a: " << tower_a.GetTowerName() << " at: " << &tower_a
			<< "\n p_tower_b: " << p_tower_b->GetTowerName() << " at: " << &p_tower_b
			<< "\n p_tower_c: " << p_tower_c->GetTowerName() << " at: " << &p_tower_c << "\n";

		// Make the required phase
		if (elements_1_2_phase == 1) {
			std::cout << "phase 1\n";
			MoveElements1And2To(tower_a, *p_tower_b);
		}
		else if (elements_1_2_phase == 2) {
			std::cout << "phase 2\n";
			MoveElements1And2To(*p_tower_b, *p_tower_c);
		}
		else if (elements_1_2_phase == 3) {
			std::cout << "phase 3\n";
			MoveElements1And2To(*p_tower_c, tower_a);
		}
	}


	// Get the non-selected tower
	Tower& GetOtherTower(const Tower& tower_a, const Tower& tower_b) {
		std::string tower_a_name = tower_a.GetTowerName();
		std::string tower_b_name = tower_b.GetTowerName();
		if (tower_a_name == TOWER_1_NAME && tower_b_name == TOWER_2_NAME
			|| tower_a_name == TOWER_2_NAME && tower_b_name == TOWER_1_NAME) {
			return t3;
		}
		if (tower_a_name == TOWER_1_NAME && tower_b_name == TOWER_3_NAME
			|| tower_a_name == TOWER_3_NAME && tower_b_name == TOWER_1_NAME) {
			return t2;
		}
		return t1;
	}


	// Check what need to be the next phase of the algorithm
	void AlgorithmCheckNextPhase() {
		std::cout << "AlgorithmCheckNextPhase ()\n"; // DEBUG

		if (!final_phase_start && !algorithm_done) {

			std::cout << "phase NOT ignored at step_" << nbr_step - 1 << "\n";

			// Check if the algorithm can start is final phase
			if (!t3.IsElementPresentInTower(1)
				&& !t3.IsElementPresentInTower(2)
				&& t3.GetTowerSize() == first_tower_height - 2) {

				final_phase_start = true;
				FinalAlgorithmPhase();
			}
			// Else start the next phase
			else {
				// Get the lowest top element, ignore (1) and (2)
				Tower& tower_lowest_top_element = FindTowerWithLowestElementAtTop();

				// ODD
				if (tower_lowest_top_element.GetTopElement() & 1) {
					MoveFloorToTower(tower_lowest_top_element, *p_before_last_move_elements_1_2, true);
					std::cout << "---------------\n";
					LoopElements1And2();

				}
				// EVEN
				else {
					MoveFloorToTower(tower_lowest_top_element, *p_last_move_elements_1_2, true);
					std::cout << "---------------\n";
					LoopElements1And2();
				}

			}
		}
	}


	// Check if the T3 has break, has the correct result, has too much step
	void AlgorithmCheckStepStatus(const Tower& to_tower) {

		std::cout << "AlgorithmCheckStepStatus (to_tower: " << to_tower.GetTowerName() << ")\n"; // DEBUG

		// Check if the receiving Tower break
		if (!to_tower.IsTowerStable()) {
			algorithm_done = true;
			std::ostringstream oss;
			oss << "Tower " << to_tower.GetTowerName() << " break! At step_" << nbr_step << "\n";
			general_error_message = oss.str();
		}
		// Check if T3 is complete (Victory!)
		else if (t3.GetTowerSize() == first_tower_height) {
			algorithm_done = true;
			std::ostringstream oss;
			oss << "Algorithm done! step_" << nbr_step << "\n";
			general_algo_message = oss.str();
		}
		// Check if the limit of step is complete
		else if (nbr_step == MAX_STEP) {
			algorithm_done = true;
			std::ostringstream oss;
			oss << "Algorithm max steps! (" << MAX_STEP << ")\n";
			general_algo_message = oss.str();
		}
		nbr_step++;
	}


	// Find the Tower with the lowest element at is top, EXCLUDING (1) and (2)
	Tower& FindTowerWithLowestElementAtTop() {

		int min_element{ first_tower_height };
		Tower* min_tower = nullptr; // Pointer to the Tower with the lowest element

		for (Tower& current_tower : array_obj_towers) {
			if (!current_tower.IsTowerEmpty()) {
				int current_element = current_tower.GetTopElement();

				if (current_element <= min_element 
					&& current_element != 1
					&& current_element != 2) {

					min_element = current_element;
					min_tower = &current_tower; // Assign the pointer
				}
			}
		}

		// If no valid tower was found, handle the case appropriately
		if (min_tower == nullptr) {
			throw std::runtime_error("No valid tower found with the lowest element.");
		}

		return *min_tower; // Dereference the pointer to return the Tower reference
	}


	// Find the Tower holding the given element
	Tower& FindElement(const int value) {
		int current_tower{ 0 };
		for (Tower& tower : array_obj_towers) {
			if (tower.IsElementPresentInTower(value)) {
				return array_obj_towers[current_tower];
			}
			current_tower++;
		}
	}


} // namespace logic
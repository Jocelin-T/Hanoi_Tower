/*****************************************************************//**
 * @file   Tower.h
 * @brief  Class Tower
 * 
 * @author ThJo
 * @date   12 June 2024
 *********************************************************************/
#pragma once
#include <iostream>
#include <vector>

namespace logic {
	class Tower{
	public:
		// Constructor
		Tower() = default;
		Tower(const std::string& tower_name);
		Tower(const std::string& tower_name, const int tower_height);

		// Tower data
		/** ***************************************** Tower Name *****************************************
		 * @brief : Get the name of the tower.
		 * 
		 * @return  : std::string
		 */
		std::string GetTowerName() const;

		/** ***************************************** Is Tower empty *****************************************
		 * @brief : Check if the vector is empty.
		 * 
		 * @return  : boolean
		 */
		bool IsTowerEmpty() const;

		/** ***************************************** Get full Tower *****************************************
		 * @brief : Get a pointer of the vector of this Tower.
		 * 
		 * @return  : std::vector<int>*
		 */
		std::vector<int>* GetTowerStack() const;

		/** ***************************************** Tower size *****************************************
		 * @brief : Get the size of the vector.
		 * 
		 * @return  : int
		 */
		int GetTowerSize() const;

		/** ***************************************** Get Floor *****************************************
		 * @brief : Get the value at the given index.
		 * 
		 * @param floor : int => bottom of the tower is index [0]
		 * @return  : int => valueat this index
		 */
		int GetTowerFloor(const int floor) const;

		/** ***************************************** Get Top Tower *****************************************
		 * @brief : Get the value of the last element of the vector.
		 * 
		 * @return  : int
		 */
		int GetTopElement() const;

		/** ***************************************** Get Bottom Tower *****************************************
		 * @brief : Get the value of the 1st element of the vector.
		 * 
		 * @return  : int
		 */
		int GetBottomElement() const;

		/** ***************************************** Tower stability *****************************************
		 * @brief : Check if the tower is stable, the next value NEED to always be lower.
		 *
		 * @return  : boolean
		 */
		bool IsTowerStable() const;


		// Tower modification
		/** ***************************************** Add *****************************************
		 * @brief : Add an value at the back of the vector.
		 * 
		 * @param value : int => value to add
		 */
		void AddTopElement(const int value);

		/** ***************************************** Remove *****************************************
		 * @brief : Remove the last value of the vector.
		 * 
		 */
		void RemoveTopElement();


		//// Debug
		//void DisplayVector() {
		//	if (!IsTowerEmpty()) {
		//		for (int floor : m_tower_stack) {
		//			std::cout << m_tower_name << ": " << floor << "\n";
		//		}
		//	}
		//}

	private:
		std::string m_tower_name{ "Tower" };
		// The vector 
		std::vector<int> m_tower_stack;

	};
} // namespace logic


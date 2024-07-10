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
		// Constructors
		Tower() = default;
		Tower(const std::string& tower_name);
		Tower(const std::string& tower_name, size_t tower_height);


		// Tower data
		/** ***************************************** Tower Name *****************************************
		 * @brief : Return the name of the tower.
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


		/** ***************************************** TO DO *****************************************
		 * @brief : Check if the given value is present in the tower.
		 *
		 * @param value : int => value to find
		 * @return  : boolean
		 */
		bool IsElementPresentInTower(int value) const;


		/** ***************************************** Get full Tower *****************************************
		 * @brief : Return a pointer of the vector of this Tower.
		 * 
		 * @return  : std::vector<int>*
		 */
		std::vector<int>* GetTowerStack() const;


		/** ***************************************** Tower size *****************************************
		 * @brief : Return the size of the vector.
		 * 
		 * @return  : int
		 */
		int GetTowerSize() const;


		/** ***************************************** Get Floor *****************************************
		 * @brief : Return the value at the given index.
		 * 
		 * @param floor : size_t => bottom of the tower is index [0]
		 * @return  : int => value at this index
		 */
		int GetTowerFloor(size_t floor) const;


		/** ***************************************** Get Top Tower *****************************************
		 * @brief : Return the value of the last element of the vector.
		 * 
		 * @return  : int
		 */
		int GetTopElement() const;


		/** ***************************************** Get Bottom Tower *****************************************
		 * @brief : Return the value of the 1st element of the vector.
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
		 * @param value : size_t => value to add
		 */
		void AddTopElement(size_t value);


		/** ***************************************** Remove *****************************************
		 * @brief : Remove the last value of the vector.
		 * 
		 */
		void RemoveTopElement();


		/** ***************************************** Clear *****************************************
		 * @brief : Clear the tower.
		 * 
		 */
		void ClearTower();

	private:
		std::string m_tower_name{ "Default Tower Name" };
		std::vector<int> m_tower_stack;
	};
} // namespace logic


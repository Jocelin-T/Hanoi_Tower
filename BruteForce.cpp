////// ******************************** For (5) Floors ********************************
//Move4thTopFloorTo(t1, t2);
//Move3rdTopFloorTo(t3, t2);
//Move3rdTopFloorTo(t1, t3); // (5) placed
////  16
//Move4thTopFloorTo(t2, t3); // (4) placed
//Move3rdTopFloorTo(t1, t3); // (3) placed
////  28
////// ******************************** For (5) Floors ********************************

//// ******************************** For (6) Floors ********************************
//MoveFloorToTower(t1, t2);
//MoveFloorToTower(t1, t3);
//MoveFloorToTower(t1, t2);
//
//// ******************************** For (6) Floors ********************************

//// ******************************** For (7) Floors ********************************
//Move4thTopFloorTo(t1, t2);
//Move3rdTopFloorTo(t3, t2);
//Move3rdTopFloorTo(t1, t3);
//// 16
//Move4thTopFloorTo(t2, t3);
//Move4thTopFloorTo(t1, t2);
//// 32
//Move4thTopFloorTo(t3, t1);
//Move3rdTopFloorTo(t2, t1);
//Move3rdTopFloorTo(t3, t2);
//// 48
//Move4thTopFloorTo(t1, t2);
//Move3rdTopFloorTo(t3, t2);
//Move3rdTopFloorTo(t1, t3); // (7) placed
//// 64
//
//Move4thTopFloorTo(t2, t1);
//Move3rdTopFloorTo(t3, t1);
//Move3rdTopFloorTo(t2, t3);
//
//Move4thTopFloorTo(t1, t3);
//Move4thTopFloorTo(t2, t1);
//
////Move3rdTopFloorTo(t2, t3);
////Move3rdTopFloorTo(t1, t2);
//
//// ******************************** For (7) Floors ********************************

//// ******************************** For (8) Floors ********************************
//Move3rdTopFloorTo(t1, t2);
//MoveFloorToTower(t3, t1);
//MoveFloorToTower(t3, t2);
//MoveFloorToTower(t1, t2);
//MoveFloorToTower(t1, t3);
//
//Move3rdTopFloorTo(t2, t3);
//Move3rdTopFloorTo(t1, t2);
//
//
//Move3rdTopFloorTo(t3, t1);
//MoveFloorToTower(t2, t3);
//MoveFloorToTower(t2, t1);
//MoveFloorToTower(t3, t1);
//MoveFloorToTower(t3, t2);
//
//algorithm_done = true;
//// ******************************** For (8) Floors ********************************

//// ******************************** For (9) Floors ********************************
//Move4thTopFloorTo(t1, t2);
//Move3rdTopFloorTo(t3, t2);
//Move3rdTopFloorTo(t1, t3);
//// 16
//Move4thTopFloorTo(t2, t3);
//Move4thTopFloorTo(t1, t2);
//// 32
//Move4thTopFloorTo(t3, t1);
//Move3rdTopFloorTo(t2, t1);
//Move3rdTopFloorTo(t3, t2);
//// 48
//Move4thTopFloorTo(t1, t2);
//Move3rdTopFloorTo(t3, t2);
//Move3rdTopFloorTo(t1, t3); // (7) moved
//// 64
//
////Move4thTopFloorTo(t2, t1);
////Move3rdTopFloorTo(t3, t1);
////Move3rdTopFloorTo(t2, t3);
////
////Move4thTopFloorTo(t1, t3);
////Move4thTopFloorTo(t2, t1);
//
//// ******************************** For (9) Floors ********************************
/// 
/// 
/// 
//// Move the 3rd floor from the TOP of a tower to another tower TOP
//void Move3rdTopFloorTo(Tower& from_tower, Tower& to_tower) {
//	Tower& other_tower = GetOtherTower(from_tower, to_tower);
//	MoveFloorToTower(from_tower, to_tower);
//	MoveFloorToTower(from_tower, other_tower);
//	MoveFloorToTower(to_tower, other_tower);
//	MoveFloorToTower(from_tower, to_tower);
//}
//
//// Move the 4th floor from the TOP of a tower to another tower TOP
//void Move4thTopFloorTo(Tower& from_tower, Tower& to_tower) {
//	Tower& other_tower = GetOtherTower(from_tower, to_tower);
//	Move3rdTopFloorTo(from_tower, other_tower);
//	MoveFloorToTower(to_tower, from_tower);
//	MoveFloorToTower(to_tower, other_tower);
//	MoveFloorToTower(from_tower, other_tower);
//	MoveFloorToTower(from_tower, to_tower);
// }

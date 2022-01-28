#ifndef MSTATE_H
#define MSTATE_H

/*************************************************************************/
/* Copyright Alessandro Bertulli 2022                                    */
/* This file is part of ExpLaineR1.					 */
/* 									 */
/* ExpLaineR1 is free software: you can redistribute it and/or modify it */
/* under the terms of the GNU General Public License as published by	 */
/* the Free Software Foundation, either version 3 of the License, or	 */
/* (at your option) any later version.					 */
/* 									 */
/* ExpLaineR1 is distributed in the hope that it will be useful, but	 */
/* WITHOUT ANY WARRANTY; without even the implied warranty of		 */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU	 */
/* General Public License for more details.				 */
/* 									 */
/* You should have received a copy of the GNU General Public License	 */
/* along with ExpLaineR1. If not, see <https://www.gnu.org/licenses/>.	 */
/*************************************************************************/

#include "Item.hpp"
#include <set>

class MState
{
public:
  MState(std::set<Item> set, bool isClosure = false);
  virtual ~MState();
  void buildClosure();
  bool addClosure(std::set<Item> newClosure);
  bool addBaseItem(Item newItem);
  bool addBaseItem(std::set<Item> newItems);
  friend std::ostream& operator<<(std::ostream& stream, const MState& mState);
private:
  std::set<Item> m_base;
  std::set<Item> m_closure;
};


#endif /* MSTATE_H */

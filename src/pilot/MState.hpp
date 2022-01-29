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
  MState(std::string name, std::set<Item> set, bool isClosure = false);
  MState(std::string name, std::set<Item> base, std::set<Item> closure);
  virtual ~MState();
  void buildClosure();
  bool addClosure(std::set<Item> newClosure);
  bool addBaseItem(Item newItem);
  bool addBaseItem(std::set<Item> newItems);
  void addTransition(char label, MState* destState);
  MState delta(char label);
  void mark();
  bool isMarked();
  bool isEmpty();
  std::string getName();
  std::set<Item> getBase();
  std::set<Item> getClosure();
  std::unordered_map<char, MState*> getTransitions();
  friend std::ostream& operator<<(std::ostream& stream, const MState& mState);
  friend bool operator==(const MState& first, const MState& second);
private:
  MState();
  std::string m_name;
  bool m_marked;
  std::set<Item> m_base;
  std::set<Item> m_closure;
  std::unordered_map<char, MState*> m_transitions;
};


#endif /* MSTATE_H */

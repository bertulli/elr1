#ifndef ITEM_H
#define ITEM_H

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

#include "../fsa/Machine.hpp"
#include "../fsa/MachineState.hpp"
#include <string>
#include <set>

class Item
{
public:
  Item(std::string stateName, Machine* machineAddr, MachineState* stateAddr, std::set<char> lookaheads = std::set<char> {});
  virtual ~Item();
  //return true if lookahead set is modified
  bool addLookahead(char lookahead);
  bool addLookahead(std::set<char> lookaheads);
  std::set<Item> closure();
  std::string getStateName() const;
  std::set<char> getLookaheads() const;
  Machine* getMachine() const;
  std::set<std::string> htmlLookaheads() const;
  bool operator<(const Item& other) const;
  friend bool operator==(const Item& first, const Item& second);
  friend std::ostream& operator<<(std::ostream& stream, const Item& item);
  friend std::ostream& operator<<(std::ostream& stream, const std::set<Item>& items);
  friend std::ostream& operator<<(std::ostream& stream, const std::set<std::string>& htmlLookaheads);
private:
  std::string m_stateName;
  Machine* m_machine;
  MachineState* m_machineState;
  std::set<char> m_lookaheadSet;
};

void customMerge(std::set<char> &dest, std::set<char> &source);
  
std::ostream& operator<<(std::ostream& stream, const std::set<char>& lookaheads);

#endif /* ITEM_H */

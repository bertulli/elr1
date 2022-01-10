#ifndef MACHINENET_H
#define MACHINENET_H

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

#include "Machine.hpp"
#include "../ast/ASTGenericNode.hpp"
#include <unordered_map>
#include <string>

//singleton
class MachineNet
{
public:
  static MachineNet* getInstance();
  virtual ~MachineNet();
  int addMachine(std::string machineName);
  Machine* getMachine(std::string machineName);
  Machine* operator[](std::string machineName);
  std::unordered_map<std::string, Machine*> getMachines();
private:
  MachineNet(MachineNet& other) = delete;
  void operator=(const MachineNet& other) = delete;

  MachineNet();
  std::unordered_map<std::string, Machine*> m_machines;
  //static MachineNet* m_net;
};


#endif /* MACHINENET_H */

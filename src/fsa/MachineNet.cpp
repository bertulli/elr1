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

#include "MachineNet.hpp"
#include "Machine.hpp"
#include <unordered_map>

MachineNet::MachineNet(){
  //  m_machines = new std::unordered_map<std::string, Machine>();
}

MachineNet* MachineNet::getInstance(){
  static MachineNet m_net;

  return &m_net;
}

Machine* MachineNet::operator[](std::string machineName) {
  return m_machines[machineName];
}

Machine* MachineNet::getMachine(std::string machineName) {
  return m_machines[machineName];
}
int MachineNet::addMachine(std::string machineName){
  m_machines[machineName] = new Machine(machineName);
  return 1;
}

std::unordered_map<std::string, Machine*> MachineNet::getMachines(){
  return m_machines;
}

MachineNet::~MachineNet(){}



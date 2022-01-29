#ifndef PILOT_H
#define PILOT_H

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

#include "MState.hpp"
#include "PilotPrinter.hpp"

class Pilot
{
public:
  static Pilot* getInstance();
  //true if pilot modified
  bool addMState(MState *mState);
  std::unordered_map<std::string, MState*> getMStates();
  void print();
  void setPrinter(PilotPrinter* printer);
  void setFileType(std::string imageFileType);
  void compileFile(std::string sourceFile, std::string destFile);
  void printOnFile(std::string filePath);
  virtual ~Pilot();
private:
  Pilot();
  Pilot(Pilot& other) = delete;
  void operator=(const Pilot& other) = delete;
  static Pilot* m_instance;
  std::unordered_map<std::string, MState*> m_mStates;
  PilotPrinter* m_printer;
};


#endif /* PILOT_H */

#ifndef DOTPRINTER_H
#define DOTPRINTER_H

#include "MachinePrinter.hpp"

class DotPrinter : public MachinePrinter
{
public:
  virtual ~DotPrinter();
  static DotPrinter* getInstance();
  void printOnFile(std::string filePath, Machine* machine);
  bool compileFile(std::string inputFile, std::string outputFile);
  void setFileType(std::string fileType);
private:
  DotPrinter();
};


#endif /* DOTPRINTER_H */

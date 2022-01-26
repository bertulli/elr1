#ifndef LATEXPRINTER_H
#define LATEXPRINTER_H

#include "MachinePrinter.hpp"

class LatexPrinter : public MachinePrinter
{
public:
  virtual ~LatexPrinter();
  static LatexPrinter* getInstance();
  void printOnFile(std::string filePath, Machine* machine);
  bool compileFile(std::string inputFile, std::string outputFile);
  void setFileType(std::string fileType);
private:
  LatexPrinter();
};


#endif /* LATEXPRINTER_H */

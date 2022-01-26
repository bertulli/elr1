#ifndef MACHINEPRINTER_H
#define MACHINEPRINTER_H

#include <string>

class Machine;

constexpr int genericPrinterCommandBufferSize{50};

//Interface
class MachinePrinter
{
public:
  MachinePrinter(){}
  virtual ~MachinePrinter() {}
  virtual void printOnFile(std::string filePath, Machine* machine) = 0;
  virtual bool compileFile(std::string inputFile, std::string outputFile) = 0;
  virtual void setFileType(std::string fileType) = 0;
protected:
  std::string m_fileType;
};


#endif /* MACHINEPRINTER_H */

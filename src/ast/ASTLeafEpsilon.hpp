#ifndef ASTLEAFEPSILON_H
#define ASTLEAFEPSILON_H

#include "ASTLeafNode.hpp"
#include "../common/BSGrammarChar.hpp"
#include <set>

class ASTLeafEpsilon : public ASTLeafNode
{
public:
  ASTLeafEpsilon(int rePos);
  virtual ~ASTLeafEpsilon();
  bool isBSNullable() override;
  std::set<BSGrammarChar> iniBSSet() override;
  std::set<BSGrammarChar> finBSSet() override;
  std::set<std::pair<BSGrammarChar, BSGrammarChar>> digBSSet() override;
};


#endif /* ASTLEAFEPSILON_H */

#include "ASTLeafEpsilon.hpp"

ASTLeafEpsilon::ASTLeafEpsilon(int rePos)
  : ASTLeafNode{'&', rePos} {}

ASTLeafEpsilon::~ASTLeafEpsilon() {}

bool ASTLeafEpsilon::isBSNullable() {
  return true;
}

std::set<BSGrammarChar> ASTLeafEpsilon::iniBSSet() {
  return std::set<BSGrammarChar>{};  //empty set
}

std::set<BSGrammarChar> ASTLeafEpsilon::finBSSet() {
  return std::set<BSGrammarChar>{};  //empty set
}

std::set<std::pair<BSGrammarChar, BSGrammarChar>> ASTLeafEpsilon::digBSSet() {
  return std::set<std::pair<BSGrammarChar, BSGrammarChar>>{};
}

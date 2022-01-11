#include "BSGrammarChar.hpp"
#include <iostream>

BSGrammarChar::BSGrammarChar(char grammarChar, int rePos)
    : m_grammarChar(grammarChar), m_rePos(rePos) {}

BSGrammarChar::~BSGrammarChar() {}

char BSGrammarChar::getGrammarChar() const{ return m_grammarChar; }

bool BSGrammarChar::operator<(const BSGrammarChar& other) const {
  return m_rePos < other.m_rePos;
}

std::ostream &operator<<(std::ostream &stream, const BSGrammarChar& gramChar) {
  stream << gramChar.m_grammarChar <<gramChar.m_rePos;
  return stream;
}

std::ostream &
operator<<(std::ostream &stream,
           const std::pair<BSGrammarChar, BSGrammarChar> &digram) {
  stream << '<' << digram.first << ", "
	 << digram.second << '>';
  return stream;
}

bool operator==(const BSGrammarChar first, const BSGrammarChar second) {
  return first.m_grammarChar == second.m_grammarChar &&
    first.m_rePos == second.m_rePos;
}

std::set<BSGrammarChar> BSGrammarChar::folBSSet(
    const std::set<std::pair<BSGrammarChar, BSGrammarChar>> digBSSet,
    BSGrammarChar keyGrammChar) {
  std::set<BSGrammarChar> res;
  for(auto i : digBSSet){
    if(i.first == keyGrammChar){
      res.emplace(i.second);
    }
  }
  return res;
}

std::set<BSGrammarChar> unionGrammarChar(std::set<BSGrammarChar> left, std::set<BSGrammarChar> right) {
  std::set<BSGrammarChar> res;
  for(auto i : left){
    if(res.count(i)==0){
      res.emplace(i);
    }
  }
  for(auto i : right){
    if(res.count(i)==0){
      res.emplace(i);
    }
  }
  return res;
}

#include "BSGrammarChar.hpp"

BSGrammarChar::BSGrammarChar(char grammarChar, int rePos)
    : m_grammarChar(grammarChar), m_rePos(rePos) {}

BSGrammarChar::~BSGrammarChar() {}

char BSGrammarChar::getGrammarChar() const{ return m_grammarChar; }

bool BSGrammarChar::operator<(const BSGrammarChar& other) const {
  return m_rePos < other.m_rePos;
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

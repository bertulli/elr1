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

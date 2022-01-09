#ifndef GRAMMARCHAR_H
#define GRAMMARCHAR_H

#include <set>

class BSGrammarChar
{
public:
  BSGrammarChar(char m_grammarChar, int m_rePos);
  char getGrammarChar() const;
  virtual ~BSGrammarChar();
  bool operator<(const BSGrammarChar &other) const;
protected:
  char m_grammarChar;
  int m_rePos;
};

std::set<BSGrammarChar> unionGrammarChar(std::set<BSGrammarChar> left, std::set<BSGrammarChar> right);

#endif /* GRAMMARCHAR_H */

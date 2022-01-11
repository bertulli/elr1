#ifndef GRAMMARCHAR_H
#define GRAMMARCHAR_H

#include <ostream>
#include <set>

class BSGrammarChar
{
public:
  BSGrammarChar(char m_grammarChar, int m_rePos);
  char getGrammarChar() const;
  virtual ~BSGrammarChar();
  bool operator<(const BSGrammarChar &other) const;

  friend std::ostream& operator<<(std::ostream& stream, const BSGrammarChar& gramChar);
  friend std::ostream& operator<<(std::ostream& stream, const std::pair<BSGrammarChar, BSGrammarChar>& digram);
protected:
  char m_grammarChar;
  int m_rePos;
};

std::set<BSGrammarChar> unionGrammarChar(std::set<BSGrammarChar> left, std::set<BSGrammarChar> right);

#endif /* GRAMMARCHAR_H */

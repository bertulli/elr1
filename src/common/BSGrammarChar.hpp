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
  static std::set<BSGrammarChar> folBSSet(std::set<std::pair<BSGrammarChar, BSGrammarChar>> digBSSet, BSGrammarChar keyGrammChar);

  //Operator overload
  friend std::ostream& operator<<(std::ostream& stream, const BSGrammarChar& gramChar);
  friend std::ostream& operator<<(std::ostream& stream, const std::pair<BSGrammarChar, BSGrammarChar>& digram);
  friend bool operator==(const BSGrammarChar first, const BSGrammarChar second);
protected:
  char m_grammarChar;
  int m_rePos;
};

std::set<BSGrammarChar> unionGrammarChar(std::set<BSGrammarChar> left, std::set<BSGrammarChar> right);

#endif /* GRAMMARCHAR_H */

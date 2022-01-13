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
  static std::set<BSGrammarChar> folBSSet(std::set<std::pair<BSGrammarChar, BSGrammarChar>> digBSSet, const BSGrammarChar keyGrammChar);
  static std::set<BSGrammarChar> folBSSet(std::set<std::pair<BSGrammarChar, BSGrammarChar>> digBSSet, const char keyChar);

  //From the state `stateSet', returns the set of followers from that state of a given char
  static std::set<BSGrammarChar> genQPrime(std::set<std::pair<BSGrammarChar, BSGrammarChar>> digBSSet, std::set<BSGrammarChar> stateSet, const char keyChar);

  //Operator overload
  friend std::ostream& operator<<(std::ostream& stream, const BSGrammarChar& gramChar);
  friend std::ostream& operator<<(std::ostream& stream, const std::pair<BSGrammarChar, BSGrammarChar>& digram);
  friend bool operator==(const BSGrammarChar first, const BSGrammarChar second);
  friend std::ostream& operator<<(std::ostream& stream, std::set<BSGrammarChar> set);
protected:
  char m_grammarChar;
  int m_rePos;
};

std::set<BSGrammarChar> unionGrammarChar(std::set<BSGrammarChar> left,
                                         std::set<BSGrammarChar> right);
//std::set<BSGrammarChar> unionFollowers(std::set<

#endif /* GRAMMARCHAR_H */

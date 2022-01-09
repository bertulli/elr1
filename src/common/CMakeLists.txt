add_library(commonlib
  BSGrammarChar.cpp
  BSGrammarChar.hpp
  BSNonTerminal.cpp
  BSNonTerminal.hpp
  BSTerminal.cpp
  BSTerminal.hpp
  Strings.hpp
  )

target_include_directories(commonlib PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}
  )

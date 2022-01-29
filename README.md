# ExpLaineR1

## About :question:

**elr1** is a tool that aims at provide a decent explanation of the construction of an ELR(1) parser. Various tools exist that deal with LR(1) parsers: this project will deal with the extended version, (allowing regular expressions in defining the right hand side of a grammar rule).

**ALPHA WARNING**
This is an hobby project, still in a very, very early stage of development. Feel free to look around, and provide feedback and/or help if you can, but remember that nothing of this is complete, and that it will likely change.

## Requirements

At present, this project only supports GNU/Linux (and possibly BSD). Windows and OSX users, sorry! I'm very happy to incorporate your suggestions to support your system.
This project need:
+ [GNU `bison`](https://www.gnu.org/software/bison/)
+ [`flex`](https://github.com/westes/flex)
+ [CMake](https://cmake.org/)
+ [Graphviz](https://graphviz.org/)
+ `make` (I used GNU `make`)
+ A C++ compiler (I used `gcc`)

You should find all of them, if you don't have them yet, on your distribution's repos. On my machine, I have the versions bison 3.8.2-1, cmake 3.22.2-1, flex 2.6.4-3, graphviz 2.50.0-2, make 4.3-3 and gcc 11.1.0-3, but the project will likely compile on earlier versions.


## Compilation

To build the project, I suggest you to create a different build tree, which on my machine I called `build`. Therefore, you should be fine using:
```sh
mkdir build
cd build
cmake ..
make
```
Then, the resulting executable file will be `build/src/elr1`. Since system installation is not yet supported, you're welcome to create a symlink to it. It runs reading a grammar file. For testing, an example is the file `prova.gram`. You can try it with

## Usage

The program reads a grammar file, from a text file or from `stdin`. Syntax is:
```sh
elr1 [OPTIONS] <input_file>
```
Relevat options are:
+ `-p` prints the pilot automaton on a `.png` file, using an intermediate `.dot` file
+ `--graphviz` `-g` uses Graphviz to render the FSAs
+ `-T <file_type>` to set the output file type for Graphviz
+ `-G <machine_name>` to produce the `.dot` file for a particular machine, and the previously specified output file
+ `--debug -d` prints debug informations
+ `--help -h` prints usage

An example file `prova.gram` is provided (corresponding to the recurring example in the course book). To run it, type (assuming you are in `build/`):
```sh
src/elr1 -p ../prova.gram
```
to produce files `prova.gram.dot` and `prova.gram.png`. Instead,
```
src/elr1 --graphviz ../prova.gram -GE
```
will produce `E.png`, the machine E.

## Input grammar

The input grammar can be specified in a text file. Here's the sample grammar `prova.gram`:
```
E : T*
;

T : a | oEc ;

//a|(b&a)
//a(b|c)*
```
Each rule has the form `NONTERMINAL : regular expression`. The production sign separating the two can be `:`, `::=`, `->`or `=>`. Each regular expression has the usual precedence rules: first `*` and `+`, then the concatenation (`.`) and then the union `|`. For simplicity, the program only accepts a-to-z, single-char terminals and non terminals. Each rule (except the last) must be terminated by a semicolon (`;`). The last rule may be terminated or not.

## Why? :robot:

This project was inspired by the Formal languages and compilers course taught at Politecnico di Milano, Italy. I found the ELR(1) parsing method interesting, and I noted the lack of an automated tool that could help us students in practicing. Mind however, this project is **not affiliated**, or by any mean **related** to the university.

## Note on correctness
If you are using this project to help you in studying formal languages and compilers, I need to warn you on two things. First, notice that states of FSAs and m-states of the pilot automaton are automatically generated. Therefore, the naming order will likely be different between your escercises and the output files. Second, and more important, the theory presented in the book assumes that every machine initial state is non re-entrant. That is, no transition can lead back to the initial state. While this is not a problem for the parsing, the machines built by this project are constructed using the Berri-Sethi algorithm. Being minimal, the initial state can be re-entrant. This may lead to the fusion of states, compared to the examples you can see on the book. Take a look for example with the recurring example: the states 0E and 1E are fused in the single state 0E, having a loop labelled T. In the generated pilot, you may need to mentally "rename" the fused state, so that some of the states named 0E corresponds, on the book, to 0E, and some correspond to 1E. To the best of my knowledge, this is the only difference, and it should be possible for you to check the correspondance

## Language :wrench:

This project is developed using three primary technologies: the C++ language, the pair flex/bison, and CMake. I'm not really an expert in none of these (except having an intermediate experience with flex/bison), and this project is also meant to be an exercise to lear them. Therefore, the code you'll se will likely not make use of best practices, and contain code smell. Please, let me know of any possible improvement you spot! I'll greatly appreciate that.

## License :bison:

This project is released under the terms of [**GNU General Public License, version 3 or any later version**](https://www.gnu.org/licenses/gpl-3.0.html). I choose that because I found it to be the most accademic-y license for an educational project. However, I'd like to point out that, in my opinion, technological progress must be paired with technology ethics. In that sense, I agree that "[software shall be used for good, not evil](https://en.wikipedia.org/wiki/Douglas_Crockford#%22Good,_not_Evil%22)". So, I'd like to accept [**the ACM Code of Ethics and Professional Conduct**](https://www.acm.org/binaries/content/assets/about/acm-code-of-ethics-booklet.pdf). I still used the GNU GPL instead of, say, the Hippocratic License because I want to mantain compatibility with other free software projects. However, please make good, ethical use of your knowledge, for the best of your sisters and brothers.

## Acknowledgements

This project is largely inspired by the book by Stefano Crespi Reghizzi, Luca Breveglieri and Angelo Morzenti, "Linguaggi formali e compilazione", Società Editrice Esculapio, 2nd edition, 2015. It is produced using [GNU Emacs](https://www.gnu.org/software/emacs/) and [Arch GNU/Linux](https://archlinux.org/). I would like to thank the website [LearnCpp](https://www.learncpp.com/) and its editors, for providing a free and yet surprisingly complete resource for learning the C++ language. I would also like to thank the online community, which is always happy to provide help and feedback (users of [StackOverflow](https://stackoverflow.com/), thanks)
## Contacts :busts_in_silhouette: :speech_balloon:

Feel free to reach me for any question, suggestion, doubt. I'm very happy to know about doubt, suggestions and errors in this project (which will likely be present).
You can find me here on GitHub, or at my student address: alessandro.bertulli@mail.polimi.it . I'll try to answer, both in English and in Italian.




*Thanks, Lord*

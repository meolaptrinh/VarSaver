# VarSaver

A lightweight C++ header-only library to extract variables from the main function into a file, and inject them back into any C++ source file.
## Features
- **Header-Only:** Simply `#include "var_saver.hpp"` and you're ready to go.
- **ONLY** depends on the available C++ STL library.
- **Binary Stream Processing:** Preserves exact line-endings (`\n` / `\r\n`) across environments.
- **Fast** : The algorithms are optimized.
### Quick Start: 
#### Save your variables to a file : 
```cpp
#include "var_saver.hpp" //include the header
int main(){
  int a = 0;
  int b = 10;
  int c;
  double f;
// Save variables to file
  VarSaver::SaveVarToFile("your_file_dir", "var_file"); //You can name the variables file yourself.
  // Don't worry, if you don't have one file available, that command will also help you create a new one.
  return 0;
}
```
#### Load variables from a file : 
```cpp
#include "var_saver.hpp" //include the header
int main(){
  // Inject saved variables into target C++ source file
  VarSaver::LoadVarToFile("var_file","your_cpp_code_file");
  return 0;
}
```
#### For details, please check the Doxygen comments in the source code.
#### Thank you !!!!

#include <iostream>
#include <dlfcn.h>

// g++ -std=c++17 main.cpp -o main -ldl
extern "C" typedef int (*Add_t)(int a, int b);

int main() {
  void* lib = dlopen("./lib.dll", RTLD_LAZY);
  Add_t Add = (Add_t)dlsym(lib, "Add" );

  std::cout << Add(5, 6) << std::endl;
  
  dlclose(lib);
}
#include <iostream>
#include <tuple>
#include <dlfcn.h>

// g++ -std=c++17 main.cpp -o main -ldl
//extern "C" typedef int (*Add_t)(int a, int b);

extern "C" typedef std::tuple<int, int> (*Max_T)(const int *x, const size_t N);
extern "C" typedef int* (*Max_T2)(const int *x, const size_t N);

int main() {
  void* lib = dlopen("./Example_Lib_Shared.dll", RTLD_LAZY);
  Max_T Max_Int = (Max_T)dlsym(lib, "Max_Int");
  Max_T2 Max_Int_Py = (Max_T2)dlsym(lib, "Max_Int_Py");

  const size_t SIZE = 5;
  int arr_n[SIZE] {1,2,3,4,5};

  auto [max_value, max_index] = Max_Int(arr_n, SIZE);

  std::cout << "Results" << std::endl;
  std::cout << max_value << std::endl;
  std::cout << max_index << std::endl;

  int *result = Max_Int_Py(arr_n, SIZE);

  std::cout << result[0] << std::endl;

  dlclose(lib);
}
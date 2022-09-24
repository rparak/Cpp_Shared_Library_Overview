#include <iostream>
#include <dlfcn.h>
#include <vector>
#include <iterator>

// g++ -std=c++17 main.cpp -o main -ldl

// Shared library type:
//   DLL: Windows
//   SO: Linux
const std::string CONST_SHARED_LIB_TYP = "DLL";

template <typename T>
void Display_Array(const T* Array, const size_t N, const std::string separator){
    std::vector<int> v(Array, Array + N);

    std::cout << "[";
    std::copy(v.begin(), v.end() - 1, std::ostream_iterator<int>(std::cout, separator.data()));
    std::cout << v.back() << "]" << std::endl;
}

extern "C" typedef int* (*Generate_Random_Array_Typ)(const int MIN, const int MAX, const size_t N);

int main() {
    std::string shared_lib_path = "..//Cpp_Shared_Lib//" + CONST_SHARED_LIB_TYP + "//Example_Lib_Shared.dll";

    void* lib = dlopen(shared_lib_path.c_str(), RTLD_LAZY);
    Generate_Random_Array_Typ Generate_Random_Array = (Generate_Random_Array_Typ)dlsym(lib, "Generate_Random_Array");

    const size_t SIZE = 5;
    auto *Arr_Rand = Generate_Random_Array(1, 100, SIZE);

    Display_Array<int>(Arr_Rand, SIZE, ", ");

    dlclose(lib);
}
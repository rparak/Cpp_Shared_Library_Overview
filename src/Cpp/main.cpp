#include <iostream>
#include <vector>
#include <iterator>
#include <dlfcn.h>

template <typename T>
class Simple_Calculator {
    /*
    Description:
        A simple class to demonstrate the calculator.
     */

    public:
        /*
        Description:
            Initialization of input parameters.
        */
        // Parametrized constructor.
        explicit Simple_Calculator(const T Parameter_1, const T Parameter_2) 
            : __Parameter_1(Parameter_1), __Parameter_2(Parameter_2)
        {}
        // Destructor.
        ~Simple_Calculator();
        char* Get_Parameters();
        void Set_Parameters(const T Parameter_1, const T Parameter_2);
        T Addition();
        T Substraction();

    private:
        // Defined parameters for calculator demonstration.
        T __Parameter_1;
        T __Parameter_2;
};

/*
Description:
    Declaration of the input/output structure for the Array_MinMax function.
 */
template <typename T> 
struct FCE_ARRAY_MinMax_INPUT_Str{
    /*
    Description:
        Structure of function (Array_MinMax) input parameters.

    Args:
        (1) Array [T* <data_type>]: Input array of values.
        (2) N [size_t]: The size of the array.
     */
    T *Array;
    size_t N;
};
template <typename T> 
struct FCE_ARRAY_MinMax_OUTPUT_Str{
    /*
    Description:
        Structure of function (Array_MinMax) output parameters.

    Args:
        (1) Value [T <data_type>]: Found value (min, max).
        (2) Index [int]: Found value index.
     */
    T Value;
    int Index;
};

extern "C" {
    typedef int* (*Generate_Random_Array_Typ)(const int MIN, const int MAX, const size_t N);
    typedef void (*Multiply_Array_By_Number_Typ)(const int Number, int *Array, const size_t N);
    typedef FCE_ARRAY_MinMax_OUTPUT_Str<int> (*Array_MinMax_Typ)(FCE_ARRAY_MinMax_INPUT_Str<int>* Input, const bool return_min_val);

    typedef Simple_Calculator<int>* (*SC_Class_Create_Typ)(const int Param_1, const int Param_2);
    typedef void (*SC_Class_Delete_Typ)(Simple_Calculator<int>* SC_Cls);
    typedef char* (*SC_Class_Get_Parameters_Typ)(Simple_Calculator<int>* SC_Cls);
    typedef bool (*SC_Class_Set_Parameters_Typ)(Simple_Calculator<int>* SC_Cls, const int Param_1, const int Param_2);
    typedef int (*SC_Class_Addition_Parameters_Typ)(Simple_Calculator<int>* SC_Cls);
    typedef int (*SC_Class_Substraction_Parameters_Typ)(Simple_Calculator<int>* SC_Cls);
}

template <typename T>
void Display_Array(const T* Array, const size_t N, const std::string separator){
    std::vector<int> v(Array, Array + N);

    std::cout << "[";
    std::copy(v.begin(), v.end() - 1, std::ostream_iterator<int>(std::cout, separator.data()));
    std::cout << v.back() << "]" << std::endl;
}
// g++ -std=c++17 main.cpp -o main -ldl

// Shared library type:
//   DLL: Windows
//   SO: Linux
const std::string CONST_SHARED_LIB_TYP = "DLL";

int main() {
    std::string shared_lib_path = "..//Cpp_Shared_Lib//" + CONST_SHARED_LIB_TYP + "//Example_Lib_Shared.dll";

    void* lib = dlopen(shared_lib_path.c_str(), RTLD_LAZY);
    Generate_Random_Array_Typ Generate_Random_Array = (Generate_Random_Array_Typ)dlsym(lib, "Generate_Random_Array"); 
    Multiply_Array_By_Number_Typ Multiply_Array_By_Number = (Multiply_Array_By_Number_Typ)dlsym(lib, "Multiply_Array_By_Number");
    Array_MinMax_Typ Array_MinMax = (Array_MinMax_Typ)dlsym(lib, "Array_MinMax");

    SC_Class_Create_Typ SC_Class_Create = (SC_Class_Create_Typ)dlsym(lib, "SC_Class_Create");
    SC_Class_Delete_Typ SC_Class_Delete = (SC_Class_Delete_Typ)dlsym(lib, "SC_Class_Delete");
    SC_Class_Get_Parameters_Typ SC_Class_Get_Parameters = (SC_Class_Get_Parameters_Typ)dlsym(lib, "SC_Class_Get_Parameters");
    SC_Class_Set_Parameters_Typ SC_Class_Set_Parameters = (SC_Class_Set_Parameters_Typ)dlsym(lib, "SC_Class_Set_Parameters");
    SC_Class_Addition_Parameters_Typ SC_Class_Addition_Parameters = (SC_Class_Addition_Parameters_Typ)dlsym(lib, "SC_Class_Addition_Parameters"); 
    SC_Class_Substraction_Parameters_Typ SC_Class_Substraction_Parameters = (SC_Class_Substraction_Parameters_Typ)dlsym(lib, "SC_Class_Substraction_Parameters");
    

    Simple_Calculator<int>* Cls = SC_Class_Create(8, 3);

    auto res = SC_Class_Addition_Parameters(Cls);

    std::cout << res << std::endl;

    SC_Class_Delete(Cls);

    /*
    const size_t SIZE = 5;
    auto *Arr_Rand = Generate_Random_Array(1, 100, SIZE);

    Display_Array<int>(Arr_Rand, SIZE, ", ");

    int Number = 5;
    Multiply_Array_By_Number(Number, Arr_Rand, SIZE);

    Display_Array<int>(Arr_Rand, SIZE, ", ");

    FCE_ARRAY_MinMax_INPUT_Str<int> input_str;
    input_str.Array = Arr_Rand;
    input_str.N = SIZE;

    FCE_ARRAY_MinMax_OUTPUT_Str<int> output_str;

    output_str = Array_MinMax(&input_str, true);

    std::cout << output_str.Value << std::endl;
    std::cout << output_str.Index << std::endl;
    */

    dlclose(lib);
}
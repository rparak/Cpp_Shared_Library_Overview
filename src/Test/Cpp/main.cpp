/****************************************************************************
MIT License
Copyright(c) 2022 Roman Parak
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*****************************************************************************
Author   : Roman Parak
Email    : Roman.Parak @outlook.com
Github   : https://github.com/rparak
File Name: Example_Lib_Shared.hpp
****************************************************************************/

#include <dlfcn.h>
// Custom Script:
//  Shared Lib. (Functions/Classes).
#include "Example_Lib_Shared.hpp"

/*
 Note:
   $ g++ -std=c++17 main.cpp -o main -ldl
   $ ./main
 */

template <typename T>
void Display_Array(const T* Array, const size_t N, const std::string separator){
    /*
    Description:
        A simple function to display an array with defined rules.

    Args:
        (1) Array [T* <data_type>]: Input array of values.
        (2) N [size_t]: The size of the array.
        (3) separator [string]: Separator between array data.
     */

    std::vector<int> v(Array, Array + N);

    std::cout << "[";
    std::copy(v.begin(), v.end() - 1, std::ostream_iterator<int>(std::cout, separator.data()));
    std::cout << v.back() << "]" << std::endl;
}

int main() {
    /*
    Description:
        Demonstration of calling different functions/classes from a shared library (C/C++).
     */

    // The path to a shared library.
    std::string shared_lib_path = "..//..//Cpp_Shared_Lib//" + CONST_SHARED_LIB_TYP + "//Example_Lib_Shared." + CONST_SHARED_LIB_TYP;

    // Access to an executable object file (load the shared library - .dll/.so).
    void* Example_SL = dlopen(shared_lib_path.c_str(), RTLD_LAZY);

    /*
    Description:
        Declaration of shared library functions.
     */
    Generate_Random_Array_Typ Generate_Random_Array = (Generate_Random_Array_Typ)dlsym(Example_SL, "Generate_Random_Array"); 
    Multiply_Array_By_Number_Typ Multiply_Array_By_Number = (Multiply_Array_By_Number_Typ)dlsym(Example_SL, "Multiply_Array_By_Number");
    Array_MinMax_Typ Array_MinMax = (Array_MinMax_Typ)dlsym(Example_SL, "Array_MinMax");
    /*
    Description:
        Declaration of a shared library class (as a multiple functions).
     */
    SC_Class_Create_Typ SC_Class_Create = (SC_Class_Create_Typ)dlsym(Example_SL, "SC_Class_Create");
    SC_Class_Delete_Typ SC_Class_Delete = (SC_Class_Delete_Typ)dlsym(Example_SL, "SC_Class_Delete");
    SC_Class_Get_Parameters_Typ SC_Class_Get_Parameters = (SC_Class_Get_Parameters_Typ)dlsym(Example_SL, "SC_Class_Get_Parameters");
    SC_Class_Set_Parameters_Typ SC_Class_Set_Parameters = (SC_Class_Set_Parameters_Typ)dlsym(Example_SL, "SC_Class_Set_Parameters");
    SC_Class_Addition_Parameters_Typ SC_Class_Addition_Parameters = (SC_Class_Addition_Parameters_Typ)dlsym(Example_SL, "SC_Class_Addition_Parameters"); 
    SC_Class_Substraction_Parameters_Typ SC_Class_Substraction_Parameters = (SC_Class_Substraction_Parameters_Typ)dlsym(Example_SL, "SC_Class_Substraction_Parameters");

    std::cout << "[INFO] ===== Validation of Part 1. =====" << std::endl;
    // Generate a randomly defined array from the input parameters of the function.
    const size_t SIZE = 5;
    auto *Arr_Rand = Generate_Random_Array(1, 100, SIZE);

    // Display an array with defined rules.
    std::cout << "[INFO] Input Array: ";
    Display_Array<int>(Arr_Rand, SIZE, ", ");

    std::cout << "[INFO] ===== Validation of Part 2. =====" << std::endl;
    // Multiply each value in the input array by the defined number.
    int Number = 5;
    Multiply_Array_By_Number(Number, Arr_Rand, SIZE);

    // Display an array with defined rules.
    std::cout << "[INFO] Multiplied the input array by " << Number << ": ";
    Display_Array<int>(Arr_Rand, SIZE, ", ");

    std::cout << "[INFO] ===== Validation of Part 3. =====" << std::endl;
    // Declaration of the input structure for the Array_MinMax function.
    FCE_ARRAY_MinMax_INPUT_Str<int> ARRAY_MinMax_In;
    ARRAY_MinMax_In.Array = Arr_Rand;
    ARRAY_MinMax_In.N     = SIZE;

    // Function to return the number and index from a defined array of values.
    //   The minimum number.
    FCE_ARRAY_MinMax_OUTPUT_Str<int> ARRAY_Min_Out = Array_MinMax(&ARRAY_MinMax_In, true);
    std::cout << "[INFO] The minimum number of an input array." << std::endl;
    std::cout << "[INFO] Value: " << ARRAY_Min_Out.Value << " | " << "Index: " << ARRAY_Min_Out.Index << std::endl;
    //   The minimum number.
    FCE_ARRAY_MinMax_OUTPUT_Str<int> ARRAY_Max_Out = Array_MinMax(&ARRAY_MinMax_In, false);
    std::cout << "[INFO] The maximum number of an input array." << std::endl;
    std::cout << "[INFO] Value: " << ARRAY_Max_Out.Value << " | " << "Index: " << ARRAY_Max_Out.Index << std::endl;

    std::cout << "[INFO] ===== Validation of Part 4. =====" << std::endl;
    // A simple class to demonstrate the calculator.
    Simple_Calculator<int>* Cls = SC_Class_Create(ARRAY_Min_Out.Value, ARRAY_Min_Out.Index);

    // Get the main parameters of the class as a string (char).
    std::cout << "[INFO] Input Parameters:" << std::endl;
    std::cout << SC_Class_Get_Parameters(Cls) << std::endl;
    // The addition of the main parameters.
    std::cout << "[INFO] Result of parameter addition: " << SC_Class_Addition_Parameters(Cls) << std::endl;
    // The subtraction of main parameters.
    std::cout << "[INFO] Result of parameter substraction: " << SC_Class_Substraction_Parameters(Cls) << std::endl;

    // Set the new (main) parameters of the class.
    SC_Class_Set_Parameters(Cls, ARRAY_Max_Out.Value, ARRAY_Max_Out.Index);

    // Get the main parameters of the class as a string (char).
    std::cout << "[INFO] Input Parameters:" << std::endl;
    std::cout << SC_Class_Get_Parameters(Cls) << std::endl;
    // The addition of the main parameters.
    std::cout << "[INFO] Result of parameter addition: " << SC_Class_Addition_Parameters(Cls) << std::endl;
    // The subtraction of main parameters.
    std::cout << "[INFO] Result of parameter substraction: " << SC_Class_Substraction_Parameters(Cls) << std::endl;

    // Delete a class object.
    SC_Class_Delete(Cls);

    // Frees memory.
    delete Arr_Rand;
    Arr_Rand = NULL;

    // Close a dlopen object.
    dlclose(Example_SL);
}
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

#include <iostream>
#include <vector>
#include <iterator>

// Shared library type:
//   DLL: Windows
//   SO: Linux
const std::string CONST_SHARED_LIB_TYP = "DLL";

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
        (2) N [size_t]: The size of an array.
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

        /*
        Description:
            Some helpful function for demostration of the class.
        */
        // Get the main parameters of the class as a string (char).
        char* Get_Parameters();
        // Set the main parameters of the class.
        void Set_Parameters(const T Parameter_1, const T Parameter_2);
        // The addition of the main parameters.
        T Addition();
        // The subtraction of main parameters.
        T Substraction();

    private:
        // Defined parameters for calculator demonstration.
        T __Parameter_1;
        T __Parameter_2;
};

/*
Description:
    Specify the required argument types and return types of the functions.
 */
extern "C" {
    // Generate a randomly defined array from the input parameters of the function.
    typedef int* (*Generate_Random_Array_Typ)(const int MIN, const int MAX, const size_t N);
    // Multiply each value in the input array by the defined number.
    typedef void (*Multiply_Array_By_Number_Typ)(const int Number, int *Array, const size_t N);
    // Function to return the minimum/maximum number and index from a defined array of values.
    typedef FCE_ARRAY_MinMax_OUTPUT_Str<int> (*Array_MinMax_Typ)(FCE_ARRAY_MinMax_INPUT_Str<int>* Input, const bool return_min_val);
    /*
    Description:
        Multiple functions to demonstrate how to work with a class to create a shared library. More information about the class 
        can be found above.
     */
    typedef Simple_Calculator<int>* (*SC_Class_Create_Typ)(const int Parameter_1, const int Parameter_2);
    typedef void (*SC_Class_Delete_Typ)(Simple_Calculator<int>* SC_Cls);
    typedef char* (*SC_Class_Get_Parameters_Typ)(Simple_Calculator<int>* SC_Cls);
    typedef bool (*SC_Class_Set_Parameters_Typ)(Simple_Calculator<int>* SC_Cls, const int Parameter_1, const int Parameter_2);
    typedef int (*SC_Class_Addition_Parameters_Typ)(Simple_Calculator<int>* SC_Cls);
    typedef int (*SC_Class_Substraction_Parameters_Typ)(Simple_Calculator<int>* SC_Cls);
}

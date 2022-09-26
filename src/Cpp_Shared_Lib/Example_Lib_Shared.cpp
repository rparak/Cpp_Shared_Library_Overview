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
File Name: Example_Lib_Shared.cpp
****************************************************************************/

#include <iostream>
#include <ctime>
#include <cstring> 

/*
Description:
    A simple example that shows how to create a shared library from the C/C++ programming language.

    Note:
        Windows:
            $ g++ -shared -std=c++17 -fPIC -o DLL/Example_Lib_Shared.dll Example_Lib_Shared.cpp
        Linux:
            $ g++ -shared -std=c++17 -fPIC -o SO/Example_Lib_Shared.so Example_Lib_Shared.cpp
 */


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
        ~Simple_Calculator()
        {}

        /*
        Description:
            Some helpful function for demostration of the class.
        */
        char* Get_Parameters(){
            /*
            Description:
                Get the main parameters of the class as a string (char).

            Returns:
                (1) parameter [char*]: Information on the main parameters of the class.
            */
            std::string res = std::string("Parameter 1: ") + std::to_string(this->__Parameter_1) + "\nParameter 2: " + std::to_string(this->__Parameter_2);
            return strdup(res.data());
        }

        void Set_Parameters(const T Parameter_1, const T Parameter_2){
            /*
            Description:
                Set the main parameters of the class.

            Args:
                (1, 2) Parameter_1/2 [T]: Main parameters of the class.
            */
            this->__Parameter_1 = Parameter_1;
            this->__Parameter_2 = Parameter_2;
        }

        T Addition(){ 
            /*
            Description:
                The addition of the main parameters.

            Returns:
                (1) parameter [T]: Addition of parameters (a + b).
            */
            return this->__Parameter_1 + this->__Parameter_2; 
        }

        T Substraction() { 
            /*
            Description:
                The subtraction of main parameters.

            Returns:
                (1) parameter [T]: Substraction of parameters (a - b).
            */
            return this->__Parameter_1 - this->__Parameter_2;
        }

    private:
        // Defined parameters for calculator demonstration.
        T __Parameter_1{0};
        T __Parameter_2{0};
};

extern "C" { 
    __declspec(dllexport) int* Generate_Random_Array(const int MIN, const int MAX, const size_t N)
    {
        /*
        Description:
            Generate a randomly defined array from the input parameters of the function.

        Args:
            (1) MIN [int]: The minimum value in the array.
            (2) MAX [int]: The maximum value in the array.
            (3) N [size_t]: The size of an array.

        Returns:
            (1) parameter [int*]: Random array of values.
        */

        std::srand(time(0)); 

        int* Output = new int[N];
        for(auto i = 0; i < N; ++i){
            Output[i] = static_cast<int>(MIN + rand() % (MAX - MIN + 1));
        }

        return Output;
    }
    
     __declspec(dllexport) void Multiply_Array_By_Number(const int Number, int *Array, const size_t N) 
     { 
        /*
        Description:
            Multiply each value in the input array by the defined number.

        Args:
            (1) Number [int]: The number that is used to multiply the value in the array.
            (2) Array [int*]: Input/Output array of values.
            (3) N [size_t]: The size of an array.
        */

        int x_temp;
        for (auto i = 0; i < N; ++i)
        {
            x_temp = Array[i];
            Array[i] = x_temp * Number;
        }
    }

    __declspec(dllexport) FCE_ARRAY_MinMax_OUTPUT_Str<int> Array_MinMax(FCE_ARRAY_MinMax_INPUT_Str<int>* Input, const bool return_min_val)
    {
        /*
        Description:
            Function to return the minimum/maximum number and index from a defined array of values.

        Args:
            (1) Input [struct FCE_ARRAY_MinMax_INPUT_Str]: Input parameters (array, size).
            (2) return_min_val [bool]: Return the minimum value if true, otherwise return the maximum value.

        Returns:
            (2) parameter [struct FCE_ARRAY_MinMax_OUTPUT_Str]: Output parameters (value, index).
        */

        FCE_ARRAY_MinMax_OUTPUT_Str<int> Output;
        Output.Value = Input->Array[0]; Output.Index = 0;
        for(auto i = 1; i < Input->N; ++i){
            if(return_min_val == true){
                if(Output.Value > Input->Array[i]){
                    Output.Value = Input->Array[i];
                    Output.Index = i;
                }
            }else{
                if(Output.Value < Input->Array[i]){
                    Output.Value = Input->Array[i];
                    Output.Index = i;
                }
            }
        }

       return Output;
    }

    /*
    Description:
        Multiple functions to demonstrate how to work with a class to create a shared library. More information about the class 
        can be found above.
     */
    __declspec(dllexport) Simple_Calculator<int>* SC_Class_Create(const int Param_1, const int Param_2)
	{
		return new Simple_Calculator<int>(Param_1, Param_2);
	}

    __declspec(dllexport) void SC_Class_Delete(Simple_Calculator<int>* SC_Cls)
	{
        if(SC_Cls){
		    delete SC_Cls;
            SC_Cls = nullptr;
        }
	}

    __declspec(dllexport) char* SC_Class_Get_Parameters(Simple_Calculator<int>* SC_Cls)
	{
        return SC_Cls->Get_Parameters();
	}

    __declspec(dllexport) bool SC_Class_Set_Parameters(Simple_Calculator<int>* SC_Cls, const int Param_1, const int Param_2)
	{
        try {
            SC_Cls->Set_Parameters(Param_1, Param_2);
            return 1;
        } catch(...) {
            return 0;
        }
	}

    __declspec(dllexport) int SC_Class_Addition_Parameters(Simple_Calculator<int>* SC_Cls)
	{
        return SC_Cls->Addition();
	}

    __declspec(dllexport) int SC_Class_Substraction_Parameters(Simple_Calculator<int>* SC_Cls)
	{
        return SC_Cls->Substraction();
	}
}

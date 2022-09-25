"""
## =========================================================================== ## 
MIT License
Copyright (c) 2022 Roman Parak
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
## =========================================================================== ## 
Author   : Roman Parak
Email    : Roman.Parak@outlook.com
Github   : https://github.com/rparak
File Name: main.py
## =========================================================================== ## 
"""

# System (Default Lib.)
import sys
# CTypes (C compatible data types, and allows calling functions in DLLs)
import ctypes as ct
# Custom Script:
#   Shared Lib. (Functions/Classes).
import Example_Lib_Shared

def main():
    """
    Description:
        Demonstration of calling different functions/classes from a shared library (C/C++).
    """

    print('[INFO] ===== Validation of Part 1. =====')
    # Generate a randomly defined array from the input parameters of the function.
    Arr_Rand = Example_Lib_Shared.Generate_Random_Array(1, 100, 5)
    print(f'[INFO] Input Array: {Arr_Rand}')

    print('[INFO] ===== Validation of Part 2. =====')
    # Multiply each value in the input array by the defined number.
    Number = 3
    Arr_Mult_Num = Example_Lib_Shared.Multiply_Array_By_Number(Number, Arr_Rand)
    print(f'[INFO] Multiplied the input array by {Number}: {Arr_Mult_Num}')

    print('[INFO] ===== Validation of Part 3. =====')
    # Declaration of the input structure for the Array_MinMax function.
    ARRAY_MinMax_In  = Example_Lib_Shared.FCE_ARRAY_MinMax_INPUT_Str((ct.c_int * len(Arr_Mult_Num))(*Arr_Mult_Num), 
                                                                      ct.c_size_t(len(Arr_Mult_Num)))
    # Function to return the number and index from a defined array of values.
    #   The minimum number.
    ARRAY_Min_Out = Example_Lib_Shared.Array_MinMax(ARRAY_MinMax_In, True)
    print('[INFO] The minimum number of an input array.')
    print(f'[INFO] Value: {ARRAY_Min_Out.Value} | Index: {ARRAY_Min_Out.Index}')
    #   The maximum number.
    ARRAY_Max_Out = Example_Lib_Shared.Array_MinMax(ARRAY_MinMax_In, False)
    print('[INFO] The maximum number of an input array.')
    print(f'[INFO] Value: {ARRAY_Max_Out.Value} | Index: {ARRAY_Max_Out.Index}')

    print('[INFO] ===== Validation of Part 4. =====')
    # A simple class to demonstrate the calculator.
    SC_Cls = Example_Lib_Shared.Simple_Calculator(ARRAY_Min_Out.Value, ARRAY_Min_Out.Index)

    # Get the main parameters of the class as a string (char).
    print('[INFO] Input Parameters:')
    print(SC_Cls.Get_Parameters())

    # The addition of the main parameters.
    print(f'[INFO] Result of parameter addition: {SC_Cls.Addition()}')
    # The subtraction of main parameters.
    print(f'[INFO] Result of parameter substraction: {SC_Cls.Substraction()}')

    # Set the new (main) parameters of the class.
    SC_Cls.Set_Parameters(ARRAY_Max_Out.Value, ARRAY_Max_Out.Index)

    # Get the main parameters of the class as a string (char).
    print('[INFO] Input Parameters:')
    print(SC_Cls.Get_Parameters())
    # The addition of the main parameters.
    print(f'[INFO] Result of parameter addition: {SC_Cls.Addition()}')
    # The subtraction of main parameters.
    print(f'[INFO] Result of parameter substraction: {SC_Cls.Substraction()}')

if __name__ == '__main__':
    sys.exit(main())
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
File Name: Example_Lib_Shared.py
## =========================================================================== ## 
"""

# CTypes (C compatible data types, and allows calling functions in DLLs)
import ctypes as ct

# Shared library type:
#   DLL: Windows
#   SO: Linux
CONST_SHARED_LIB_TYP = 'DLL'

# Load the shared library (.dll/.so).
Example_SL = ct.cdll.LoadLibrary(f'..//..//Cpp_Shared_Lib//{CONST_SHARED_LIB_TYP}//Example_Lib_Shared.dll')

"""
Description:
    Specify the required argument types and return types of the function.
"""
Example_SL.Generate_Random_Array.argtypes = [ct.c_int, ct.c_int, ct.c_size_t]
Example_SL.Generate_Random_Array.restype  = ct.POINTER(ct.c_int)

def Generate_Random_Array(MIN, MAX, N):
    """
    Description:
        Generate a randomly defined array from the input parameters of the function.

    Args:
        (1) MIN [int]: The minimum value in the array.
        (2) MAX [int]: The maximum value in the array.
        (3) N [size_t]: The size of an array.

    Returns:
        (1) parameter [int array]: Random array of values.
    """

    return Example_SL.Generate_Random_Array(MIN, MAX, N)[0:N]

"""
Description:
    Specify the required argument types and return types of the function.
"""
Example_SL.Multiply_Array_By_Number.argtypes = [ct.c_int, ct.POINTER(ct.c_int), ct.c_size_t]
Example_SL.Multiply_Array_By_Number.restype  = ct.c_void_p

def Multiply_Array_By_Number(Number, Array):
    """
    Description:
        Multiply each value in the input array by the defined number.

    Args:
        (1) Number [int]: The number that is used to multiply the value in the array.
        (2) Array [int array]: Input/Output array of values.
    """

    # Convert a python array to an array of type C.
    Array_ct = (ct.c_int * len(Array))(*Array)
    # The size of the array.
    N = len(Array_ct)

    Example_SL.Multiply_Array_By_Number(Number, Array_ct, N)

    return Array_ct[0:N]

"""
Description:
    Declaration of the input/output structure for the Array_MinMax function.
"""
class FCE_ARRAY_MinMax_INPUT_Str(ct.Structure):
    """
    Description:
        Structure of function (Array_MinMax) input parameters.

    Args:
        (1) Array [int array]: Input array of values.
        (2) N [size_t]: The size of an array.
    """
    _fields_ = [('Array', ct.POINTER(ct.c_int)), 
                ('N', ct.c_size_t)]

class FCE_ARRAY_MinMax_OUTPUT_Str(ct.Structure):
    """
    Description:
        Structure of function (Array_MinMax) output parameters.

    Args:
        (1) Value [int]: Found value (min, max).
        (2) Index [int]: Found value index.
    """
    _fields_ = [('Value', ct.c_int), 
                ('Index', ct.c_int)]

"""
Description:
    Specify the required argument types and return types of the function.
"""
Example_SL.Array_MinMax.argtypes = [ct.POINTER(FCE_ARRAY_MinMax_INPUT_Str), ct.c_bool]
Example_SL.Array_MinMax.restype  = FCE_ARRAY_MinMax_OUTPUT_Str

def Array_MinMax(FCE_ARRAY_MinMax_INPUT, return_min_val):
    """
    Description:
        Function to return the minimum/maximum number and index from a defined array of values.

    Args:
        (1) Input [struct FCE_ARRAY_MinMax_INPUT_Str]: Input parameters (array, size).
        (2) return_min_val [bool]: Return the minimum value if true, otherwise return the maximum value.

    Returns:
        (2) parameter [struct FCE_ARRAY_MinMax_OUTPUT_Str]: Output parameters (value, index).
    """
    return Example_SL.Array_MinMax(FCE_ARRAY_MinMax_INPUT, return_min_val)


"""
Description:
    Specify the required argument types and return types of the Class (Simple_Calculator).
"""
# 1\
Example_SL.SC_Class_Create.argtypes = [ct.c_int, ct.c_int]
Example_SL.SC_Class_Create.restype  = ct.c_void_p
# 2\
Example_SL.SC_Class_Delete.argtypes = [ct.c_void_p]
Example_SL.SC_Class_Delete.restype  = ct.c_void_p
# 3\
Example_SL.SC_Class_Get_Parameters.argtypes = [ct.c_void_p]
Example_SL.SC_Class_Get_Parameters.restype  = ct.c_char_p
# 4\
Example_SL.SC_Class_Set_Parameters.argtypes = [ct.c_void_p, ct.c_int, ct.c_int]
Example_SL.SC_Class_Set_Parameters.restype  = ct.c_bool
# 5\
Example_SL.SC_Class_Addition_Parameters.argtypes = [ct.c_void_p]
Example_SL.SC_Class_Addition_Parameters.restype  = ct.c_int
# 6\
Example_SL.SC_Class_Substraction_Parameters.argtypes = [ct.c_void_p]
Example_SL.SC_Class_Substraction_Parameters.restype  = ct.c_int

class Simple_Calculator(object):
    """
    Description:
        A simple class to demonstrate the calculator.
    """
    def __init__(self, Parameter_1, Parameter_2):
        """
        Description:
            Initialization of input parameters.
        """
        self.__Parameter_1 = Parameter_1
        self.__Parameter_2 = Parameter_2

        # Create instance of the class.
        self.__DLL_SC_Cls = Example_SL.SC_Class_Create(self.__Parameter_1, self.__Parameter_2)

    def __del__(self):
        """
        Description:
            Delete a class object.
        """

        return Example_SL.SC_Class_Delete(self.__DLL_SC_Cls)

    def Get_Parameters(self):
        """
        Description:
            Get the main parameters of the class as a string (char).

        Returns:
            (1) parameter [string]: Information on the main parameters of the class.
        """
        return Example_SL.SC_Class_Get_Parameters(self.__DLL_SC_Cls).decode('utf-8')

    def Set_Parameters(self, Parameter_1, Parameter_2):
        """
        Description:
            Set the main parameters of the class.

        Args:
            (1, 2) Parameter_1/2 [int]: Main parameters of the class.
        """

        self.__Parameter_1 = Parameter_1
        self.__Parameter_2 = Parameter_2

        return Example_SL.SC_Class_Set_Parameters(self.__DLL_SC_Cls, self.__Parameter_1, self.__Parameter_2)

    def Addition(self):
        """
        Description:
            The addition of the main parameters.

        Returns:
            (1) parameter [int]: Addition of parameters (a + b).
        """

        return Example_SL.SC_Class_Addition_Parameters(self.__DLL_SC_Cls)

    def Substraction(self):
        """
        Description:
            The subtraction of main parameters.

        Returns:
            (1) parameter [int]: Substraction of parameters (a - b).
        """

        return Example_SL.SC_Class_Substraction_Parameters(self.__DLL_SC_Cls)

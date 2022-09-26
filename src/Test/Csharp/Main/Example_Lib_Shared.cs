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
File Name: Example_Lib_Shared.cs
****************************************************************************/

// System Lib.
using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace Example_Lib_Shared
{
    public static class Core
    {
        // Shared library type:
        //   DLL: Windows
        //   SO: Linux
        const string CONST_SHARED_LIB_TYP = "dll";
        // The path to a shared library.
        const string shared_lib_path = "..//..//..//Cpp_Shared_Lib//" + CONST_SHARED_LIB_TYP + "//Example_Lib_Shared." + CONST_SHARED_LIB_TYP;
        
        // Generate a randomly defined array from the input parameters of the function.
        [DllImport(shared_lib_path, EntryPoint = "Generate_Random_Array", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Generate_Random_Array(int MIN, int MAX, int N);
        // Multiply each value in the input array by the defined number.
        [DllImport(shared_lib_path, EntryPoint = "Multiply_Array_By_Number", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Multiply_Array_By_Number(int Number, IntPtr Array, int N);

        /*
        Description:
            Declaration of the input/output structure for the Array_MinMax function.
         */
        [StructLayout(LayoutKind.Sequential)]
        public struct FCE_ARRAY_MinMax_INPUT_Str
        {
            /*
            Description:
                Structure of function (Array_MinMax) input parameters.

            Args:
                (1) Array [IntPtr]: Input array of values.
                (2) N [int]: The size of an array.
             */
            public IntPtr Array;
            public int N;
        }
        [StructLayout(LayoutKind.Sequential)]
        public struct FCE_ARRAY_MinMax_OUTPUT_Str
        {
            /*
            Description:
                Structure of function (Array_MinMax) output parameters.

            Args:
                (1) Value [int]: Found value (min, max).
                (2) Index [int]: Found value index.
             */
            public int Value;
            public int Index;
        }

        // Function to return the minimum/maximum number and index from a defined array of values.
        [DllImport(shared_lib_path, EntryPoint = "Array_MinMax", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern FCE_ARRAY_MinMax_OUTPUT_Str Array_MinMax(ref FCE_ARRAY_MinMax_INPUT_Str Input, bool return_min_val);

        /*
        Description:
            Some helpful function for demostration of the class.
         */
        [DllImport(shared_lib_path, EntryPoint = "SC_Class_Create", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr SC_Class_Create(int Parameter_1, int Parameter_2);
        [DllImport(shared_lib_path, EntryPoint = "SC_Class_Delete", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern void SC_Class_Delete(IntPtr SC_Cls);
        // Get the main parameters of the class as a string (char).
        [DllImport(shared_lib_path, EntryPoint = "SC_Class_Get_Parameters", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr SC_Class_Get_Parameters(IntPtr SC_Cls);
        // Set the main parameters of the class.
        [DllImport(shared_lib_path, EntryPoint = "SC_Class_Set_Parameters", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern bool SC_Class_Set_Parameters(IntPtr SC_Cls, int Parameter_1, int Parameter_2);
        // The addition of the main parameters.
        [DllImport(shared_lib_path, EntryPoint = "SC_Class_Addition_Parameters", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SC_Class_Addition_Parameters(IntPtr SC_Cls);
        // The subtraction of main parameters.
        [DllImport(shared_lib_path, EntryPoint = "SC_Class_Substraction_Parameters", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern int SC_Class_Substraction_Parameters(IntPtr SC_Cls);
    }
}

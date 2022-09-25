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
File Name: Program.cs
****************************************************************************/

// System Lib.
using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;
// Custom Script:
//  Shared Lib. (Functions/Classes).
using Example_SL = Example_Lib_Shared.Core;

/*
 Note:
   $ dotnet build
   $ dotnet run
 */
 
namespace Main
{
    class Program
    {
        static void Main(string[] args)
        {
            /*
            Description:
                Demonstration of calling different functions/classes from a shared library (C/C++).
             */

            Console.WriteLine("[INFO] ===== Validation of Part 1. =====");
            // Generate a randomly defined array from the input parameters of the function.
            int SIZE = 5;
            IntPtr Arr_Rand_Ptr = Example_SL.Generate_Random_Array(1, 100, 5);
            // Display an array with defined rules.
            int[] Arr_Rand = IntPtr_To_Array<int>(Arr_Rand_Ptr, SIZE);
            Console.WriteLine("[INFO] Input Array: [{0}]", string.Join(", ", Arr_Rand));

            Console.WriteLine("[INFO] ===== Validation of Part 2. =====");
            // Multiply each value in the input array by the defined number.
            int Number = 5;
            Example_SL.Multiply_Array_By_Number(Number, Arr_Rand_Ptr, SIZE);
            // Display an array with defined rules.
            int[] Arr_Mult_Num = IntPtr_To_Array<int>(Arr_Rand_Ptr, SIZE);
            Console.WriteLine("[INFO] Multiplied the input array by {0}: [{1}]", Number, string.Join(", ", Arr_Mult_Num));

            Console.WriteLine("[INFO] ===== Validation of Part 3. =====");
            // Declaration of the input structure for the Array_MinMax function.
            Example_SL.FCE_ARRAY_MinMax_INPUT_Str ARRAY_MinMax_In = new Example_SL.FCE_ARRAY_MinMax_INPUT_Str();
            ARRAY_MinMax_In.Array = Arr_Rand_Ptr;
            ARRAY_MinMax_In.N     = SIZE;

            // Function to return the number and index from a defined array of values.
            //   The minimum number.
            Example_SL.FCE_ARRAY_MinMax_OUTPUT_Str ARRAY_Min_Out = Example_SL.Array_MinMax(ref ARRAY_MinMax_In, true);
            Console.WriteLine("[INFO] The minimum number of an input array.");
            Console.WriteLine("[INFO] [INFO] Value: {0} | Index: {1}", ARRAY_Min_Out.Value, ARRAY_Min_Out.Index);
            //   The minimum number.
            Example_SL.FCE_ARRAY_MinMax_OUTPUT_Str ARRAY_Max_Out = Example_SL.Array_MinMax(ref ARRAY_MinMax_In, false);
            Console.WriteLine("[INFO] The maximum number of an input array.");
            Console.WriteLine("[INFO] [INFO] Value: {0} | Index: {1}", ARRAY_Max_Out.Value, ARRAY_Max_Out.Index);

            Console.WriteLine("[INFO] ===== Validation of Part 4. =====");
            // A simple class to demonstrate the calculator.
            IntPtr Cls = Example_SL.SC_Class_Create(ARRAY_Min_Out.Value, ARRAY_Min_Out.Index);

            // Get the main parameters of the class as a string (char).
            Console.WriteLine("[INFO] Input Parameters:");
            IntPtr Parameters_Ptr = Example_SL.SC_Class_Get_Parameters(Cls);
            Console.WriteLine(Marshal.PtrToStringAnsi(Parameters_Ptr));
            // The addition of the main parameters.
            Console.WriteLine("[INFO] Result of parameter addition: {0}", Example_SL.SC_Class_Addition_Parameters(Cls));
            Console.WriteLine("[INFO] Result of parameter substraction: {0}", Example_SL.SC_Class_Substraction_Parameters(Cls));

            // Set the new (main) parameters of the class.
            Example_SL.SC_Class_Set_Parameters(Cls, ARRAY_Max_Out.Value, ARRAY_Max_Out.Index);
            
            // Get the main parameters of the class as a string (char).
            Console.WriteLine("[INFO] Input Parameters:");
            Parameters_Ptr = Example_SL.SC_Class_Get_Parameters(Cls);
            Console.WriteLine(Marshal.PtrToStringAnsi(Parameters_Ptr));
            // The addition of the main parameters.
            Console.WriteLine("[INFO] Result of parameter addition: {0}", Example_SL.SC_Class_Addition_Parameters(Cls));
            Console.WriteLine("[INFO] Result of parameter substraction: {0}", Example_SL.SC_Class_Substraction_Parameters(Cls));

            // Delete a class object.
            Example_SL.SC_Class_Delete(Cls);

            // Frees memory.
            Marshal.FreeHGlobal(Arr_Rand_Ptr);
        }

        public static T[] IntPtr_To_Array<T>(IntPtr Array, int N)
        {
            /*
            Description:
                A simple function to convert an IntPtr type to an array.

            Args:
                (1) Array [IntPtr]: Input array (pointer) of values.
                (2) N [size_t]: The size of the array.

            Returns:
                (1) parameter [T[]]: Output converted array of values.
             */

            dynamic Array_Out = new T[N];
            Marshal.Copy(Array, Array_Out, 0, Array_Out.Length);

            return Array_Out;
        }
    }
}

using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

namespace app
{
    class Program
    {
        // Shared library type:
        //   DLL: Windows
        //   SO: Linux
        const string CONST_SHARED_LIB_TYP = "DLL";
        // The path to a shared library.
        const string shared_lib_path = "..//..//Cpp_Shared_Lib//" + CONST_SHARED_LIB_TYP + "//Example_Lib_Shared.dll";
        
        [DllImport(shared_lib_path, EntryPoint = "Generate_Random_Array", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Generate_Random_Array(int MIN, int MAX, int N);

        [DllImport(shared_lib_path, EntryPoint = "Multiply_Array_By_Number", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Multiply_Array_By_Number(int Number, IntPtr Array, int N);

        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");

            IntPtr res = Generate_Random_Array(1, 100, 5);

            int[] managedArray1 = new int[5];
            Marshal.Copy(res, managedArray1, 0, managedArray1.Length);

            Console.WriteLine("[{0}]", string.Join(", ", managedArray1));

            Multiply_Array_By_Number(5, res, 5);

            int[] managedArray2 = new int[5];
            Marshal.Copy(res, managedArray2, 0, managedArray2.Length);

            Console.WriteLine("[{0}]", string.Join(", ", managedArray2));


            //int[] result = new int[5];
            int[] result = IntPtr_To_Array<int>(res, 5);
            Console.WriteLine("[{0}]", string.Join(", ", result));
        }

        public static T[] IntPtr_To_Array<T>(IntPtr Array, int N)
        {
            dynamic Array_Out = new T[N];
            Marshal.Copy(Array, Array_Out, 0, Array_Out.Length);

            return Array_Out;
        }
    }
}

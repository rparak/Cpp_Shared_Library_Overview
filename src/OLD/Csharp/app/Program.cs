using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;


namespace app
{
    class Program
    {
        [DllImport("Example_Lib_Shared.dll", EntryPoint = "Max_Int", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Max_Int(ref int[] arr, int N);

        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");

            int[] input_1 = { 1, 2, 3, 4, 5 };

            IntPtr result = Max_Int(input_1, input_1.Length);
        }
    }
}

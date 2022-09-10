using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

// https://travis.media/how-to-run-csharp-in-vscode/
namespace app
{
    class Program
    {
        [DllImport("lib.dll", EntryPoint = "Array_Mult", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern void Array_Mult(int a, int[] b);

        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
            //Console.WriteLine(Add(5, 6));

            int[] input_1 = { 1, 2, 3, 4, 5 };
            Array_Mult(5, input_1);

            foreach ( int x in input_1)
            {
                Console.WriteLine("Element is {0}", x);
            }
        }
    }
}

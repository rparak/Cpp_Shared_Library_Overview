using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

// https://travis.media/how-to-run-csharp-in-vscode/
// https://www.796t.com/post/YWFjcXc=.html
namespace app
{
    class Program
    {
        [StructLayout(LayoutKind.Sequential)]
        public struct ArrayStruct
        {
            [MarshalAs(UnmanagedType.ByValArray, SizeConst = 5)]
            public int[] arr;
            public int length;
        }

        [DllImport("lib.dll", EntryPoint = "GetArray", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern void GetArray(ref ArrayStruct a);

        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
            //Console.WriteLine(Add(5, 6));


            ArrayStruct a = new ArrayStruct();
            a.arr = new int[5];
            GetArray(ref a);

            Console.WriteLine(a.length);
            foreach( int x in a.arr){
                Console.WriteLine("Element is {0}", x);
            }

            /*
            int[] input_1 = { 1, 2, 3, 4, 5 };
            Array_Mult(5, input_1);

            foreach ( int x in input_1)
            {
                Console.WriteLine("Element is {0}", x);
            }
            */
        }
    }
}

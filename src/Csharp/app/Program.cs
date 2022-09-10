using System;
using System.Runtime.InteropServices;

// https://travis.media/how-to-run-csharp-in-vscode/
namespace app
{
    class Program
    {
        [DllImport("lib.dll", EntryPoint = "Add", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern int Add(int a, int b);

        static void Main(string[] args)
        {
            Console.WriteLine("Hello World!");
            Console.WriteLine(Add(5, 6));
        }
    }
}

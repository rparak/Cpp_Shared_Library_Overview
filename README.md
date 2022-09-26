# Brief Overview of Creating a Shared Library (.dll / .so) in C++

## Requirements:

**Programming Language:**

```bash
C++, C#, Python
```

**Import Libraries:**
```bash
More information can be found in the individual scripts (.hpp, .py, etc.)
```

**Supported on the following operating systems:**
```bash
Windows, Linux
```

## Project Description:
A simple demonstration that shows how to create and export a shared library from a C/C++ programming language and import it into another programming language (Python, C#, C++).

The main goal of the project is to demonstrate the calling of various functions/classes from a shared library (C/C++), as well as the use of C++ templates in this particular problem. 

The project can be used as a guide to create a custom application that is limited by the type of programming language or the number of appropriate functions, but it would be useful to use the C++ programming language to speed up calculations or something else. 

A good example is importing a shared library in the Unity3D simulation software, because the SW is limited by the C# language.

For a simple example of exporting and importing a shared library that generates an array of random rational numbers, see the "Simple Demonstration" section below. More detailed programs can be found in the repository folders (see the project hierarchy).

**Running a program in different programming languages:**

1\ Programming Language: C++ (.dll/.so)
```bash
Windows:
    $ g++ -shared -std=c++17 -fPIC -o Shared_Lib_Name.dll Shared_Lib_Name.cpp
Linux:
    $ g++ -shared -std=c++17 -fPIC -o Shared_Lib_Name.so Shared_Lib_Name.cpp
```

2\ Programming Language: C++
```bash
   $ g++ -std=c++17 main.cpp -o main -ldl
   $ ./main
```

2\ Programming Language: C#
```bash
   $ dotnet build
   $ dotnet run
```

2\ Programming Language: Python
```bash
Windows:
    $ py -3.6 main.py
Linux:
    $ python3 main.py
```

**A useful information about creating and running a C# program in Visual Studio Code:**
1. Install .NET X.X if it is not already installed.

Link: https://dotnet.microsoft.com/download

Then confirm that dotnet is installed.
```bash
$ dotnet --version
```
2. Create a new C# project
```bash 
$ dotnet new console -o Main
$ cd Main
```
3. Compile code
```bash 
$ dotnet build
```
4. Run C# code
```bash 
$ dotnet run
```

## Project Hierarchy:
**Repositary [/Cpp_Shared_Library_Overview/src]:**
```bash

Language = Cpp, Csharp/Main, Python

1\ Shared library.
[/Cpp_Shared_Lib/]
Cpp: Example_Lib_Shared.cpp
DLL: Example_Lib_Shared.dll
SO: Example_Lib_Shared.so

2\ Simple tests to verify functionality.
[/Test/{Language}/]
Cpp: Example_Lib_Shared.hpp
Cpp: main.cpp
Csharp/Main: Example_Lib_Shared.cs
Csharp/Main: Program.cs
Python: Example_Lib_Shared.py
Python: main.py

```

## Simple Demonstration

**Creating and exporting a shared C++ library:**
```cpp 
#include <iostream>
#include <ctime>

/*
Note:
    Windows:
        $ g++ -shared -std=c++17 -fPIC -o Shared_Lib_Name.dll Shared_Lib_Name.cpp
    Linux:
        $ g++ -shared -std=c++17 -fPIC -o Shared_Lib_Name.so Shared_Lib_Name.cpp
*/

extern "C" {
    __declspec(dllexport) double* Generate_Random_Array(const double MIN, const double MAX, const size_t N)
    {
        /*
        Description:
            Generate a randomly defined array from the input parameters of the function.
        Args:
            (1) MIN [double]: The minimum value in the array.
            (2) MAX [double]: The maximum value in the array.
            (3) N [size_t]: The size of an array.
        Returns:
            (1) parameter [double*]: Random array of values.
        */

        std::srand(time(0)); 

        double* Output = new double[N];
        for(auto i = 0; i < N; ++i){
            Output[i] = static_cast<double>(MIN + (double)(rand()) / ((double)(RAND_MAX/(MAX - MIN))));
        }

        return Output;
    }
}
```

**Importing and testing a shared library in C++:**
```cpp
#include <iostream>
#include <iterator>
#include <vector>
#include <dlfcn.h>

/*
 Note:
   $ g++ -std=c++17 main.cpp -o main -ldl
   $ ./main
 */

/*
Description:
    Specify the required argument types and return types of the functions.
 */
extern "C" {
    typedef double* (*Generate_Random_Array_Typ)(const double MIN, const double MAX, const size_t N);
}

// Shared library type:
//   DLL: Windows
//   SO: Linux
const std::string CONST_SHARED_LIB_TYP = "dll";

int main() {
    // The path to a shared library.
    std::string shared_lib_path = "Shared_Lib_Name." + CONST_SHARED_LIB_TYP;

    // Access to an executable object file (load the shared library - .dll/.so).
    void* Example_SL = dlopen(shared_lib_path.c_str(), RTLD_LAZY);

    // Declaration of shared library function.
    Generate_Random_Array_Typ Generate_Random_Array = (Generate_Random_Array_Typ)dlsym(Example_SL, "Generate_Random_Array"); 

    // Generate a randomly defined array from the input parameters of the function.
    const size_t SIZE = 5;
    double *Arr_Rand = Generate_Random_Array(1.0, 10.0, SIZE);

    // Display an array with defined rules.
    std::vector<double> v(Arr_Rand, Arr_Rand + 5);
    std::cout << "[";
    std::copy(v.begin(), v.end() - 1, std::ostream_iterator<double>(std::cout << std::scientific, ", "));
    std::cout << v.back() << "]" << std::endl;

    // Frees memory.
    delete Arr_Rand;
    Arr_Rand = NULL;

    // Close a dlopen object.
    dlclose(Example_SL);
}
```

**Importing and testing a shared library in C#:**
```cs
// System Lib.
using System;
using System.Collections.Generic;
using System.Runtime.InteropServices;

/*
 Note:
   $ dotnet build
   $ dotnet run
 */

namespace Main
{
    class Program
    {
        // Shared library type:
        //   DLL: Windows
        //   SO: Linux
        const string CONST_SHARED_LIB_TYP = "dll";
        // The path to a shared library.
        const string shared_lib_path = "..//Shared_Lib_Name." + CONST_SHARED_LIB_TYP;

        // Generate a randomly defined array from the input parameters of the function.
        [DllImport(shared_lib_path, EntryPoint = "Generate_Random_Array", ExactSpelling = false, CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Generate_Random_Array(double MIN, double MAX, int N);

        static void Main(string[] args)
        {
            // Generate a randomly defined array from the input parameters of the function.
            int SIZE = 5;
            IntPtr Arr_Rand_Ptr = Generate_Random_Array(1.0, 10.0, SIZE);
            // Display an array with defined rules.
            double[] Arr_Rand = IntPtr_To_Array<double>(Arr_Rand_Ptr, SIZE);
            Console.WriteLine("[{0}]", string.Join(", ", Arr_Rand));

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
```

**Importing and testing a shared library in Python:**
```py 
# CTypes (C compatible data types, and allows calling functions in DLLs)
import ctypes as ct

"""
Note:
    Windows:
        $ py -3.6 main.py
    Linux:
        $ python3 main.py
"""

# Shared library type:
#   DLL: Windows
#   SO: Linux
CONST_SHARED_LIB_TYP = 'dll'

# Load the shared library (.dll/.so).
Example_SL = ct.cdll.LoadLibrary(f'Shared_Lib_Name.{CONST_SHARED_LIB_TYP}')

# Specify the required argument types and return types of the function.
Example_SL.Generate_Random_Array.argtypes = [ct.c_double, ct.c_double, ct.c_size_t]
Example_SL.Generate_Random_Array.restype  = ct.POINTER(ct.c_double)

# Generate a randomly defined array from the input parameters of the function.
print(Example_SL.Generate_Random_Array(1.0, 10.0, 5)[0:5])
```

## Contact Info:
Roman.Parak@outlook.com

## License
[MIT](https://choosealicense.com/licenses/mit/)

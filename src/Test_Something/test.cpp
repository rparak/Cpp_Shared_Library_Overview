#include <stdio.h>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
// https://stephenscotttucker.medium.com/interfacing-python-with-c-using-ctypes-classes-and-arrays-42534d562ce7

// g++ -shared -std=c++17 -fPIC -o test.dll test.cpp
// gcc -shared test.cpp -o test.dll
// https://github.com/aphage/demo/tree/master/c-cplusplus/cplusplus-class-export/hello-aphage
/*
extern "C" {  
    __declspec(dllexport) int add(int a, int b) {  
      return a + b;  
    }  
    __declspec(dllexport) int subtract(int a, int b) {  
      return a - b;  
    }  

   __declspec(dllexport) void func_vec(int a, int b){
      printf("%d", a*b);
   } 
}  
*/

class Room {
  public:
      double length;
      double width;
      double height;   

      double calculateArea(){   
          return this->length * this->width;
      }

      double calculateVolume(){   
          return this->length * this->width * this->height;
      }

};

template <typename T> T Add_T(T a, T b)
{ 
  return a + b;
}
template <typename T> T Substract_T(T a, T b) 
{
  return a - b;
}

//typedef int dtype;

extern "C" {  
    __declspec(dllexport) double Add(double a, double b)
    {
      return Add_T(a, b);
    }
    __declspec(dllexport) double Substract(double a, double b)
    {
      return Substract_T(a, b);
    }

    __declspec(dllexport) Room Room_Cls();
}
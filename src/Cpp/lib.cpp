#include <iostream>
#include <vector>
#include <cstdio>

// g++ -shared -fPIC -o libhello.so hello.cpp
/*
extern "C" int Add(int a, int b) {
  return a + b;
}
*/

extern "C" void Array_Mult(int nElements, int *pElements) { 
	int x;
	for (int i = 0; i < nElements; i++)
	{
		x = pElements[i];
		pElements[i] = x + 10;
	}
}
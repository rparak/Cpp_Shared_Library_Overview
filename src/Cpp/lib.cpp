#include <iostream>
#include <vector>
#include <cstdio>

// https://peaku.co/questions/22798-pasar-un-vector-matriz-de-c%2B%2B-no-administrado-a-c%23
// g++ -shared -fPIC -o libhello.so hello.cpp
/*
extern "C" int Add(int a, int b) {
  return a + b;
}
*/

/*
extern "C" void Array_Mult(int nElements, int *pElements) { 
	int x;
	for (int i = 0; i < nElements; i++)
	{
		x = pElements[i];
		pElements[i] = x + 10;
	}
}
*/

struct ArrayStruct
{
	std::vector<int> arr;
	int length;
};

extern "C" __declspec(dllexport) void GetArray(ArrayStruct* a)
{
	a->length = 5;
	for(int i=0; i<a->length; i++)
		a->arr.push_back(i);
}
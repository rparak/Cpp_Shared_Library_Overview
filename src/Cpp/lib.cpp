#include <cstdio>

// g++ -shared -fPIC -o libhello.so hello.cpp
extern "C" int Add(int a, int b) {
  return a + b;
}
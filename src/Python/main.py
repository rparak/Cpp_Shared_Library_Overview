# CTypes (C compatible data types, and allows calling functions in DLLs)
import ctypes as ct
from types import DynamicClassAttribute

# https://stackoverflow.com/questions/4351721/python-ctypes-passing-a-struct-to-a-function-as-a-pointer-to-get-back-data
__dll_lib = ct.cdll.LoadLibrary('lib.dll')
#print(__dll_lib.Add(5, 6))

a = ct.c_int(5)
py_values = [1, 2, 3, 4, 5]
arr = (ct.c_int * len(py_values))(*py_values)

__dll_lib.Array_Mult(a, arr)

print(type(arr))
for arr_i in arr:
    print(arr_i)

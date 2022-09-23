import ctypes as ct
from numpy.ctypeslib import ndpointer

class FCE_ARRAY_MinMax_INPUT_Str(ct.Structure):
    _fields_ = [('Array', ct.POINTER(ct.c_int)), ('N', ct.c_size_t)]

class FCE_ARRAY_MinMax_OUTPUT_Str(ct.Structure):
    _fields_ = [('Value', ct.c_int), ('Index', ct.c_int)]

__dll_lib = ct.cdll.LoadLibrary('Example_Lib_Shared.dll')

__dll_lib.Array_MinMax.argtypes = [ct.POINTER(FCE_ARRAY_MinMax_INPUT_Str), ct.c_bool]
__dll_lib.Array_MinMax.restype  = FCE_ARRAY_MinMax_OUTPUT_Str

data = [5, 11, 3, 8, 5]
input_v = FCE_ARRAY_MinMax_INPUT_Str((ct.c_int * len(data))(*data), ct.c_size_t(len(data)))

res = __dll_lib.Array_MinMax(input_v, False)

print(res.Value, res.Index)

__dll_lib.Generate_Random_Array.argtypes = [ct.c_int, ct.c_int, ct.c_size_t]
__dll_lib.Generate_Random_Array.restype = ct.POINTER(ct.c_int)

res_0 = __dll_lib.Generate_Random_Array(1, 1000, 10)

print(type(res_0))
for i in range(0, 10):
    print(res_0[i])

__dll_lib.Multiply_Array_By_Number.argtypes = [ct.c_int, ct.POINTER(ct.c_int), ct.c_size_t]
__dll_lib.Multiply_Array_By_Number.restype = None

py_values = [1, 2, 3, 4, 5]
arr = (ct.c_int * len(py_values))(*py_values)
__dll_lib.Multiply_Array_By_Number(ct.c_int(5), arr, ct.c_size_t(len(arr)))

for i in range(0, len(arr)):
    print(arr[i])

"""
__dll_lib.Max_Int_Py.argtypes = (ct.POINTER(ct.c_int), ct.c_size_t)
__dll_lib.Max_Int_Py.restype  = ndpointer(dtype=ct.c_int, shape=(2,))

data = [1, 11, 3, 8, 5]
data_ct = (ct.c_int * len(data))(*data)
res = __dll_lib.Max_Int_Py(data_ct, ct.c_size_t(5))

print(res[0])
"""




import ctypes as ct
from numpy.ctypeslib import ndpointer

class Find_Min_Value_Output_str(ct.Structure):
    _fields_ = [("value", ct.c_int), ("idx", ct.c_int)]

class Find_Min_Value_Input_str(ct.Structure):
    _fields_ = [("x", ct.POINTER(ct.c_int)), ("N", ct.c_size_t)]

__dll_lib = ct.cdll.LoadLibrary('Example_Lib_Shared.dll')


__dll_lib.Min_Int.argtypes = [ct.POINTER(Find_Min_Value_Input_str)]
__dll_lib.Min_Int.restype  = Find_Min_Value_Output_str

data = [5, 11, 3, 8, 5]
input_v = Find_Min_Value_Input_str((ct.c_int * len(data))(*data), ct.c_size_t(len(data)))

res = __dll_lib.Min_Int(input_v)

print(res.value, res.idx)

"""
__dll_lib.Max_Int_Py.argtypes = (ct.POINTER(ct.c_int), ct.c_size_t)
__dll_lib.Max_Int_Py.restype  = ndpointer(dtype=ct.c_int, shape=(2,))

data = [1, 11, 3, 8, 5]
data_ct = (ct.c_int * len(data))(*data)
res = __dll_lib.Max_Int_Py(data_ct, ct.c_size_t(5))

print(res[0])
"""




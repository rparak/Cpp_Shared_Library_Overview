import ctypes as ct
from numpy.ctypeslib import ndpointer

__dll_lib = ct.cdll.LoadLibrary('Example_Lib_Shared.dll')

__dll_lib.Max_Int_Py.argtypes = (ct.POINTER(ct.c_int), ct.c_size_t)
__dll_lib.Max_Int_Py.restype  = ndpointer(dtype=ct.c_int, shape=(2,))

data = [1, 11, 3, 8, 5]
data_ct = (ct.c_int * len(data))(*data)
res = __dll_lib.Max_Int_Py(data_ct, ct.c_size_t(5))

print(res[0])




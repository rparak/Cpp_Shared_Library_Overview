# CTypes (C compatible data types, and allows calling functions in DLLs)
import ctypes as ct

__dll_lib = ct.cdll.LoadLibrary('test.dll')

in_1 = 5.0
in_2 = 6.0
__dll_lib.Add.argtypes = [ct.c_double, ct.c_double]
__dll_lib.Add.restype  = ct.c_double
Add_res = __dll_lib.Add(in_1, in_2)
print(type(Add_res))

__dll_lib.Substract.argtypes = [ct.c_double, ct.c_double]
__dll_lib.Substract.restype  = ct.c_double
Substract_res = __dll_lib.Substract(in_1, in_2)
print(Substract_res)

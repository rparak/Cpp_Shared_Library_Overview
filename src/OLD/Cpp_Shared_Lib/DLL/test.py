import ctypes as ct
from numpy.ctypeslib import ndpointer

# https://www.auctoris.co.uk/2017/04/29/calling-c-classes-from-python-with-ctypes/
# https://stephenscotttucker.medium.com/interfacing-python-with-c-using-ctypes-classes-and-arrays-42534d562ce7
# https://solarianprogrammer.com/2019/07/18/python-using-c-cpp-libraries-ctypes/
# https://kezunlin.me/post/41fe963e/
# https://github.com/Auctoris/ctypes_demo/blob/master/foo.py
# https://betterprogramming.pub/how-to-create-a-python-wrapper-for-c-c-shared-libraries-35ffefcfc10b
# https://bitcoden.com/answers/how-to-expose-c-class-to-python-without-using-boost

class FCE_ARRAY_MinMax_INPUT_Str(ct.Structure):
    _fields_ = [('Array', ct.POINTER(ct.c_int)), ('N', ct.c_size_t)]

class FCE_ARRAY_MinMax_OUTPUT_Str(ct.Structure):
    _fields_ = [('Value', ct.c_int), ('Index', ct.c_int)]

__dll_lib = ct.cdll.LoadLibrary('Example_Lib_Shared.dll')

Array_MinMax = getattr(__dll_lib, 'Array_MinMax')
Array_MinMax.argtypes = [ct.POINTER(FCE_ARRAY_MinMax_INPUT_Str), ct.c_bool]
Array_MinMax.restype  = FCE_ARRAY_MinMax_OUTPUT_Str

data = [5, 11, 3, 8, 5]
input_v = FCE_ARRAY_MinMax_INPUT_Str((ct.c_int * len(data))(*data), ct.c_size_t(len(data)))

res = Array_MinMax(input_v, True)

print(res.Value, res.Index)

__dll_lib.Generate_Random_Array.argtypes = [ct.c_int, ct.c_int, ct.c_size_t]
__dll_lib.Generate_Random_Array.restype = ct.POINTER(ct.c_int)

res_0 = __dll_lib.Generate_Random_Array(1, 1000, 10)

print(type(res_0))

__dll_lib.Multiply_Array_By_Number.argtypes = [ct.c_int, ct.POINTER(ct.c_int), ct.c_size_t]
__dll_lib.Multiply_Array_By_Number.restype = None

py_values = [1, 2, 3, 4, 5]
arr = (ct.c_int * len(py_values))(*py_values)
__dll_lib.Multiply_Array_By_Number(ct.c_int(5), arr, ct.c_size_t(len(arr)))

class Simple_Calculator(object):
    def __init__(self, DLL_Lib, Parameter_1, Parameter_2):
        self.__DLL_Lib = DLL_Lib
        self.__Parameter_1 = Parameter_1
        self.__Parameter_2 = Parameter_2

        # ...
        self.__DLL_Lib.SC_Class_Create.argtypes = [ct.c_int, ct.c_int]
        self.__DLL_Lib.SC_Class_Create.restype  = ct.c_void_p
        # ...
        self.__DLL_Lib.SC_Class_Delete.argtypes = [ct.c_void_p]
        self.__DLL_Lib.SC_Class_Delete.restype  = ct.c_void_p
        # ...
        self.__DLL_Lib.SC_Class_Get_Parameters.argtypes = [ct.c_void_p]
        self.__DLL_Lib.SC_Class_Get_Parameters.restype  = ct.c_char_p
        # ...
        self.__DLL_Lib.SC_Class_Set_Parameters.argtypes = [ct.c_void_p, ct.c_int, ct.c_int]
        self.__DLL_Lib.SC_Class_Set_Parameters.restype  = ct.c_bool
        # ...
        self.__DLL_Lib.SC_Class_Addition_Parameters.argtypes = [ct.c_void_p]
        self.__DLL_Lib.SC_Class_Addition_Parameters.restype  = ct.c_int
        # ...
        self.__DLL_Lib.SC_Class_Substraction_Parameters.argtypes = [ct.c_void_p]
        self.__DLL_Lib.SC_Class_Substraction_Parameters.restype  = ct.c_int

        self.__DLL_SC_Cls = self.__DLL_Lib.SC_Class_Create(self.__Parameter_1, self.__Parameter_2)

    def __del__(self):
        return self.__DLL_Lib.SC_Class_Delete(self.__DLL_SC_Cls)

    def Get_Parameters(self):
        return self.__DLL_Lib.SC_Class_Get_Parameters(self.__DLL_SC_Cls).decode('utf-8')

    def Set_Parameters(self, Parameter_1, Parameter_2):
        self.__Parameter_1 = Parameter_1
        self.__Parameter_2 = Parameter_2

        return self.__DLL_Lib.SC_Class_Set_Parameters(self.__DLL_SC_Cls, self.__Parameter_1, self.__Parameter_2)

    def Addition(self):
        return self.__DLL_Lib.SC_Class_Addition_Parameters(self.__DLL_SC_Cls)

    def Substraction(self):
        return self.__DLL_Lib.SC_Class_Substraction_Parameters(self.__DLL_SC_Cls)


SC_Cls = Simple_Calculator(__dll_lib, 12, 5)
print(SC_Cls.Get_Parameters())
print(SC_Cls.Addition())
print(SC_Cls.Substraction())

print(SC_Cls.Set_Parameters(10, 8))

print(SC_Cls.Get_Parameters())
print(SC_Cls.Addition())
print(SC_Cls.Substraction())


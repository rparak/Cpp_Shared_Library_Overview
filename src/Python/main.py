# CTypes (C compatible data types, and allows calling functions in DLLs)
import ctypes as ct

__dll_lib = ct.cdll.LoadLibrary('lib.dll')
print(__dll_lib.Add(5, 6))
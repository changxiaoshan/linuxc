from ctypes import cdll      
somelibc = cdll.LoadLibrary("./libsample.so")
somelibc.helloWorld()

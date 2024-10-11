import ctypes

# 加载共享库
lib = ctypes.CDLL('./example1.so')  # 在Windows上可能是 './example.dll'

# 指定函数的返回类型和参数类型

# MyClass* MyClass_new(int value)
lib.MyClass_new.argtypes = [ctypes.c_int]
lib.MyClass_new.restype = ctypes.POINTER(ctypes.c_void_p)

# void MyClass_delete(MyClass* instance)
lib.MyClass_delete.argtypes = [ctypes.POINTER(ctypes.c_void_p)]
lib.MyClass_delete.restype = None

# void MyClass_set_value(MyClass* instance, int value)
lib.MyClass_set_value.argtypes = [ctypes.POINTER(ctypes.c_void_p), ctypes.c_int]
lib.MyClass_set_value.restype = None

# int MyClass_get_value(MyClass* instance)
lib.MyClass_get_value.argtypes = [ctypes.POINTER(ctypes.c_void_p)]
lib.MyClass_get_value.restype = ctypes.c_int

# void MyClass_display(MyClass* instance)
lib.MyClass_display.argtypes = [ctypes.POINTER(ctypes.c_void_p)]
lib.MyClass_display.restype = None

# 创建MyClass的实例
instance = lib.MyClass_new(10)

# 调用方法
lib.MyClass_display(instance)  # 输出: Value: 10

# 修改值
lib.MyClass_set_value(instance, 42)

# 获取值
value = lib.MyClass_get_value(instance)
print(f"New value: {value}")  # 输出: New value: 42

# 显示修改后的值
lib.MyClass_display(instance)  # 输出: Value: 42

# 销毁实例
lib.MyClass_delete(instance)


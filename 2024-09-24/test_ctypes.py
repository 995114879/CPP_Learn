import ctypes

example = ctypes.CDLL('./example_c.so')

add_result = example.add(1,1)
print(add_result)

example.greet.restype = ctypes.c_char_p
greeting = example.greet()
print(greeting.decode('utf-8'))
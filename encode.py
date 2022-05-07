from ctypes import *

def fctem_to_txt(fctem_path: str):
    addres = create_string_buffer(100000000,"\0")
    lib = cdll.LoadLibrary('./encode/lib/libencode.so')
    lib.FCTEM2TXT.argtypes = [c_char_p, c_char_p]
    fctem = open(fctem_path)
    fctem_context = fctem.read()
    lib.FCTEM2TXT(bytes(fctem_context,'UTF-8'),addres)
    return str(addres.value.decode('UTF-8'))
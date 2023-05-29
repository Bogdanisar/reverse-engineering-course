import winreg
import random
import string
import subprocess
import pwn
import pyperclip


# Run this outside of IDA.
# The script assumes the system is Little-Endian.


def get_machine_guid_registry_key():
    computer_name = None # This computer
    aReg = winreg.ConnectRegistry(computer_name, winreg.HKEY_LOCAL_MACHINE)
    # print(r"*** Reading from %s ***" % aReg)

    aKey = winreg.OpenKey(aReg, "SOFTWARE\\Microsoft\\Cryptography")
    machine_guid_tuple = winreg.QueryValueEx(aKey, "MachineGuid")
    return machine_guid_tuple[0]


def get_random_license_key():
    possible_chars = string.ascii_lowercase + string.digits
    generated_key = [random.choice(possible_chars) for _ in range(36)]

    generated_key[8] = '-'
    generated_key[13] = '-'
    generated_key[18] = '-'
    generated_key[23] = '-'

    return generated_key


def computeXorOfKey(key):
    xor_sum = 0

    for i in range(0, len(key), 4):
        current_bytes = key[i:i+4]
        # print(f"{current_bytes = }")

        current_int = 0
        current_int += (ord(current_bytes[0]) << 0)
        current_int += (ord(current_bytes[1]) << 8)
        current_int += (ord(current_bytes[2]) << 16)
        current_int += (ord(current_bytes[3]) << 24)
        # print(f"{current_int = }")

        xor_sum ^= current_int

    return xor_sum


def get_bit(number, pos):
    return (number >> pos) & 1

def set_bit(number, pos, bit):
    if bit == 1:
        return number | (1 << pos)
    elif bit == 0:
        return number & ~(1 << pos)
    assert(False)


def fix_last_4_bytes_of_random_key(generated_key, machine_guid):
    xor_guid = computeXorOfKey(machine_guid)
    print(f"{xor_guid = }")

    xor_generated_key_partial = computeXorOfKey(generated_key[:-4])
    print(f"{xor_generated_key_partial = }")

    # We need to fix the last 4-bytes/int32 of generated_key,
    # which will give the final xor value by the formula:
    # xor_generated_key_full = (xor_generated_key_partial ^ last_int32)
    # The generated key will be correct, if:
    # - count_bits(xor_generated_key_full) >= 16
    # - last_2_bits(xor_generated_key_full) == last_2_bits(xor_guid)
    # - generated_key is visible ASCII, i.e. we need bytes(last_int32) to be visible ASCII too.
    # This means that:
    # We can choose a good value for xor_generated_key_full that fits the requirements
    # and compute last_int32 in reverse.

    last_int32 = 0
    for i in range(0, 4):
        current_byte_in_generated_partial = (xor_generated_key_partial >> (i * 8)) & 0xFF

        target_byte_in_result = 0b1111_1111
        if i == 0:
            for pos in range(0, 2):
                wanted_bit = get_bit(xor_guid, pos)
                target_byte_in_result = set_bit(target_byte_in_result, pos, wanted_bit)

        best_byte_in_last_int32 = (current_byte_in_generated_partial ^ target_byte_in_result)

        # This way we ensure that the byte looks like 0b011xxxxx. This means that it will be
        # a character in the fourth column of the ASCII table (lowercase letters or others).
        # Since we change 3 bits below, then the only guarantee is that bits(actual_byte_in_result) >= bits(target_byte_in_result) - 3.
        # So, bits_of_final_byte_i >= 5 when i == 1,2,3 and bits_of_final_byte_i >= 3 when i == 0;
        # So, total_bits_in_result >= 5 + 5 + 5 + 3 = 18 which is bigger than the target number of 16 bits.
        visible_byte_in_last_int32 = best_byte_in_last_int32
        visible_byte_in_last_int32 = set_bit(visible_byte_in_last_int32, 7, 0)
        visible_byte_in_last_int32 = set_bit(visible_byte_in_last_int32, 6, 1)
        visible_byte_in_last_int32 = set_bit(visible_byte_in_last_int32, 5, 1)

        # BUT, the DEL char is also in the fourth ASCII column.
        if (visible_byte_in_last_int32 == 127):
            print("DEL character was computed. Fix...")

            # We had no guarantees in regards to bit number 6 anyway, so this doesn't change the inequality above.
            visible_byte_in_last_int32 = set_bit(visible_byte_in_last_int32, 6, 0)

            # DEL is now '?'
            assert chr(visible_byte_in_last_int32) == '?'

        # print(f"{visible_byte_in_last_int32 = }")
        last_int32 = last_int32 | (visible_byte_in_last_int32 << (i * 8))

    # Patch the last 4 bytes in generated_key.
    for i in range(4):
        idx = len(generated_key) - 4 + i
        current_byte = (last_int32 >> (i * 8)) & 0xFF

        print(f"We patch byte number {idx} in the license key from '{generated_key[idx]}' to '{chr(current_byte)}'")
        generated_key[idx] = chr(current_byte)


def launch_process_with_key(generated_key):
    path = "C:\\Users\\test\\Desktop\\1_Minesweeper_skip_debug_check.exe"

    # p = subprocess.Popen([path], stdout=subprocess.PIPE, stdin=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
    # minesweeper_stdout = p.communicate(input=generated_key)[0]
    # print(f"{minesweeper_stdout = }")

    io = pwn.process(path)
    io.sendline(generated_key.encode("utf-8"))
    io.interactive()


machine_guid = get_machine_guid_registry_key()
print(f"{machine_guid           = }")

generated_key = get_random_license_key()
print(f"{''.join(generated_key) = }\n")

fix_last_4_bytes_of_random_key(generated_key, machine_guid)
license_key = ''.join(generated_key)
print(f"{license_key           = }")


## The GUI doesn't work for some reason if we launch Minesweeper like this. So we need to launch it manually.
# launch_process_with_key(license_key)

# Copy generated license key to clipboard.
pyperclip.copy(license_key)

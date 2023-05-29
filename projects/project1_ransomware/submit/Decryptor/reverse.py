import os
import string
import sys
import subprocess


def is_hex_str(s):
    return set(s).issubset(string.hexdigits)

def get_seed_from_file_path(file_path):
    file_name = os.path.basename(file_path)
    assert is_hex_str(file_name)

    input_bytes = file_name
    reversed_bytes = ''

    print(f'{input_bytes = }')

    for i in range(0, len(input_bytes), 2):
        curr = input_bytes[i:i+2]
        reversed_bytes = curr + reversed_bytes

    print(f'{reversed_bytes = }')

    scrambled_seed = int(reversed_bytes, 16)
    print(f'{scrambled_seed = }')

    seed = scrambled_seed**(1/4)
    print(f'{seed = }')

    seed = int(seed)
    print(f'{seed = }')

    return seed

def decrypt_file(file_path, seed):
    input_file = file_path
    args = ["./reverseFile.exe", input_file, str(seed)]
    p = subprocess.Popen(args,
                         stdin=subprocess.PIPE,
                         stdout=subprocess.PIPE,
                         stderr=subprocess.PIPE,
                         text=True)

    (stdoutData, stderrData) = p.communicate()
    print(f'{p.returncode = }\n')
    print(f'stdoutData:\n{stdoutData}')
    print(f'stderrData:\n{stderrData}')

    return p.returncode


if (len(sys.argv) < 2):
    print(f'Usage: "{sys.argv[0]}" file_to_decrypt [file_to_decrypt...]')
    exit(-1)

for i in range(1, len(sys.argv)):
    file_path = sys.argv[i]
    seed = get_seed_from_file_path(file_path)
    print()
    decrypt_file(file_path, seed)
    print('\n--------------------------------------------------------\n')


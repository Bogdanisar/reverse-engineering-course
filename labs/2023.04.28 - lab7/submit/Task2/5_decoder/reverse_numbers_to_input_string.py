import os
import sys


script_path = os.path.dirname(os.path.realpath(__file__))
os.chdir(script_path)


target_numbers = [0] * 23
for i in range(23):
    file_name = 'dumps/number_product_target{}.txt'.format(i)
    with open(file_name, "r") as fin:
        target_numbers[i] = int(fin.readline())

print(f"{target_numbers = }")


target_input = ""
for i in range(23):
    current_number = target_numbers[i]
    current_bytes = current_number.to_bytes(2, byteorder = 'big')
    target_input += current_bytes.decode("utf-8")

print(f"{target_input = }")

# import ida_bytes
import os

# This executes as Python2 in IDA


# Make the dumps directory
os.mkdir('../5_decoder/dumps')


# Dump the array of prime numbers
prime_array_address = 0x2214
prime_array_size = 3476 * 2
prime_array_bytes_str = ida_bytes.get_bytes(prime_array_address, prime_array_size)
prime_array = [0] * 3476
for p in range(3476):
    prime_array[p] = (ord(prime_array_bytes_str[2*p + 1]) << 8) + ord(prime_array_bytes_str[2*p])

with open('../5_decoder/dumps/prime_array.txt', 'w') as f:
    for prime in prime_array:
        f.write("{}\n".format(prime))


# Dump each of the arrays of prime powers for which the validate() function looks.
address_of_target0_prime_powers = 0x2A5D0
size_of_targetX_prime_powers = 3476 * 2
for i in range(23):
    # We subtract because the arrays are in reverse order in memory
    address_of_target_i_prime_powers = address_of_target0_prime_powers - i * size_of_targetX_prime_powers

    current_bytes_str = ida_bytes.get_bytes(address_of_target_i_prime_powers, size_of_targetX_prime_powers)
    current_powers = [0] * 3476

    for p in range(3476):
        current_powers[p] = (ord(current_bytes_str[2*p + 1]) << 8) + ord(current_bytes_str[2*p])

    file_name = '../5_decoder/dumps/target{}_prime_powers.txt'.format(i)
    with open(file_name, 'w') as f:
        for p in range(3476):
            f.write("{}: {}\n".format(prime_array[p], current_powers[p]))

    file_name = '../5_decoder/dumps/trimmed_target{}_prime_powers.txt'.format(i)
    current_target_product = 1
    with open(file_name, 'w') as f:
        for p in range(3476):
            if current_powers[p] != 0:
                f.write("{}: {}\n".format(prime_array[p], current_powers[p]))

                for k in range(current_powers[p]):
                    current_target_product *= prime_array[p]

    file_name = '../5_decoder/dumps/number_product_target{}.txt'.format(i)
    with open(file_name, 'w') as f:
        f.write("{}\n".format(current_target_product))

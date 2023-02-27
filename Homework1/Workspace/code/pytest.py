#!/usr/bin/python3

print(ord('í'))
print(ord('€'))

fout = 'crusucrypt_output.txt'

with open(fout, 'wb') as f:
    f.write('í')


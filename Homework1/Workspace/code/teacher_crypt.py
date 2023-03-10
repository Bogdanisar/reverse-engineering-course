
# This script crypts by applying Xor with the key per Unicode code point (!!), not per byte.


password = 'CsyxHTZQ'
print(password)

# fin = 'input/jsonSample_input0.json_'
fin = 'input/_data 8 bogdan.burcea.json'
fout = 'temp/crusu_crypt_output.json'
# fin,fout = fout,fin

with open(fin, 'rb') as f:
    temp = f.read()
    s = temp.decode('utf8')

string_length = len(s)
pass_length = len(password)

res = ''
for i in range(string_length):
    # print(f'{ord(s[i]) = }')

    newChar = chr(ord(s[i]) ^ ord(password[i % pass_length]))
    res += newChar

    # print(f'{ord(newChar) = }')

with open(fout, 'w') as f:
    f.write(res)

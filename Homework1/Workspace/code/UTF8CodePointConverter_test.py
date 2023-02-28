import UTF8CodePointConverter

# print(ord('í'))
# print(ord('€'))

# fout = 'crusucrypt_output.txt'

# with open(fout, 'wb') as f:
#     f.write('í')



input = 'input/_data 8 bogdan.burcea.json'
# input = 'input/jsonSample_input0.json'
temp = 'temp/json_codepoint_test.txt'
output = 'temp/json_codepoint_test_reverted.json'

UTF8CodePointConverter.ConvertUTF8ToCodePoints(input, temp)
UTF8CodePointConverter.ConvertCodePointsToUTF8(temp, output)


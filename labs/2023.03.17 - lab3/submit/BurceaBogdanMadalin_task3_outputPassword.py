lst = [20, 13, 8, 1, 20, 2]

password = ''
for index in lst:
    password += chr(ord('a') + index)

print(f"{password = }")


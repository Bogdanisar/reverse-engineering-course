import sys


def ConvertUTF8ToCodePoints(utf8InputFile, codePointListOutputFile):
    with open(utf8InputFile, 'rb') as fin:
        content = fin.read().decode('utf8')

    with open(codePointListOutputFile, 'w') as fout:
        for i in range(len(content)):
            currentCharacter = content[i]
            currentCodePoint = ord(currentCharacter)
            fout.write(f"{currentCodePoint}\n")


def ConvertCodePointsToUTF8(codePointListInputFile, utf8OutputFile):
    content = ""
    with open(codePointListInputFile, 'r') as fin:
        for line in fin.readlines():
            codePoint = int(line)
            content += chr(codePoint)

    with open(utf8OutputFile, 'w') as fout:
        fout.write(content)

if __name__ == '__main__':
    if len(sys.argv) != 4:
        print(f"""
            Usage:
                - {sys.argv[0]} utf8-cp utf8InputFile codePointListOutputFile
                - {sys.argv[0]} cp-utf8 codePointListInputFile utf8OutputFile
        """)
        exit(-1)

    if sys.argv[1] == 'utf8-cp':
        ConvertUTF8ToCodePoints(sys.argv[2], sys.argv[3])
    elif sys.argv[1] == 'cp-utf8':
        ConvertCodePointsToUTF8(sys.argv[2], sys.argv[3])

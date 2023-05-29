import time

file = 'writeToMe.txt'
while True:
    seconds = 3
    print(f"Sleeping for {seconds}")
    time.sleep(seconds)

    with open(file, "w") as fout:
        print(f"Writing to file: {file}\n")
        fout.write("Hello \n")


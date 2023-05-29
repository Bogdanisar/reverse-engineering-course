import inspect, os, shutil


def generate_assembly_for_codecave_according_to_custom_text():

    with open("input/task4_custom_text_matrix_input.txt", 'r') as fin:
        matrix = [line.strip() for line in fin.readlines()]

    num_lines = len(matrix)
    num_cols = len(matrix[0])

    assert num_lines == 16
    for i in range(num_lines):
        assert len(matrix[i]) == 30


    print("matrix:")
    for i in range(num_lines):
        print(matrix[i])
    print("")


    address_of_game_matrix = hex(0x14000D140)
    assembly = f"""
    .intel_syntax noprefix
    _main:

    mov     r10d, 1    # This is the instruction we replaced to call this codecave

    push r8
    push r9


    # Only proceed for the highest difficulty
    mov r8, 0x140008034  #  &selectedDifficulty
    mov r8d, dword ptr [r8]

    cmp r8d, 3   #  3 == "Large" difficulty
    jne end_label


    # Remove the generated bombs from all the cells

    mov r8, {address_of_game_matrix}
    mov r9, {40 * 40}  # number of cells for the entire allocated matrix

    clean_matrix_loop:
        mov dword ptr [r8], 0
        add r8, 4
        dec r9
        test r9, r9
        jnz clean_matrix_loop
    """
    assembly = inspect.cleandoc(assembly)
    assembly += "\n\n\n\n"

    assembly_for_bomb_cells = ""

    total_bombs = 0
    for line_idx in range(num_lines):
        for col_idx in range(num_cols):
            if matrix[line_idx][col_idx] == '*':
                total_bombs += 1

                sizeof_element = 4
                offset_for_current_cell = ((line_idx + 1) * 40 + (col_idx + 1)) * sizeof_element
                assembly_for_bomb_cells += f"""
                    mov r8, {address_of_game_matrix}
                    mov r9, {offset_for_current_cell}
                    add r9, r8
                    mov dword ptr [r9], 42  # bomb
                """

    # remove indentation
    assembly_for_bomb_cells = inspect.cleandoc(assembly_for_bomb_cells)

    assembly += assembly_for_bomb_cells
    assembly += f"""

    mov r8, 0x140008620  # numTotalBombs
    mov dword ptr [r8], {total_bombs}

    end_label:
    pop r9
    pop r8
    ret

    """

    with open("intermediary/task4_assembly_to_insert.s", "w") as fout:
        fout.write(assembly)


def generate_object_file_from_assembly():
    os.system("gcc -c -O0 intermediary/task4_assembly_to_insert.s -o intermediary/task4_assembly_to_insert_object.o")

def dump_instruction_bytes_from_object_file():
    os.system("objcopy intermediary/task4_assembly_to_insert_object.o intermediary/entire_dump.bin --dump-section .text=intermediary/task4_assembly_to_insert_dump.bin")

def dump_instruction_bytes_into_executable_codecave():
    input_file = "input/task4_Minesweeper_with_working_RE_text_used_as_input.exe"
    bytes_file = "intermediary/task4_assembly_to_insert_dump.bin"
    output_file = "output/Minesweeper_last_difficulty_with_custom_text.exe"

    # Duplicate the .exe file
    shutil.copyfile(input_file, output_file)

    # Read the bytes
    with open(bytes_file, "rb") as fin:
        codecave_bytes = fin.read()
    print(f"Before-pad: {len(codecave_bytes) = }")


    # This is the byte address in the file at which the codecave function starts.
    file_address_of_codecave = 26112


    # Pad the bytes to remove everything else after our bytes.
    output_file_size = os.path.getsize(output_file)
    remaining_file_bytes = output_file_size - file_address_of_codecave
    # codecave_bytes += b"\x00" * (remaining_file_bytes - len(codecave_bytes))
    codecave_bytes = codecave_bytes.ljust(remaining_file_bytes, b"\x00")
    print(f"After-pad:  {len(codecave_bytes) = }")


    # Patch the bytes in the output file
    with open(output_file, "r+b") as fout:
        fout.seek(file_address_of_codecave)
        fout.write(codecave_bytes)



generate_assembly_for_codecave_according_to_custom_text()

# These two are a replacement for what could be done manually through "defuse.ca/online-x86-assembler.htm"
generate_object_file_from_assembly()
dump_instruction_bytes_from_object_file()

dump_instruction_bytes_into_executable_codecave()


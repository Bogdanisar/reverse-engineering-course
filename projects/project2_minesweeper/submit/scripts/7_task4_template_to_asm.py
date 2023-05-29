import inspect


with open("6_task4_template_RE_matrix.txt", 'r') as fin:
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

assembly_for_bomb_cells = ""

total_bombs = 0
for line_idx in range(num_lines):
    for col_idx in range(num_cols):
        if matrix[line_idx][col_idx] == '*':
            total_bombs += 1

            sizeof_element = 4
            offset_for_current_cell = (line_idx * 40 + col_idx) * sizeof_element
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

with open("8_task4_assembly_to_insert.txt", "w") as fout:
    fout.write(assembly)

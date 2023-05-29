
# Run this inside IDA > Python to patch the bytes.


# When the code generates random bomb positions and does "gameMatrix[randLine][randCol] = bomb",
# we want to insert a mov instruction below the existing one such that the code also does
# hasFlagMatrix[randLine][randCol] = 1.
# We notice that there are some NOP instructions a bit lower in the code.
# We delete those NOP instructions and move some existing instructions downwards using this script.
# Result: We now have enough space to insert a new instruction for "hasFlagMatrix[randLine][randCol] = 1".
def move_instructions_downwards():
    address_of_first_instruction_to_move = 0x14000118B
    address_after_instructions_we_want_to_move = 0x1400011B4
    num_bytes_to_move = address_after_instructions_we_want_to_move - address_of_first_instruction_to_move

    # Get existing instructions
    instruction_bytes = [
        ida_bytes.get_original_byte(address_of_first_instruction_to_move + idx) for idx in range(num_bytes_to_move)
    ]

    print([hex(int(byte)) for byte in instruction_bytes])

    # Move existing instructions lower
    address_of_new_instructions = address_of_first_instruction_to_move + 12
    for idx in range(num_bytes_to_move):
        ida_bytes.patch_byte(address_of_new_instructions + idx, instruction_bytes[idx])

    # Some of these instructions use relative offsets so we need to subtract 12 from these offsets.
    for idx_patch_byte in [3, 8, 14, 29, 35]:
        idx = idx_patch_byte - 1
        ida_bytes.patch_byte(address_of_new_instructions + idx, int(instruction_bytes[idx]) - 12)

    # Fix a jmp instruction a bit above in the code
    ida_bytes.patch_byte(0x140001145, ida_bytes.get_original_byte(0x140001145) + 12)


def insert_new_mov_instruction():
    # rax == An offset into gameMatrix of the current bomb cell
    # &gameMatrix == 0x14000D140
    # &hasFlagMatrix == 0x140009F40
    # (0xA4) == (164) == (41 * sizeof(int)) == (offset needed to jump over the first line of the matrix)
    # new_target_instruction      -->  hasFlagMatrix[randLine][randCol] = 1;
    # new_target_instruction_asm  -->  mov     dword ptr [rax - 0x14000D140 + 0x140009F40 + 0xA4], 0x01
    # See: https://defuse.ca/online-x86-assembler.htm#disassembly

    bytes_for_new_target_instruction = b"\xC7\x80\xA4\xCE\xFF\xFF\x01\x00\x00\x00"
    bytes_for_new_target_instruction += b"\x90\x90" # Fill the rest with NOPs

    assert (len(bytes_for_new_target_instruction) == 12)

    address_of_first_instruction_to_move = 0x14000118B
    ida_bytes.patch_bytes(address_of_first_instruction_to_move, bytes_for_new_target_instruction)


move_instructions_downwards()
insert_new_mov_instruction()

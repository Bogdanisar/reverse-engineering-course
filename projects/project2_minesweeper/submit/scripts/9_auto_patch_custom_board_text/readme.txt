
An automatic patcher for the last task. You can use this to patch any custom text into the bomb board of the last difficulty.

How to use:
- Change the "input/task4_custom_text_matrix_input.txt" file to suit your liking. 
	Use only '*' and '#' characters. '*' means bomb, '#' means not-a-bomb. 
	The board must have a size of 16x30.
	There are some example input files inside the '/input' folder.
- Run 
	$> python3 "task4_auto_patch_custom_text.py"
- Launch "output/Minesweeper_last_difficulty_with_custom_text.exe" and play the last difficulty.
- ??
- Profit

Notes:
	- The file "input/task4_Minesweeper_with_working_RE_text_used_as_input.exe" is used as a basis for generating the output file. It already contains the patch for calling the codecave, so the script only replaces the code inside the codecave to draw the desired text.
	- "task4_auto_patch_custom_text.py" does the following:
		- What "7_task4_template_to_asm.py" does;
		- It simulates "defuse.ca/online-x86-assembler.htm" automatically;
		- It patches the binary automatically;

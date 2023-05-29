#!/usr/bin/python3

import subprocess
import itertools


def runProcess(args, stdinput, asText):
	p = subprocess.Popen(args, stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=asText)
	(stdoutData, stderrData) = p.communicate(stdinput)

	return (stdoutData, stderrData)


def printStdoutAndStderr(stdout, stderr):
	print(f'stdout:\n{stdout}\n\n')
	print(f'stderr:\n{stderr}')

def seeFirstOutput():
	(stdout, stderr) = runProcess(['ltrace', './crackme'], 'a', asText=True)
	printStdoutAndStderr(stdout, stderr)

def findPasswordLength():
	usualStderr = runProcess(['ltrace', './crackme'], 'a', asText=True)[1]
	usualStderrLineCount = len(usualStderr.splitlines())
	print(f'{usualStderrLineCount = }') # Prints 12

	maxlength = 10000 # From the fgets() call inside the first output

	password = ''
	for currentLength in range(1, maxlength + 1):
		password += 'a'
		(stdout, stderr) = runProcess(['ltrace', './crackme'], password, asText=True)
		if len(stderr.splitlines()) != usualStderrLineCount:
			print(f"Target password length = {currentLength}")   # Prints 71
			return

def seeOutputForCorrectPasswordLength():
	password = 'a' * 71
	(stdout, stderr) = runProcess(['ltrace', './crackme'], password, asText=True)
	printStdoutAndStderr(stdout, stderr)

def seeOutputForCorrectPasswordComponents():
	passwordComponents = [
		"zihldazjcn", # Added on first run
		"vlrgmhasbw", # Added on second run
		"jqvanafylz", # Added on third run
		"hhqtjylumf", # Added on 4th run
		"yemlopqosj", # Added on 5th run
		"mdcdyamgec", # Added on 6th run
		"nhnewfhetk", # Added on 7th run
	]
	password = "".join(passwordComponents)

	# right-pad the password to the correct length
	password = password + ('a' * (71 - len(password)))
	print(password)

	beforeLast = False
	if beforeLast:
		(stdout, stderr) = runProcess(['ltrace', './crackme'], password, asText=True)
		printStdoutAndStderr(stdout, stderr)
	else:
		(stdout, stderr) = runProcess(['ltrace', './crackme'], password.encode(), asText=False)
		print(len(stdout)) # 151

		prefix = stdout[:110]
		token = stdout[110:-1]
		print(f'{prefix = }')
		print(f'{token = }')

		token.decode() # fails

def tryPasswordComponentsPermutations():
	passwordComponents = [
		"zihldazjcn", # Added on first run
		"vlrgmhasbw", # Added on second run
		"jqvanafylz", # Added on third run
		"hhqtjylumf", # Added on 4th run
		"yemlopqosj", # Added on 5th run
		"mdcdyamgec", # Added on 6th run
		"nhnewfhetk", # Added on 7th run
	]

	idx = 0
	for componentsPermutation in itertools.permutations(passwordComponents):
		password = ''.join(componentsPermutation)

		# The 'crackme' binary was built with the expectation that there will be an extra '\n' character at the end (from standard input),
		password += '\n'

		if idx % 100 == 0:
			print(f'{idx = }; {password = };', flush=True)

		(stdout, _) = runProcess(['./crackme'], password.encode(), asText=False)
		# print(f'{idx = }; {password = }; {stdout = }', flush=True)

		try:
			# Bad passwords will (probabily) give us junk in the output.
			# We are looking for something human-readeable.
			decodeStdout = stdout.decode() # Does this call fail?

			# The decoding didn't fail => The output is human readable => Maybe this is what we are looking for.
			print(f'Found result: {idx = }; {password = }')
		except:
			pass

		idx += 1

	# Found result: idx = 4932; password = 'nhnewfhetkmdcdyamgeczihldazjcnhhqtjylumfvlrgmhasbwjqvanafylzyemlopqosj\n'

def solve():
	# Prints flag: timctf{7dfadd1ee67a9c516c9efbf8f0cf43f4}
	(stdout, stderr) = runProcess(['ltrace', './crackme'], 'nhnewfhetkmdcdyamgeczihldazjcnhhqtjylumfvlrgmhasbwjqvanafylzyemlopqosj\n', asText=True)
	printStdoutAndStderr(stdout, stderr)


# seeFirstOutput()
# findPasswordLength()
# seeOutputForCorrectPasswordLength()
# seeOutputForCorrectPasswordComponents()
# tryPasswordComponentsPermutations()
solve()


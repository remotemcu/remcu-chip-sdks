import sys
import subprocess

_file = "/dev/shm/temp.c"
#_file = "temp.c"
_out = "/dev/shm/temp.out"

#_CC = "gcc"
_CC = "clang"

#CPP_GPP = "g++"
CPP_GPP = "clang++"

def runtimeOutput(source, compilerOpt=[], debug=False, compiler = _CC):
	with open(_file, 'w') as f:
		f.write(source)
		f.flush()

	command  = [compiler, _file, "-o", _out, '-Wfatal-errors']
	command.extend(compilerOpt)
	str_command = " ".join(command)
	if debug:
		print(source)
		print(str_command)
	res = subprocess.call(command)
	if res != 0:
		return "", "no need parse"
	result = subprocess.run([_out], stderr=subprocess.DEVNULL, stdout=subprocess.PIPE)
	if result.returncode == 0:
		return result.stdout.decode("utf-8") , ""
	return "", "no time"


if __name__ == "__main__":
	if len(sys.argv) == 1:
		print("set name file")
		exit()
	source = ""
	with open(sys.argv[1], 'r') as f:
		source = f.read()
	compilerOpt = []
	if len(sys.argv) > 2:
		compilerOpt = [sys.argv[2]]
	debug = false
	if len(sys.argv) > 3:
		debug = bool(sys.argv[3])

	out, err = runtimeOutput(source,compilerOpt,debug)
	print(out, err)
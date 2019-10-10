#
import argparse
import os
import platform
import sys
import glob
import textwrap

from parserfile import ParseHeader, PyText

version = 0.1

parser = argparse.ArgumentParser(prog='header2py',
                                     description='Version %s. Generate python code from C headers' % (version))

parser.add_argument("-a", "--add-dir",
                        dest="dirs",
                        help="add dir with header",
                        action="append",
                        default=[])

parser.add_argument("-f", "--add-header-file",
                        dest="files",
                        help="add header files",
                        action="append",
                        default=[])

parser.add_argument("-s", "--add-sets-of-files",
                        dest="sets_of_files",
                        help="add header files bundles",
                        action="append",
                        default=[])

parser.add_argument("-c", "--compile-options",
                        dest="compile_options",
                        help="add header files",
                        default="" )

parser.add_argument("-o", "--output-file",
                        dest="output",
                        default="output.py")

parser.add_argument("-d", "--debug-level",
                        dest="debug_level",
                        default=0)
files = []

options = parser.parse_args()
files.extend(options.files)

for set_of_files in options.sets_of_files:
	set_of_files = set_of_files.split(" ")
	files.extend(set_of_files)

compile_options = options.compile_options

for d in options.dirs:
	f_list = glob.glob(d + "*.h")
	files.extend(f_list)
	compile_options += " -I" + d

#print(files)
pytext = PyText()

compile_options = compile_options.split(" ")

debug = int(options.debug_level) > 0

pytext.text = "import ctypes\n\n"

for f in files:
	pytext.addComment("file %s : \n" % f)
	parser = ParseHeader(f, compile_options, debug)
	pt = parser.parse()
	pytext.add(pt)
	pytext.addComment(20*"--" + "\n")

source_text = pytext.text

source_text += "\n__all__ = "

text = "[%s]" % ", ".join([repr(str(n)) for n in pytext.all])
wrapper = textwrap.TextWrapper(break_long_words=False, width=88, initial_indent=" ",
                                       subsequent_indent="    ")
for line in wrapper.wrap(text):
	source_text += line + "\n"

if debug:
      print(source_text)

output_file = options.output

with open(output_file, 'w+') as f:
      f.write(source_text)
      f.flush()

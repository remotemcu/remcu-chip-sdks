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

parser.add_argument("-i", "--include-string",
                        dest="include_string",
                        help="add string in begin test code",
                        default="" )

parser.add_argument("-o", "--output-file",
                        dest="output",
                        default="output.py")

parser.add_argument("-d", "--debug-level",
                        dest="debug_level",
                        default=0)

parser.add_argument("--version",
                        dest="version",
                        default="undef_version")

files = []

options = parser.parse_args()
#files.extend(options.files)
files.extend(map(lambda x: os.path.abspath(x), options.files))

for set_of_files in options.sets_of_files:
	set_of_files = set_of_files.split(" ")
	files.extend(set_of_files)

compile_options = options.compile_options

for d in options.dirs:
	f_list = glob.glob(d + "/*.h")
	f_list = map(lambda x: os.path.abspath(x), f_list)
	files.extend(f_list)
	compile_options += " -I" + d

#print(files)
pytext = PyText()

compile_options = compile_options.split(" ")

include_string = options.include_string

debug = int(options.debug_level) > 0

version = '"%s"' % options.version

print(files)

pytext.text = """# -*- coding: utf-8 -*-
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES,
# INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE  FOR ANY DIRECT, INDIRECT, INCIDENTAL,
# SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
# WHETHER IN CONTRACT, STRICT LIABILITY,OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# To improve the quality of the software, users are encouraged to share modifications, enhancements or bug fixes with
# remotemcu.com (remcu@remotemcu.com)
#
# It is python header file for using REMCU library
#
#
# word size : 32 bit
#
#


import ctypes

\n\n"""

pytext.addValue('__version__' , version)
pytext.addValue('__RUN' , 0)
pytext.addValue('__HALT'  , 1)
pytext.addValue('__ERROR' , 0)
pytext.addValue('__WARNING' , 1)
pytext.addValue('__INFO' , 2)
pytext.addValue('__DEBUG' , 3)
pytext.addValue('__ALL_LOG' , 4)
pytext.addValue('DEFAULT_OPENOCD_PORT' , 6666)
pytext.addValue('DEFAULT_GDB_PORT' , 3333)



for f in files:
	base_name = os.path.basename(f)
	pytext.addComment("file %s : \n" % base_name)
	parser = ParseHeader(f, compile_options, include_string, debug)
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

import re
import argparse

parser = argparse.ArgumentParser(prog='header2py',
                                     description='Generate canonical headers from ST headers')

parser.add_argument("-o", "--output-inc",
                        dest="output")

parser.add_argument("-s", "--output-src",
                        dest="source")

parser.add_argument("-i", "--input-inc",
                        dest="input_inc")

options = parser.parse_args()

with open(options.input_inc, 'r') as include_file:
	original_inc = include_file.read() #read all of file


#first stage. replace include functions:
STATIC_TOKEN_GROUP = "(__STATIC_INLINE )"
SIGNATURE_FUNCTION_GROUP = "(.*?)"
BODY_FUNCTION_GROUP = "({.*?})"

static_pattern = re.compile(STATIC_TOKEN_GROUP + SIGNATURE_FUNCTION_GROUP + BODY_FUNCTION_GROUP, re.S)

STATIC_TOKEN = r"\1"
SIGNATURE_FUN = r"\2"
BODY_FUN = r"\3"

REMCU_START = "#ifdef REMCU_LIB\n"
_ELSE = "\n#else\n"
_END = "\n#endif"


#generate extra source file for static function of body:
extra_src = '#include "%s"\n' % options.output

static_funs = re.findall(static_pattern,original_inc)
for fun in static_funs:
	extra_src += "\n" + fun[1] + fun[2] + "\n" #sing + body

replace_template = REMCU_START + SIGNATURE_FUN + ";" + _ELSE + STATIC_TOKEN + SIGNATURE_FUN + BODY_FUN + _END

stage_1 = re.sub(static_pattern, replace_template, original_inc)

#Save files

with open(options.source, 'w') as file:
	file.write(extra_src)


with open(options.output, 'w') as file:
	file.write(stage_1)


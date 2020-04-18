import re
import argparse

parser = argparse.ArgumentParser(prog='header2py',
                                     description='Generate canonical headers from ST headers')

parser.add_argument("-o", "--output",
                        dest="output")

parser.add_argument("-f", "--file",
                        dest="file")

options = parser.parse_args()

with open(options.file, 'r') as include_file:
	original_src = include_file.read() #read all of file


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
_END = "\n#end"

replace_template = REMCU_START + SIGNATURE_FUN + _ELSE + STATIC_TOKEN + SIGNATURE_FUN + BODY_FUN + _END

stage_1 = re.sub(static_pattern, replace_template, original_src)

print stage_1

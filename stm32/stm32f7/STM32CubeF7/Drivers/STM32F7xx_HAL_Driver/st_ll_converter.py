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

parser.add_argument("-d", "--debug-level",
                        dest="debug_level",
                        default=0)

options = parser.parse_args()

debug = int(options.debug_level) > 0

with open(options.input_inc, 'r') as include_file:
	original_inc = include_file.read() #read all of file


#first stage. replace include functions:
STATIC_INLINE_TOKEN = "__STATIC_INLINE"
STATIC_TOKEN_GROUP = "(%s )" % STATIC_INLINE_TOKEN
SIGNATURE_FUNCTION_GROUP = "(.*?)"
#BODY_FUNCTION_GROUP = "({.*?})"
OPEN_TOKEN = "{"
CLOSE_TOKEN = "}"
OPEN_TOKEN_GROUP = "(%s)" % OPEN_TOKEN

static_pattern = re.compile(STATIC_TOKEN_GROUP + SIGNATURE_FUNCTION_GROUP + OPEN_TOKEN_GROUP, re.S)
"""
STATIC_TOKEN = r"\1"
SIGNATURE_FUN = r"\2"
BODY_FUN = r"\3"
"""
REMCU_START = "#ifdef REMCU_LIB\n"
_ELSE = "\n#else\n"
_END = "\n#endif"


#generate extra source file for static function of body:
#extra_src = '#include "%s"\n' % options.output

split_inc = re.split(static_pattern,original_inc)
split_inc.reverse()
#import pdb; pdb.set_trace()
tr_stage_1 = ""
extra_src = ""

while split_inc[-1].find(STATIC_INLINE_TOKEN) != 0:
	tr_stage_1 += split_inc.pop() #add first comment
	extra_src += tr_stage_1
	if split_inc == []:
		break

if split_inc != []:
	def convert2_common_fun(static_token, signature_fun, body_fun):
		global tr_stage_1
		global extra_src
		replace_template = REMCU_START + signature_fun + ";" + _ELSE + static_token + signature_fun + body_fun + _END
		tr_stage_1 += replace_template
		extra_src += signature_fun + body_fun #"\n" + signature_fun + "\n" + body_fun + "\n"

	def parse_body(probably_body_fun):
		body = ""
		stack_token = []
		#import pdb; pdb.set_trace()
		for s in probably_body_fun:
			body += s
			if s == CLOSE_TOKEN:
				stack_token.pop()
			if s == OPEN_TOKEN:
				stack_token.append(OPEN_TOKEN)
			if stack_token == [] and s == CLOSE_TOKEN:
				break

		rest_split = probably_body_fun.split(body)[1] #rest part of split text

		return body, rest_split

	#import pdb; pdb.set_trace()

	while split_inc != []:
		static_token = split_inc.pop()
		signature_fun = split_inc.pop()
		open_token = split_inc.pop()
		probably_body_fun = open_token + split_inc.pop()

		body_fun, rest_inc_part = parse_body(probably_body_fun)	

		convert2_common_fun(static_token, signature_fun, body_fun)
		tr_stage_1 += rest_inc_part #add comment coming after function
		extra_src += rest_inc_part

"""
print tr_stage_1

print "---------"

print extra_src
"""

with open(options.source, 'w') as file:
	file.write(extra_src)


with open(options.output, 'w') as file:
	file.write(tr_stage_1)


import sys
from pycompiler import runtimeOutput, CPP_GPP

ctypes_set = {"c": "ctypes.c_char",
			"a" : "ctypes.c_int8",
			"h" : "ctypes.c_uint8",
			"s" : "ctypes.c_int16",
			"t" : "ctypes.c_uint16",
			"i" : "ctypes.c_int32",
			"j" : "ctypes.c_uint32",
			"l" : "ctypes.c_int64",
			"m" : "ctypes.c_uint64",}

__c_void_p = "ctypes.c_void_p"
__unknown = "unknown"


def get_size_and_type(string_id):
	_p = string_id.index("_")
	_num_str = string_id[1:_p]
	try:
		size = int(_num_str)
	except Exception as e:
		raise Exception("size array error in result : " + string_id)

	_t_str = string_id[_p+1 : ]

	ctype_id = ctypes_set.get(_t_str, __unknown)
	if ctype_id == __unknown:
		raise Exception("strangly type of array : " + string_id + " / " + ctype_id)

	return  size, ctype_id


def parse_type_of_field(options, name_class, name_field):
	#ctext = '#include "%s" \n' % (options.filename)
	#ctext += '#include "stdio.h"\n'
	ctext  = options.prepareSourceCode()

	ctext += '#include <typeinfo>\n'
	ctext += 'int main(){ printf("%%s", typeid(((%s *)0)->%s).name()); return 0; }' % (name_class, name_field)
	rt_type_id, error = runtimeOutput(ctext, options.compile_options, options.debug, compiler=CPP_GPP)
	if error != "":
		raise Exception("rto error of the field / " + error)

	if len(rt_type_id) == 1:
		ctype_id = ctypes_set.get(rt_type_id, __unknown)
		if ctype_id == __unknown:
			return "", "unknown field"
		result = ctype_id
	elif rt_type_id[0] == 'P':
		result = __c_void_p
	elif rt_type_id[0] == 'A':
		size, ctype_id = get_size_and_type(rt_type_id)
		arr_type = "%s * %d" % (ctype_id, size)
		result = arr_type
	else:
		if options.debug:
			print("rt_type_id : " + rt_type_id)
		raise Exception("strangly type of field")

	return result



if __name__ == "__main__":
	def options(): pass
	if len(sys.argv) == 1:
		print("set name file")
		exit()
	options.filename = sys.argv[1]
	options.compile_options = ['-w', '-I.']
	options.debug = True
	name_class = sys.argv[2]
	name_field = sys.argv[3]
	print(parse_type_of_field(options, name_class, name_field))
 
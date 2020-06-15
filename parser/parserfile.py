import CppHeaderParser
import sys
from pycompiler import runtimeOutput
from parse_type import parse_type_of_field

_offset = "	"

class PyText(object):
	def __init__(self):
		self.text = ""
		self.all = []

	def addValue(self, var, value):
		#chec value on int
		self.text += var + " = "+  str(value) + "\n"
		self.all.append(var)

	def addComment(self, comment):
		self.text += "# " + comment +"\n"

	def add(self, other):
		self.text += other.text
		self.all.extend(other.all)

	def addNameStruct(self, name):
		self.all.append(name)
		self.text += "\nclass " + name + "(ctypes.Structure):\n"
		self.text += _offset + "_pack_ = False\n"
		self.text += _offset + "_fields_ = [\n"

	def addFieldStruct(self, name, c_type):
		self.text += _offset*2 + "('" + name + "',	" + c_type + "),\n"

	def releaseStruct(self):
		self.text += _offset + "]\n"
		self.text += _offset + "def ref(self):\n"
		self.text += _offset*2 + "return ctypes.byref(self)\n\n"

	def toStr(self):
		return self.text



class ParseHeader(object):
	def __init__(self, filename, compile_options=[], include_string="", debug=False):
		self.filename = filename
		self.compile_options = compile_options
		self.pytext = PyText()
		self.debug = debug
		self.include_string = include_string
	
	def pEnums(self,enums):
		if len(enums) == 0:
			return PyText
		for e in enums:
			name = e['name']
			self.pytext.addComment("Enum " + name)
			values = e['values']
			if len(values) == 0:
				continue
			for v in values:
				enum_name = v['name']
				#value = self.runtimeValue(enum_name)
				self.pushValue(enum_name)

	def pDefines(self, defines):
		if len(defines) == 0:
			return
		for d in defines:
			d = d.strip() #trim define/ del tabs and whsp
			first_space = d.find(" ")
			if first_space < 0:
				self.pytext.addComment("empty define %s" % d)
				continue
			name = d[:first_space]
			name = name.strip() #trim define/ del tabs and whsp
			if name.find("(") >= 0:
				#first_row = d.split('\n')[0]
				d = d.replace('\n', '\n#')
				self.pytext.addComment("fun define %s" % d)
				continue
			self.pushValue(name)

	def pVariable(self, variables):
		if len(variables) == 0:
			return PyText
		for v in variables:
			name_var = v['name']
			if len(name_var) == 0:
				continue
			self.pushValue(name_var)

	def parse(self):
		header = CppHeaderParser.CppHeader(self.filename)
		self.pEnums(header.enums)
		self.pDefines(header.defines)
		self.pVariable(header.variables)
		self.pStruct(header.classes)
		#print(self.pytext.text)
		return self.pytext

	def pushValue(self, name):
		result, error = self.runtimeValue(name)
		if error == "" and result != "":
			self.pytext.addValue(name,result)
			return
		self.pytext.addComment("Skip " + name + " : " + error)

	def prepareSourceCode(self):
		ctext = self.include_string + "\n"
		ctext += '#include "%s" \n' % (self.filename)
		ctext += '#include "stdio.h"\n'
		return ctext

	def runtimeValue(self, value):
		ctext = self.prepareSourceCode()
		ctext += 'int main(){ printf("0x%%LX", %s); return 0; }' % value
		result, error = runtimeOutput(ctext, self.compile_options, self.debug)
		return result, error

	def sizeOfField(self, name_class, name_field):
		ctext = self.prepareSourceCode()
		ctext += 'int main(){ printf("%%d", sizeof(((%s *)0)->%s)); return 0; }' % (name_class, name_field)
		result, error = runtimeOutput(ctext, self.compile_options, self.debug)
		return result, error

	def checkStruct(self, class_, name_class):
		if class_['abstract']:
			return 'abstract'
		if class_['declaration_method'] != 'struct':
			return "declaration_method is not struct"
		if class_['inherits'] != []:
			return "inherits"
		if class_['parent'] != None:
			return "parent"
		prop = class_['properties']
		if prop['private'] != [] or prop['protected'] != []:
			return "private or protected"
		public_fields = prop['public']
		if len(public_fields) == 0:
			return "no public"
		for field in public_fields:
			name_field = field['name']

			if field['class'] != 0:
				return "field is class : " + name_field
			#if field['array'] != 0:
				#return "field is array"
			#if field['pointer'] != 0:
				#return "field is pointer"
			
			result, error = self.sizeOfField(name_class, name_field)
			if error != "":
				if self.debug:
					print("runtime time error: " + error + " , name: " + name_field)
				continue
			size = int(result)
			if size == 0:
				return "error size of %s is %s " %(name_field, result)
		return ""

	def pStruct(self, classes):
		if len(classes) == 0:
			return
		for name_class in classes:
			class_ = classes[name_class]
			self.pytext.addComment("struct " + name_class)
			err = self.checkStruct(class_, name_class)
			if err != "":
				self.pytext.addComment("struct " + name_class + " : " + err)
				continue
			prop = class_['properties']
			public_fields = prop['public']
			self.pytext.addNameStruct(name_class)
			for field in public_fields:
				name_field = field['name']
				result, error = self.sizeOfField(name_class, name_field)
				if error != "":
					continue

				try:
					ctype = parse_type_of_field(self, name_class, name_field)
				except Exception as e:
					if self.debug:
						print(e)
					size = int(result)
					ctypes = {1 : "ctypes.c_uint8",
						2: "ctypes.c_uint16",
						4: "ctypes.c_uint32",
						8: "ctypes.c_uint64",}
					universal_size = "ctypes.c_uint8 * " + result
					ctype = ctypes.get(size, universal_size)					
		
				self.pytext.addFieldStruct(name_field, ctype)
			self.pytext.releaseStruct()

			



if __name__ == "__main__":
	if len(sys.argv) == 1:
		#print("set name file")
		sys.exit("set name file")

	compile_options = []
	if len(sys.argv) >= 2:
		options = sys.argv[2]
		compile_options = options.split(" ")
		#print(compile_options)

	parser = ParseHeader(sys.argv[1], compile_options)
	#parser = ParseHeader("dff")
	pytext = parser.parse()
	print(pytext.text)

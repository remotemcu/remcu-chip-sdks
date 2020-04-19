mkdir -p transformed_Inc
mkdir -p fun_implementation

rm transformed_Inc/*
rm fun_implementation/*.c

for F in Inc/*ll*.h; do
	BASENAME_F="$(basename -- $F)"
	echo ST_LL_converter.py -i $F -o transformed_Inc/$BASENAME_F -s fun_implementation/$BASENAME_F.c
	python ST_LL_converter.py -i $F -o transformed_Inc/$BASENAME_F -s fun_implementation/$BASENAME_F.c;
done
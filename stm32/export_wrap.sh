sed -i '1s/^/#include "remcu_exports_symbol_enter.h"\n/' $1/*.c

for f in $1/*.c; do
	printf '\n#include "remcu_exports_symbol_exit.h"' >> $f;
done
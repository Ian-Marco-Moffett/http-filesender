CFILES = $(wildcard src/*.c)
CFLAGS = -Werror=implicit \
				 -Werror=implicit-function-declaration \
				 -Werror=implicit-int \
				 -Werror=int-conversion \
				 -Werror=incompatible-pointer-types \
				 -Werror=int-to-pointer-cast \
				 -Iinclude \
				 -fsanitize=address


bin/fsend: $(CFILES)
	@ mkdir -p bin/
	gcc $(CFLAGS) $^ -o $@

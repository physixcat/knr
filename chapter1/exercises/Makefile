CFLAGS = -Werror -Wall -Wextra -Wpedantic -Wformat=2 -Wformat-overflow=2 \
-Wformat-truncation=2 -Wformat-security -Wnull-dereference -Wstack-protector \
-Wtrampolines -Walloca -Wvla -Warray-bounds=2 -Wimplicit-fallthrough=3 \
-Wtraditional-conversion -Wshift-overflow=2 -Wcast-qual -Wstringop-overflow=4 \
-Wconversion -Warith-conversion -Wlogical-op -Wduplicated-cond \
-Wduplicated-branches -Wformat-signedness -Wshadow -Wstrict-overflow=4 \
-Wundef -Wstrict-prototypes -Wswitch-default -Wswitch-enum \
-Wstack-usage=1000000 -Wcast-align=strict -D_FORTIFY_SOURCE=3 \
-fstack-protector-strong -fstack-clash-protection -fPIE -fsanitize=bounds \
-fsanitize-undefined-trap-on-error -Wl,-z,relro -Wl,-z,now -Wl,-z,noexecstack \
-Wl,-z,separate-code -Wstrict-aliasing=2 -Wwrite-strings -flto=auto \
-march=native -pipe -std=c89 -O2
CC = gcc
VPATH = src

bin_detab_modulo_custom : detab_modulo_custom.c
	$(CC) $(CFLAGS) $? -o $@

clean :
	rm bin_detab_modulo_custom

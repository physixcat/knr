CC = gcc
CFLAGS = -Werror -Wall -Wextra -Wpedantic -Wformat=2 -Wformat-overflow=2 \
-Wformat-truncation=2 -Wnull-dereference -Wstack-protector \
-Wtrampolines -Walloca -Wvla -Warray-bounds=2 -Wimplicit-fallthrough=3 \
-Wtraditional-conversion -Wshift-overflow=2 -Wcast-qual -Wstringop-overflow=4 \
-Wconversion -Warith-conversion -Wlogical-op -Wduplicated-cond \
-Wduplicated-branches -Wformat-signedness -Wshadow -Wstrict-overflow=2 -Wundef \
-Wstrict-prototypes -Wswitch-default -Wswitch-enum -Wstack-usage=1000000 \
-Wcast-align=strict -fsanitize=bounds -fsanitize-trap=all \
-Wstrict-aliasing=2 -Wwrite-strings -pipe -std=c89 -O0 -g
# OBJS =
# BIN =
VPATH = src

bin_wrap_line : wrap_line.c
	$(CC) $(CFLAGS) $? -o $@

clean :
	rm bin_wrap_line

# all : $(BIN)

# main:$(OBJS)
# 	$(CC) $(CFLAGS) $(OBJS) -o main

# %.o: %.c
# 	$(CC) $(CFLAGS) -c $< -o $@

# clean:
# 	$(RM) -r main *.o

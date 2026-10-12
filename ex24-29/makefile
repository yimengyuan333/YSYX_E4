# Makefile for ex24-29
CC = clang
CFLAGS = -Wall -g
LDLIBS = -ldl          # ex29 需要 libdl

# 找出所有练习源文件（ex 开头，排除 lib 开头的库文件）
SRCS = $(filter-out lib%.c, $(wildcard ex*.c))
TARGETS = $(SRCS:.c=)

# 默认目标：编译所有练习 + 共享库
all: $(TARGETS) libex29.so

# 通用规则：每个 ex*.c 生成同名可执行文件
%: %.c
	$(CC) $(CFLAGS) -o $@ $<

# ex29 需要额外链接 -ldl（覆盖通用规则）
ex29: ex29.c
	$(CC) $(CFLAGS) -o $@ $< $(LDLIBS)

# 构建动态库 libex29.so
libex29.so: libex29.c
	$(CC) $(CFLAGS) -fPIC -shared -o $@ $<

# 清理生成的文件
clean:
	rm -f $(TARGETS) libex29.so *.o

.PHONY: all clean
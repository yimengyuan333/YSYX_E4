CC = clang
CFLAGS = -Wall -g -lm

SRCS = $(wildcard *.c)

TARGETS = $(SRCS:.c=)

# 默认目标：编译所有
all: $(TARGETS)

# 通用编译规则：每个 .c 生成同名可执行文件
%: %.c
	$(CC) $(CFLAGS) -v -o $@ $<


clean:
	rm -f $(TARGETS) *.o *.out

.PHONY: all clean
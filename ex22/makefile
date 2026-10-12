CC = clang
CFLAGS = -Wall -g

# 默认目标：生成 ex22 可执行文件
all: ex22

# ex22 由两个源文件共同编译链接
ex22: ex22.c ex22_main.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f ex22 *.o *.out

.PHONY: all clean
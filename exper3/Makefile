CC = gcc
CFLAGS = -Wall -g
SRCS_COMMON = src/queue.c
HEADERS = src/pcb.h src/queue.h

# FCFS 调度算法
TARGET_FCFS = fcfs
SRCS_FCFS = FCFS.c $(SRCS_COMMON)
OBJS_FCFS = $(SRCS_FCFS:.c=.o)

# PR 调度算法
TARGET_PR = pr
SRCS_PR = PR.c $(SRCS_COMMON)
OBJS_PR = $(SRCS_PR:.c=.o)

# HRRN 调度算法
TARGET_HRRN = hrrn
SRCS_HRRN = HRRN.c $(SRCS_COMMON)
OBJS_HRRN = $(SRCS_HRRN:.c=.o)

# SPF 调度算法
TARGET_SPF = spf
SRCS_SPF = SPF.c $(SRCS_COMMON)
OBJS_SPF = $(SRCS_SPF:.c=.o)

# 默认目标，编译所有
all: $(TARGET_FCFS) $(TARGET_PR) $(TARGET_HRRN) $(TARGET_SPF)

# 编译 FCFS
$(TARGET_FCFS): $(OBJS_FCFS)
	$(CC) $(CFLAGS) -o $@ $^

# 编译 PR
$(TARGET_PR): $(OBJS_PR)
	$(CC) $(CFLAGS) -o $@ $^

# 编译 HRRN
$(TARGET_HRRN): $(OBJS_HRRN)
	$(CC) $(CFLAGS) -o $@ $^

# 编译 SPF
$(TARGET_SPF): $(OBJS_SPF)
	$(CC) $(CFLAGS) -o $@ $^

# 通用规则，编译 .c 文件为 .o 文件
%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

# 清理生成的文件
clean:
	rm -f $(OBJS_FCFS) $(OBJS_PR) $(OBJS_HRRN) $(OBJS_SPF) $(TARGET_FCFS) $(TARGET_PR) $(TARGET_HRRN) $(TARGET_SPF)

.PHONY: all clean
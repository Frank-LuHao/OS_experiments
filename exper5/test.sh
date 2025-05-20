#!/bin/bash
# filepath: /home/administrator/OS_Learning/exper5/test.sh

# 定义测试文件目录和结果文件
TEST_DIR="./test"
RESULT_FILE="result.txt"

# 清空结果文件
> $RESULT_FILE

# 编译程序
make

# 检查编译是否成功
if [ ! -f "./a.out" ]; then
    echo "编译失败，无法找到可执行文件 a.out" >> $RESULT_FILE
    exit 1
fi

# 遍历测试文件并运行测试
for TEST_FILE in "$TEST_DIR"/*.txt; do
    echo "运行测试文件: $TEST_FILE" >> $RESULT_FILE
    ./a.out < "$TEST_FILE" >> $RESULT_FILE
    echo "----------------------------------------" >> $RESULT_FILE
done

echo "所有测试完成，结果已保存到 $RESULT_FILE"

# 清理编译生成的文件
make clean
#!/bin/bash

# 定义测试目录和输出目录
TEST_DIR="./test"
OUTPUT_DIR="./output"
EXECUTABLES=("fcfs" "pr" "hrrn" "spf")

# 创建输出目录
mkdir -p $OUTPUT_DIR

# 测试函数
run_test() {
    local executable=$1
    local test_file=$2
    local output_file=$3

    echo "Running $executable with $test_file..."
    ./$executable < $test_file > $output_file
    echo "Output saved to $output_file"
}

# 遍历每个可执行文件
for exe in "${EXECUTABLES[@]}"; do
    # 检查可执行文件是否存在
    if [ ! -f "./$exe" ]; then
        echo "Error: Executable $exe not found. Please compile the project first."
        exit 1
    fi

    # 查找对应的测试文件
    for test_file in $TEST_DIR/${exe}*.txt; do
        # 提取测试文件名
        test_name=$(basename $test_file .txt)
        # 定义输出文件名
        output_file="$OUTPUT_DIR/${test_name}_output.txt"
        # 运行测试
        run_test $exe $test_file $output_file
    done
done

echo "All tests completed. Check the $OUTPUT_DIR directory for results."
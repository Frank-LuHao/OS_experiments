import matplotlib.pyplot as plt
import numpy as np

def parse_results(filename):
    algorithms = []
    frame_sizes = []
    hit_rates = []
    
    current_algo = None
    with open(filename, 'r', encoding='utf-8') as f:
        for line in f:
            line = line.strip()
            if line.startswith('-----算法：'):
                current_algo = line.split('：')[1].split('-----')[0].strip()
            elif 'page frames' in line and current_algo:
                parts = line.split(',')
                frame_size = int(parts[0].split()[0])
                rate = float(parts[1].split()[1].replace('%', ''))
                
                algorithms.append(current_algo)
                frame_sizes.append(frame_size)
                hit_rates.append(rate/100)  # 转换为0-1的小数
    
    # 转换为按算法分类的字典
    results = {}
    for algo in ['FIFO', 'LRU', 'OPT']:
        results[algo] = {'frames': [], 'rates': []}
    
    for i in range(len(algorithms)):
        algo = algorithms[i]
        if algo in results:  # 确保只处理已知算法
            results[algo]['frames'].append(frame_sizes[i])
            results[algo]['rates'].append(hit_rates[i])
    
    # 确保每个算法的数据按frame_size排序
    for algo in results:
        if results[algo]['frames']:  # 只处理有数据的算法
            sorted_data = sorted(zip(results[algo]['frames'], results[algo]['rates']))
            results[algo]['frames'], results[algo]['rates'] = zip(*sorted_data)
    
    return results

def plot_results(results):
    plt.figure(figsize=(12, 7))
    
    colors = {'FIFO': 'blue', 'LRU': 'green', 'OPT': 'red'}
    markers = {'FIFO': 'o', 'LRU': 's', 'OPT': '^'}
    linestyles = {'FIFO': '--', 'LRU': '-.', 'OPT': '-'}
    
    for algo in ['FIFO', 'LRU', 'OPT']:  # 按固定顺序绘制
        if algo in results and results[algo]['frames']:
            x = results[algo]['frames']
            y = results[algo]['rates']
            plt.plot(x, y, 
                     label=algo, 
                     color=colors[algo],
                     marker=markers[algo],
                     linestyle=linestyles[algo],
                     linewidth=2,
                     markersize=8,
                     markeredgecolor='black',
                     markeredgewidth=0.5)
    
    plt.xlabel('memory page', fontsize=14)
    plt.ylabel('hit rate', fontsize=14)
    plt.xticks(np.arange(4, 33, 2))
    plt.yticks(np.arange(0, 1.01, 0.1))
    plt.grid(True, linestyle='--', alpha=0.7)
    plt.legend(fontsize=12, loc='lower right')
    
    # 设置y轴为百分比格式
    ax = plt.gca()
    ax.yaxis.set_major_formatter(plt.FuncFormatter(lambda y, _: f'{y:.0%}'))
    
    # 添加横向参考线
    for y in np.arange(0, 1.1, 0.1):
        plt.axhline(y=y, color='gray', linestyle=':', alpha=0.3)
    
    plt.tight_layout()
    plt.savefig('vis.png', dpi=300, bbox_inches='tight')
    plt.show()

if __name__ == '__main__':
    # 解析结果文件
    results = parse_results('res.txt')
    
    # 打印解析结果检查
    print("解析结果检查:")
    for algo in results:
        print(f"{algo}:")
        print(f"  页数: {results[algo]['frames']}")
        print(f"  命中率: {results[algo]['rates']}")
    
    # 绘制图表
    plot_results(results)
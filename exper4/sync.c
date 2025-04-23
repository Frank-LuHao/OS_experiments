#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <string.h>

#define MAX 256

// 全局变量
char *buffer;
sem_t empty;    // 表示缓冲区空位信号量
sem_t full;     // 表示缓冲区产品信号量
sem_t mutex;    // 互斥信号量，保护缓冲区访问

// 生产者函数
void *producer(void *arg) {
    while (1) {
        // 等待缓冲区有空位
        sem_wait(&empty);
        // 获取互斥锁
        sem_wait(&mutex);
        
        // 生产产品并放入缓冲区
        printf("Producer: Please input product (or 'quit' to exit): ");
        fgets(buffer, MAX, stdin);
        
        // 检查用户是否想退出
        if (strncmp(buffer, "quit", 4) == 0) {
            sem_post(&mutex);
            sem_post(&full);
            break;
        }
        
        printf("Producer: Produced product: %s", buffer);
        
        // 释放互斥锁
        sem_post(&mutex);
        // 通知消费者有产品可用
        sem_post(&full);
    }
    pthread_exit(NULL);
}

// 消费者函数
void *consumer(void *arg) {
    while (1) {
        // 等待缓冲区有产品
        sem_wait(&full);
        // 获取互斥锁
        sem_wait(&mutex);
        
        // 检查是否收到退出信号
        if (strncmp(buffer, "quit", 4) == 0) {
            sem_post(&mutex);
            sem_post(&empty);
            break;
        }
        
        // 消费产品
        printf("Consumer: Consumed product: %s", buffer);
        memset(buffer, 0, MAX);  // 清空缓冲区
        
        // 释放互斥锁
        sem_post(&mutex);
        // 通知生产者有空位可用
        sem_post(&empty);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t id_producer, id_consumer;
    int ret;
    
    // 分配缓冲区内存
    buffer = (char *)malloc(MAX);
    if (buffer == NULL) {
        perror("Failed to allocate buffer");
        exit(EXIT_FAILURE);
    }
    
    // 初始化信号量
    // 缓冲区初始为空，empty初始为1，full初始为0
    // mutex初始为1表示互斥锁可用
    sem_init(&empty, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);
    
    // 创建生产者线程
    ret = pthread_create(&id_producer, NULL, producer, NULL);
    if (ret != 0) {
        perror("Failed to create producer thread");
        exit(EXIT_FAILURE);
    }
    
    // 创建消费者线程
    ret = pthread_create(&id_consumer, NULL, consumer, NULL);
    if (ret != 0) {
        perror("Failed to create consumer thread");
        exit(EXIT_FAILURE);
    }
    
    // 等待线程结束
    pthread_join(id_producer, NULL);
    pthread_join(id_consumer, NULL);
    
    // 销毁信号量
    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);
    
    // 释放缓冲区内存
    free(buffer);
    
    printf("Program exited successfully.\n");
    return 0;
}

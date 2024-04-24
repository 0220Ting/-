#define  _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
// 进程结构体
typedef struct {
    int pid;  //进程的标识符
    int arrivalTime;  //到达时间
    int burstTime;  //执行时间
} Process;

// 比较函数用于排序（根据进程的执行时间）
int compare(const void* a, const void* b) {    //因为 qsort 函数要求传入的比较函数参数类型为 const void *，即指向常量的指针
    const Process* processA = (const Process*)a; //将const void *类型的指针转换为const Process *类型的指针。
    //这样一来，我们就可以通过processA->burstTime和processB->burstTime来访问两个进程的执行时间，从而进行比较。
    const Process* processB = (const Process*)b;
    return processA->burstTime - processB->burstTime; //比较执行时间,如果结果为负数，表示 processA 的执行时间较短，应该排在 processB 前面（升序排序）
}

// 短作业优先调度算法函数
float SJF_Scheduling(Process processes[], int numProcesses) {  //传入进程数组 和进程数量
    printf("初始进程数量为：%d\n", numProcesses);
    // 排序进程列表（根据执行时间从短到长）
    qsort(processes, numProcesses, sizeof(Process), compare); //给他们排序
    int completionTime = 0;
    float waitingTime = 0;
    for (int i = 0; i < numProcesses; ++i) {

        if (completionTime > processes[i].arrivalTime) {
            waitingTime += completionTime - processes[i].arrivalTime;//算等待时间
        }
        // 更新完成时间
        completionTime += processes[i].burstTime;

        printf("进程ID为 %d，完成时间为 %d，等待时间为 %.2f\n", processes[i].pid, completionTime, waitingTime);
    }
    // 计算平均等待时间
    float avgWaitingTime = waitingTime / numProcesses;
    return avgWaitingTime;
}
int main() {
    int numProcesses;
    printf("请输入进程数量：");
    scanf("%d", &numProcesses);
    // malloc 返回的 void* 转换为 Process* 类型
    Process* processes = (Process*)malloc(numProcesses * sizeof(Process));
    for (int i = 0; i < numProcesses; ++i) {
        printf("进程ID为 %d\n", i + 1);
        printf("请输入到达时间：");
        scanf("%d", &processes[i].arrivalTime);
        printf("请输入执行时间：");
        scanf("%d", &processes[i].burstTime);
        processes[i].pid = i + 1;
    }
    float avgWaitingTime = SJF_Scheduling(processes, numProcesses);
    printf("平均等待时间为：%.2f\n", avgWaitingTime);
    free(processes); // 释放动态分配的内存
    return 0;
}

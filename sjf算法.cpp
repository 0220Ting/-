#define  _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
// ���̽ṹ��
typedef struct {
    int pid;  //���̵ı�ʶ��
    int arrivalTime;  //����ʱ��
    int burstTime;  //ִ��ʱ��
} Process;

// �ȽϺ����������򣨸��ݽ��̵�ִ��ʱ�䣩
int compare(const void* a, const void* b) {    //��Ϊ qsort ����Ҫ����ıȽϺ�����������Ϊ const void *����ָ������ָ��
    const Process* processA = (const Process*)a; //��const void *���͵�ָ��ת��Ϊconst Process *���͵�ָ�롣
    //����һ�������ǾͿ���ͨ��processA->burstTime��processB->burstTime�������������̵�ִ��ʱ�䣬�Ӷ����бȽϡ�
    const Process* processB = (const Process*)b;
    return processA->burstTime - processB->burstTime; //�Ƚ�ִ��ʱ��,������Ϊ��������ʾ processA ��ִ��ʱ��϶̣�Ӧ������ processB ǰ�棨��������
}

// ����ҵ���ȵ����㷨����
float SJF_Scheduling(Process processes[], int numProcesses) {  //����������� �ͽ�������
    printf("��ʼ��������Ϊ��%d\n", numProcesses);
    // ��������б�����ִ��ʱ��Ӷ̵�����
    qsort(processes, numProcesses, sizeof(Process), compare); //����������
    int completionTime = 0;
    float waitingTime = 0;
    for (int i = 0; i < numProcesses; ++i) {

        if (completionTime > processes[i].arrivalTime) {
            waitingTime += completionTime - processes[i].arrivalTime;//��ȴ�ʱ��
        }
        // �������ʱ��
        completionTime += processes[i].burstTime;

        printf("����IDΪ %d�����ʱ��Ϊ %d���ȴ�ʱ��Ϊ %.2f\n", processes[i].pid, completionTime, waitingTime);
    }
    // ����ƽ���ȴ�ʱ��
    float avgWaitingTime = waitingTime / numProcesses;
    return avgWaitingTime;
}
int main() {
    int numProcesses;
    printf("���������������");
    scanf("%d", &numProcesses);
    // malloc ���ص� void* ת��Ϊ Process* ����
    Process* processes = (Process*)malloc(numProcesses * sizeof(Process));
    for (int i = 0; i < numProcesses; ++i) {
        printf("����IDΪ %d\n", i + 1);
        printf("�����뵽��ʱ�䣺");
        scanf("%d", &processes[i].arrivalTime);
        printf("������ִ��ʱ�䣺");
        scanf("%d", &processes[i].burstTime);
        processes[i].pid = i + 1;
    }
    float avgWaitingTime = SJF_Scheduling(processes, numProcesses);
    printf("ƽ���ȴ�ʱ��Ϊ��%.2f\n", avgWaitingTime);
    free(processes); // �ͷŶ�̬������ڴ�
    return 0;
}

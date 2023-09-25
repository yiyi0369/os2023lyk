#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/syscall.h>
#include <unistd.h>
#define MAX_PROCESS_NUM 256

int pid[MAX_PROCESS_NUM];
char name[MAX_PROCESS_NUM * 16];
int isrunning[MAX_PROCESS_NUM];
unsigned long long cputime[MAX_PROCESS_NUM];

int pid_2[MAX_PROCESS_NUM];
char name_2[MAX_PROCESS_NUM * 16];
int isrunning_2[MAX_PROCESS_NUM];
unsigned long long cputime_2[MAX_PROCESS_NUM];

float cputime_s[MAX_PROCESS_NUM];


float cpu[MAX_PROCESS_NUM];

// get the infomation of the tasks,now we can get it
void cpu_cal()
{
    int i, j;
    unsigned long long cpu_total = 0;

    for (i = 0; i < MAX_PROCESS_NUM - 1; i++)
    {
        int flag = 0;
        for (j = 0; j < MAX_PROCESS_NUM - 1; j++)
        {
            if (pid[i] > 0 && (pid[i] == pid_2[j]))
            {
                cputime[i] = cputime_2[i] - cputime[j];
                flag = 1;
            }
        }
        if (flag == 0)
            pid[i] = 0;
        else
            cpu_total += cputime[i];
    }
    for (i = 0; i < MAX_PROCESS_NUM - 1; i++)
    {
        cpu[i] = ((float)cputime[i] / (float)cpu_total) * 100.0;

        cputime_s[i] = (float)cputime[i] * 1.0e-9;
    }
};
void swap_name(int a, int b)
{
    if (a == b)
        return;
    int i = 0;
    char code;
    for (i = 0; i < 16; i++)
    {
        code = name[a * 16 + i];
        name[a * 16 + i] = name[b * 16 + i];
        name[b * 16 + i] = code;
    }
    return;
}
void sort_by_cpu()
{
    int i, j, k;
    int pid_temp, isrunning_temp;
    float cpu_temp;
    float cpu_s_temp;
    for (i = 0; i < MAX_PROCESS_NUM - 1; i++)
    {
        for (j = 0; j < MAX_PROCESS_NUM - 2; j++)
        {
            if (cpu[j] < cpu[j + 1])
            {
                pid_temp = pid[j];
                pid[j] = pid[j + 1];
                pid[j + 1] = pid_temp;
                isrunning_temp = isrunning[j];
                isrunning[j] = isrunning[j + 1];
                isrunning[j + 1] = isrunning_temp;
                cpu_temp = cpu[j];
                cpu[j] = cpu[j + 1];
                cpu[j + 1] = cpu_temp;
                cpu_s_temp = cputime_s[j];
                cputime_s[j] = cputime_s[j + 1];
                cputime_s[j + 1] = cpu_s_temp;
                swap_name(j, j + 1);
            }
        }
    }
    return;
};

int main(int argc, char **argv)
{
    int i, j, k;

    // sleep(1);

    int sleeptime = 1;
    if (argc == 1)
        sleeptime = 1;
    else if (argc == 2)
    {
        sleeptime = atoi(argv[1]);
        if (sleeptime <= 1)
            sleeptime = 1;
    }
    syscall(333, pid, name, isrunning, cputime);
    sleep(sleeptime);
    system("clear");
    while (1)
    {
        // printf("testing!\n");

        syscall(333, pid_2, name_2, isrunning_2, cputime_2);

        cpu_cal();
        sort_by_cpu();

        printf("pid:\tisrun:\tcuprate:\tcputime:\tcom:\t\n");
        int count = 0;

        for (i = 0; i < MAX_PROCESS_NUM; i++)
        {
            if (pid[i] > 0 && count < 19)
            {
                count++;
                printf("%d\t%d\t%2.6f%%\t%2.7f\t", pid[i], isrunning[i], cpu[i], cputime_s[i]);

                for (j = 0; j < 16; j++)
                {
                    printf("%c", name[16 * i + j]);
                }
                printf("\t\n");
            }
        }
        sleep(sleeptime);
        for (i = 0; i < MAX_PROCESS_NUM; i++)
        {
            pid[i] = pid_2[i];
            isrunning[i] = isrunning_2[i];
            cputime[i] = cputime_2[i];
            for (j = 0; j < 16; j++)
            {
                name[16 * i + j] = name_2[16 * i + j];
            }
        }
        system("clear");
    }
}

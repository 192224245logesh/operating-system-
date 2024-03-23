#include <stdio.h>

#define MAX_PROCESS 10
#define TIME_QUANTUM 2

struct Process {
    int process_id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

void roundRobin(struct Process processes[], int n) {
    int remaining_processes = n;
    int current_time = 0;
    int time_quantum = TIME_QUANTUM;
    int front = 0, rear = 0;
    int queue[MAX_PROCESS]; 

   
    for (int i = 0; i < n; i++) {
        queue[i] = -1;
    }

    while (remaining_processes > 0) {
        
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && processes[i].remaining_time > 0) {
                queue[rear] = i;
                rear = (rear + 1) % MAX_PROCESS;
            }
        }

       
        int process_index = queue[front];
        front = (front + 1) % MAX_PROCESS;

        if (process_index == -1) {
            current_time++; 
            continue;
        }

        
        int execute_time = (processes[process_index].remaining_time < time_quantum)
                               ? processes[process_index].remaining_time
                               : time_quantum;
        processes[process_index].remaining_time -= execute_time;
        current_time += execute_time;

    
        if (processes[process_index].remaining_time == 0) {
            remaining_processes--;
            processes[process_index].completion_time = current_time;
            processes[process_index].turnaround_time =
                processes[process_index].completion_time - processes[process_index].arrival_time;
            processes[process_index].waiting_time =
                processes[process_index].turnaround_time - processes[process_index].burst_time;
        } else {
            
            queue[rear] = process_index;
            rear = (rear + 1) % MAX_PROCESS;
        }
    }
}

void calculateTimes(struct Process processes[], int n) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    
    printf("Process ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");

    
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].arrival_time,
               processes[i].burst_time, processes[i].completion_time, processes[i].turnaround_time,
               processes[i].waiting_time);
        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

   
    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

   
    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d:\n", i + 1);
        processes[i].process_id = i + 1;
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        processes[i].remaining_time = processes[i].burst_time;
    }

   
    roundRobin(processes, n);

    
    calculateTimes(processes, n);

    return 0;
}

#include <stdio.h>

struct Process {
    int process_id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
};

void calculateTimes(struct Process processes[], int n) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    
    int current_time = 0;
    for (int i = 0; i < n; i++) {
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }
        processes[i].completion_time = current_time + processes[i].burst_time;
        current_time = processes[i].completion_time;

        
        processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;

      
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;

        total_waiting_time += processes[i].waiting_time;
        total_turnaround_time += processes[i].turnaround_time;
    }

   
    printf("Process ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");

    
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].arrival_time,
               processes[i].burst_time, processes[i].completion_time, processes[i].turnaround_time,
               processes[i].waiting_time);
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
        processes[i].arrival_time = 0; 
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
    }

   
    calculateTimes(processes, n);

    return 0;
}

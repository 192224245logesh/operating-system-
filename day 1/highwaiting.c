#include <stdio.h>

struct Process {
    int process_id;
    int arrival_time;
    int burst_time;
    int priority;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int executed; // Flag to track if the process has been executed
};

void calculateTimes(struct Process processes[], int n) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    // Calculate completion time for each process
    int current_time = 0;
    int completed_processes = 0;
    while (completed_processes < n) {
        int highest_priority_index = -1;
        int highest_priority = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && !processes[i].executed &&
                processes[i].priority > highest_priority) {
                highest_priority = processes[i].priority;
                highest_priority_index = i;
            }
        }

        if (highest_priority_index == -1) {
            current_time++; // No processes are available, move to the next time unit
        } else {
            processes[highest_priority_index].executed = 1;
            processes[highest_priority_index].completion_time =
                current_time + processes[highest_priority_index].burst_time;
            processes[highest_priority_index].turnaround_time =
                processes[highest_priority_index].completion_time - processes[highest_priority_index].arrival_time;
            processes[highest_priority_index].waiting_time =
                processes[highest_priority_index].turnaround_time - processes[highest_priority_index].burst_time;
            total_waiting_time += processes[highest_priority_index].waiting_time;
            total_turnaround_time += processes[highest_priority_index].turnaround_time;
            current_time = processes[highest_priority_index].completion_time;
            completed_processes++;
        }
    }

    // Print table header
    printf("Process ID\tArrival Time\tBurst Time\tPriority\tCompletion Time\tTurnaround Time\tWaiting Time\n");

    // Print details for each process
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].arrival_time,
               processes[i].burst_time, processes[i].priority, processes[i].completion_time,
               processes[i].turnaround_time, processes[i].waiting_time);
    }

    // Print average waiting time and average turnaround time
    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input process details
    printf("Enter arrival time, burst time, and priority for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d:\n", i + 1);
        processes[i].process_id = i + 1;
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        printf("Priority: ");
        scanf("%d", &processes[i].priority);
        processes[i].executed = 0; // Initialize executed flag to 0
    }

    // Calculate completion time, turnaround time, and waiting time for each process
    calculateTimes(processes, n);

    return 0;
}

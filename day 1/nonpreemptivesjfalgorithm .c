#include <stdio.h>

struct Process {
    int process_id;
    int arrival_time;
    int burst_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int executed;
};

void calculateTimes(struct Process processes[], int n) {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    // Calculate completion time for each process
    int current_time = 0;
    int completed_processes = 0;
    while (completed_processes < n) {
        int shortest_burst_time = 999999; // Set to a large value initially
        int shortest_job_index = -1;
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival_time <= current_time && !processes[i].executed &&
                processes[i].burst_time < shortest_burst_time) {
                shortest_burst_time = processes[i].burst_time;
                shortest_job_index = i;
            }
        }

        if (shortest_job_index == -1) {
            current_time++; // No processes are available, move to the next time unit
        } else {
            processes[shortest_job_index].executed = 1;
            processes[shortest_job_index].completion_time = current_time + processes[shortest_job_index].burst_time;
            processes[shortest_job_index].turnaround_time =
                processes[shortest_job_index].completion_time - processes[shortest_job_index].arrival_time;
            processes[shortest_job_index].waiting_time =
                processes[shortest_job_index].turnaround_time - processes[shortest_job_index].burst_time;
            total_waiting_time += processes[shortest_job_index].waiting_time;
            total_turnaround_time += processes[shortest_job_index].turnaround_time;
            current_time = processes[shortest_job_index].completion_time;
            completed_processes++;
        }
    }

    // Print table header
    printf("Process ID\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");

    // Print details for each process
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].arrival_time,
               processes[i].burst_time, processes[i].completion_time, processes[i].turnaround_time,
               processes[i].waiting_time);
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
    printf("Enter arrival time and burst time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d:\n", i + 1);
        processes[i].process_id = i + 1;
        printf("Arrival Time: ");
        scanf("%d", &processes[i].arrival_time);
        printf("Burst Time: ");
        scanf("%d", &processes[i].burst_time);
        processes[i].executed = 0; // Initialize executed flag to 0
    }

    // Calculate completion time, turnaround time, and waiting time for each process
    calculateTimes(processes, n);

    return 0;
}

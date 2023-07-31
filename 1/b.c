#include <stdio.h>
#include <stdlib.h>

typedef struct process {
  int Id, AT, BT, CT, TAT, WT;
} pro;

pro p[15]; // Array to store process details

void main() {
  int n, tempBT[15], total_WT = 0, total_TAT = 0;
  float avg_WT = 0, avg_TAT = 0;

  printf("\nEnter the number of processes:\n");
  scanf("%d", &n);

  printf("\nEnter the arrival time and burst time of the processes:\n");
  printf("AT BT\n");
  for (int i = 0; i < n; i++) {
    p[i].Id = (i + 1);
    scanf("%d%d", &p[i].AT, &p[i].BT);
    tempBT[i] = p[i].BT; // Store burst time in a temporary array for later calculations
  }

  printf("\nGantt Chart:\n");
  int minIndex, minBT, completed = 0, curTime = 0;
  while (completed != n) {
    minIndex = -1;
    minBT = 9999;
    for (int i = 0; i < n; i++) {
      // Find the process with the minimum burst time that has arrived and not completed
      if (p[i].AT <= curTime && p[i].BT > 0) {
        if (p[i].BT < minBT || (p[i].BT == minBT && p[i].AT < p[minIndex].AT)) {
          minBT = p[i].BT;
          minIndex = i;
        }
      }
    }
    curTime++;
    if (minIndex != -1) {
      p[minIndex].BT--;
      printf("| P%d(1) %d", p[minIndex].Id, curTime);
      if (p[minIndex].BT == 0) {
        // The process has completed
        p[minIndex].CT = curTime; // Completion time
        p[minIndex].TAT = p[minIndex].CT - p[minIndex].AT; // Turnaround time
        p[minIndex].WT = p[minIndex].TAT - tempBT[minIndex]; // Waiting time
        total_TAT += p[minIndex].TAT; // Update total turnaround time
        total_WT += p[minIndex].WT; // Update total waiting time
        completed++; // Increment the number of completed processes
      }
    }
  }
  printf("|\n");

  avg_TAT = (float)total_TAT / n; // Calculate average turnaround time
  avg_WT = (float)total_WT / n; // Calculate average waiting time

  // Printing the table of processes with details
  printf("\nPID\tAT\tBT\tCT\tTAT\tWT\n");
  for (int i = 0; i < n; i++) {
    printf("%d\t%d\t%d\t%d\t%d\t%d\n", p[i].Id, p[i].AT, tempBT[i], p[i].CT,
           p[i].TAT, p[i].WT);
  }
  printf("\nAverage TAT = %.2f\nAverage WT = %.2f\n", avg_TAT, avg_WT);
}

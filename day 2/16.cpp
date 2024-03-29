#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define FILENAME "employee.dat"

typedef struct {
    int empID;
    char empName[30];
    float empSalary;
} Employee;

void addEmployee() {
    FILE *file = fopen(FILENAME, "ab");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    Employee newEmployee;

    printf("Enter Employee ID: ");
    scanf("%d", &newEmployee.empID);
    fflush(stdin);  // Clear input buffer

    printf("Enter Employee Name: ");
    fgets(newEmployee.empName, sizeof(newEmployee.empName), stdin);
    newEmployee.empName[strcspn(newEmployee.empName, "\n")] = '\0';  // Remove newline character

    printf("Enter Employee Salary: ");
    scanf("%f", &newEmployee.empSalary);

    fseek(file, 0, SEEK_END);
    fwrite(&newEmployee, sizeof(Employee), 1, file);

    fclose(file);

    printf("Employee added successfully.\n");
}

void displayEmployee(int empID) {
    FILE *file = fopen(FILENAME, "rb");
    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    Employee displayEmp;
    int found = 0;

    while (fread(&displayEmp, sizeof(Employee), 1, file) == 1) {
        if (displayEmp.empID == empID) {
            printf("Employee Details:\n");
            printf("Employee ID: %d\n", displayEmp.empID);
            printf("Employee Name: %s\n", displayEmp.empName);
            printf("Employee Salary: %.2f\n", displayEmp.empSalary);
            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("Employee with ID %d not found.\n", empID);
    }
}

int main() {
    int choice, empID;

    do {
        printf("\nEmployee Database Menu:\n");
        printf("1. Add Employee\n");
        printf("2. Display Employee Details\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                printf("Enter Employee ID to display details: ");
                scanf("%d", &empID);
                displayEmployee(empID);
                break;
            case 0:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    } while (choice != 0);

    return 0;
}


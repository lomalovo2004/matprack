#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    char name[BUFSIZ];
    char surname[BUFSIZ];
    float salary;
} Employee;

int compare_employees(const void* a, const void* b) {
    Employee* emp1 = (Employee*)a;
    Employee* emp2 = (Employee*)b;

    if (emp1->salary < emp2->salary)
        return -1;
    else if (emp1->salary > emp2->salary)
        return 1;
    else {
        int surname_cmp = strcmp(emp1->surname, emp2->surname);
        if (surname_cmp != 0)
            return surname_cmp;
        else {
            int name_cmp = strcmp(emp1->name, emp2->name);
            if (name_cmp != 0)
                return name_cmp;
            else
                return emp1->id - emp2->id;
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        printf("Use: program <input_file> <flag> <output_file>\n");
        return 1;
    }

    char* input_file = argv[1];
    char flag = argv[2][1];
    char* output_file = argv[3];

    FILE* file = fopen(input_file, "r");
    if (file == NULL) {
        printf("Error opening input file.\n");
        fclose(file);
        return 1;
    }

    int num_employees = 0;
    Employee* employees = NULL;

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        num_employees++;
        employees = realloc(employees, num_employees * sizeof(Employee));
        if (employees == NULL){
            printf("Memmory does not allocated\n");
            fclose(file);
            return 1;
        }

        sscanf(line, "%d %s %s %f", &employees[num_employees - 1].id, employees[num_employees - 1].name,
               employees[num_employees - 1].surname, &employees[num_employees - 1].salary);
    }

    fclose(file);

    if (flag == 'a') {
        qsort(employees, num_employees, sizeof(Employee), compare_employees);
    } else if (flag == 'd') {
        qsort(employees, num_employees, sizeof(Employee), compare_employees);
        // Reverse the sorted array
        for (int i = 0; i < num_employees / 2; i++) {
            Employee temp = employees[i];
            employees[i] = employees[num_employees - i - 1];
            employees[num_employees - i - 1] = temp;
        }
    } else {
        printf("Invalid flag. Use -a or -d.\n");
        return 1;
    }

    file = fopen(output_file, "w");
    if (file == NULL) {
        printf("Error opening output file.\n");
        fclose(file);
        return 1;
    }

    for (int i = 0; i < num_employees; i++) {
        fprintf(file, "%d %s %s %.2f\n", employees[i].id, employees[i].name, employees[i].surname, employees[i].salary);
    }

    fclose(file);

    free(employees);

    return 0;
}

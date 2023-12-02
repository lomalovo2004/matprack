//perfect
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum 
{
    OK = 0,
    BAD_ALLOC,
    NO_INPUT_FILE,
    NO_TRACE_FILE,
    NO_ARGUMENTS,
} EXIT_CODE;

typedef struct {
    int id;
    char name[BUFSIZ];
    char surname[BUFSIZ];
    char group[BUFSIZ];
    unsigned char* grades;
} Student;

EXIT_CODE args_check(int argc, char* agrv[]){
    if (argc != 2 && argc != 3) {
        return NO_ARGUMENTS;
    }
    return OK;
}

EXIT_CODE memory_chek(Student* students){
    if (students == NULL){
        return BAD_ALLOC;
    }
    return OK;
}

EXIT_CODE input_file_check(char* input_file){
    if (input_file == NULL){
        return NO_INPUT_FILE;
    }
    return OK;
}

EXIT_CODE trace_file_check(char* trace_file){
    if (trace_file == NULL){
        return NO_TRACE_FILE;
    }
    return OK;
}

int compare_students_by_id(const void* a, const void* b) {
    Student* student1 = (Student*)a;
    Student* student2 = (Student*)b;
    return student1->id - student2->id;
}

int compare_students_by_surname(const void* a, const void* b) {
    Student* student1 = (Student*)a;
    Student* student2 = (Student*)b;
    return strcmp(student1->surname, student2->surname);
}

int compare_students_by_name(const void* a, const void* b) {
    Student* student1 = (Student*)a;
    Student* student2 = (Student*)b;
    return strcmp(student1->name, student2->name);
}

int compare_students_by_group(const void* a, const void* b) {
    Student* student1 = (Student*)a;
    Student* student2 = (Student*)b;
    return strcmp(student1->group, student2->group);
}

float calculate_average_grade(Student* student) {
    float sum = 0;
    for (int i = 0; i < 5; i++) {
        sum += student->grades[i];
    }
    return sum / 5;
}

int main(int argc, char* argv[]) {
    if (args_check(argc, argv) == NO_ARGUMENTS){
        printf("Use: program <input_file> or program <input_file> <trace_file>\n");
        return 1;
    }

    char* input_file = argv[1];

    FILE* file = fopen(input_file, "r");
    
    if (input_file_check(input_file) == NO_INPUT_FILE) {
        printf("Error opening input file\n");
        fclose(file);
        return 1;
    }
    
    int num_students = 0;
    Student* students = NULL;

    char line[BUFSIZ];
    while (fgets(line, sizeof(line), file)) {
        num_students++;
        students = realloc(students, num_students * sizeof(Student));
        students[num_students - 1].grades = malloc(5 * sizeof(unsigned char));
        if (memory_chek(students) == BAD_ALLOC){
            printf("Memmory does not allocate\n");
            fclose(file);
            return 1;
        }

        sscanf(line, "%d %s %s %s %hhu %hhu %hhu %hhu %hhu", &students[num_students - 1].id,
               students[num_students - 1].name, students[num_students - 1].surname,
               students[num_students - 1].group, &students[num_students - 1].grades[0],
               &students[num_students - 1].grades[1], &students[num_students - 1].grades[2],
               &students[num_students - 1].grades[3], &students[num_students - 1].grades[4]);
    }

    fclose(file);

    int option;
    printf("Choose an option:\n");
    printf("1. Search by id\n");
    printf("2. Search by surname\n");
    printf("3. Search by name\n");
    printf("4. Search by group\n");
    printf("5. Sort by id\n");
    printf("6. Sort by surname\n");
    printf("7. Sort by name\n");
    printf("8. Sort by group\n");
    printf("Options 9-10 do not work without trace_file\n");
    printf("9. Upper average grade\n");
    printf("10. Trace student id\n");
    printf("Enter your option: ");
    scanf("%d", &option);

    switch (option) {
        case 1: {
            int search_id;
            printf("Enter the id to search: ");
            scanf("%d", &search_id);

            int found = 0;
            for (int i = 0; i < num_students; i++) {
                if (students[i].id == search_id) {
                    printf("Found student:\n");
                    printf("ID: %d\n", students[i].id);
                    printf("Name: %s\n", students[i].name);
                    printf("Surname: %s\n", students[i].surname);
                    printf("Group: %s\n", students[i].group);
                    float average_grade = calculate_average_grade(&students[i]);
                    printf("Average grade: %.2f\n", average_grade);

                    found = 1;
                    break;
                }
            }
            if (!found){
                printf("Unknown id\n");
            }
            break;
        }
        case 2: {
            char search_surname[BUFSIZ];
            printf("Enter the surname to search: ");
            scanf("%s", search_surname);

            int found = 0;
            for (int i = 0; i < num_students; i++) {
                if (strcmp(students[i].surname, search_surname) == 0) {
                    printf("Found student:\n");
                    printf("ID: %d\n", students[i].id);
                    printf("Name: %s\n", students[i].name);
                    printf("Surname: %s\n", students[i].surname);
                    printf("Group: %s\n", students[i].group);
                    float average_grade = calculate_average_grade(&students[i]);
                    printf("Average grade: %.2f\n", average_grade);

                    found = 1;
                    break;
                }
            }
            if (!found){
                printf("Unknown surname\n");
            }
            break;
        }
        case 3: {
            char search_name[BUFSIZ];
            printf("Enter the name to search: ");
            scanf("%s", search_name);

            int found = 0;
            for (int i = 0; i < num_students; i++) {
                if (strcmp(students[i].name, search_name) == 0){
                    printf("Found student:\n");
                    printf("ID: %d\n", students[i].id);
                    printf("Name: %s\n", students[i].name);
                    printf("Surname: %s\n", students[i].surname);
                    printf("Group: %s\n", students[i].group);
                    float average_grade = calculate_average_grade(&students[i]);
                    printf("Average grade: %.2f\n", average_grade);

                    found = 1;
                    break;
                }
            }
            if (!found){
                printf("Unknown name\n");
            }
            break;
        }
        case 4: {
            char search_group[BUFSIZ];
            printf("Enter the group to search: ");
            scanf("%s", search_group);

            int found = 0;
            for (int i = 0; i < num_students; i++) {
                if (strcmp(students[i].group, search_group) == 0){
                    printf("Found student:\n");
                    printf("ID: %d\n", students[i].id);
                    printf("Name: %s\n", students[i].name);
                    printf("Surname: %s\n", students[i].surname);
                    printf("Group: %s\n", students[i].group);
                    float average_grade = calculate_average_grade(&students[i]);
                    printf("Average grade: %.2f\n", average_grade);

                    found = 1;
                    break;
                }
            }
            if (!found){
                printf("Unknown group\n");
            }
            break;
        }
        case 5:
            qsort(students, num_students, sizeof(Student), compare_students_by_id);
            printf("Students sorted by ID:\n");
            for (int i = 0; i < num_students; i++) {
                printf("ID: %d\n", students[i].id);
                printf("Name: %s\n", students[i].name);
                printf("Surname: %s\n", students[i].surname);
                printf("Group: %s\n", students[i].group);
                float average_grade = calculate_average_grade(&students[i]);
                printf("Average grade: %.2f\n", average_grade);
                printf("\n");
            }
            break;
        case 6:
            qsort(students, num_students, sizeof(Student), compare_students_by_surname);
            for (int i = 0; i < num_students; i++) {
                printf("ID: %d\n", students[i].id);
                printf("Name: %s\n", students[i].name);
                printf("Surname: %s\n", students[i].surname);
                printf("Group: %s\n", students[i].group);
                float average_grade = calculate_average_grade(&students[i]);
                printf("Average grade: %.2f\n", average_grade);
                printf("\n");
            }
            break;
        case 7:
            qsort(students, num_students, sizeof(Student), compare_students_by_name);
            for (int i = 0; i < num_students; i++) {
                printf("ID: %d\n", students[i].id);
                printf("Name: %s\n", students[i].name);
                printf("Surname: %s\n", students[i].surname);
                printf("Group: %s\n", students[i].group);
                float average_grade = calculate_average_grade(&students[i]);
                printf("Average grade: %.2f\n", average_grade);
                printf("\n");
            }
            break;
        case 8:
            qsort(students, num_students, sizeof(Student), compare_students_by_group);
            for (int i = 0; i < num_students; i++) {
                printf("ID: %d\n", students[i].id);
                printf("Name: %s\n", students[i].name);
                printf("Surname: %s\n", students[i].surname);
                printf("Group: %s\n", students[i].group);
                float average_grade = calculate_average_grade(&students[i]);
                printf("Average grade: %.2f\n", average_grade);
                printf("\n");
            }
            break;
        case 9:{
            char* trace_file = argv[2];
            file = fopen(trace_file, "w");
            if (trace_file_check(trace_file) == NO_TRACE_FILE) {
                printf("Error opening trace file.\n");
                fclose(file);
                return 1;
            }
            float average_grade_all = 0;
            int count_above_average = 0;
            for (int i = 0; i < num_students; i++) {
                float average_grade = calculate_average_grade(&students[i]);
                average_grade_all += average_grade;

                if (average_grade > average_grade_all / num_students) {
                    fprintf(file, "%s %s\n", students[i].surname, students[i].name);
                    count_above_average++;
                }
            }
            fprintf(file, "Average grade: %.2f\n", average_grade_all / num_students);
            fprintf(file, "Number of students with above average grade: %d\n", count_above_average);
            fclose(file);
            break;
        }
        case 10:{
            char* trace_file = argv[2];
            file = fopen(trace_file, "w");
            if (trace_file_check(trace_file) == NO_TRACE_FILE) {
                printf("Error opening trace file.\n");
                fclose(file);
                return 1;
            }
            int trace_search_id;
            printf("Enter the id to search: ");
            scanf("%d", &trace_search_id);

            int found = 0;
            for (int i = 0; i < num_students; i++) {
                if (students[i].id == trace_search_id) {
                    fprintf(file, "Found student:\n");
                    fprintf(file, "ID: %d\n", students[i].id);
                    fprintf(file, "Name: %s\n", students[i].name);
                    fprintf(file ,"Surname: %s\n", students[i].surname);
                    fprintf(file, "Group: %s\n", students[i].group);
                    float average_grade = calculate_average_grade(&students[i]);
                    fprintf(file, "Average %.2f\n", average_grade);

                    found = 1;
                    break;
                }
            }
            if (!found) {
                printf("Unknown id\n");
            }
            fclose(file);
            break;
        }
        default:
            printf("Invalid option.\n");
            break;
    }
    
    for (int i = 0; i < num_students; i++) {
        free(students[i].grades);
    }
    free(students);
    
    return 0;
}

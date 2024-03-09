#include <stdio.h>//in process
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>


typedef enum
{
    OK,
    BAD_ALLOC,
    INVALID_INPUT,
    FILE_ERROR
} EXIT_CODE;

typedef enum
{
    SURNAME,
    NAME,
    OTCHESTVO,
    BIRTH_DAY,
    GENDER,
    SALARY,
    DELETE
} Commands;

void errors(EXIT_CODE error)
{
    switch (error)
    {
        case OK:
            return;
        case BAD_ALLOC:
            printf("Memmory does not allocated\n");
            return;
        case INVALID_INPUT:
            printf("Invalid input\n");
            return;
        case FILE_ERROR:
            printf("Error opening file\n");
            return;
        default:
            printf("Unknown error\n");
            return;
    }
}

typedef struct Liver
{
    int flag;
    char name[16];
    char surname[16];
    char OTCHESTVO[16];
    char birthday[16];
    char gender[2];
    double salary;
    struct Liver* next;
} Liver;

typedef struct
{
    Liver * top;
    Liver * bot;
    unsigned long long int size;
} List;

typedef struct modification
{
    struct modification* prev;
    Liver* liver;
    char info[16];
    double salary;
    Commands flag;
    struct modification* next;
}modification;

typedef struct modifications_list
{
    unsigned long long int amt_of_modifications;
    unsigned long long int size;
    char info[16];
    struct modification* top;
    struct modification* bot;
} modifications_list;

EXIT_CODE create_modifications_list(modifications_list* list)
{
    if (list == NULL)
    {
        return INVALID_INPUT;
    }
    list->amt_of_modifications = 0;
    list->size = 0;
    list->top = NULL;
    list->bot = NULL;
    return OK;
}


EXIT_CODE pop_back(modifications_list* tmp)
{
    if (tmp == NULL)
    {
        tmp->size = 0;
        tmp->amt_of_modifications = 0;
        return OK;
    }
    modification* current = tmp->top;
    if (tmp->size)
    {
        tmp->top = current->next;
        free(current);
        tmp->top->prev = NULL;
        tmp->amt_of_modifications--;
    }
    return OK;
}


EXIT_CODE push_front(modifications_list* tmp, Liver* liver, Commands flag, const char* info, double salary)
{
    if (tmp == NULL)
    {
        return INVALID_INPUT;
    }
    modification* new = (modification*)malloc(sizeof(modification));
    if (new == NULL)
    {
        return BAD_ALLOC;
    }
    new->flag = flag;
    new->liver = liver;
    if (flag == SALARY)
    {
        new->salary = salary;
    }
    else if (flag != DELETE)
    {
        strcpy(new->info, info);
    }
    if (tmp->bot != NULL)
    {
        tmp->bot->next = new;
        new->prev = tmp->bot;
    }
    else if (tmp->top == NULL)
    {
        tmp->top = new;
        new->prev = NULL;
    }
    tmp->bot = new;
    new->next = NULL;
    tmp->amt_of_modifications++;
    tmp->size++;
    return OK;
}

EXIT_CODE pop_front(modifications_list* tmp)
{
    modification* last = tmp->bot;
    if (tmp->amt_of_modifications == 0)
    {
        return OK;
    }
    if (tmp->amt_of_modifications == 1)
    {
        tmp->top = tmp->bot = NULL;
        tmp->amt_of_modifications = 0;
        return OK;
    }
    tmp->bot = last->prev;
    last->prev->next = NULL;
    tmp->amt_of_modifications--;
    return OK;
}

EXIT_CODE destruct_modifications_list(modifications_list* tmp)
{
    if (tmp->top == NULL)
    {
        return OK;
    }
    if (tmp->top == tmp->bot)
    {
        free(tmp->bot);
        tmp->top = tmp->bot = NULL;
    }
    else
    {
        modification* current = tmp->top;
        while (current != NULL)
        {
            tmp->top = current->next;
            free(current);
            current = current->next;
        }
    }
    tmp->amt_of_modifications = 0;
    return OK;
}


EXIT_CODE get_str(char** str)
{
    int max_size = 20;
    int temp_size = 0;
    *str = (char*)malloc(sizeof(char) * max_size);
    if (*str == NULL)
    {
        return BAD_ALLOC;
    }
    char c;
    while ((c = getchar()) != '\n')
    {
        if (temp_size +  1 == max_size)
        {
            max_size *=  2;
            char* new_str = (char*)realloc(*str, max_size +  1);
            if (new_str == NULL)
            {
                free(*str);
                return BAD_ALLOC;
            }
            *str = new_str;
        }
        (*str)[temp_size] = c;
        temp_size++;
    }
    (*str)[temp_size] = '\0';
    return OK;
}

EXIT_CODE null_list(List* list)
{
    if (list == NULL)
    {
        return INVALID_INPUT;
    }
    list->size = 0;
    list->top = NULL;
    list->bot = NULL;
    return OK;
}

EXIT_CODE create_list(List* list)
{
    if (list == NULL)
    {
        return INVALID_INPUT;
    }

    list->top = list->bot;
    list->bot = list->top;
    list->size = 0;
    return OK;
}

EXIT_CODE destruct_list(List* list)
{
    if (list == NULL)
    {
        return INVALID_INPUT;
    }
    if (list->top == NULL || list->bot == NULL)
    {
        return list->top == list->bot ? OK : BAD_ALLOC;
    }
    Liver* item = list->top;
    Liver* next_item = item->next;
    while (item->next != NULL)
    {
        free(item);
        item = next_item;
        next_item = item->next;
    }
    free(item);
    list->size = 0;
    list->top = NULL;
    list->bot = NULL;
    return OK;
}

int compare_age(const char* a, const char* b)
{
    if (a[6] > b[6])
    {
        return 1;
    }
    else if (a[6] < b[6])
    {
        return 0;
    }

    int a_age = 0;
    int b_age = 0;

    for (int i = 6; i < 10; ++i)
    {
        a_age = a_age * 10 + a[i] - '0';
        b_age = b_age * 10 + b[i] - '0';
    }

    if (a_age > b_age)
    {
        return 1;
    }
    else if (b_age < a_age)
    {
        return 0;
    }

    a_age = 0;
    b_age = 0;

    for (int i = 3; i < 5; ++i)
    {
        a_age = a_age * 10 + a[i] - '0';
        b_age = b_age * 10 + b[i] - '0';
    }

    if (a_age > b_age)
    {
        return 1;
    }
    else if (b_age < a_age)
    {
        return 0;
    }

    a_age = 0;
    b_age = 0;

    for (int i = 0; i < 2; ++i)
    {
        a_age = a_age * 10 + a[i] - '0';
        b_age = b_age * 10 + b[i] - '0';
    }

    if (a_age > b_age)
    {
        return 1;
    }
    else if (b_age < a_age)
    {
        return 0;
    }
    return 0;
}

EXIT_CODE push_back_list(List* livers, Liver* liver)
{
    if (livers == NULL || liver == NULL)
    {
        return INVALID_INPUT;
    }
    if (livers->bot != NULL)
    {
        livers->bot->next = liver;
    }
    if (livers->top == NULL)
    {
        livers->top = liver;
    }
    livers->bot = liver;
    liver->next = NULL;
    livers->size++;
    return OK;
}

EXIT_CODE push_front_list(List* livers, Liver* liver)
{
    if (livers == NULL || liver == NULL)
    {
        return INVALID_INPUT;
    }
    if (livers->top != NULL)
    {
        liver->next = livers->top;
    }
    if (livers->bot == NULL)
    {
        livers->bot = liver;
    }
    livers->top = liver;
    livers->size++;
    return OK;
}

EXIT_CODE add_liver(List* livers, Liver* liver)
{
    if (livers == NULL || liver == NULL)
    {
        return INVALID_INPUT;
    }
    liver->flag = 1;
    if (livers->size == 0)
    {
        push_back_list(livers, liver);
        return OK;
    }
    if (compare_age(livers->top->birthday, liver->birthday))
    {
        push_front_list(livers, liver);
        return OK;
    }
    Liver* current = livers->top;
    while (current->next != NULL)
    {
        if (compare_age(current->next->birthday, liver->birthday))
        {
            break;
        }
        current = current->next;
    }
    if (current->next == NULL)
    {
        push_back_list(livers, liver);
        return OK;
    }
    liver->next = current->next;
    current->next = liver;
    return OK;
}

void print_list(List list)
{
    Liver* item = list.top;
    if (list.size == 0)
    {
        printf("List is empty\n");
        return;
    }
    while (item != NULL)
    {
        if (item->flag)
        {
            if (strcmp(item->OTCHESTVO, "NONE"))
            {
                printf("%s %s %s %s %s %lf\n", item->surname, item->name, item->OTCHESTVO, item->birthday, item->gender, item->salary);
            }
            else
            {
                printf("%s %s %s %s %lf\n", item->surname, item->name, item->birthday, item->gender, item->salary);
            }
        }
        item = item->next;
    }
    printf("\n");
}

void print_liver(Liver* item)
{
    if (strcmp(item->OTCHESTVO, "NONE") != 0)
    {
        printf("%s %s %s %s %s %lf\n", item->surname, item->name, item->OTCHESTVO, item->birthday, item->gender, item->salary);
    }
    else
    {
        printf("%s %s %s %s %lf\n", item->surname, item->name, item->birthday, item->gender, item->salary);
    }
}

EXIT_CODE without_OTCHESTVO(Liver* liver, const char* str)
{
    if (liver == NULL || str == NULL)
    {
        return INVALID_INPUT;
    }
    if (sscanf(str, "%s %s %s %s %lf", liver->surname, liver->name, liver->birthday, liver->gender, &liver->salary) != 5)
    {
        return INVALID_INPUT;
    }
    strcpy(liver->OTCHESTVO, "NONE");
    return OK;
}

EXIT_CODE check_person(const char* str, Commands flag)
{
    if (str == NULL || strlen(str) > 14)
    {
        return INVALID_INPUT;
    }
    if (flag != OTCHESTVO && *str == '\0')
    {
        return INVALID_INPUT;
    }
    for (int i = 0; str[i]; ++i)
    {
        if (!isalpha(str[i]))
        {
            return INVALID_INPUT;
        }
    }
    return OK;
}

EXIT_CODE valid_birthday(const char* str)
{
    if (str == NULL || strlen(str) != 10)
    {
        return INVALID_INPUT;
    }
    if (str[2] != '.' && str[5] != '.')
    {
        return INVALID_INPUT;
    }
    if (!isdigit(str[0]) && !isdigit(str[1]) && !isdigit(str[3]) && !isdigit(str[4]))
    {
        return INVALID_INPUT;
    }
    for (int i = 6; i < 10; ++i)
    {
        if (!isdigit(str[i]))
        {
            return INVALID_INPUT;
        }
    }
    return OK;
}

EXIT_CODE get_flag(Commands* error, char ch)
{
    if (ch == 's')
    {
        *error = SALARY;
    }
    else if (ch == 'n')
    {
        *error = NAME;
    }
    else if (ch == 'S')
    {
        *error = SURNAME;
    }
    else if (ch == 'm')
    {
        *error = OTCHESTVO;
    }
    else if (ch == 'b')
    {
        *error = BIRTH_DAY;
    }
    else if (ch == 'g')
    {
        *error = GENDER;
    }
    else if (ch == 'd')
    {
        *error = DELETE;
    }
    else
    {
        return INVALID_INPUT;
    }
    return OK;
}

EXIT_CODE get_liver(List* livers, const char* ptr)
{
    if (livers == NULL || ptr == NULL)
    {
        return INVALID_INPUT;
    }
    EXIT_CODE st = OK;
    Commands flag;
    Liver* current = (Liver*)malloc(sizeof(Liver));
    if (current == NULL)
    {
        st = BAD_ALLOC;
    }
    if (sscanf(ptr, "%s %s %s %s %s %lf", current->surname, current->name, current->OTCHESTVO, current->birthday, current->gender, &(current->salary)) != 6)
    {
        st = st ? st: without_OTCHESTVO(current, ptr) == INVALID_INPUT ? st : OK;
    }
    if (!st)
    {
        st = check_person(current->surname, SURNAME);
    }
    if (!st)
    {
        st = check_person(current->name, NAME);
    }
    if (!st)
    {
        st = check_person(current->OTCHESTVO, OTCHESTVO);
    }
    if (!st)
    {
        st = valid_birthday(current->birthday);
    }
    if (!st)
    {
        st = add_liver(livers, current);
    }
    if (st)
    {
        free(current);
        return st;
    }
    return OK;
}

EXIT_CODE read_from_file(FILE* file, List* livers)
{
    if (file == NULL || livers == NULL)
    {
        return INVALID_INPUT;
    }
    char* tmp_str = (char*)malloc(sizeof(char) * 128);
    if (tmp_str == NULL)
    {
        return BAD_ALLOC;
    }
    int error = 1;
    size_t length = 0;
    EXIT_CODE st = OK;
    while (((error = getline(&tmp_str, &length, file)) != -1) && !st)
    {
        if (error)
        {
            st = get_liver(livers, tmp_str);
        }
    }
    free(tmp_str);
    return st;
}


EXIT_CODE change_liver(Liver* liver, modifications_list* modifications, const char* info, char* gender, double salary, Commands flag)
{
    if (liver == NULL || modifications == NULL)
    {
        return INVALID_INPUT;
    }
    EXIT_CODE st = OK;
    if (flag == NAME)
    {
        st = push_front(modifications, liver, flag, liver->name, liver->salary);
        if (!st && !(modifications->size & 1))
        {
            st = pop_back(modifications);
        }
        if (!st)
        {
            printf("Liver %s changed name to %s \n", liver->surname , info);
            strcpy(liver->name, info);
        }
    }
    if (!st && flag == SURNAME)
    {
        st = push_front(modifications, liver, flag, liver->surname, liver->salary);
        if (!st && !(modifications->size & 1))
        {
            st = pop_back(modifications);
        }
        if (!st)
        {
            printf("Liver %s changed surname to %s \n", liver->surname , info);
            strcpy(liver->surname, info);
        }
    }
    else if (!st && flag == OTCHESTVO)
    {
        st = push_front(modifications, liver, flag, liver->OTCHESTVO, liver->salary);
        if (!st && !(modifications->size & 1))
        {
            st = pop_back(modifications);
        }
        if (!st)
        {
            printf("Liver %s changed middle name to %s \n", liver->surname , info);
            strcpy(liver->OTCHESTVO, info);
        }
    }
    else if (!st && flag == BIRTH_DAY)
    {
        st = push_front(modifications, liver, flag, liver->birthday, liver->salary);
        if (!st && !(modifications->size & 1))
        {
            st = pop_back(modifications);
        }
        if (!st)
        {
            printf("Liver %s changed birthday date to %s \n", liver->surname , info);
            strcpy(liver->birthday, info);
        }
    }
    else if (!st && flag == GENDER)
    {
        st = push_front(modifications, liver, flag, liver->gender, liver->salary);
        if (!st && !(modifications->size & 1))
        {
            st = pop_back(modifications);
        }
        if (!st)
        {
            printf("Liver %s changed gender to %s \n", liver->surname , info);
            strcpy(liver->gender, gender);
        }
    }
    else if (!st && flag == SALARY)
    {
        st = push_front(modifications, liver, flag, liver->surname, liver->salary);
        if (!st && !(modifications->size & 1))
        {
            st = pop_back(modifications);
        }
        if (!st)
        {
            printf("Liver's %s salary changed to %s \n", liver->surname , info);
            liver->salary = salary;
        }
    }
    else if (!st && flag == DELETE)
    {
        liver->flag = 0;
        st = push_front(modifications, liver, flag, liver->surname, liver->salary);
        if (!st && !(modifications->size & 1))
        {
            st = pop_back(modifications);
        }
        if (!st)
        {
            printf("Liver was deleted\n");
        }
    }
    return OK;
}

EXIT_CODE search_liver(List* livers, Liver* liver, Liver** result)
{
    if (livers == NULL || liver == NULL)
    {
        return INVALID_INPUT;
    }
    Liver* current = livers->top;
    while (current != NULL)
    {
        if (!strcmp(liver->surname, current->surname) && !strcmp(liver->name, current->name) && !strcmp(liver->OTCHESTVO, current->OTCHESTVO)
            && !strcmp(liver->birthday, current->birthday) && !strcmp(liver->name, current->name) && (fabs(liver->salary-current->salary) < __DBL_EPSILON__) && current->flag)
        {
            *result = current;
            return OK;
        }
        current = current->next;
    }
    return INVALID_INPUT;
}

EXIT_CODE undo(modifications_list* modifications)
{
    if (modifications == NULL || modifications->amt_of_modifications == 0)
    {
        return INVALID_INPUT;
    }
    modification* current = modifications->bot;

    switch (current->flag)
    {
        case DELETE:
            current->liver->flag = 1;
            break;
        case NAME:
            strcpy(current->liver->name, current->info);
            break;
        case SURNAME:
            strcpy(current->liver->surname, current->info);
            break;
        case OTCHESTVO:
            strcpy(current->liver->OTCHESTVO, current->info);
            break;
        case BIRTH_DAY:
            strcpy(current->liver->birthday, current->info);
            break;
        case GENDER:
            strcpy(current->liver->gender, current->info);
            break;
        case SALARY:
            current->liver->salary = current->salary;
            break;
    }
    EXIT_CODE st = pop_front(modifications);
    return st;
}

EXIT_CODE write_to_file(List* livers)
{
    if (livers == NULL)
    {
        return INVALID_INPUT;
    }
    int size =  16;
    int cnt =  0;
    char* file_name = (char*)malloc(sizeof(char) * size);
    if (file_name == NULL)
    {
        return BAD_ALLOC;
    }
    EXIT_CODE st = OK;
    printf("Enter name of output file\n");
    char c = getchar();
    while (c != '\n')
    {
        if (cnt == size -  1)
        {
            size *=  2;
            char* new_file_name = (char*)realloc(file_name, sizeof(char) * size);
            if (new_file_name == NULL)
            {
                free(file_name);
                return BAD_ALLOC;
            }
            file_name = new_file_name;
        }
        file_name[cnt++] = c;
        c = getchar();
    }
    file_name[cnt] = '\0';
    FILE* out = fopen(file_name, "w");
    if (out == NULL)
    {
        st = FILE_ERROR;
    }
    if (!st)
    {
        Liver* current = livers->top;
        while (current != NULL)
        {
            if (current->flag)
            {
                if (strcmp(current->OTCHESTVO, "NONE") !=  0)
                {
                    fprintf(out, "%s %s %s %s %s %lf\n", current->surname, current->name, current->OTCHESTVO, current->birthday, current->gender, current->salary);
                }
                else
                {
                    fprintf(out, "%s %s %s %s %lf\n", current->surname, current->name, current->birthday, current->gender, current->salary);
                }
            }
            current = current->next;
        }
    }
    fclose(out);
    free(file_name);
    return st;
}

EXIT_CODE create_liver(Liver** res)
{
    EXIT_CODE st = OK;
    Liver* needed = (Liver*)malloc(sizeof(Liver));
    if (needed == NULL)
    {
        st = BAD_ALLOC;
    }
    char* tmp;
    printf("Enter name of liver\n");
    st = get_str(&tmp);
    if (!st)
    {
        st = check_person(tmp, NAME);
        if (!st)
        {
            strcpy(needed->name, tmp);
        }
        free(tmp);
    }
    if (!st)
    {
        printf("Enter surname of liver\n");
        st = get_str(&tmp);
        if (!st)
        {
            st = check_person(tmp, SURNAME);
            if (!st)
            {
                strcpy(needed->surname, tmp);
            }
            free(tmp);
        }
    }
    if (!st)
    {
        printf("Enter otchestvo of liver if it has it\n");
        st = get_str(&tmp);
        if (!st)
        {
            st = check_person(tmp, OTCHESTVO);
            if (!st)
            {
                strcpy(needed->OTCHESTVO, tmp);
            }
            free(tmp);
        }
    }
    if (!st)
    {
        printf("Enter birth date of liver\n");
        st = get_str(&tmp);
        if (!st)
        {
            st = valid_birthday(tmp);
            if (!st)
            {
                strcpy(needed->birthday, tmp);
            }
            free(tmp);
        }
    }
    if (!st)
    {
        printf("Enter gender of liver\n");
        st = get_str(&tmp);
        if (strlen(tmp) != 1)
        {
            st = INVALID_INPUT;
        }
        if (!st)
        {
            strcpy(needed->gender, tmp);
        }
    }
    if (!st)
    {
        printf("Enter salary of liver\n");
        st = get_str(&tmp);
        if (!st)
        {
            needed->salary = strtod(tmp, NULL);
            needed->flag = 1;
        }
    }
    if (st)
    {
        free(needed);
        return st;
    }
    *res = needed;
    return st;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        return INVALID_INPUT;
    }
    EXIT_CODE st = OK;
    FILE* input = fopen(argv[1], "r");
    if (input == NULL)
    {
        st = FILE_ERROR;
        errors(st);
        return st;
    }
    List livers;
    modifications_list modifications;
    if (!st)
    {
        st = create_modifications_list(&modifications);
    }
    st = null_list(&livers);
    if (!st)
    {
        st = create_list(&livers);
    }
    if (!st)
    {
        st = read_from_file(input, &livers);
    }
    int running = 1;
    while (!st && running)
    {
        char* command = NULL;
        printf("Available commands:\n");
        printf("1) exit\n");
        printf("2) print all\n");
        printf("3) find liver\n");
        printf("4) delete liver\n");
        printf("5) change name\n");
        printf("6) change surname\n");
        printf("7) change birth date\n");
        printf("8) change otchestvo\n");
        printf("9) change gender\n");
        printf("10) change salary\n");
        printf("11) undo\n");
        printf("12) print to file\n");
        printf("Enter command: \n");
        st = get_str(&command);
        if (!st)
        {
            if (!strcmp(command, "1"))
            {
                printf("Program was closed\n");
                running = 0;
            }
            else if (!strcmp(command, "2"))
            {
                print_list(livers);
            }
            else if (!strcmp(command, "3"))
            {
                Liver* res;
                Liver* needed;
                st = create_liver(&needed);
                if (!st)
                {
                    st = search_liver(&livers, needed, &res);
                    if (st != OK)
                    {
                        printf("Liver not found\n");
                    }
                    else
                    {
                        print_liver(res);
                    }
                }
                free(needed);
            }
            else if (!st && !strcmp(command, "4"))
            {
                Liver* current;
                Liver* res;
                st = create_liver(&current);
                if (!st)
                {
                    st = search_liver(&livers, current, &res);
                    if (st != OK)
                    {
                        printf("Liver not found\n");
                    }
                    else
                    {
                        change_liver(res, &modifications, NULL," ", 0, DELETE);
                    }
                    print_list(livers);
                    printf("\n");
                }
                free(current);
            }
            else if (!st && !strcmp(command, "5"))
            {
                Liver* current;
                Liver* res;
                st = create_liver(&current);
                if (!st)
                {
                    st = search_liver(&livers, current, &res);
                    if (st != OK)
                    {
                        printf("Liver not found\n");
                    }
                    else
                    {
                        char* tmp;
                        printf("Enter new name\n");
                        st = get_str(&tmp);
                        if (!st)
                        {
                            st = check_person(tmp, NAME);
                        }
                        if (!st)
                        {
                            change_liver(res, &modifications, tmp," ", 0, NAME);
                        }
                        free(tmp);
                    }
                }
                free(current);
            }
            else if (!st && !strcmp(command, "6"))
            {
                Liver* current;
                Liver* res;
                st = create_liver(&current);
                if (!st)
                {
                    st = search_liver(&livers, current, &res);
                    if (st != OK)
                    {
                        printf("Liver not found\n");
                    }
                    else
                    {
                        char* tmp;
                        printf("Enter new surname\n");
                        st = get_str(&tmp);
                        if (!st)
                        {
                            st = check_person(tmp, SURNAME);
                        }
                        if (!st)
                        {
                            change_liver(res, &modifications, tmp," ", 0, SURNAME);
                        }
                        free(tmp);
                    }
                }
                free(current);
            }
            else if (!st && !strcmp(command, "7"))
            {
                Liver* current;
                Liver* res;
                st = create_liver(&current);
                if (!st)
                {
                    st = search_liver(&livers, current, &res);
                    if (st != OK)
                    {
                        printf("Liver not found\n");
                    }
                    else
                    {
                        char* tmp;
                        printf("Enter new birth date\n");
                        st = get_str(&tmp);
                        if (!st)
                        {
                            st = valid_birthday(tmp);
                        }
                        if (!st)
                        {
                            change_liver(res, &modifications, tmp," ", 0, BIRTH_DAY);
                        }
                        free(tmp);
                    }
                }
                free(current);
            }
            else if (!st && !strcmp(command, "8"))
            {
                Liver* current;
                Liver* res;
                st = create_liver(&current);
                if (!st)
                {
                    st = search_liver(&livers, current, &res);
                    if (st != OK)
                    {
                        printf("Liver not found\n");
                    }
                    else
                    {
                        char* tmp;
                        printf("Enter new otchestvo\n");
                        st = get_str(&tmp);
                        if (!st)
                        {
                            st = check_person(tmp, OTCHESTVO);
                        }
                        if (!st)
                        {
                            change_liver(res, &modifications, tmp," ", 0, OTCHESTVO);
                        }
                        free(tmp);
                    }
                }
                free(current);
            }
            else if (!st && !strcmp(command, "9"))
            {
                Liver* current;
                Liver* res;
                st = create_liver(&current);
                if (!st)
                {
                    st = search_liver(&livers, current, &res);
                    if (st != OK)
                    {
                        printf("Liver not found\n");
                    }
                    else
                    {
                        char* tmp;
                        printf("Enter new gender\n");
                        st = get_str(&tmp);
                        if (!st && strlen(tmp) != 1)
                        {
                            st = INVALID_INPUT;
                        }
                        if (!st)
                        {
                            change_liver(res, &modifications, tmp, tmp, 0, GENDER);
                        }
                        free(tmp);
                    }
                }
                free(current);
            }
            else if (!st && !strcmp(command, "10"))
            {
                Liver* current;
                Liver* res;
                st = create_liver(&current);
                if (!st)
                {
                    st = search_liver(&livers, current, &res);
                    if (st != OK)
                    {
                        printf("Liver not found\n");
                    }
                    else
                    {
                        char* tmp;
                        printf("Enter new salary\n");
                        st = get_str(&tmp);
                        if (!st)
                        {
                            double income = strtod(tmp, NULL);
                            change_liver(res, &modifications, tmp,tmp, income, SALARY);
                        }
                        free(tmp);
                    }
                }
                free(current);
            }
            else if (!st && !strcmp(command, "11"))
            {
                if (modifications.amt_of_modifications > 0)
                {
                    undo(&modifications);
                }
                else
                {
                    printf("Any modifications were not done\n");
                }
            }
            else if (!st && !strcmp(command, "12"))
            {
                st = write_to_file(&livers);
            }
        }
        free(command);
        if (st)
        {
            free(command);
            running = 0;
        }
    }
    if (st)
    {
        errors(st);
    }
    destruct_list(&livers);
    destruct_modifications_list(&modifications);
    fclose(input);
    return st;
}
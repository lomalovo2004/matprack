#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>



typedef enum
{

    OK = 0,
    INVALID,
    NO_FILE,
    BAD_ALLOC,
    NONE,
    APPEND,
    AGRUMENT_ERROR,
    SPACE_ERROR

} EXIT_CODE;



typedef enum
{
    ASSIGN = 0,
    PLUS,
    MINUS,
    MULTIPLICITY,
    DIVISION,
    MODULUS,
    NEXT,
    SKIP,
    END,
    DEFAULT,

} OPERATION;



typedef struct
{

    char* name;
    long long int value;

} memory_cell;




typedef struct
{

    long long int occupied;

    long long int allocated;

    memory_cell** cells;

} memory_vec;



EXIT_CODE cell_constr (memory_cell** dest, char* name, long long int value)
{

    memory_cell* buff = (memory_cell*)malloc(sizeof(memory_cell));

    if (!buff)
    {
        return BAD_ALLOC;
    }

    buff->name = (char*)malloc(sizeof(char) * (strlen(name) + 1));

    if (!(buff->name))
    {

        free(buff);
        
        return BAD_ALLOC;
    
    }

    buff->value = value;

    strcpy(buff->name, name);

    *dest = buff;

    return OK;

}


EXIT_CODE cell_destr (memory_cell** dest)
{

    free((*dest)->name);
    (*dest)->name = NULL;

    (*dest)->value = 0;

    free(*dest);

    return OK;

}



EXIT_CODE vec_init (memory_vec** dest)
{

    (*dest)->occupied = 0;

    (*dest)->allocated = 0;
    
    (*dest)->cells = NULL;

    return OK;

}


int lex_cmp (const void* v1, const void* v2)
{

    memory_cell** c1 = (memory_cell**)v1;
    memory_cell** c2 = (memory_cell**)v2;

    return (strcmp((*c1)->name, (*c2)->name));


}


EXIT_CODE vec_append (memory_vec* dest, memory_cell* to_add)
{

    if (dest->occupied == dest->allocated)
    {

        dest->allocated += 1;
        dest->allocated *= 2;       

        memory_cell** temp = (memory_cell**)realloc(dest->cells, sizeof(memory_cell*) * (dest->allocated));

        if (!temp)
        {
            return BAD_ALLOC;
        }

        dest->cells = temp;

    }

    *((dest->cells) + dest->occupied) = to_add;

    dest->occupied++;

    qsort(dest->cells, dest->occupied, sizeof(memory_cell*), lex_cmp);

    return OK;

}



EXIT_CODE vec_display (memory_vec* src)
{

    if (!src->occupied)
    {
        return OK;
    }

    memory_cell** crawler = src->cells;

    for (int i = 0; i < src->occupied; i++)
    {

        printf("%s = %lld\n", (*crawler)->name, (*crawler)->value);

        crawler++;

    }

    return OK;

}


EXIT_CODE vec_destr (memory_vec** dest)
{

    memory_cell** crawler = (*dest)->cells;

    while (((*dest)->occupied)--)
    {

        cell_destr(&(*crawler));

        crawler++;

    }

    (*dest)->allocated = 0;

    return OK;
}


EXIT_CODE file_handle (char* src, FILE** dest)
{

    FILE* buff = fopen(src, "r");

    if (!buff)
    {
        return NO_FILE;
    }

    *dest = buff;

    return OK;

}


OPERATION op_handle (char c)
{

    switch (c)
    {

        case ';':
            return NEXT;

        case ' ':
            return SKIP;

        case '=':
            return ASSIGN;

        case '+':
            return PLUS;

        case '-':
            return MINUS;

        case '*':
            return MULTIPLICITY;

        case '/':
            return DIVISION;

        case '%':
            return MODULUS;
        
        default:
            return DEFAULT;

    }

}


EXIT_CODE get_variable (char** dest, FILE* src, char* c)
{

    char* buff = (char*)malloc(sizeof(char));

    if (!buff)
    {
        return BAD_ALLOC;
    }

    buff[0] = '\0';

    int amount = 0;

    while ((op_handle(*c = fgetc(src)) == DEFAULT) && (*c > 0))
    {

        if (amount == strlen(buff))
        {
            char* temp = (char*)realloc(buff, sizeof(char) * ((amount + 1) * 2));

            if (!temp)
            {
                return BAD_ALLOC;
            }

            buff = temp;

        }

        buff[amount] = *c;
        buff[++amount] = '\0';

    }

    *dest = buff;

    return OK;

}


EXIT_CODE is_num(char* name, long long int* dest)
{

    char* end_ptr;

    *dest = strtol(name, &end_ptr, 10);

    return (end_ptr == name + strlen(name)) ? OK : INVALID;


}


EXIT_CODE dichotomy_take (memory_vec* base, long long int* dest, char* name)
{

    if (!(base->occupied))
    {
        return INVALID;
    }

    long long int left = 0;
    long long int right = base->occupied;

    long long int mid = 0;

    do
    {

        mid = (left + right) / 2;

        if (!strcmp((base->cells[mid]->name), name))
        {

            *dest = base->cells[mid]->value;
            return OK;

        }

        if (strcmp((base->cells[mid]->name), name) < 0)
        {
            left = mid;
        }

        else 
        {
            right = mid;
        }

    } while (left < right);

    return INVALID;

}



EXIT_CODE identify_var (char* str, long long int* dest, memory_vec* base)
{

    if (!str)
    {
        return OK;
    }

    if (!is_num(str, dest))
    {
        return OK;
    }

    else 
    {
        if (dichotomy_take(base, dest, str) == INVALID)
        {
            return INVALID;
        }

        return OK;
    }

}


EXIT_CODE delete_op (OPERATION op, long long int v1, long long int v2, long long int* res)
{

    if (op == ASSIGN || op == NEXT)
    {
        *res = v1;

        return OK;
    }

    switch (op)
    {
        
        case PLUS:

            *res = v1 + v2;
            break;

        case MINUS:

            *res = v1 - v2;
            break;

        case MULTIPLICITY:

            *res = v1 * v2;
            break;

        case DIVISION:

            if (!v2)
            {
                return INVALID;
            }

            *res = v1 / v2;
            break;

        case MODULUS:

            if (!v2)
            {
                return INVALID;
            }

            *res = v1 % v2;
            break;

        default:
            break;
    }

    return OK;

}



EXIT_CODE fill_instr(long long int* value, FILE* src, char* c, memory_vec* base)
{

    long long int var1 = 0;
    long long int var2 = 0;
    OPERATION op = ASSIGN;

    char* v1 = NULL;
    
    get_variable(&v1, src, c);

    EXIT_CODE assist = identify_var(v1, &var1, base);

    op = op_handle(*c);

    free(v1);

    if (op != NEXT)
    {

        get_variable(&v1, src, c);

        assist = identify_var(v1, &var2, base);

        free(v1);

    }

    return delete_op(op, var1, var2, value);

}


EXIT_CODE fill_print(FILE* src, char* c, memory_vec* base)
{

    char* name = NULL;

    long long int value = 0;

    get_variable(&name, src, c);

    if (dichotomy_take(base, &value, name) == INVALID)
    {
        return INVALID;
    }

    printf("%s = %lld\n\n", name, value);

    free(name);

    return OK;

}


EXIT_CODE check_op (long long int* value, FILE* in, char* c, memory_vec* base)
{

    switch(op_handle(*c))
    {

        case ASSIGN:
            return fill_instr(value, in, c, base);

        case SKIP:
            return fill_print(in, c, base);

        case NEXT:
            return vec_display(base);
        //
        case MINUS:
            return OK;
        case MULTIPLICITY:
            return OK;
        case DIVISION:
            return OK;
        case MODULUS:
            return OK;
        case PLUS:
            return OK;
        default:
            return OK;
        //
    }

    return OK;
}


EXIT_CODE dichotomy_rewrite (memory_vec* base, long long int value, char* name)
{


    if (!(base->occupied))
    {
        return NONE;
    }

    long long int left = 0;
    long long int right = base->occupied;

    long long int mid = 0;

    do
    {

        mid = ((left + right) / 2);

        if (!strcmp((base->cells[mid]->name), name))
        {

            base->cells[mid]->value = value;
            return OK;

        }

        if (strcmp((base->cells[mid]->name), name) < 0)
        {
            left = mid;
        }

        else 
        {
            right = mid;
        }

    } while (left < right && mid != ((left + right) / 2));

    return NONE;

}


EXIT_CODE get_cell (memory_cell** dest, memory_vec* base, FILE* src, char* c)
{

    char* name = NULL;

    long long int value = 0;

    get_variable(&name, src, c);

    OPERATION op = op_handle(*c);

    if (check_op(&value, src, c, base) == INVALID)
    {
        return INVALID;
    }

    *c = fgetc(src);

    if (op != NEXT && op != SKIP && dichotomy_rewrite(base, value, name) == NONE)
    {

        cell_constr(dest, name, value);

        free(name);

        return APPEND;

    }

    free(name);

    return OK;

}


EXIT_CODE fill_vec (memory_vec* dest, FILE* src)
{

    char c = 1;

    EXIT_CODE assist;

    while (c > 0)
    {

        memory_cell* unit = NULL;

        assist = get_cell(&unit, dest, src, &c);

        switch(assist)
        {

            case APPEND:

                vec_append(dest, unit);
                break;

            case INVALID:

                return INVALID;
                break;

            default:
                break;
                
        }

    }

    return OK;

}


EXIT_CODE memory_hub (FILE* src)
{

    memory_vec* memory = (memory_vec*)malloc(sizeof(memory_vec));

    if (!memory)
    {
        return BAD_ALLOC;
    }

    vec_init(&memory);

    EXIT_CODE assist = fill_vec(memory, src);

    vec_destr(&memory);

    return assist;

}


EXIT_CODE data_handle (char* filename)
{

    FILE* in = NULL;

    EXIT_CODE assist = file_handle(filename, &in);

    if (assist)
    {
        return assist;
    }

    assist = memory_hub(in);

    fclose(in);

    return assist;

}


EXIT_CODE input_handle (int argc, char** argv)
{

    if (argc != 2)
    {
        return AGRUMENT_ERROR;
    }

    return data_handle(*(argv + 1));

}



int main (int argc, char** argv)
{

    switch(input_handle(argc, argv))
    {

        case OK:

            break;

        case INVALID:

            printf("Some variable is not defined\n");
            break;

        case AGRUMENT_ERROR:
        
            printf("Use: ./lab37.c lab37_input.txt\n");
            break;

        default:
            printf("Error\n");

    }

    return 0;

}
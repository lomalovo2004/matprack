#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef enum
{
    OK,
    INVALID_ARGUMENTS,
    BAD_ALLOC,
    NULL_POINTER,
    OPENING_ERROR
} EXIT_CODE;


void errors_list(EXIT_CODE error)
{
    switch (error)
    {
        case OK:
            return;
        case INVALID_ARGUMENTS:
            printf("Use: ./lab10 lab30_input.txt lab30_output.txt\n");
            return;
        case BAD_ALLOC:
            printf("Memmory does not allocated\n");
            return;
        case NULL_POINTER:
            printf("NULL pointer error\n");
            return;
        case OPENING_ERROR:
            printf("Error opening file\n");
            return;
        default:
            printf("Unknown error\n");
            return;
    }
}

typedef struct Node
{
    char key;
    struct Node* child;
    struct Node* brother;
    struct Node* parent;
} Node;


typedef struct tree
{
    Node* root;
} tree;


EXIT_CODE destroy_tree(Node* node)
{
    if (node == NULL)
    {
        return OK;
    }
    destroy_tree(node->child);
    destroy_tree(node->brother);
    free(node);
    return OK;
}


EXIT_CODE insert_child(Node* node, char data)
{
    Node* new = (Node*)malloc(sizeof(Node));
    if (new == NULL)
    {
        return BAD_ALLOC;
    }
    new->key = data;
    new->parent = node;
    new->brother = NULL;
    new->child = NULL;
    node->child = new;
    return OK;
}


EXIT_CODE insert_brother(Node* node, char data)
{
    Node* new = (Node*)malloc(sizeof(Node));
    if (new == NULL)
    {
        return BAD_ALLOC;
    }
    new->key = data;
    new->parent = node->parent;
    new->child = NULL;
    node->brother = new;
    new->brother = NULL;
    return OK;
}


EXIT_CODE create_tree(tree* tree, char* exp)
{
    size_t length = strlen(exp);
    char symb;
    Node* root = (Node*)malloc(sizeof(Node));
    if (root == NULL)
    {
        return BAD_ALLOC;
    }
    int i = 0;
    root->key = exp[i];
    root->child = NULL;
    root->brother = NULL;
    root->parent = NULL;
    tree->root = root;
    i++;
    EXIT_CODE insert;
    Node* current = tree->root;
    for ( ; i < length; ++i)
    {
        symb = exp[i];
        switch (symb)
        {
            case '(':
                i++;
                insert = insert_child(current, exp[i]);
                if (insert == BAD_ALLOC)
                {
                    return BAD_ALLOC;
                }
                current = current->child;
                break;
            case ')':
                current = current->parent;
                break;
            case ',':
                i++;
                insert = insert_brother(current, exp[i]);
                if (insert == BAD_ALLOC)
                {
                    return BAD_ALLOC;
                }
                current = current->brother;
                break;
            default:
                break;
        }    
    }
    return OK;
}


EXIT_CODE print_node(FILE* file, Node* node, int depth)
{
    if (node == NULL)
    {
        return OK;
    }
    if (node->brother)
    {
        print_node(file, node->brother, depth);
    }
    
    for (int i = 0; i < depth; ++i)
    {
        if (i == depth-1)
        {
            fprintf(file, "\\___");
        }
        else
        {
            fprintf(file, "|   ");
        }
    }
    fprintf(file, "%c    \n", node->key);

    if (node->child)
    {
        print_node(file, node->child, depth + 1);
    }

    return OK;
}



EXIT_CODE print_tree(FILE* file, tree* tree, char* exp)
{
    int depth = 0;
    fprintf(file, "Expression: %sTree:\n", exp);
    print_node(file, tree->root, depth);
    fprintf(file, "\n");
    return OK;
}



EXIT_CODE processing(FILE* input, FILE* output)
{
    if (input == NULL || output == NULL)
    {
        return NULL_POINTER;
    }
    tree root;
    root.root = NULL;
    EXIT_CODE create;
    char* exp = NULL;
    int read;
    size_t len = 0;


    while ((read = getline(&exp, &len, input)) != -1)
    {
        if (read == -1)
        {
            free(exp);
            return BAD_ALLOC;
        }
        create = create_tree(&root, exp);
        if (create == BAD_ALLOC)
        {
            free(exp);
            return BAD_ALLOC;
        }
        print_tree(output, &root, exp);
        free(exp);
        destroy_tree(root.root);
        exp = NULL;
        root.root = NULL;
    }
    free(exp);
    return OK;
}

int main(int argc, char* argv[])
{
    if (argc < 3)
    {
        errors_list(INVALID_ARGUMENTS);
        return INVALID_ARGUMENTS;
    }
    const char* filename_in = argv[1];
    const char* filename_out = argv[2];
    FILE* input;
    FILE* output;
    if ((input = fopen(filename_in, "r")) == NULL)
    {
        errors_list(OPENING_ERROR);
        return OPENING_ERROR;
    }
    if ((output = fopen(filename_out, "w")) == NULL)
    {
        errors_list(OPENING_ERROR);
        return OPENING_ERROR;
    }
    EXIT_CODE error = processing(input, output);
    if (error != OK)
    {
        errors_list(error);
        return error;
    }
    printf("Programm completed\n");
    fclose(input);
    fclose(output);
    return OK;
}

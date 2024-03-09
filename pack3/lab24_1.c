#include <stdio.h>//сделать проверку на уникальный id
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <ctype.h>
#include <time.h>


typedef enum
{
    OK,
    BAD_ALLOC,
    NULL_POINTER,
    INVALID_INPUT,
    INVALID,
    SAME_MAIL_ID,
    SAME_IDX
} EXIT_CODE;


typedef struct String
{
    char* str;
    int size;
} String;


typedef struct Address
{
    String city;
    String street;
    unsigned building_number;
    String building;
    unsigned apart_number;
    String idx;
} Address;


typedef struct Mail
{
    Address user;
    double weight;
    String post_id;
    String date_of_creation;
    String estimated_date_of_sent;
    String is_sent;
} Mail;


typedef struct Post
{
    int max_size;
    int tmp_size;
    Address post_building;
    Mail* mails;
} Post;


void errors(EXIT_CODE EXIT_CODE)
{
    switch (EXIT_CODE)
    {
        case OK:
            return;
        case BAD_ALLOC:
            printf("Memmory does not allocated\n");
            return;
        case NULL_POINTER:
            printf("NULL pointer error\n");
            return;
        case INVALID_INPUT:
            printf("Invalid input\n");
            return;
        case SAME_MAIL_ID:
            printf("This mail id has been already used\n");
            return;
        case SAME_IDX:
            printf("This idx has been already used\n");
            return;
            
        default:
            printf("Unknow error\n");
            return;
    }
}


EXIT_CODE create_string(char* s, String* result)
{
    if (s == NULL)
    {
        result->size = 0;
        result->str = NULL;
        return OK;
    }
    int length = (int)strlen(s);
    result->str = (char*)malloc(sizeof(char) * (length + 1));
    if (result->str == NULL)
    {
        return BAD_ALLOC;
    }
    result->str[length] = '\0';
    for (int i = 0; i < length; ++i)
    {
        result->str[i] = s[i];
    }
    result->size = length;
    return OK;
}


EXIT_CODE delete_string(String* string)
{
    if (string->str == NULL)
    {
        return NULL_POINTER;
    }
    free(string->str);
    string->str = NULL;
    string->size = 0;
    return OK;
}


int string_compare_in_order(String str1, String str2)
{
    if (str1.str == NULL || str2.str == NULL)
    {
        return NULL_POINTER;
    }
    int length_1 = str1.size;
    int length_2 = str2.size;
    int min = length_1;
    if (length_1 > length_2)
    {
        min = length_2;
    }
    for (int i = 0; i < min; ++i)
    {
        if (str1.str[i] != str2.str[i])
        {
            return str1.str[i] < str2.str[i] ? -1 : 1;
        }
    }
    return 0;
}


int compare_strings(String str1, String str2)
{
    if (str1.str == NULL || str2.str == NULL)
    {
        return NULL_POINTER;
    }
    int length_1 = str1.size;
    int length_2 = str2.size;
    if (length_2 != length_1)
    {
        return 0;
    }
    return string_compare_in_order(str1, str2) == 0;
}


EXIT_CODE string_copy(String* dest, String* src)
{
    if (src->str == NULL || dest->str == NULL)
    {
        return NULL_POINTER;
    }
    int length_1 = dest->size;
    int length_2 = src->size;

    for (int i = 0; i < length_2; ++i)
    {
        if (i == length_1)
        {
            break;
        }
        dest->str[i] = src->str[i];
    }
    dest->str[length_2] = '\0';
    return OK;
}


EXIT_CODE string_copy_in_new_one(String* dest, String* source)
{
    create_string(source->str, dest);
    return OK;
}


EXIT_CODE string_concatenation(String* str1, String* str2)
{
    int length = str1->size + str2->size;
    for (int i = 0; i < length; ++i)
    {
        str1->str[str1->size + i] = str2->str[i];
    }
    str1->size = length;
    return OK;
}


void free_all(int cnt, ...)
{
    va_list ptr;
    va_start(ptr, cnt);
    for (int i = 0; i < cnt; ++i)
    {
        void* tmp = va_arg(ptr, void*);
        free(tmp);
    }
    va_end(ptr);
}


void free_address(Address tmp)
{
    delete_string(&(tmp.idx));
    delete_string(&(tmp.street));
    delete_string(&(tmp.building));
    delete_string(&(tmp.city));
}


void free_mail(Mail* tmp)
{
    free_address(tmp->user);
    delete_string(&(tmp->estimated_date_of_sent));
    delete_string(&(tmp->date_of_creation));
    delete_string(&(tmp->post_id));
    delete_string(&(tmp->is_sent));
}


void free_post(Mail* mails, int* size)
{
    for (int i = 0; i < *size; ++i)
    {
        free_mail(&mails[i]);
    }
    *size = 0;
}


EXIT_CODE is_uint(char* str)
{
    if (str == NULL)
    {
        return INVALID_INPUT;
    }
    int length = (int)strlen(str);
    for (int i = 0; i < length; ++i)
    {
        if (!isdigit(str[i]))
        {
            return INVALID_INPUT;
        }
    }
    return OK;
}


EXIT_CODE is_udouble(char* str)
{
    if (str == NULL)
    {
        return INVALID_INPUT;
    }
    int length = (int) strlen(str);
    int dots = 0;
    for (int i = 0; i < length; ++i)
    {
        char c = str[i];
        if (!isdigit(c))
        {
            if (c != '.')
            {
                return INVALID_INPUT;
            }
            dots++;
        }
    }
    if (dots > 1)
    {
        return INVALID_INPUT;
    }
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
        if (temp_size + 1 == max_size)
        {
            max_size *= 2;

            if (realloc(str, max_size + 1) != OK)
            {
                free(*str);
                return BAD_ALLOC;
            }
        }
        (*str)[temp_size] = c;
        temp_size++;
    }
    (*str)[temp_size] = '\0';
    return OK;
}


EXIT_CODE create_post(Post* post, const Address address)
{
    if (post == NULL)
    {
        return NULL_POINTER;
    }

    post->post_building = address;
    post->tmp_size = 0;
    post->max_size = 10;
    post->mails = (Mail*)malloc(sizeof(Mail) * 10);
    if (post->mails == NULL)
    {
        post->max_size = 0;
        return BAD_ALLOC;
    }
    return OK;
}


EXIT_CODE create_post_address(Address* address)
{
    String city;
    String street;
    String building;
    String idx;
    EXIT_CODE st = create_string(NULL, &city);
    if (st != OK)
    {
        return st;
    }
    st = create_string(NULL, &street);
    if (st != OK)
    {
        return st;
    }
    st = create_string(NULL, &building);
    if (st != OK)
    {
        return st;
    }
    st = create_string(NULL, &idx);
    if (st != OK)
    {
        return st;
    }
    address->idx = idx;
    address->building = building;
    address->street = street;
    address->city = city;
    address->apart_number = 0;
    address->building_number = 0;
    return OK;
}


EXIT_CODE delete_address(Address* address)
{
    if (address == NULL)
    {
        return NULL_POINTER;
    }
    delete_string(&(address->city));
    delete_string(&(address->street));
    delete_string(&(address->building));
    delete_string(&(address->idx));
    address->apart_number = 0;
    address->building_number = 0;
    return OK;
}


EXIT_CODE delete_post(Post* post)
{
    if (post == NULL)
    {
        return NULL_POINTER;
    }
    for (int i = 0; i < post->tmp_size; ++i)
    {
        free_mail(&(post->mails[i]));
    }
    free(post->mails);
    delete_address(&(post->post_building));
    return OK;
}


EXIT_CODE create_info(Mail* mail)
{
    char *city = NULL, *street = NULL, *building_number = NULL, *building = NULL, *apart_number = NULL, *weight = NULL, *idx = NULL, *post_id = NULL;
    printf("Enter the mail info\n");
    printf("City: ");
    EXIT_CODE EXIT_CODE;
    EXIT_CODE = get_str(&city);
    if (EXIT_CODE != OK)
    {
        free_all(8, city, street, building, idx, post_id, building_number, apart_number, weight);
        return EXIT_CODE;
    }
    if (strlen(city) == 0)
    {
        free_all(8, city, street, building, idx, post_id, building_number, apart_number, weight);
        return INVALID_INPUT;
    }
    printf("Street: ");
    EXIT_CODE = get_str(&street);
    if (EXIT_CODE != OK)
    {
        free_all(8, city, street, building, idx, post_id, building_number, apart_number, weight);
        return EXIT_CODE;
    }
    if (strlen(street) == 0)
    {
        free_all(8, city, street, building, idx, post_id, building_number, apart_number, weight);
        return INVALID_INPUT;
    }
    printf("Building number: ");
    EXIT_CODE = get_str(&building_number);
    if (EXIT_CODE != OK)
    {
        free_all(8, city, street, building, idx, post_id, building_number, apart_number, weight);
        return EXIT_CODE;
    }
    if (strlen(building_number) == 0 || building_number[0] == '0')
    {
        free_all(8, city, street, building, idx, post_id, building_number, apart_number, weight);
        return INVALID_INPUT;
    }
    if (is_uint(building_number) != OK)
    {
        free_all(8, city, street, building, idx, post_id, building_number, apart_number, weight);
        return INVALID_INPUT;
    }
    printf("Building: ");
    EXIT_CODE = get_str(&building);
    if (EXIT_CODE != OK)
    {
        free_all(8, city, street, building, idx, post_id, building_number, apart_number, weight);
        return EXIT_CODE;
    }
    printf("Apartments number: ");
    EXIT_CODE = get_str(&apart_number);
    if (EXIT_CODE != OK)
    {
        free_all(8, city, street, building, idx, post_id, building_number, apart_number, weight);
        return BAD_ALLOC;
    }
    if (apart_number[0] == '0' || strlen(apart_number) == 0)
    {
        free_all(8, city, street, building, idx, post_id, building_number, apart_number, weight);
        return INVALID_INPUT;
    }
    if (is_uint(apart_number) != OK)
    {
        free_all(8, city, street, building, idx, post_id, building_number, apart_number, weight);
        return INVALID_INPUT;
    }
    printf("Recipient idx(6 symbols): ");
    EXIT_CODE = get_str(&idx);
    if (EXIT_CODE != OK)
    {
        free_all(8, city, street, building, idx, post_id, building_number, apart_number, weight);
        return EXIT_CODE;
    }
    if (is_uint(idx) != OK)
    {
        free_all(8, city, street, building, idx, post_id, building_number, apart_number, weight);
        return INVALID_INPUT;
    }
    if (strlen(idx) != 6)
    {
        free_all(8, city, street, building, idx, post_id, building_number, apart_number, weight);
        return INVALID_INPUT;
    }
    printf("Weight: ");
    EXIT_CODE = get_str(&weight);
    if (EXIT_CODE != OK)
    {
        free_all(8, city, street, building, idx, post_id, building_number, apart_number, weight);
        return EXIT_CODE;
    }
    if (is_udouble(weight) != OK)
    {
        free_all(8, city, street, building, idx, post_id, building_number, apart_number, weight);
        return INVALID_INPUT;
    }
    printf("Mail id(14 symbols): ");
    EXIT_CODE = get_str(&post_id);
    if (EXIT_CODE != OK)
    {
        free_all(8, city, street, building, idx, post_id, building_number, apart_number, weight);
        return EXIT_CODE;
    }
    if ((is_uint(post_id) != OK) || (strlen(post_id) != 14))
    {
        free_all(8, city, street, building, idx, post_id, building_number, apart_number, weight);
        return INVALID_INPUT;
    }
    time_t timer = time(NULL);
    struct tm *tmp_time = localtime(&timer);
    char* time_field = (char*)malloc(sizeof(char) * 20);
    if (time_field == NULL)
    {
        free_all(8, city, street, building, idx, post_id, building_number, apart_number, weight);
        return BAD_ALLOC;
    }
    char* est_time = (char*)malloc(sizeof(char) * 20);
    if (est_time == NULL)
    {
        free_all(8, city, street, building, idx, post_id, building_number, apart_number, weight);
        return BAD_ALLOC;
    }

    sprintf(time_field, "%02d:%02d:%04d %02d:%02d:%02d",
            tmp_time->tm_mday, tmp_time->tm_mon + 1, tmp_time->tm_year + 1900,
            tmp_time->tm_hour, tmp_time->tm_min, tmp_time->tm_sec);

    sprintf(est_time, "%02d:%02d:%04d %02d:%02d:%02d",
            tmp_time->tm_mday, tmp_time->tm_mon + 1, tmp_time->tm_year + 1900,
            tmp_time->tm_hour, tmp_time->tm_min + 1, tmp_time->tm_sec);

    EXIT_CODE = create_string(city, &(mail->user.city));

    if (EXIT_CODE != OK)
    {
        free_all(9, city, street, building, idx, post_id, building_number, apart_number, weight, time_field);
        return EXIT_CODE;
    }

    EXIT_CODE = create_string(street, &(mail->user.street));
    {
        if (EXIT_CODE != OK)
        {
            free_all(9, city, street, building, idx, post_id, building_number, apart_number, weight, time_field);
            return EXIT_CODE;
        }
    }

    mail->user.building_number = atoi(building_number);

    EXIT_CODE = create_string(building, &(mail->user.building));
    {
        if (EXIT_CODE != OK)
        {
            free_all(9, city, street, building, idx, post_id, building_number, apart_number, weight, time_field);
            return EXIT_CODE;
        }
    }

    mail->user.apart_number = atoi(apart_number);

    EXIT_CODE = create_string(idx, &(mail->user.idx));
    {
        if (EXIT_CODE != OK)
        {
            free_all(9, city, street, building, idx, post_id, building_number, apart_number, weight, time_field);
            return EXIT_CODE;
        }
    }

    mail->weight = atof(weight);

    EXIT_CODE = create_string(post_id, &(mail->post_id));
    {
        if (EXIT_CODE != OK)
        {
            free_all(9, city, street, building, idx, post_id, building_number, apart_number, weight, time_field);
            return EXIT_CODE;
        }
    }

    EXIT_CODE = create_string(time_field, &(mail->date_of_creation));
    {
        if (EXIT_CODE != OK)
        {
            free_all(9, city, street, building, idx, post_id, building_number, apart_number, weight, time_field);
            return EXIT_CODE;
        }
    }

    EXIT_CODE = create_string(est_time, &(mail->estimated_date_of_sent));
    {
        if (EXIT_CODE != OK)
        {
            free_all(9, city, street, building, idx, post_id, building_number, apart_number, weight, time_field);
            return EXIT_CODE;
        }
    }

    EXIT_CODE = create_string("No", &(mail->is_sent));
    {
        if (EXIT_CODE != OK)
        {
            free_all(9, city, street, building, idx, post_id, building_number, apart_number, weight, time_field);
            return EXIT_CODE;
        }
    }

    free_all(10, city, street, building, idx, post_id, building_number, apart_number, weight, time_field, est_time);
    return OK;
}


EXIT_CODE compare(Mail mail1, Mail mail2)
{
    if (!compare_strings(mail1.user.idx, mail2.user.idx))
    {
        return string_compare_in_order(mail1.user.idx, mail2.user.idx);
    }

    return string_compare_in_order(mail1.post_id, mail2.post_id);
}


EXIT_CODE check_for_duplicates(Mail* mails, int tmp_amount, Mail* new_mail)
{
    for (int i =   0; i < tmp_amount; ++i)
    {
        /* idx
        if (compare_strings(mails[i].user.idx, new_mail->user.idx) ==   1)
        {
            return SAME_IDX;
        }
        */
        // 
        if (compare_strings(mails[i].post_id, new_mail->post_id) ==   1)
        {
            return SAME_MAIL_ID;
        }
        //
    }

    return OK;
}


EXIT_CODE create_mail(Mail** mails, int* tmp_amount, int* max_amount)
{
    Mail mail;
    EXIT_CODE EXIT_CODE = create_info(&mail);
    if (EXIT_CODE != OK)
    {
        return EXIT_CODE;
    }
//
    EXIT_CODE = check_for_duplicates(*mails, *tmp_amount, &mail);
    if (EXIT_CODE != OK)
    {
        free_mail(&mail);
        return EXIT_CODE;
    }
//

    if (*tmp_amount - 1 == *max_amount)
    {
        *max_amount *= 2;
        
        if (realloc(mails, *max_amount + 1) != OK)
        {
            free_mail(&mail);
            return BAD_ALLOC;
        }
    }
    if (*tmp_amount == 0)
    {
        (*mails)[*tmp_amount] = mail;
        (*tmp_amount)++;
        return OK;
    }
    int idx = 0;
    int k = compare(mail, (*mails)[idx]);
    while ((k > 0) && (idx < *tmp_amount))
    {
        k = compare(mail, (*mails)[idx]);
        if (k == -1)
        {
            break;
        }
        idx++;
    }
    for (int i = *tmp_amount - 1; i >= idx; --i)
    {
        (*mails)[i+1] = (*mails)[i];
    }
    (*mails)[idx] = mail;
    (*tmp_amount)++;
    return OK;
}


EXIT_CODE print_mail(Mail* mail)
{
    printf("Mail id: %s\n", mail->post_id.str);
    printf("Address of user:\n");
    printf("City: %s\n", mail->user.city.str);
    printf("Street: %s\n", mail->user.street.str);
    printf("Building number: %u\n", mail->user.building_number);
    printf("Building: %s\n", mail->user.building.str);
    printf("Apartment number: %u\n", mail->user.apart_number);
    printf("User's post idx: %s\n", mail->user.idx.str);
    printf("Weight of mail: %.4f\n", mail->weight);
    printf("Creation time: %s\n", mail->date_of_creation.str);
    printf("Estimated receiving time: %s\n", mail->estimated_date_of_sent.str);
    printf("Mail is sent: %s\n\n", mail->is_sent.str);
    return OK;
}


EXIT_CODE find_mail(Mail** mails, int tmp_amount, String id, int* idx)
{
    for (int i = 0; i < tmp_amount; ++i)
    {
        Mail mail = (*mails)[i];
        String tmp = mail.post_id;
        if (string_compare_in_order(id, tmp) == 0)
        {
            *idx = i;
            return OK;
        }
    }
    return INVALID_INPUT;
}


EXIT_CODE delete_mail(Mail** mails, int* tmp_amount)
{
    printf("Enter the mail id you want to delete\n");
    String mail_id;
    int idx = 0;
    char* m_id = NULL;
    EXIT_CODE EXIT_CODE = get_str(&m_id);
    if (EXIT_CODE != OK)
    {
        return EXIT_CODE;
    }
    EXIT_CODE = create_string(m_id, &mail_id);
    if (EXIT_CODE != OK)
    {
        free(m_id);
        return EXIT_CODE;
    }
    EXIT_CODE = find_mail(mails, *tmp_amount, mail_id, &idx);
    if (EXIT_CODE != OK)
    {
        free(m_id);
        delete_string(&mail_id);
        return EXIT_CODE;
    }
    free_mail(mails[idx]);
    (*tmp_amount)--;
    for (int i = idx; i < *tmp_amount; ++i)
    {
        (*mails)[i] = (*mails)[i+1];
    }
    free(m_id);
    delete_string(&mail_id);
    return OK;
}


EXIT_CODE searching(Mail** mails, int tmp_amount)
{
    printf("Enter mail id you want to find\n");
    char* id;
    int idx = 0;
    String mail_id;
    EXIT_CODE EXIT_CODE = (get_str(&id));
    if (EXIT_CODE != OK)
    {
        return EXIT_CODE;
    }
    EXIT_CODE = create_string(id, &mail_id);
    if (EXIT_CODE != OK)
    {
        free(id);
        return EXIT_CODE;
    }
    if (find_mail(mails, tmp_amount, mail_id, &idx) != OK)
    {
        free(id);
        delete_string(&mail_id);
        return EXIT_CODE;
    }
    print_mail(&(*mails)[idx]);
    free(id);
    delete_string(&mail_id);
    return OK;
}


EXIT_CODE is_sent(Mail** mails, int tmp_amount)
{
    printf("Enter mail id that is sent\n");
    char* id;
    String mail_id;
    int idx = 0;
    EXIT_CODE EXIT_CODE = (get_str(&id));
    if (EXIT_CODE != OK)
    {
        return EXIT_CODE;
    }
    EXIT_CODE = create_string(id, &mail_id);
    if (EXIT_CODE != OK)
    {
        free(id);
        return EXIT_CODE;
    }
    if (find_mail(mails, tmp_amount, mail_id, &idx) != OK)
    {
        free(id);
        delete_string(&mail_id);
        return EXIT_CODE;
    }
    delete_string(&((*mails)[idx].is_sent));
    EXIT_CODE = create_string("Yes", &((*mails)[idx].is_sent));
    if (EXIT_CODE != OK)
    {
        free(id);
        delete_string(&mail_id);
        return EXIT_CODE;
    }
    free(id);
    delete_string(&mail_id);
    return OK;
}


int compare_mails(const void* a, const void* b)
{
    String str1 = ((Mail*)a)->date_of_creation;
    String str2 = ((Mail*)b)->date_of_creation;
    for (int i = 0; i < 4; ++i)
    {
        if (str1.str[i + 6] != str2.str[i + 6])
        {
            return str1.str[i + 6] < str2.str[i + 6] ? 1 : -1;
        }
    }
    for (int i = 0; i < 2; ++i)
    {
        if (str1.str[i+3] != str2.str[i+3])
        {
            return str1.str[i + 3] < str2.str[i + 3] ? 1 : -1;
        }
    }
    return string_compare_in_order(str1, str2);
}


int compare_time(String *a, String* b)
{
    for (int i = 0; i < 4; ++i)
    {
        if (a->str[i + 6] != b->str[i + 6])
        {
            return a->str[i + 6] < b->str[i + 6] ? -1 : 1;
        }
    }
    for (int i = 0; i < 2; ++i)
    {
        if (a->str[i+3] != b->str[i+3])
        {
            return a->str[i + 3] < b->str[i + 3] ? -1 : 1;
        }
    }
    return string_compare_in_order(*a, *b);
}


EXIT_CODE sort_mails(Mail** mails, int amount)
{
    qsort(*mails, amount, sizeof(String), compare_mails);
    return OK;
}


EXIT_CODE view_all_mails(Mail* mails, int tmp_size)
{
    for (int i = 0; i < tmp_size; ++i)
    {
        print_mail(&(mails[i]));
    }
    return OK;
}


EXIT_CODE view_sent_mails(Mail* mails, int tmp_size)
{
    int amount_of_sent = 0;
    String is_sent;
    EXIT_CODE EXIT_CODE = create_string("Yes", &is_sent);
    if (EXIT_CODE != OK)
    {
        return EXIT_CODE;
    }
    Mail* sent_mails = (Mail*)malloc(sizeof(*mails) * tmp_size);
    if (sent_mails == NULL)
    {
        delete_string(&is_sent);
        return BAD_ALLOC;
    }
    for (int i = 0; i < tmp_size; ++i)
    {
        Mail tmp = mails[i];
        if (string_compare_in_order(tmp.is_sent, is_sent) == 0)
        {
            sent_mails[amount_of_sent] = mails[i];
            amount_of_sent++;
        }
    }
    sort_mails(&sent_mails, amount_of_sent);
    view_all_mails(sent_mails, amount_of_sent);
    delete_string(&is_sent);
    free(sent_mails);
    return OK;
}


EXIT_CODE view_unsent_mails(Mail* mails, int tmp_size)
{
    int amount_of_sent = 0;
    char* current_time = (char*)malloc(sizeof(char) * 20);
    if (current_time == NULL)
    {
        return BAD_ALLOC;
    }
    time_t timer = time(NULL);
    struct tm *tmp_time = localtime(&timer);
    sprintf(current_time, "%02d:%02d:%04d %02d:%02d:%02d",
            tmp_time->tm_mday, tmp_time->tm_mon + 1, tmp_time->tm_year + 1900,
            tmp_time->tm_hour, tmp_time->tm_min, tmp_time->tm_sec);
    String is_sent;
    EXIT_CODE EXIT_CODE = create_string(current_time, &is_sent);
    if (EXIT_CODE != OK)
    {   free(current_time);
        return EXIT_CODE;
    }
    Mail* unsent_mails = (Mail*)malloc(sizeof(*mails) * tmp_size);
    if (unsent_mails == NULL)
    {
        free(current_time);
        delete_string(&is_sent);
        return BAD_ALLOC;
    }
    for (int i = 0; i < tmp_size; ++i)
    {
        Mail tmp = mails[i];
        if (compare_time(&is_sent, &(tmp.estimated_date_of_sent)) > 0)
        {
            unsent_mails[amount_of_sent] = tmp;
            amount_of_sent++;
        }
    }
    sort_mails(&unsent_mails, amount_of_sent);
    view_all_mails(unsent_mails, amount_of_sent);
    delete_string(&is_sent);
    free(unsent_mails);
    free(current_time);
    return OK;
}


int main()
{
    char* tmp = NULL;
    Address post_addr;
    EXIT_CODE fck = create_post_address(&post_addr);
    if (fck != OK)
    {
        errors(fck);
        return fck;
    }
    Post post;
    String exit, create, delete, search, send, view_all, view_sent, view_unsent;
    EXIT_CODE st = create_post(&post, post_addr);
    EXIT_CODE st1;
    if (!st)
    {
        st = create_string("1", &exit);
    }
    if (!st)
    {
        st = create_string("2", &create);
    }
    if (!st)
    {
        st = create_string("3", &delete);
    }
    if (!st)
    {
        st = create_string("4", &search);
    }
    if (!st)
    {
        st = create_string("5", &send);
    }
    if (!st)
    {
        st = create_string("6", &view_all);
    }
    if (!st)
    {
        st = create_string("7", &view_sent);
    }
    if (!st)
    {
        st = create_string("8", &view_unsent);
    }
    
    int running = 1;

    while (running && !st)
    {
        String command;
        printf("Available commands:\n");
        printf("1) exit\n");
        printf("2) create mail\n");
        printf("3) delete mail\n");
        printf("4) search mail\n");
        printf("5) send mail\n");
        printf("6) view all mails\n");
        printf("7) view sent mails\n");
        printf("8) view unsent mails\n");
        printf("Enter one of upper commands: ");
        st = get_str(&tmp);
        st1 = create_string(tmp, &command);
        free(tmp);
        if (!st && !st1)
        {
            EXIT_CODE main_EXIT_CODE = OK;
            if (compare_strings(command, exit))
            {
                printf("Programm was closed\n");
                running = 0;
            }
            else if (compare_strings(command, create))
            {
                main_EXIT_CODE = create_mail(&(post.mails), &(post.tmp_size), &(post.max_size));
                if (!main_EXIT_CODE)
                {
                    printf("Mail was created\n");
                }
            }
            else if (compare_strings(command, delete))
            {
                main_EXIT_CODE = delete_mail(&(post.mails), &(post.tmp_size));
                if (!main_EXIT_CODE)
                {
                    printf("Mail was deleted\n");
                }
            }
            else if (compare_strings(command, search))
            {
                main_EXIT_CODE = searching(&(post.mails), post.tmp_size);
            }
            else if (compare_strings(command, send))
            {
                main_EXIT_CODE = is_sent(&(post.mails), post.tmp_size);
                printf("Mail was sent\n");
            }
            else if (compare_strings(command, view_all))
            {
                view_all_mails(post.mails, post.tmp_size);
            }
            else if (compare_strings(command, view_sent))
            {
                main_EXIT_CODE = view_sent_mails(post.mails, post.tmp_size);
            }
            else if (compare_strings(command, view_unsent))
            {
                main_EXIT_CODE = view_unsent_mails(post.mails, post.tmp_size);
            }
            else
            {
                printf("Unknown command\n");
            }
            if (main_EXIT_CODE)
            {
                errors(main_EXIT_CODE);
            }
            delete_string(&command);
            printf("\n");
        }
    }
    delete_string(&exit);
    delete_string(&create);
    delete_string(&search);
    delete_string(&view_all);
    delete_string(&view_unsent);
    delete_string(&view_sent);
    delete_string(&delete);
    delete_string(&send);
    delete_post(&post);

    if (st)
    {
        errors(st);
        return st;
    }
    if (st1)
    {
        errors(st1);
        return st1;
    }

    return 0;
}
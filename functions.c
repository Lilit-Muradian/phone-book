#include "functions.h"

void AddContact(FILE* st, int* count) {
    fseek(st, 0, SEEK_END);
    char ch = '\0';
    Contact new;

    printf("Do you want to add new contacts(y/n): ");
    scanf(" %c", &ch);
    while (ch == 'y') {
        printf("Insert contact's name, phone number and email in sequence.\n");
        scanf(" %s %s %s", new.name, new.phone, new.email);
        fprintf(st, "%s %s %s\n", new.name, new.phone, new.email);
        (*count)++;
        printf("Do you want to add new contacts(y/n): ");
        scanf(" %c", &ch);
    }
    fflush(st);
    sortContacts(st, *count);
}

void SearchByName(FILE* st, int* count) {
    Contact user;
    char name[NAME_LEN];
    printf("\nInsert contact's name for search: ");
    scanf(" %s", name);

    fseek(st, 0, SEEK_SET);

    int flag = 1;
    while (fscanf(st, " %s %s %s", user.name, user.phone, user.email) == 3) {
        if (strcmp(name, user.name) == 0) {
            printf("\nName: %s\nPhone: %s\nEmail: %s\n", user.name, user.phone, user.email);
            flag = 0;
        }
    }
    if (flag) {
        printf("\nThere is no matches.\n");
    }
}

void DeleteContact(FILE* st, int* count) {
    printf("Insert the contact's name you want to delete: ");
    char name[NAME_LEN];
    scanf(" %s", name);

    Contact* c_arr = malloc(sizeof(Contact) * (*count));
    if (c_arr == NULL) {
        perror("Malloc");
        exit(EXIT_FAILURE);
    }

    fseek(st, 0, SEEK_SET);
    Contact tmp;
    int deleted = 0;
    int j = 0;
    for (int i = 0; i < *count; ++i) {
        fscanf(st, " %s %s %s", tmp.name, tmp.phone, tmp.email);
        if (strcmp(tmp.name, name)) {
            strcpy(c_arr[j].name, tmp.name);
            strcpy(c_arr[j].phone, tmp.phone);
            strcpy(c_arr[j++].email, tmp.email);
        } else {
            deleted++;
        }
    }
    *count -= deleted;
    fseek(st, 0, SEEK_SET);
    for (int i = 0; i < *count; ++i) {
        fprintf(st, "%s %s %s\n", c_arr[i].name, c_arr[i].phone, c_arr[i].email);
    }
    int byte_count = ftell(st);
    truncate("phoneBook.txt", byte_count);
    fflush(st); 
    free(c_arr);
}

void SearchByPhoneNumber(FILE* st, int* count) {
    Contact user;
    char phone[PHONE_LEN];
    printf("\nInsert contact's phone number for search: ");
    scanf(" %s", phone);

    fseek(st, 0, SEEK_SET);

    int flag = 1;
    while (fscanf(st, " %s %s %s", user.name, user.phone, user.email) == 3) {
        if (strcmp(phone, user.phone) == 0) {
            printf("\nName: %s\nPhone: %s\nEmail: %s\n", user.name, user.phone, user.email);
            flag = 0;
        }
    }
    if (flag) {
        printf("\nThere is no matches.\n");
    }
}

void SearchByEmail(FILE* st, int* count) {
    Contact user;
    char email[EMAIL_LEN];
    printf("\nInsert contact's email for search: ");
    scanf(" %s", email);

    fseek(st, 0, SEEK_SET);

    int flag = 1;
    while (fscanf(st, " %s %s %s", user.name, user.phone, user.email) == 3) {
        if (strcmp(email, user.email) == 0) {
            printf("\nName: %s\nPhone: %s\nEmail: %s\n", user.name, user.phone, user.email);
            flag = 0;
        }
    }
    if (flag) {
        printf("\nThere is no matches.\n");
    }
}

void sortContacts(FILE* st, int count) {
    Contact* c_arr = malloc(sizeof(Contact) * count);
    if (c_arr == NULL) {
        perror("Malloc");
        exit(EXIT_FAILURE);
    }

    fseek(st, 0, SEEK_SET);
    
    for (int i = 0; i < count; ++i) {
        fscanf(st, " %s %s %s", c_arr[i].name, c_arr[i].phone, c_arr[i].email);
    }
    Contact tmp;
    for (int i = 0; i < count - 1; ++i) {
        for (int j = 0; j < count - i - 1; ++j) {
            if (strcmp(c_arr[j].name, c_arr[j + 1].name) > 0) {
                strcpy(tmp.name, c_arr[j].name);
                strcpy(tmp.phone, c_arr[j].phone);
                strcpy(tmp.email, c_arr[j].email);
                strcpy(c_arr[j].name, c_arr[j + 1].name);
                strcpy(c_arr[j].phone, c_arr[j + 1].phone);
                strcpy(c_arr[j].email, c_arr[j + 1].email);
                strcpy(c_arr[j + 1].name, tmp.name);
                strcpy(c_arr[j + 1].phone, tmp.phone);
                strcpy(c_arr[j + 1].email, tmp.email);
            }
        }
    }
    fseek(st, 0, SEEK_SET);
    for (int i = 0; i < count; ++i) {
        fprintf(st, "%s %s %s\n", c_arr[i].name, c_arr[i].phone, c_arr[i].email);
    }
    fflush(st);
    free(c_arr);
}

void ContactList(FILE* st, int* count) {
    int fd = fileno(st);
    int len = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);

    char* buff = calloc(sizeof(char), len + 1);
    if (buff == NULL) {
        perror("Calloc");
        exit(EXIT_FAILURE);
    }
    read(fd, buff, len);
    printf("\n%s", buff);
}
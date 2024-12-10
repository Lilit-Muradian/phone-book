#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define NAME_LEN 20
#define PHONE_LEN 20
#define EMAIL_LEN 40

typedef struct {
    char name[NAME_LEN];
    char phone[PHONE_LEN];
    char email[EMAIL_LEN];
} Contact;

typedef void (*fptr)(FILE*, int*);

void ContactList(FILE* st, int* count); //0

void AddContact(FILE* st, int* count); //1

void SearchByName(FILE* st, int* count); //2

void SearchByPhoneNumber(FILE* st, int* count); //3

void SearchByEmail(FILE* st, int* count); //4

void DeleteContact(FILE* st, int* count); //5

void sortContacts(FILE* st, int count); //6
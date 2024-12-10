#include "functions.h"


int main() {
    int count = 0;
    FILE* contact_count = fopen("contCount.txt", "r+");
    if (contact_count == NULL) {
        perror("Fopen.");
        exit(EXIT_FAILURE);
    }
    fscanf(contact_count, " %d", &count);
    
    FILE* st = fopen("phoneBook.txt", "r+");
    if (st == NULL) {
        perror("Fopen");
        exit(EXIT_FAILURE);
    }

    fptr function[6];
    function[0] = ContactList;
    function[1] = AddContact;
    function[2] = SearchByName;
    function[3] = SearchByPhoneNumber;
    function[4] = SearchByEmail;
    function[5] = DeleteContact;

    printf("\n******************Hello******************\n\n");
    printf("********Choose your action(Insert the number coresponding to the action or q for quit):********\n\n");
    printf("0. List the contact book\n1. Add contact\n2. Search by name\n3. Search by phone number\n4. Search by email\n5. Delete contact\n");
    int n = 0;

    while (scanf("%d", &n) == 1)
    {
        if (n > 5) {
            putchar(10);
            printf("Your entered number is not correct.\n");
            printf("********Choose your action(Insert the number coresponding to the action or q for quit):********\n\n");
            printf("0. List the contact book\n1. Add contact\n2. Search by name\n3. Search by phone number\n4. Search by email\n5. Delete contact\n");
            continue;
        }
        function[n](st, &count);
        putchar(10);
        printf("********Choose your action(Insert the number coresponding to the action or q for quit):********\n\n");
        printf("0. List the contact book\n1. Add contact\n2. Search by name\n3. Search by phone number\n4. Search by email\n5. Delete contact\n");
    }

    printf("\n******************Goodbye******************\n");
    fclose(st);
    fseek(contact_count, 0, SEEK_SET);
    fprintf(contact_count, "%d", count);
    fclose(contact_count);
}

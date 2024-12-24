#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <conio.h>
#include <math.h>

#define MAX_CHAR 500

FILE *fptr;
int entCount = 0;

struct myLib{
    char title[300];
    int id;
    char date[50];
    char description[500];
};

void createFile();
void writeFile(struct myLib entry);
void readFile();
void deleteEntry();
void findEntry();
int isIdExisting(int newID, struct myLib entry[], int totalEnt);
int generateUniqueId(struct myLib entry[], int totalEnt);

void fileNULLMessage(){
    if(fptr == NULL){
        printf("\n\t\t\t\t\t   ERROR: File not found. Exiting program...");
        getch();
        exit(1);
    }
}

void mainMenu(){
    printf("\t\t\t\t\t--------------------------------");
    printf("\n\t\t\t\t\t    LIBRARY MANAGEMENT SYSTEM\n");
    printf("\t\t\t\t\t      made by EightisVIII\n");
    printf("\t\t\t\t\t--------------------------------");

    printf("\n\n\t\t\t\t\t   ------- SELECTION -------");
    printf("\n\t\t\t\t\t     1. Create Library");
    printf("\n\t\t\t\t\t     2. View Library");
    printf("\n\t\t\t\t\t     3. Find Library Entry");
    printf("\n\t\t\t\t\t     4. Delete Library Entry");
    printf("\n\t\t\t\t\t     5. Exit Program");
    printf("\n\t\t\t\t\t   -------------------------");
}

int main(){
    srand(time(NULL));

    createFile();

    int userChoice, libEnt;

    while(1){
      system("cls");
      mainMenu();
      printf("\n\n\t\t\t\t\t     Enter your choice: ");
      scanf("%d", &userChoice);

      if(userChoice == 1){
        system("cls");
        printf("\t\t\t\t\t--------------------------------");
        printf("\n\t\t\t\t\t     CREATE PERSONAL LIBRARY\n");
        printf("\t\t\t\t\t--------------------------------");
        printf("\n\n\t\t\t            How many entries would you like to make? ");
        scanf("%d", &libEnt);

        struct myLib libValues[libEnt];

        for(int i = 0; i < libEnt; i++){
            if(i == 0){
                getchar();
            }
            printf("\n\n\t\t\t\t\t ---------- ENTRY #%d ----------\n", i+1);
            printf("\t\t\t\t   Title: ");
            fgets(libValues[i].title, 300, stdin);
            strtok(libValues[i].title, "\n");

            libValues[i].id = generateUniqueId(libValues, i);
            printf("\t\t\t\t   ID: %d", libValues[i].id);

            printf("\n\t\t\t\t   Date of Publishing: ");
            fgets(libValues[i].date, 50, stdin);
            strtok(libValues[i].date, "\n");

            printf("\t\t\t\t   Description of Work: ");
            fgets(libValues[i].description, 2000, stdin);
            strtok(libValues[i].description, "\n");
            printf("\t\t\t\t\t -------------------------------");

            writeFile(libValues[i]);
        }
        getch();
      }
      else if(userChoice == 2){
        system("cls");
        printf("\t\t\t\t\t--------------------------------");
        printf("\n\t\t\t\t\t       VIEW PERSONAL LIBRARY\n");
        printf("\t\t\t\t\t--------------------------------");
        readFile();
        getch();
      }
      else if(userChoice == 3){
        system("cls");
        printf("\t\t\t\t\t--------------------------------");
        printf("\n\t\t\t\t\t       FIND LIBRARY ENTRY\n");
        printf("\t\t\t\t\t--------------------------------");
        findEntry();
        getch();
      }
      else if(userChoice == 4){
        system("cls");
        printf("\t\t\t\t\t--------------------------------");
        printf("\n\t\t\t\t\t       DELETE LIBRARY ENTRIES\n");
        printf("\t\t\t\t\t--------------------------------");
        deleteEntry();
        getch();
      }
      else if(userChoice == 5){
        exit(0);
      }
      else{
        printf("\n\n\t\t\t\t\t   Incorrect input. Please try again.");
        getch();
        continue;
      }
    }

    return 0;
}

int isIdExisting(int newId, struct myLib entry[], int totalEnt){
    for(int i = 0; i < totalEnt; i++){
        if(entry[i].id == newId){
            return 1;
        }
    }
    return 0;
}

int generateUniqueId(struct myLib entry[], int totalEnt){
    int newId;
    do{
        newId = 1000 + rand() % 10000;
    } while(isIdExisting(newId, entry, totalEnt));
    return newId;
}

void createFile() {
    fptr = fopen("library.txt", "r");
    if(fptr == NULL){
        fptr = fopen("library.txt", "w");
        fileNULLMessage();
        fclose(fptr);
    } else{
        fclose(fptr);
    }
}

void writeFile(struct myLib entry){
    fptr = fopen("library.txt", "a");
    fileNULLMessage();

    int totalEnt = 0;
    FILE *readFile = fopen("library.txt", "r");
    fileNULLMessage();

    char buffer[MAX_CHAR];
    while (fgets(buffer, MAX_CHAR, readFile)) {
        if (strstr(buffer, "---------- ENTRY")) {
            totalEnt++;
        }
    }
    fclose(readFile);

    entCount++;

    fprintf(fptr, "\n\n\t\t\t\t\t ---------- ENTRY #%d ----------\n", totalEnt + 1);
    fprintf(fptr, "\t\t\t\t   Title: %s\n", entry.title);
    fprintf(fptr, "\t\t\t\t   ID: %d\n", entry.id);
    fprintf(fptr, "\t\t\t\t   Date: %s\n", entry.date);
    fprintf(fptr, "\t\t\t\t   Description: %s\n", entry.description);
    fprintf(fptr, "\t\t\t\t\t -----------------------------\n");

    fclose(fptr);
}

void readFile(){
    fptr = fopen("library.txt", "r");
    fileNULLMessage();

    char readLibrary[MAX_CHAR];

    while(fgets(readLibrary, MAX_CHAR, fptr)){
        printf("%s", readLibrary);
    }

    fclose(fptr);
}

void deleteEntry(){
    FILE *tempFile;
    int deleteChoice, totalEnt = 0;
    struct myLib entry[entCount];
    char buffer[MAX_CHAR];

    fptr = fopen("library.txt", "r");
    fileNULLMessage();

    while(fgets(buffer, MAX_CHAR, fptr)){
        if(strstr(buffer, "---------- ENTRY")){
            fgets(buffer, MAX_CHAR, fptr);
            sscanf(buffer, "   Title: %[^\n]", entry[totalEnt].title);

            fgets(buffer, MAX_CHAR, fptr);
            sscanf(buffer, "   ID: %d", &entry[totalEnt].id);

            fgets(buffer, MAX_CHAR, fptr);
            sscanf(buffer, "   Date: %[^\n]", entry[totalEnt].date);

            fgets(buffer, MAX_CHAR, fptr);
            sscanf(buffer, "   Description: %[^\n]", entry[totalEnt].description);

            totalEnt++;
        }
    }
    fclose(fptr);

    readFile();

    getchar();
    printf("\n\t\t\t   Enter an entry number to delete (0 to end): ");
    while(scanf("%d", &deleteChoice) && deleteChoice != 0){
        if(deleteChoice > 0 && deleteChoice <= totalEnt){
            for(int i = deleteChoice - 1; i < totalEnt - 1; i++) {
                entry[i] = entry[i + 1];
            }
            totalEnt--;
            printf("\n\t\t\t\t\t   Entry #%d deleted.\n", deleteChoice);
        } else{
            printf("\n\t\t\t\t\tInvalid entry number. Please try again.\n");
        }
        printf("\n\t\t\t   Enter an entry number to delete (0 to end): ");
    }

    tempFile = fopen("library.txt", "w");
    fileNULLMessage();

    for(int j = 0; j < totalEnt; j++){
        fprintf(tempFile, "\n\n\t\t\t\t\t --------- ENTRY #%d ---------\n", j + 1);
        fprintf(tempFile, "\t\t\t\t   Title: %s\n", entry[j].title);
        fprintf(tempFile, "\t\t\t\t   ID: %d\n", entry[j].id);
        fprintf(tempFile, "\t\t\t\t   Date: %s\n", entry[j].date);
        fprintf(tempFile, "\t\t\t\t   Description: %s\n", entry[j].description);
        fprintf(tempFile, "\t\t\t\t\t -----------------------------\n");
    }

    fclose(tempFile);
    printf("\n\t\t\t\t\t   Entries successfully updated.");
}

void findEntry(){
    int totalEnt = 0;
    struct myLib entry[entCount];
    char search[MAX_CHAR];
    char buffer[MAX_CHAR];

    getchar();
    printf("\n\n\t\t\t\tSearch: ");
    fgets(search, MAX_CHAR, stdin);
    strtok(search, "\n");

    fptr = fopen("library.txt", "r");
    fileNULLMessage();

    while(fgets(buffer, MAX_CHAR, fptr)){
        if(strstr(buffer, "---------- ENTRY")){
            fgets(buffer, MAX_CHAR, fptr);
            sscanf(buffer, "   Title: %[^\n]", entry[totalEnt].title);

            fgets(buffer, MAX_CHAR, fptr);
            sscanf(buffer, "   ID: %d", &entry[totalEnt].id);

            fgets(buffer, MAX_CHAR, fptr);
            sscanf(buffer, "   Date: %[^\n]", entry[totalEnt].date);

            fgets(buffer, MAX_CHAR, fptr);
            sscanf(buffer, "   Description: %[^\n]", entry[totalEnt].description);

            totalEnt++;
        }
    }
    fclose(fptr);

    printf("\nDebug: Loaded %d entries.\n", totalEnt);
    for (int i = 0; i < totalEnt; i++) {
        printf("Entry #%d: Title='%s', ID=%d, Date='%s', Description='%s'\n",
               i + 1, entry[i].title, entry[i].id, entry[i].date, entry[i].description);
    }

    int entryFound = 0;
    for(int j = 0; j < totalEnt; j++){
        char idString[5];
        sprintf(idString, "%d", entry[j].id);

        if((strcmp(search, entry[j].title) == 0) ||
           (strcmp(search, idString) == 0) ||
           (strcmp(search, entry[j].description) == 0)){
            printf("\n\n\t\t\t\t\t --------- ENTRY #%d ---------\n", j + 1);
            printf("\t\t\t\t   Title: %s\n", entry[j].title);
            printf("\t\t\t\t   ID: %d\n", entry[j].id);
            printf("\t\t\t\t   Date: %s\n", entry[j].date);
            printf("\t\t\t\t   Description: %s\n", entry[j].description);
            printf("\t\t\t\t\t -----------------------------\n");
            entryFound = 1;
            break;
        }
    }

    if(entryFound == 0){
        printf("\n\n\t\t\t\t\t  No entry found matching \"%s\".", search);
    }
}

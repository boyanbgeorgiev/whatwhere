#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 50

struct fRecord
{
    int id;
    char name[MAX_NAME_LENGTH];
};

struct FWW
{
    int koe;
    int kude;
};

void addRecord(FILE *file, struct fRecord record)
{
    fprintf(file, "%d,%s\n", record.id, record.name);
}

void displayRecords(FILE *file)
{
    struct fRecord record;

    rewind(file);

    while (fscanf(file, "%d,%49[^,\n]\n", &record.id, record.name) == 2)
    {
        printf("ID: %d, Name: %s\n", record.id, record.name);
    }
}

void displayRecordsAtIndex(FILE *file, int index)
{
    struct fRecord record;
    fseek(file, (index - 1) * sizeof(struct fRecord), SEEK_SET);
    if (fscanf(file, "%d,%49[^,\n]\n", &record.id, record.name) == 2)
    {
        printf("ID: %d, Name: %s\n", record.id, record.name);
    }
    else
    {
        printf("Record with ID %d not found\n", index);
    }
}

void displayFWW(const char *FIFileName, const char *FPFileName, const char *FWWFileName)
{
    FILE *fileFWW;
    fileFWW = fopen(FWWFileName, "a+");
    if (fileFWW == NULL)
    {
        perror("Error opening FWW.txt");
        exit(EXIT_FAILURE);
    }

    struct FWW recordFWW;

    rewind(fileFWW);
    char koe[MAX_NAME_LENGTH], kude[MAX_NAME_LENGTH];
    printf("Enter item:");
    scanf("%s", koe);
    printf("Enter place:");
    scanf("%s", kude);
    printf("%s %s", koe, kude);
    recordFWW.koe=inputitem (FIFileName, koe);
    recordFWW.kude=inputitem (FPFileName, kude);
    fprintf(fileFWW, "%d,%d\n", recordFWW.koe, recordFWW.kude);

    fclose(fileFWW);
}

void add_item_place(const char *fileName, int mode)
{
    FILE *dbFile;
    int i = 0;
    struct fRecord newRecord, record;

    dbFile = fopen(fileName, "r+");

    if (dbFile == NULL)
    {
        perror("Error opening database file");
        exit(EXIT_FAILURE);
    }

    rewind(dbFile);
    while (fscanf(dbFile, "%d,%49[^,\n]\n", &record.id, record.name) == 2)
    {
        i = 1;
    }

    if (i)
        newRecord.id = record.id + 1;
    else
        newRecord.id = 1;

    if (mode)
    printf("Enter item: ");
    else
        printf("Enter place: ");
    scanf(" %49[^\n]", newRecord.name);

    addRecord(dbFile, newRecord);

    displayRecords(dbFile);

    printf("\n");

    fclose(dbFile);
}

int inputitem(const char *fileName, char *item)
{
    FILE *dbFile;
    int i = 0;
    struct fRecord newRecord, record;

    dbFile = fopen(fileName, "r+");

    if (dbFile == NULL)
    {
        perror("Error opening database file");
        exit(EXIT_FAILURE);
    }

    rewind(dbFile);
    while (fscanf(dbFile, "%d,%49[^,\n]\n", &record.id, record.name) == 2)
    {
        i++;
        if (!strcmp(record.name, item))
        {
            fclose(dbFile);
            return i;
        }
    }
    newRecord.id=i+1;
    strcpy(newRecord.name, item);
    addRecord(dbFile, newRecord);
    fclose(dbFile);
    return i+1;
}

int item_to_id(const char *fileName, char *item)
{
    FILE *dbFile;
    int i = 0;
    struct fRecord record;

    dbFile = fopen(fileName, "r+");

    if (dbFile == NULL)
    {
        perror("Error opening database file");
        exit(EXIT_FAILURE);
    }

    rewind(dbFile);
    while (fscanf(dbFile, "%d,%49[^,\n]\n", &record.id, record.name) == 2)
    {
        i++;
        if (!strcmp(record.name, item))
        {
            fclose(dbFile);
            return i;
        }
    }
    fclose(dbFile);
    return 0;
}

void search_by_item()
{
    char item [MAX_NAME_LENGTH];
    printf("Enter item:");
    scanf("%s", item);
    printf("%s location is: ",item);
    id_to_item("FP.txt", id_item_to_id_place("FWW.txt", item_to_id("FI.txt", item)));
}
void search_by_place()
{
    char place [MAX_NAME_LENGTH];
    printf("Enter location:");
    scanf("%s", place);
    printf("The selected location %s has the following items:\n",place);
    id_place_to_id_item("FWW.txt", item_to_id("FP.txt", place));
}

int id_item_to_id_place(const char *fileName, int item)
{
    FILE *dbFile;
    int i = 0;
    struct FWW record;

    dbFile = fopen(fileName, "r+");

    if (dbFile == NULL)
    {
        perror("Error opening database file");
        exit(EXIT_FAILURE);
    }

    rewind(dbFile);
    while (fscanf(dbFile, "%d,%d\n", &record.koe, &record.kude) == 2)
    {
        i++;
        if (item==record.koe)
        {
            item=record.koe;
        }
    }
    fclose(dbFile);
    return item;
}
int id_place_to_id_item(const char *fileName, int placeid)
{
    FILE *dbFile;
    int i = 0;
    struct FWW record;

    dbFile = fopen(fileName, "r+");

    if (dbFile == NULL)
    {
        perror("Error opening database file");
        exit(EXIT_FAILURE);
    }

    rewind(dbFile);
    while (fscanf(dbFile, "%d,%d\n", &record.koe, &record.kude) == 2)
    {
        i++;
        if (placeid==record.kude)
        {
            //printf("%d", record.koe);
            item_id_to_name_id("FI.txt", record.koe);
        }
    }
    fclose(dbFile);
    return 0;
}
void item_id_to_name_id(const char *fileName, int itemid)
{
    FILE *dbFile;
    int i = 0;
    struct fRecord record;

    dbFile = fopen(fileName, "r+");

    if (dbFile == NULL)
    {
        perror("Error opening database file");
        exit(EXIT_FAILURE);
    }

    rewind(dbFile);
    while (fscanf(dbFile, "%d,%49[^,\n]\n", &record.id, record.name) == 2)
    {
        i++;
        if (record.id==itemid)
        {
            printf("%d. %s\n", itemid,record.name);
        }
    }
    fclose(dbFile);
}

void id_to_item(const char *fileName, int item)
{
    FILE *dbFile;
    int i = 0;
    struct fRecord record;

    dbFile = fopen(fileName, "r+");

    if (dbFile == NULL)
    {
        perror("Error opening database file");
        exit(EXIT_FAILURE);
    }

    rewind(dbFile);
    while (fscanf(dbFile, "%d,%49[^,\n]\n", &record.id, record.name) == 2)
    {
        i++;
        if (item==record.id)
        {
            fclose(dbFile);
            printf("%s", record.name);
        }
    }
    fclose(dbFile);
    return 0;
}
void menu1(int n)
{
    while (n != 27)
        {
            system("cls");
            printf("1: search by item\n2: search by place\nEsc: exit\n");
            n=_getch();

            switch (n)
            {
            case '1':
                search_by_item();
                _getch();
                break;
            case '2':
                search_by_place();
                _getch();
                break;
            }
        }
}
void menu2(char n)
{
    while (n != 27)
        {
            system("cls");
            printf("1: add an item\n2: add a place\n3: add an item and where it is\nEsc: exit\n");
            n=_getch();

            switch (n)
            {
            case '1':
                add_item_place("FI.txt", 1);
                break;
            case '2':
                add_item_place("FP.txt", 0);
                break;
            case '3':
                displayFWW("FI.txt", "FP.txt", "FWW.txt");
                break;
            }
}
}
int main()
{
 //   int n = 1, m=0;
 char n='2';
    //printf("Choose 1 to check what is where\nChoose 2 to add what and where\n");
    //scanf("%d", &n);

        while (n != 27)
        {
            system("cls");
            printf("1: check what is where\n2: add item and place\nEsc: exit\n");
            //scanf("%d", &n);
            n=_getch();
            //printf("%c", n);

            switch (n)
            {
            case '1':
                menu1(1);
                //add_item_place("FI.txt", 1);
                break;
            case '2':
                menu2(2);
                //add_item_place("FP.txt", 0);
                break;
            }
        }
    return 0;
}

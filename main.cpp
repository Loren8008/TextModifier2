/* linijka komentarza */

# include <cstring>
# include <iostream>
# include <stdio.h>
# include <stdlib.h>
void ModifireTextLine(char Text[], char ChangeCharacter, char NewCharacter, FILE* filePointer)
{
    int StringLengh = strlen(Text);
    for(int i=0;i<StringLengh;i++) Text[i] = 0; // zerowanie bufora

    fgetpos(filePointer, &pos);
    printf("In-File-Pointer przed fgets = %d \n", pos);
    status = fgets(Text, sz, filePointer);

    StringLengh = strlen(Text);
    for(i=0;i<40;i++)
    {
        printf("%x | ", Text[i]);
    }
    printf("\n");
    printf(" Input: %s   length: %d\n", Text, StringLengh);
    for(i=0;i<StringLengh;i++)
    {
        if(ChangeCharacter == Text[i])
        {
            Text[i] = NewCharacter;
        }
    }
}

void showText(FILE* filePointer)
{
    char Text[1024];
    fseek(filePointer, 0, SEEK_SET);
    while (fgets(Text, sizeof(Text), filePointer)) //loop to show whole text before changing it
    {
        printf("%s", Text);
    }
    printf("\n");
    fseek(filePointer, 0, SEEK_SET);
}

int main(int argc, char* argv[])
{

    char const *const fileName = argv[1];
    FILE* filePointer;
    char Text[1024];

    char * status;
    char zzz;
    int sz;
    int StringLengh, i;
    char ChangeCharacter, NewCharacter, EndKey; //first - sign u wish to be replaced, second - sign that will replace previous sign
    char NewLineCharacter = NULL;
    int NewLineCharacterNeeded = 0;

    filePointer = fopen(fileName, "r+");
    if(NULL == filePointer)
    {
        printf("Blad otwarcia pliku \n");
        return -1;
    }
    else
    {
        printf("File pointer = %x \n", filePointer);
    }

    showText(filePointer);

    printf("Enter a character you wish to change\n");
    fflush(stdin);
    scanf("%c", &ChangeCharacter);
    printf("Enter a character that will replace these characters\n");
    fflush(stdin);
    scanf("%c", &NewCharacter);

    printf("==================================================\n");
    for(i=0;i<1024;i++) Text[i] = 0;

    fpos_t pos;
    char a = 1;

    /* = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =  MAIN LOOP = = = = = = = = = = = = = = = = = = */

    status = &a;

    while (1)
    {
        for(i=0;i<1024;i++) Text[i] = 0; // zerowanie bufora

        fgetpos(filePointer, &pos); //=====
        printf("In-File-Pointer przed fgets = %d \n", pos);
        status = fgets(Text, sz, filePointer);
        if(status == NULL)
        {
            printf("\n koniec pliku \n");
            return 0;
        }

        StringLengh = strlen(Text);

        for(i=0;i<40;i++)
        {
            printf("%x | ", Text[i]);
        }
        printf("\n");
        printf(" Input: %s   length: %d\n", Text, StringLengh);

        for(i=0;i<StringLengh;i++)
        {
            if(ChangeCharacter == Text[i])
            {
                Text[i] = NewCharacter;
            }
        }

        StringLengh = strlen(Text);
        putchar('\n');
        printf("Output: %s   length: %d\n", Text, StringLengh);

        fsetpos(filePointer, &pos); //=====
        printf("In-File-Pointer przed fputs = %d \n", pos);
        fputs(Text, filePointer);

        if(false != feof(filePointer))
        {
            break;
        }

        /*NewLineCharacter = fgetc(filePointer);
        if(0x0D != NewLineCharacter || 0x0A != NewLineCharacter)
        {
            NewLineCharacterNeeded++;
        }
        */

        printf("==================================================\n");
        fflush(stdin);

        printf("pos = %d\n", pos);
        do
        {
            fgetpos(filePointer, &pos);
            NewLineCharacter = getc(filePointer);
            printf("NewLineCharacter = %x, pos = %d\n", NewLineCharacter, pos);
        }
        while((NewLineCharacter == 0x0A) || (NewLineCharacter == 0x0D));
        printf("przed fsetpos() pos = %d\n", NewLineCharacter, pos);
        fsetpos(filePointer, &pos);
        printf("po fsetpos() pos = %d\n", NewLineCharacter, pos);
        scanf("%c", &zzz);
    }

    /* = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =  END OF THE LOOP = = = = = = = = = = = = = = = = = */

    putchar('\n');

    rewind(filePointer);
    while (fgets(Text, sizeof(Text), filePointer)) //loop to show whole text before closing program
    {
        printf("%s", Text);
    }

    printf("Press ENTER to quit the program");
    putchar('\n');

    //============================
    fflush(stdin);
    scanf("%c", &ChangeCharacter);

    fclose(filePointer);

    return 0;
}



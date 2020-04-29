#include <stdio.h>
#include <conio.h>

typedef enum {false, true} bool;
const char *fileName = "NameOfFile";

bool can(const char *fw){
    return (bool) fopen(fw, "r");
}

void writeFile(){
    FILE *rw = fopen(fileName, "w");
    fclose(rw);
}

int main() {
 if (can(fileName)) {
     writeFile();
     printf("Successfully cleared contents of file.\n");
 } else {
     printf("Could not access file, create file? (y/n)\n");
     char ans;
     scanf("%c",&ans);
     if (ans == 'y' || ans == 'Y'){
         writeFile();
         printf( "%s%s",fileName, " created successfully.");
     }
 }
 getch();
 return 0;
}
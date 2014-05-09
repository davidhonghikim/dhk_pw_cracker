#define _XOPEN_SOURCE
#include <unistd.h>
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


FILE *fp;
string WORDFILE = "rockyou.txt"; //"wordfile.txt";
int PW_LENGTH = 16; //length of password


int n;
string cipherText;
string password;
string testPW;
char salt[2];

string hashTest(string testPW, char salt[]){
    //hashing test
    char cSalt[2] = {salt[0], salt[1]}; 
    printf("crypting with %s and %s\n", testPW, salt);
    string password = crypt(testPW, cSalt);
    printf("crypted : ");
    printf("%s \n", password);
    
    return password;
}

int main(int argc, string argv[]){
    fp = fopen(WORDFILE, "r+w");
    printf("scanning wordfile...\n");

    if(argv[1]==NULL){
        printf("Usage: /crack <cipherText>\n");
        return 1;
    }

    cipherText = argv[1];
    salt[0] = cipherText[0];
    salt[1] = cipherText[1];
    
    printf("cipherText: %s \n", cipherText);
    printf("salt: %c%c \n\n", salt[0],salt[1]);
    
    if (fp != NULL ){
        char line [PW_LENGTH];
        while (fgets (line, sizeof line, fp ) != NULL ) {
            line[strlen(line) - 1] = '\0';
            testPW = line;
            password = hashTest(testPW, salt);
            int x = strcmp(cipherText, password);
            if(x == 0){
                printf("Found password! : %s\n", testPW);
                return 0;
            }
        }
        
    } else {
        return 1;
    }

    printf("\n");
    fclose(fp);
    
    return 0;

}


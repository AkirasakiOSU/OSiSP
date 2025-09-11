//
// Created by dimab on 09.09.2025.
//

#include <stdlib.h>

#include "stdio.h"
#include <conio.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

void printMessage(char const *e) {
    printf("%s", e);
    _getch();
}

void clearInputBuffer() {
    fflush(stdin);
    //char c;
    //while ((c=getc(stdin)) != EOF && c != '\n');
}

#pragma region n1
int createFile(char const *path) {
    unsigned char bytes[] = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    FILE *file = fopen(path, "wb");
    if(file == NULL)
        return 1;
    fwrite(bytes, sizeof(unsigned char), sizeof(bytes), file);
    fclose(file);
    return 0;
}

/*int main(int argc, char** argv) {
    unsigned char byteBuffer[4];
    FILE *file = NULL;
    int i;
    unsigned char byte = 0;


    if(argc == 1) {
        return 1;
    }
    if(createFile(argv[1]))
        return 1;
    file = fopen(argv[1], "rb");
    if(file == NULL)
        return 1;
    while(fread(&byte, sizeof(unsigned char), 1, file) == sizeof(unsigned char)) {
        printf("%d\n", byte);
        printf("%s %d %d %d %d %d %s %s\n\n",
            file->_base,
            file->_bufsiz,
            file->_charbuf,
            file->_cnt,
            file->_file,
            file->_flag,
            file->_ptr,
            file->_tmpfname);
    }
    fclose(file);
    file = fopen(argv[1], "rb");
    if(file == NULL)
        return 1;
    fseek(file, 3*sizeof(unsigned char), SEEK_SET);
    fread(&byteBuffer, sizeof(unsigned char), 4, file);
    for(i = 0; i < 4; ++i)
        printf("%d ", byteBuffer[i]);
    fclose(file);
    return 0;
}*/

#pragma endregion

#pragma region n2
struct user {
    char login[BUFSIZ];
    int pin, isSanctioned;
} typedef user;

int findUser(
    char const *login,
    int pin,
    user const *registredUsers,
    int userCount) {
    if(userCount == -1 || registredUsers == NULL)
        return -1;
    int i;
    for(i = 0; i < userCount; ++i) {
        if(
            !strcmp(registredUsers[i].login, login) &&
            registredUsers[i].pin == pin
            ) {
            return i;
        }
    }
    return -1;
}

int findUserByLogin(char const *login, user const *registredUsers, int userCount) {
    if(userCount == -1 || registredUsers == NULL)
        return -1;
    int i = 0;
    for(i = 0; i < userCount; ++i) {
        if(!strcmp(registredUsers[i].login, login))
            return i;
    }
    return -1;
}

int validateUsersInfo(char const *login, int pin) {
    if(strlen(login) > 6 || !strlen(login))
        return 1;
    int i = 0, l = strlen(login);
    for(i = 0; i < l; ++i) {
        if(!isalnum(login[i]))
            return 1;
    }
    if(pin < 0 || pin > 100000)
        return 1;
    return 0;
}

int separateUserCommand(char *userCommand, char argsBuffer[][BUFSIZ]) {
    int countOfArg = 0;
    char *token = strtok(userCommand, " ");

    while(token != NULL && countOfArg < 3) {
        strncpy(argsBuffer[countOfArg], token, BUFSIZ - 1);
        argsBuffer[countOfArg][BUFSIZ - 1] = '\0';
        countOfArg++;
        token = strtok(NULL, " ");
    }
    return countOfArg;
}

time_t strToTime(char const *str) {
    if(str == NULL)
        return time(NULL);
    struct tm tm = {0};
    char strCopy[strlen(str) + 1], *c = NULL;
    int i[6] = {0}, *ip = i;
    strcpy(c = strCopy, str);
    while(*c != '\0') {
        if(!isdigit(*c)) {
            *c = '\0';
            if(strcmp(str, "00"))
                *ip = atoi(str);
            ++ip;
            str = ++c;
        } else
            ++c;
    }
    *ip = atoi(str);
    tm.tm_mday = i[0];
    tm.tm_mon = i[1] - 1;
    tm.tm_year = i[2] - 1900;
    tm.tm_hour = i[3];
    tm.tm_min = i[4];
    tm.tm_sec = i[5];
    return mktime(&tm);
}

/*int main(int argc, char** argv) {
    unsigned char command = 0;
    char currentLogin[7], userCommand[BUFSIZ], separatedUserCommand[3][BUFSIZ], timeBuffer[BUFSIZ];
    user *registredUsers = NULL;
    time_t currentTime = time(NULL), t2, t3;
    struct tm tm = {0};
    int currentUser = -1, currentPin = 0, userCount = 0, pSize = 0, userCommandSize, i;
    while(1) {
        if(currentUser != -1) {
            // Handle user commands
            clearInputBuffer();
            if(registredUsers != NULL && registredUsers[currentUser].isSanctioned) {
                printMessage("You was sanctioned!\n");
                printf("Enter command:\nLogout\n");
                gets(userCommand);
                if(strcmp(userCommand, "Logout"))
                    printMessage("Unknown command");
                else
                    currentUser = -1;
                system("cls");
                continue;
            }
            printf("Enter command:\nTime \nDate \nHowmuch <datetime> <flag> \nSanctions <username> \nLogout \n");
            gets(userCommand);
            for(i = 0; i < 3; ++i)
                separatedUserCommand[i][0] = '\0';
            userCommandSize = separateUserCommand(userCommand, separatedUserCommand);
            if(!userCommandSize) {
                system("cls");
                continue;
            }
            if(!strcmp(separatedUserCommand[0], "Time")) {
                currentTime = time(NULL);
                strftime(timeBuffer, BUFSIZ, "%H:%M:%S\n", localtime(&currentTime));
                printMessage(timeBuffer);
            } else if(!strcmp(separatedUserCommand[0], "Date")) {
                currentTime = time(NULL);
                strftime(timeBuffer, BUFSIZ, "%d:%m:%Y\n", localtime(&currentTime));
                printMessage(timeBuffer);
            } else if(!strcmp(separatedUserCommand[0], "Howmuch")) {
                if(userCommandSize != 3) {
                    printMessage("Arg error");
                } else {
                    //доделать парсинг вводимого времени
                    currentTime = time(NULL);
                    t2 = strToTime(separatedUserCommand[1]);
                    strftime(timeBuffer, BUFSIZ, "%d:%m:%Y_%H:%M:%S\n", localtime(&t2));
                    double timediff = difftime(currentTime, t2);
                    if(!strcmp(separatedUserCommand[2], "-y"))
                        timediff /= 365 * 24 * 60 * 60;
                    else if(!strcmp(separatedUserCommand[2], "-h"))
                        timediff /= 3600.0;
                    else if(!strcmp(separatedUserCommand[2], "-m"))
                        timediff /= 60.0;
                    printf("Time difference: %f\n", timediff);
                    _getch();
                }
            } else if(!strcmp(separatedUserCommand[0], "Sanctions")) {
                int targetUserId = findUserByLogin(separatedUserCommand[1], registredUsers, userCount);
                if(targetUserId == -1) {
                    printMessage("User not found");
                } else {
                    if(currentUser == targetUserId)
                        printMessage("Are you stupid?");
                    else {
                        registredUsers[targetUserId].isSanctioned = 1;
                        printf("%s was Sanctioned", separatedUserCommand[1]);
                        _getch();
                    }
                }

            } else if(!strcmp(separatedUserCommand[0], "Logout")) {
                currentUser = -1;
            } else {
                printMessage("Unknown command");
            }
            system("cls");
            continue;
        }
        printf("Enter command:\n1 - login\n2 - regist\n0 - exit\n");
        scanf("%d", &command);
        if(!command)
            break;
        printf("Enter <login> <PIN>:\n");
        scanf("%s %d", &currentLogin, &currentPin);
        if(validateUsersInfo(currentLogin, currentPin)) {
            printMessage("Validation error");
            continue;
        }
        switch (command) {
            case 1:
                if(registredUsers == NULL ||
                (currentUser = findUser(currentLogin, currentPin, registredUsers, userCount)) == -1
                )
                    printMessage("User not found");
            break;
            case 2:
                if(registredUsers == NULL) {
                    pSize = sizeof(user) * 4;
                    registredUsers = (user *)malloc(pSize);
                    if(registredUsers == NULL)
                        return 1;
                }
                if(findUserByLogin(currentLogin, registredUsers, userCount) != -1) {
                    printMessage("User allready exist");
                    break;
                }
                strcpy(registredUsers[userCount++].login, currentLogin);
                registredUsers[userCount - 1].pin = currentPin;
                registredUsers[userCount - 1].isSanctioned = 0;
                if(userCount == pSize) {
                    user *ptr = registredUsers;
                    registredUsers = (user *)realloc(registredUsers, pSize *= 2);
                    if(registredUsers == NULL) {
                        free(ptr);
                        return 1;
                    }
                }
                //currentUser = userCount - 1;
                printMessage("Registration successfully completed");
                break;
            default:
                printMessage("Unknown command");
            break;
        }
        system("cls");
    }
    if(registredUsers != NULL)
        free(registredUsers);
    return 0;
}*/
#pragma endregion

#pragma region n3

#pragma endregion
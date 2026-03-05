#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct UserProfile {
    unsigned char* email;
    long uid;
    unsigned char* role;
};

struct UserProfile parseUserProfile(unsigned char string[]){
    struct UserProfile userProfile;
    int emailLength = 0;
    for(int i=6;i<strlen(string);i++){
        if(string[i] == '&'){
            break;
        } else {
            emailLength++;
        }
    }
    unsigned char* email = calloc(emailLength+1,1);
    for(int i=0;i<emailLength;i++){
        email[i] = string[6+i];
    }
    userProfile.email = email;
//--------------------------------------------------------
    int uidStringLength = 0;
    int uidStringStart = strlen("email=")+emailLength+strlen("&uid=");
    for(int i=uidStringStart;i<strlen(string);i++){
        if(string[i] == '&'){
            break;
        } else {
            uidStringLength++;
        }
    }
    unsigned char* uidString = calloc(uidStringLength+1,1);
    for(int i=0;i<uidStringLength;i++){
        uidString[i] = string[uidStringStart+i];
    }
    long uid = strtol(uidString, NULL, 10);
    
    userProfile.uid = uid;
//--------------------------------------------------------
    int roleStart = strlen("email=")+ emailLength + strlen("&uid=")+ uidStringLength +strlen("&role=");
    int roleLength = strlen(string) - roleStart;
    unsigned char* role = calloc(roleLength+1,1);
    for(int i=0;i<roleLength;i++){
        role[i] = string[roleStart+i];
    }
    userProfile.role = role;

    return userProfile;
}

struct UserProfile profile_for(char* string){
    int emailLength = strlen(string);
    unsigned char* email = calloc(emailLength+1,sizeof(unsigned char));
    int j=0;
    for(int i=0;i<strlen(string);i++){
        if(string[i] == '&' || string[i] == '='){
            continue;
        } else {
            email[j]=string[i];
            j++;
        }
    }
    struct UserProfile result;
    result.email = email;
    result.uid = 10;
    result.role="user";
    return result;
}

unsigned char* encodeUserProfile(struct UserProfile userProfile){
    unsigned char* email = userProfile.email;
    int len = snprintf(NULL, 0, "%ld",userProfile.uid);
    unsigned char* uidString = malloc(len+1);
    snprintf(uidString, len+1, "%ld", userProfile.uid);
    unsigned char* role = userProfile.role;
    int resultLength = strlen("email=")+strlen(email)+strlen("&uid=")+strlen(uidString)+strlen("&role=")+strlen(userProfile.role);
    unsigned char* result = calloc(resultLength+1,sizeof(unsigned char));
    result[0] = 'e';
    result[1] = 'm';
    result[2] = 'a';
    result[3] = 'i';
    result[4] = 'l';
    result[5] = '=';
    for(int i=0;i<strlen(email);i++){
        result[i+strlen("email=")] = email[i];
    }
    int emailEnd = strlen("email=")+strlen(email);
    result[emailEnd] = '&';
    result[emailEnd+1] = 'u';
    result[emailEnd+2] = 'i';
    result[emailEnd+3] = 'd';
    result[emailEnd+4] = '=';
    int uidStart = emailEnd+strlen("&uid=");
    for(int i=0;i<strlen(uidString);i++){
        result[uidStart+i] = uidString[i];
    }
    int uidEnd = uidStart+strlen(uidString);
    result[uidEnd] = '&';
    result[uidEnd+1] = 'r';
    result[uidEnd+2] = 'o';
    result[uidEnd+3] = 'l';
    result[uidEnd+4] = 'e';
    result[uidEnd+5] = '=';
    int roleStart = uidEnd + strlen("&role=");
    for(int i=0;i<strlen(role);i++){
        result[roleStart+i] = role[i];
    }
    return result;

}
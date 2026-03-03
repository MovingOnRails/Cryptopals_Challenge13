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

int main(){
    struct UserProfile userProfile = parseUserProfile("email=foo@bar.com&uid=10&role=user");
    printf("email: %s\n",userProfile.email);
    printf("uid: %d\n",userProfile.uid);
    printf("role: %s\n",userProfile.role);
}
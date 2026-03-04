#include <stdio.h>
#include <string.h>
#include <stdlib.h>

static long GLOBAL_UID=1;

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
    unsigned char* email = calloc(strlen(string)+1,1);
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
    result.uid = GLOBAL_UID;
    GLOBAL_UID++;
    result.role="user";
    return result;
}

unsigned char* encodeUserProfile(struct UserProfile userProfile){
    unsigned char* email = userProfile.email;
    int len = snprintf(NULL, 0, "%ld",userProfile.uid);
    char* uidString = malloc(len+1);
    snprintf(uidString, len+1, "%ld", userProfile.uid);
    int resultLength = strlen("email=")+strlen(email)+strlen("&uid=")+strlen(uidString)+strlen("&role=")+strlen(userProfile.role);
    unsigned char* result = calloc(resultLength,sizeof(unsigned char));
    // TODO Concatenate email= with email, &uid= with uid and &role= with role

}

int main(){
    struct UserProfile userProfile = parseUserProfile("email=foo@bar.com&uid=10&role=user");
    printf("------------------UserProfile1------------------\n");
    printf("email: %s\n",userProfile.email);
    printf("uid: %d\n",userProfile.uid);
    printf("role: %s\n",userProfile.role);
    
    printf("------------------UserProfile2------------------\n");
    struct UserProfile userProfile2 = profile_for("foo@bar.com");
    printf("email: %s\n",userProfile2.email);
    printf("uid: %d\n",userProfile2.uid);
    printf("role: %s\n",userProfile2.role);

    printf("------------------UserProfile3------------------\n");
    struct UserProfile userProfile3 = profile_for("foo@bar.com&role=admin");
    printf("email: %s\n",userProfile3.email);
    printf("uid: %d\n",userProfile3.uid);
    printf("role: %s\n",userProfile3.role);

    unsigned char* encodedUserProfile = encodeUserProfile(userProfile);

}
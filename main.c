#include "./profile.c"
#include "../Challenge10/aes.c"
#include <sys/random.h>

unsigned char* oracle(unsigned char* message){

}

int main(){
    unsigned char key[16];
    getrandom(key,16,NULL);
    
    unsigned char craftedEmail[12] = "foo@bar.com\0";
    struct UserProfile userProfile = profile_for(craftedEmail);
    unsigned char* message = encodeUserProfile(userProfile);
    int messageSize = strlen(message);
    unsigned char* encrypted = aes_ecb_encrypt(message,messageSize,key);
    unsigned char* decrypted = aes_ecb_decrypt(encrypted,getCiphertextLengthAES128(messageSize),key);
    printf("%s\n",decrypted);

}
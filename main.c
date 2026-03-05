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
    //printf("%s\n",decrypted);

    int resultLength = strlen("email=foooo@bar.com&uid=10&role=admin\0");
    unsigned char* result = calloc(getCiphertextLengthAES128(resultLength),sizeof(unsigned char));

    unsigned char* craftedMessage1 = encodeUserProfile(profile_for("foooo@bar.com\0"));
    unsigned char* encrypted1 = aes_ecb_encrypt(craftedMessage1,getCiphertextLengthAES128(strlen(craftedMessage1)),key);
    memcpy(result,encrypted1,32);

    unsigned char* craftedMessage2 = encodeUserProfile(profile_for("foooo@bar.admin\11\11\11\11\11\11\11\11\11\11\11\0"));
    unsigned char* encrypted2 = aes_ecb_encrypt(craftedMessage2,getCiphertextLengthAES128(strlen(craftedMessage2)),key);
    memcpy(result+32,encrypted2+16,16);

    unsigned char* decryptedResult = aes_ecb_decrypt(result,getCiphertextLengthAES128(resultLength),key);
    printf("%s",decryptedResult);

}
#include "./profile.c"

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
    printf("encoded UserProfile: %s\n", encodedUserProfile);
    return 0;
}
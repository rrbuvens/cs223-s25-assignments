#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 32

int main()
{
    int bool;
    int adj;
    printf("Boolean: ");
    scanf("%d", &bool);
    printf("Number: ");
    scanf("%d", &adj);
    char** adjectives = malloc(sizeof(char*) * adj);
    for (int i = 0; i < adj; i++) {
        adjectives[i] = malloc(sizeof(char) * 32);
        printf("Adjective: ");
        scanf("%s", adjectives[i]);
    }
    printf("You are the most ");
    for (int i = adj - 1; i > 0; i--) {
        printf("%s, ", adjectives[i]);
    }
    printf("and %s person that I know and you know it's ", adjectives[0]);
    if (bool) { printf("true!\n"); }
    else { printf ("false!\n"); }
    
    for (int i = 0; i < adj; i++) {
        free(adjectives[i]);
    }
    free(adjectives);
    return 0;
}

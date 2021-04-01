#include <string.h>
#include "raylib.h"
#include "utils.h"
// utility functions



// creates a new string containing the concatenation of str1 and str2
char* strcat_safe(char* str1, char* str2) {
    int l1 = strlen(str1), l2 = strlen(str2);
    char* s = malloc(sizeof(char) * (l1 + l2 + 1));
    for (int i = 0;i < l1;i++)
        s[i] = str1[i];
    for (int i = 0;i < l2;i++)
        s[i + l1] = str2[i];
    s[l1 + l2] = '\0';
    return s;
}
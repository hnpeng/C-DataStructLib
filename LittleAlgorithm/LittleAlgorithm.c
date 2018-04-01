#include "LittleAlgorithm.h"

#include <stdio.h>

void reverseStr(const char *s)
{
    if (s != NULL &&  *s != '\0') {
        reverseStr(s + 1);
        printf("%c", *s);
    }
}

int strLen(const char *s)
{
    return s == NULL ? -1 : (*s == '\0' ? 0 : (strLen(s + 1) + 1));
}

void hanoi(int n, char src, char aid, char dest)
{
    if (n > 0) {
        if (n == 1) {
            printf("%c -> %c\n", src, dest);
        } else {
            hanoi(n - 1, src, dest, aid);

            printf("%c -> %c\n", src, dest);

            hanoi(n - 1, aid, src, dest);
        }
    }
}

void permutation(char* s, int begin, int end)
{
    if (begin == end) {
        printf("%s\n", s);
    } else {
        int i;

        for (i=begin; i<=end; i++) {
            int j;
            int flag = 0;

            for (j=begin; j<i; j++) {
                if (s[j] == s[i])
                    flag = 1;
            }

            if (flag == 1) {
                continue;
            }

            char temp = s[begin];
            s[begin] = s[i];
            s[i] = temp;

            permutation(s, begin + 1, end);

            temp = s[begin];
            s[begin] = s[i];
            s[i] = temp;
        }
    }
}

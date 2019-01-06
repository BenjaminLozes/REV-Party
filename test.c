#include <stdio.h>
#include <stdbool.h>

void testing(FILE* logfp) {
    fprintf(logfp, "tamarre");
}

int main(void) {
    bool temp = 0;
    if(!temp)
        printf("okay\n");
    FILE* logfp = fopen("log.txt", "ab+");
    logfp = stdout;
    fprintf(logfp, "bonjour");
    testing(logfp);
}
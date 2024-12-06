#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <time.h>

#define PROMPT "> "

char *process(const char*);

int main(){
	rl_inhibit_completion = 1;
    char *input = readline(PROMPT);
	clock_t start = 0;
	clock_t end = 0;
	float time = 0;
    while(input != NULL){
        printf("input: \"%s\"\n", input);
		start = clock();
        char *output = process(input);
		end = clock();
		time = (float)(end - start) / CLOCKS_PER_SEC;
        printf("output: \"%s\"\n", output);
		printf("\nexecution time: %f\n\n", time);
        free(input);
        free(output);
        input = readline(PROMPT);
    }
    return 0;
}

char *process(const char *input){
    char *s = strdup(input);
    int s_len = strlen(s);
    char *res = calloc(s_len + 2, sizeof(char));
    int len = 0;
    char *word = strtok(s, "\t ");
    while(word != NULL){
        int w_len = strlen(word);
        if((w_len % 2) == 0){
			memcpy(res + len, word, w_len * sizeof(char));
            len += w_len;
            res[len] = ' ';
            len++;
        }
		word = strtok(NULL, "\t ");
	}
    free(s);
    if(len > 0){
        len--;
    }
    res[len] = '\0';
    res = realloc(res, (len + 1) * sizeof(char));
    return res;
}


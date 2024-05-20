#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// 函数声明
int count_characters(FILE *file);
int count_words(FILE *file);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s -c|-w input_file_name\n", argv[0]);
        return 1;
    }

    char *parameter = argv[1];
    char *file_name = argv[2];

    // 打开文件
    FILE *file = fopen(file_name, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    int result = 0;
    if (strcmp(parameter, "-c") == 0) {
        result = count_characters(file);
        printf("%d\n", result);
    } else if (strcmp(parameter, "-w") == 0) {
        result = count_words(file);
        printf("%d\n", result);
    } else {
        printf("Invalid parameter. Use -c for characters count or -w for words count.\n");
        fclose(file);
        return 1;
    }

    // 关闭文件
    fclose(file);
    return 0;
}

int count_characters(FILE *file) {
    int count = 0;
    int ch;

    while ((ch = fgetc(file)) != EOF) {
        count++;
    }

    return count;
}

int count_words(FILE *file) {
    int count = 0;
    int in_word = 0;
    int ch;

    while ((ch = fgetc(file)) != EOF) {
        if (isspace(ch) || ch == ',') {
            if (in_word) {
                count++;
                in_word = 0;
            }
        } else {
            in_word = 1;
        }
    }

    if (in_word) {
        count++;
    }

    return count;
}


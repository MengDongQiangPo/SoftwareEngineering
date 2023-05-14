#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct {
    int max_num;
    char operators[5];
    int num_operators;
    int num_operators_type;
    int has_bracket;
    int has_decimal;
} Operation;

const int MAX_BUFFER = 1000;

void init_operation(Operation *op, int max_num, const char *operators, int num_operators, int has_bracket, int has_decimal) {
    op->max_num = max_num;
    snprintf(op->operators, sizeof(op->operators), "%s", operators);
    op->num_operators = num_operators;
    op->has_bracket = has_bracket;
    op->has_decimal = has_decimal;
    op->num_operators_type = strlen(op->operators);
}

int generate_random_number(int min, int max) {
    return rand() % (max - min + 1) + min;
}

void generate_expression(Operation *op, char *expression) {
    int num_operators = op->num_operators;
    int nums[num_operators + 1];
    char ops[num_operators];
    int bracket_num = 0;
    int i;

    for (i = 0; i < num_operators + 1; i++) {
        nums[i] = generate_random_number(1, op->max_num);
    }

    for (i = 0; i < num_operators; i++) {
        ops[i] = op->operators[generate_random_number(0, op->num_operators_type - 1)];
    }

    int index = 0;
    for (i = 0; i < num_operators; i++) {
        if (op->has_bracket && (rand() / (double)RAND_MAX) > 0.5) {
            expression[index++] = '(';
            bracket_num++;
        }
        index += sprintf(&expression[index], "%d", nums[i]);
        if (op->has_bracket && (rand() / (double)RAND_MAX) > 0.5 && bracket_num > 0) {
            expression[index++] = ')';
            bracket_num--;
        }
        expression[index++] = ops[i];
    }

    index += sprintf(&expression[index], "%d", nums[num_operators]);

    if (op->has_decimal) {
        index += sprintf(&expression[index], ".%02d", generate_random_number(0, 99));
    }

    while (bracket_num > 0) {
        expression[index++] = ')';
        bracket_num--;
    }

    expression[index] = '\0';
}

void generate_exercises(Operation *op, int num_exercises, char exercises[][MAX_BUFFER]) {
    int i;
    for (i = 0; i < num_exercises; i++) {
        generate_expression(op, exercises[i]);
    }
}

void output_to_file(Operation *op, char exercises[][MAX_BUFFER], int num_exercises, const char *file_path) {
    FILE *file = fopen(file_path, "w");
    if (file == NULL) {
        printf("fail to open file：%s\n", file_path);
        return;
    }

    int i;
    for (i = 0; i < num_exercises; i++) {
        fprintf(file, "%d. %s = \n", i+1, exercises[i]);
    }

    fclose(file);
}

void output_to_console(char exercises[][MAX_BUFFER], int num_exercises) {
    int i;
    for (i = 0; i < num_exercises; i++) {
        printf("%d. %s = \n", i+1, exercises[i]);
    }
}

int main(int argc, char** argv) {
    int max_num;
    char operators[5];
    int num_operators;
    int has_bracket;
    int has_decimal;
    int num_exercises;
    int output_type;
    const char file_path[50];
/*
    printf("请输入最大数：");
    scanf("%d", &max_num);

    printf("请输入运算符（+ - * /):");
    scanf("%s", operators);

    printf("请输入运算符个数：");
    scanf("%d", &num_operators);

    printf("是否有括号(y/n):");
    char choice[2];
    scanf("%s", choice);
    has_bracket = (choice[0] == 'y' || choice[0] == 'Y');

    printf("是否有小数(y/n):");
    scanf("%s", choice);
    has_decimal = (choice[0] == 'y' || choice[0] == 'Y');

    printf("请输入题目数量：");
    scanf("%d", &num_exercises);

    printf("请选择输出方式(1. 输出到控制台 2. 输出到文件）：");
    scanf("%d", &output_type);
*/
    if (argc < 8) {
        printf("Invalid number of arguments!\n");
        return 1;
    }
    max_num = atoi(argv[1]);
    strncpy(operators, argv[2], sizeof(operators));
    num_operators = atoi(argv[3]);
    has_bracket = (argv[4][0] == 'y' || argv[4][0] == 'Y');
    has_decimal = (argv[5][0] == 'y' || argv[5][0] == 'Y');
    num_exercises = atoi(argv[6]);
    output_type = atoi(argv[7]);
    if (argc != 9 && output_type != 2) {
        printf("Invalid number of arguments!\n");
        return 1;
    }
    strncpy((char*)file_path, argv[8], sizeof(file_path));

    Operation operation;
    init_operation(&operation, max_num, operators, num_operators, has_bracket, has_decimal);

    char exercises[num_exercises][MAX_BUFFER];
    generate_exercises(&operation, num_exercises, exercises);

    if (output_type == 1) {
        output_to_console(exercises, num_exercises);
    } else if (output_type == 2) {
        output_to_file(&operation, exercises, num_exercises, file_path);
        printf("The question has been output to a file:%s\n", file_path);
    } else {
        printf("Invalid output method\n");
    }

    return 0;
}

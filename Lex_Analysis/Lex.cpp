/*
 * @Author: suyifan
 * @Date: 2020-10-29 22:04:37
 * @LastEditTime: 2020-10-30 22:07:15
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \AlgorithmsC\C_Compiler\source\newlexAnalysis\suyifan.c
 */
#include "util.h"
char* src;
int main(void) {
    FILE* fd1;
    FILE* fd2;
    int i;
    struct node* p;
    p = (node*)malloc(sizeof(node));
    char path[100] =
        "D:\\Colleage\\AlgorithmsC\\C_Compiler\\source\\newlexAnalysis\\Lex_"
        "Analysis\\Text_File.cpp";
    if ((fd1 = fopen(path, "r")) == NULL) {
        printf("could not open(%s)\n", path);
        return -1;
    }
    if ((fd2 = fopen(".\\output.txt", "w")) == NULL) {
        printf("could not open(%s)\n", path);
        return -1;
    }

    if (!(src = (char*)malloc(SIZE))) {
        printf("could not malloc for source area\n");
        return -1;
    }
    // ��ȡԴ�ļ�
    if ((i = fread(src, 1, SIZE, fd1)) <= 0) {
        printf("read() returned %d\n", i);
        return -1;
    }
    src[i] = 0;  // ���EOF�ַ�
    fclose(fd1);
    //Ԥ������
    PRETREATMENT(src, i);
    PROGRAM(p, fd2);
    fclose(fd2);
}

int PRETREATMENT(char* src, int length) {
    char temp_src[SIZE];
    int count = 0;
    //��ÿһ���ַ������ж�
    for (int i = 0; i <= length; i++) {
        //�ж��Ƿ���ע��, �Լ��Ƿ���#
        if ((src[i] == '/' && src[i + 1] == '/') || src[i] == '#') {
            while (src[i] != '\n' && src[i] != 0) {
                i++;
            }
        }
        if (src[i] == '/' && src[i + 1] == '*') {
            i = i + 2;
            while (!(src[i] == '*' && src[i + 1] == '/')) {
                i++;
                //��������Ҳû���ҵ���ע��*/�����������
                if (src[i] == 0) {
                    printf("δ�ҵ�*/��Դ�������");
                    exit(0);
                }
            }
            i = i + 2;
        }
        //�޳�����ո�
        if (src[i] == ' ' && src[i + 1] == ' ') {
            i++;
            while (src[i + 1] == ' ') i++;
        }
        //�޳��س��������з���ˮƽ�Ʊ����Ӧ���Ƕ���ʽ��\n��˵�����Լ�д��"abc\n"
        //���뵽�ַ��л���\\n
        if (src[i] != '\n' && src[i] != '\t' && src[i] != '\r') {
            temp_src[count++] = src[i];
        }
        //�������EOF�����˳�
        if (src[i] == 0) {
            break;
        }
    }
    temp_src[count] = 0;
    strcpy(src, temp_src);
    return count;
}

bool IS_LETTER(char letter) {
    if ((letter >= 'a' && letter <= 'z') || (letter >= 'A' && letter <= 'Z') ||
        letter == '_') {
        return true;
    } else {
        return false;
    }
}

bool IS_DIGIT(char digit) {
    if (digit >= '0' && digit <= '9') {
        return true;
    } else {
        return false;
    }
}

bool IS_OPERATION(char op) {
    if (op == '+' || op == '-' || op == '*' || op == '/' || op == '%' ||
        op == '!' || op == '&' || op == '^' || op == '|' || op == '~' ||
        op == '<' || op == '>' || op == '=') {
        return true;
    } else {
        return false;
    }
}

bool IS_SEPARATOR(char sep) {
    if (sep == '(' || sep == ')' || sep == '[' || sep == ']' || sep == '{' ||
        sep == '}' || sep == ';' || sep == ',' || sep == '\"' || sep == '\'') {
        return true;
    } else {
        return false;
    }
}

TOKEN_TYPE SEARCH_SEPARATOR(char sep) {
    for (int i = 0; i < 10; i++) {
        if (sep == SEPARATOR[i]) {
            //ƫ����Ϊ69
            return TOKEN_TYPE(i + 69);
        }
    }
    return ERROR;
}

TOKEN_TYPE SEARCH_OPERATOR(char* word) {
    for (int i = 0; i < 31; i++) {
        if (strcmp(OPERATION[i], word) == 0) {
            //ƫ����Ϊ38
            return TOKEN_TYPE(i + 38);
        }
    }
    return ERROR;
}

TOKEN_TYPE SEARCH_RESERVE(char* word) {
    for (int i = 0; i < 32; i++) {
        if (strcmp(RESERVEWORD[i], word) == 0) {
            return TOKEN_TYPE(i + 1);
        }
    }
    return ERROR;
}

struct node* GET_CHAR(struct node* p) {
    TOKEN_TYPE type;
    char token[40], *key;
    char* forward = src;
    int i;
    for (i = 0; i < 20; i++) {
        token[i] = 0;
    }
    if (*forward == ' ') {
        forward++;
    }
    if (IS_LETTER(*forward)) {
        i = 0;
        token[i++] = *forward;
        forward++;
        //������������ĸ������ʱ��������������abc1(�����*forward = (
        while (IS_LETTER(*forward) || IS_DIGIT(*forward)) {
            token[i++] = *forward;
            forward++;
        }
        token[i] = '\0';
        if (SEARCH_RESERVE(token) != ERROR) {
            type = SEARCH_RESERVE(token);
            key = (char*)malloc(sizeof("KEY_WORD"));
            key = (char*)"KEY_WORD";
        } else {
            type = ID;
            key = (char*)malloc(sizeof("ID"));
            key = (char*)"ID";
        }
    } else if (IS_DIGIT(*forward)) {
        i = 0;
        token[i++] = *forward;
        forward++;
        while (IS_DIGIT(*forward)) {
            token[i++] = *forward;
            forward++;
        }
        //������
        if (*forward == '.') {
            token[i++] = *forward;
            forward++;
            while (IS_DIGIT(*forward)) {
                token[i++] = *forward;
                forward++;
            }
            token[i] = '\0';
            type = DECIMAL;

        } else {
            token[i] = '\0';
            type = INTEGER;
        }
        key = (char*)malloc(sizeof("DIGITS"));
        key = (char*)"DIGITS";
    } else if (IS_OPERATION(*forward)) {
        i = 0;
        token[i++] = *forward;
        forward++;
        //�����ж��Ƿ���˫Ŀ�����
        if (IS_OPERATION(*forward)) {
            token[i++] = *forward;
            token[i] = '\0';
            forward++;
            if (SEARCH_OPERATOR(token)) {
                type = SEARCH_OPERATOR(token);
                key = (char*)malloc(sizeof("OPERATOR"));
                key = (char*)"OPERATOR";
            } else {
                type = ERROR;
                key = (char*)malloc(sizeof("UNDEFINED"));
                key = (char*)"UNDEFINED";
            }
        } else {  //��Ŀ�����
            token[i] = '\0';
            type = SEARCH_OPERATOR(token);
            key = (char*)malloc(sizeof("OPERATOR"));
            key = (char*)"OPERATOR";
        }
    } else if (IS_SEPARATOR(*forward)) {
        i = 0;
        token[i++] = *forward;
        if (SEARCH_SEPARATOR(*forward) != ERROR) {
            if (*forward == '\"') {
                forward++;
                while (*forward != '\"' && *forward != '\0') {
                    token[i++] = *forward;
                    forward++;
                }
                token[i++] = *forward;
                type = STRING;
                key = (char*)malloc(sizeof("STRING"));
                key = (char*)"STRING";
            } else if (*forward == '\'') {
                forward++;
                while (*forward != '\'' && *forward != '\0') {
                    token[i++] = *forward;
                    forward++;
                }
                token[i++] = *forward;
                type = CHARACTER;
                key = (char*)malloc(sizeof("CHARACTER"));
                key = (char*)"CHARACTER";
            } else {
                type = SEARCH_SEPARATOR(*forward);
                key = (char*)malloc(sizeof("SEPARATOR"));
                key = (char*)"SEPARATOR";
            }
        } else {
            type = ERROR;
            key = (char*)malloc(sizeof("UNDEFINED"));
            key = (char*)"UNDEFINED";
        }
        token[i] = '\0';
        forward++;
    }

    src = forward;  //������һ������ʶ��
    now_char = *src;
    p->type = type;
    for (i = 0; i < 40; i++) {
        p->value[i] = token[i];
    }
    strcpy(p->key, key);
    return p;
}

void PROGRAM(struct node* p, FILE* fd2) {
    p = GET_CHAR(p);
    while (now_char > 0) {
        printf("< %10s   %10s   %10d>\n", p->key, p->value, p->type);
        fprintf(fd2, "< %10s   %10s   %10d>\n", p->key, p->value, p->type);
        p = GET_CHAR(p);
    }
    printf("< %10s   %10s   %10d>\n", p->key, p->value, p->type);
    fprintf(fd2, "< %10s   %10s   %10d>\n", p->key, p->value, p->type);
}
/*
 * @Author: your name
 * @Date: 2020-10-28 01:23:02
 * @LastEditTime: 2020-10-30 22:08:04
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \AlgorithmsC\C_Compiler\source\newlexAnalysis\util.h
 */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 10240

char now_char;

typedef enum TOKEN_TYPE
// tokens:
{
    //����
    ERROR, //0
    /* ������ */
    AUTO,
    BREAK,
    CASE,
    CHAR,
    CONST,
    CONTINUE,
    DEFAULT,
    DO,
    DOUBLE,
    ELSE,
    ENUM,
    EXTERN,
    FLOAT,
    FOR,
    GOTO,
    IF,
    INT,
    LONG,
    REGISTER,
    RETURN,
    SHORT,
    SIGNED,
    SIZEOF,
    STATIC,
    STRUCT,
    SWITCH,
    TYPEDEF,
    UNION,
    UNSIGNED,
    VOID,
    VOLATILE,
    WHILE,
    ID,        /* letter_|(letter|digits)* */
    INTEGER,   /* digits */
    DECIMAL,   /* С�� */
    HEX, 
    CHARACTER, /* char */
    STRING,    /* char* */
    /* ����� */
    PLUS,         /* + */
    MINUS,        /* - */
    TIMES,        /* * */
    DIVISION,     /* / */
    MOD,          /* % */
    NOT,          /* ! */
    AND,          /* & */
    XOR,          /* ^ */
    OR,           /* | */
    NEFATE,       /* ~ */
    SHL,          /* << */
    SHR,          /* >> */
    ASSIGN,       /* = */
    PLUS_ASSIGN,  /* += */
    MINUS_ASSIGN, /* -= */
    TIMES_ASSIGN, /* *= */
    DIV_ASSIGN,   /* /= */
    MOD_ASSIGN,   /* %= */
    AND_ASSIGN,   /* &= */
    OR_ASSIGN,    /* |= */
    XOR_ASSIGN,   /* ^= */
    MORE,         /* > */
    LESS,         /* < */
    MORE_EQUAL,   /* >= */
    LESS_EQUAL,   /* <= */
    IS_EQUAL,     /* == */
    IS_NOTEQUAL,  /* != */
    AND_AND,      /* && */
    OR_OR,        /* || */
    SELFPLUS,     /* ++ */
    SELFMINUS,    /* -- */
    /* ��� */
    SEMI,             /* ; */
    LPAREN,           /* ( */
    RPAREN,           /* ) */
    COMMA,            /* , */
    DOUBLE_QUOTATION, /* " */
    QUOTATION,        /* ' */
    LBRACKET,         /* [ */
    RBRACKET,         /* ] */
    LCBRACKET,        /* { */
    RCBRACKET,        /* } */
} TOKEN_TYPE;

typedef struct node {
    TOKEN_TYPE type;
    char value[40];
    char key[20];
} node;

/******************************�����ֱ�******************************/
static char* RESERVEWORD[32] = {
    "auto",     "break",  "case",    "char",   "const",    "continue",
    "default",  "do",     "double",  "else",   "enum",     "extern",
    "float",    "for",    "goto",    "if",     "int",      "long",
    "register", "return", "short",   "signed", "sizeof",   "static",
    "struct",   "switch", "typedef", "union",  "unsigned", "void",
    "volatile", "while"};
/********************************************************************/

/******************************����������*****************************/
static const char* OPERATION[31] = {
    "+",
    "-",
    "*",
    "/",
    "%",
    "!",
    /*λ������*/
    "&",
    "^",
    "|",
    "~",
    /*��λ������*/
    "<<",
    ">>",
    /*��ֵ������*/
    "=",
    "+=",
    "-=",
    "*=",
    "/=",
    "%=",
    "&=",
    "|=",
    "^=",
    /*��ϵ������*/
    ">",
    "<",
    ">=",
    "<=",
    "==",
    "!=",
    /*�߼�������*/
    "&&",
    "||",
    /*����*/
    "++",
    "--",
};
/***********************************************************************/

static const char SEPARATOR[10] = {';',  '(', ')', ',', '\"',
                                   '\'', '[', ']', '{', '}'};
/******************************��ʶ����******************************/
// static char* ID_TABLE[1000] = {""};
/*******************************************************************/

/**
 * @description: ���ұ�����
 * @param {char* s}
 * @return {TOKEN_TYPE}
 */
TOKEN_TYPE SEARCH_RESERVE(char* word);

/**
 * @description: �ж��Ƿ�Ϊ��ĸ
 * @param {char letter}
 * @return {bool}
 */
bool IS_LETTER(char letter);

/**
 * @description: �ж��Ƿ�������
 * @param {char digit}
 * @return {bool}
 */
bool IS_DIGIT(char digit);

/**
 * @description: �ж��Ƿ��ǲ�����
 * @param {char* operation}
 * @return {bool}
 */
bool IS_OPERATION(char op);

/**
 * @description: �ж��Ƿ��ǽ��
 * @param {*}
 * @return {*}
 */
bool IS_SEPARATOR(char sep);

/**
 * @description: Ѱ�ҽ�����ֱ���
 * @param {*}
 * @return {*}
 */
TOKEN_TYPE SEARCH_SEPARATOR(char sep);

/**
 * @description: Ѱ�Ҳ��������ֱ���
 * @param {*}
 * @return {*}
 */
TOKEN_TYPE SEARCH_OPERATOR(char* word);

/**
 * @description: Ԥ�������������£�
 *                  1. �޳���������س��������з�
 *                  2. ȥ��ע��
 *                  3. ������ո�Ϊһ��
 * @param {char* src, int length}
 * @return {bool}
 */
int PRETREATMENT(char* src, int length);

/**
 * @description: �ʷ�����������DFAת������
 * @param {char* src, int length}
 * @return {Ԥ����Դ�����ĳ���}
 */
void PROGRAM(struct node* p, FILE* fd2);
struct node* GET_CHAR(struct node* p);
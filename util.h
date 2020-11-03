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
    //错误
    ERROR, //0
    /* 保留字 */
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
    DECIMAL,   /* 小数 */
    HEX, 
    CHARACTER, /* char */
    STRING,    /* char* */
    /* 运算符 */
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
    /* 界符 */
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

/******************************保留字表******************************/
static char* RESERVEWORD[32] = {
    "auto",     "break",  "case",    "char",   "const",    "continue",
    "default",  "do",     "double",  "else",   "enum",     "extern",
    "float",    "for",    "goto",    "if",     "int",      "long",
    "register", "return", "short",   "signed", "sizeof",   "static",
    "struct",   "switch", "typedef", "union",  "unsigned", "void",
    "volatile", "while"};
/********************************************************************/

/******************************界符运算符表*****************************/
static const char* OPERATION[31] = {
    "+",
    "-",
    "*",
    "/",
    "%",
    "!",
    /*位操作符*/
    "&",
    "^",
    "|",
    "~",
    /*移位操作符*/
    "<<",
    ">>",
    /*赋值操作符*/
    "=",
    "+=",
    "-=",
    "*=",
    "/=",
    "%=",
    "&=",
    "|=",
    "^=",
    /*关系操作符*/
    ">",
    "<",
    ">=",
    "<=",
    "==",
    "!=",
    /*逻辑操作符*/
    "&&",
    "||",
    /*其他*/
    "++",
    "--",
};
/***********************************************************************/

static const char SEPARATOR[10] = {';',  '(', ')', ',', '\"',
                                   '\'', '[', ']', '{', '}'};
/******************************标识符表******************************/
// static char* ID_TABLE[1000] = {""};
/*******************************************************************/

/**
 * @description: 查找保留字
 * @param {char* s}
 * @return {TOKEN_TYPE}
 */
TOKEN_TYPE SEARCH_RESERVE(char* word);

/**
 * @description: 判断是否为字母
 * @param {char letter}
 * @return {bool}
 */
bool IS_LETTER(char letter);

/**
 * @description: 判断是否是数字
 * @param {char digit}
 * @return {bool}
 */
bool IS_DIGIT(char digit);

/**
 * @description: 判断是否是操作符
 * @param {char* operation}
 * @return {bool}
 */
bool IS_OPERATION(char op);

/**
 * @description: 判断是否是界符
 * @param {*}
 * @return {*}
 */
bool IS_SEPARATOR(char sep);

/**
 * @description: 寻找界符的种别码
 * @param {*}
 * @return {*}
 */
TOKEN_TYPE SEARCH_SEPARATOR(char sep);

/**
 * @description: 寻找操作符的种别码
 * @param {*}
 * @return {*}
 */
TOKEN_TYPE SEARCH_OPERATOR(char* word);

/**
 * @description: 预处理函数作用如下：
 *                  1. 剔除跳格符、回车符、换行符
 *                  2. 去掉注释
 *                  3. 将多个空格化为一个
 * @param {char* src, int length}
 * @return {bool}
 */
int PRETREATMENT(char* src, int length);

/**
 * @description: 词法分析程序，由DFA转换而来
 * @param {char* src, int length}
 * @return {预处理源程序后的长度}
 */
void PROGRAM(struct node* p, FILE* fd2);
struct node* GET_CHAR(struct node* p);
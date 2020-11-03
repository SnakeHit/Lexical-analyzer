/*
 * @Author: your name
 * @Date: 2020-10-22 12:50:08
 * @LastEditTime: 2020-10-30 22:00:08
 * @LastEditors: Please set LastEditors
 * @Description: In User Settings Edit
 * @FilePath: \AlgorithmsC\OJ\quiz4_1.c
 */
#include <stdio.h>
typedef enum token { ID1, ID2 } token;
int main(void) {
    token t = token(1);
    int a = 10;
    double b = 10.1;
    int c = 0x10;
    printf("result:t=%d\n", t);
    return 0;
}
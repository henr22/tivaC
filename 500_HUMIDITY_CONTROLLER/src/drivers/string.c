/**
 * @file
 */


/*
 * This function handles until 10 digit numbers
 */
#include <stdint.h>
#include "inc/tm4c1230h6pm.h"
#include "string.h"

void itoa(char* buffer, int n)
{
    int i = 0;
    char temp[11];

    if(n == 0)
    {
        temp[i] = '0';
        i++;
    }
    else
    {
        while (n > 0)
        {
           temp[i] = n % 10 + 48; //Convert to ascii
           n /= 10;
           i++;
        }
    }

    temp[i] = 0;

    invertString(temp);
    strCopy(temp, buffer);
}

void invertString(char* a)
{
    int i;
    int j = sizeOfString(a);
    for(i = 0; i < j/2; i++)
    {
        swap(&a[i], &a[j - i - 1]);
    }
}

void swap(char *a, char *b)
{
    char temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

int sizeOfString(char *a)
{
    int size = 0;
    while(*a)
    {
        size++;
        a++;
    }
    return size;
}

void strCopy(char* a, char *b)
{
    while(*a)
    {
        *b = *a;
        a++;
        b++;
    }
    *b = 0;
}


/*
STRING LIBARY

This is a simple String libary in C. Everything is on the heap, an it has a lot of memory leaks.
The String is dynamic in size an various fuctions are avaliable.

Init a String: 
String* myString = fastInitString(char*);

A complet reference can be found in the docs
*/

#ifndef String_c 
#define String_c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char* s;
    int len;
    int maxlen;
} String;

String* initString(){
    String* newstr = (String*) malloc(sizeof(String));
    newstr->s = (char*) malloc(20*sizeof(char));
    newstr->s[0] = '\0';
    newstr->len = 0;
    newstr->maxlen = 20;
    return newstr;
}

int lenChar(char* c){
    return strlen(c);
}

int testIfStringFull(String* s, int size){
    if (s->maxlen < s->len + size){
        return 1;
    }else{
        return 0;
    }
}

void createNewString(String* s){
    char* newCharpointer = (char*) malloc(s->maxlen*2);
    s->s = strcpy(newCharpointer, s->s);
    s->maxlen *= 2;
}

void nullString(String* s){
    s->s[0] = '\0';
    s->len = 0;
}

void addString(String* s, String* s2){
    if (testIfStringFull(s, s2->len)){
        createNewString(s);
    }
    strncat(s->s, s2->s, s2->len);
    s->len += s2->len;
}

void addStringLen(String* s, String* s2, int len){
    if (s2->len < len){
        printf("error the len is longer than the string\n, function: addStringLen\n");
    }
    if (testIfStringFull(s, len)){
        createNewString(s);
    }
    strncat(s->s, s2->s, len);
    s->len += len;
}

void addChar(String* s, char* s2, int len2){
    if(testIfStringFull(s, len2)){
        createNewString(s);
    }
    strncat(s->s, s2, len2);
    s->len += len2;
}

String* fastInitString(char* c){
    String* s = initString();
    addChar(s, c, lenChar(c));
    return s;
}

String* fastInitStringfs(String* s){
    String* new_s = initString();
    addString(new_s, s);
    return new_s;
}

void addStringwithOffset(String* s, String* s2, int len, int offset){
    if (s2->len - len - offset < 0){
        printf("\nerror offset and len is bigger than size of String\n");
    }

    if (testIfStringFull(s, len)){
        createNewString(s);
    }
    strncat(s->s, &s2->s[offset], len);
    s->len += len;
}

void addCharwithOffset(String* s, char* c, int len, int offset){
    if (testIfStringFull(s, len)){
        createNewString(s);
    }
    strncat(s->s, &c[offset], len);
    s->len += len;
}

void printString(String* s){
    printf(s->s);
}

int getIndexOfCharstart(String* s,char* c){ //wierd name
    for (int i = 0; i < s->len; i++){
        if (s->s[i] == *c){
            return i;
        }
    }
    return -1;
}

int getIndexOfChar(String* s, char* c, int offset){
    for (int i = offset; i < s->len; i++){
        if (s->s[i] == *c){
            return i;
        }
    }
    return -1;
}

int cmpCharSeq(String* s, int offset, char* c, int len){
    int r = memcmp(&s->s[offset], c, len);
    if (r == 0){
        return 1;
    } else{
        return 0;
    }
}

int cmpChar(String* s, char* c){
    int len_c = lenChar(c);
    int r = memcmp(s->s, c, len_c);
    if (r == 0){
        return 1;
    }else{
        return 0;
    }
}

int stringcmp(String* s, String* s2){
    if (s->len != s2->len){
        return 0;
    }
    int r = memcmp(s->s, s2->s, s->len);
    if (r == 0){
        return 1;
    }else{
        return 0;
    }
}

int getIndexofCharSeq(String* s, char* c, int len){
    for (int i = 0; i < s->len; i++){
        if (cmpCharSeq(s,i,c,len)){
            return i;
        }
    }
    return -1;
}

int getIndexofCharSeqrev(String* s, char* c, int len){
    for (int i = s->len-len; i >= 0; i--){
        if (cmpCharSeq(s, i, c, len)){
            return i;
        }
    }
    return -1;
}

int* getIndexListofChar(String* s, char* c){
    //first element is the len of the listed
    int res = 0;
    int num = 0;
    while(res != -1){
        res = getIndexOfChar(s, c, res); //not good while loop
        if (res == -1){
            break;
        }
        if (res != -1){
            num += 1;
            res += 1;
        }
    }
    int* list = (int*) malloc((num+1)*sizeof(int));
    list[0] = num;
    res = 0;
    for (int i = 0; i < num; i++){
        list[i+1] = getIndexOfChar(s, c, res);
        res = list[i+1]+1; // notlösung
    }
    return list;
}

String** splitString(String* s, int i){
    if (s->len - i < 0){
        printf("\nerror offset biger than size of string\n");
    }

    String* s1 = initString();
    String* s2 = initString();
    //improvement not add everything to heap, tried but list on the stack corrupts after returning pointers
    String** list = (String**) malloc(2*sizeof(String*));
    addStringLen(s1, s, i);
    addStringwithOffset(s2, s, s->len-i, i);
    list[0] = s1;
    list[1] = s2;
    //return (String* [2]){s1,s2};
    return list; // other way does not work unfortunately
}

String** splitStringcut(String* s, int i){
    if (s->len - i < 0){
        printf("\nerror offset biger than size of string\n");
    }

    String* s1 = initString();
    String* s2 = initString();
    //improvement not add everything to heap
    String** list = (String**) malloc(2*sizeof(String*));
    addStringLen(s1, s, i);
    addStringwithOffset(s2, s, s->len-i-1, i+1);
    list[0] = s1;
    list[1] = s2;
    //return (String* [2]){s1,s2};
    return list; // other way does not work unfortunately
}

void decString(String* s, int n){
    s->s[s->len-n] = '\0';
    s->len -= n;
}

String** splitStringOffset(String* s, int i, int gap){
    if (s->len-i-gap < 0){
        printf("\nerror offset and gap bigger than siez of string\n");
    }

    String* s1 = initString();
    String* s2 = initString();

    String** list = (String**)malloc(2*sizeof(String*));
    
    addStringLen(s1, s, i);
    addStringwithOffset(s2, s, s->len-i-gap, i+gap);
    list[0] = s1;
    list[1] = s2;
    //return (String* [2]) {s1,s2};
    return list; //other way does not work
}

String* getinsertChar(String* s, char* c, int len, int i){
    if (s->len < i){
        printf("error index out of string, fucntion getinsertChar\n");
        return s;
    }
    if (s->len == i){
        String* new_string = fastInitString(s->s);
        addChar(new_string, c, len);
        return new_string;
    }
    if (i == 0){
        String* new_string = fastInitString(c);
        addString(new_string, s);
        return new_string;
    }

    String** list = splitString(s, i);
    addChar(list[0], c, len);
    addString(list[0], list[1]);
    //memory
    free(list[1]);
    free(s);
    
    return list[0];
}

String* getreplaceChar(String* s, char* oldc, int lenold, char* charnew, int lennew){
    int i = getIndexofCharSeq(s, oldc, lenold);
    if (i == -1){
        printf("error could not finde replace string, function gerreaplacechar\n");
        return s;
    }
    String** list = splitStringOffset(s, i, lenold);
    addChar(list[0], charnew, lennew);
    addString(list[0], list[1]);
    
    free(list[1]);
    free(s);
    
    return list[0];
}

String* getreplaceString(String* s, String* olds, String* stringnew){
    int i = getIndexofCharSeq(s, olds->s, olds->len);
    if (i == -1){
        printf("error could not fin replace string, function getreplacestring\n");
        return s;
    }
    String** list = splitStringOffset(s, i, olds->len);
    addString(list[0], stringnew);
    addString(list[0], list[1]);
    
    free(list[1]);
    
    return list[0];
}

String* getreplaceStringlast(String* s, String* olds, String* news){
    int i = getIndexofCharSeqrev(s, olds->s, olds->len);
    if (i == -1){
        printf("error coul not find replave string, function getreplacestringreverse\n");
        return s;
    }
    String** list = splitStringOffset(s, i, olds->len);
    addString(list[0], news);
    addString(list[0], list[1]);
    
    free(list[1]);
    
    return list[0];
}

String* getCharSeqFromString(String* s, int i, int i2){
    if (i2 >= s->len){
        printf("error the index is bigger than the string");
        return s;
    }
    i2 += 1;
    char copy[((i2-i) * sizeof(char))]; 
    strncpy(copy,&s->s[i], i2-i);
    String* new_s = initString();
    addChar(new_s, copy, i2-i);
    return new_s;
}

int searchReverseCharOffsetNum(String* s, char* c, int offset, int num){
    for (int i = offset; i >= 0; i--){
        if (s->s[i] == *c){
            if (num == 0){
                return 0;
            } else {
                num -= 1;
            }
        }
    }

    return -1;
}

int getIndexBorderofCharList(String* s, char** list, int lenList, int offset){
    for (int i = offset+1; i < s->len; i++){
        for (int j = 0; j < lenList; j++){
            if (s->s[i] == *list[j]){
                return i;
            }
        }
    }
    return -1;
}

int getReverseIndexBorderofCharList(String* s, char** list, int lenList, int offset){
    for (int i = offset-1; i > 0; i--){
        for (int j = 0; j < lenList; j++){
            if (s->s[i] == *list[j]){
                return i;
            }
        }
    }
    return -1;
}

#endif

//improvements
//realoc
//strlen
//strncmp

//only handel with the char* not with full strings

//getIndexofCharSeqRev
//getreplaceStringreverse

//write tests




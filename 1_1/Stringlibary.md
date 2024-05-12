# String Libary

### About the Stringlibary

The Stringlibry is a libary how dynamicly handels chararrays and provides useful functions to work with the strings.

Every Stringobject is on the Heap, so it cant get out of scope. In some of the fucntions you get a list of string. Even the list is on the Heap. Some function have memory leaks.

---

### init a string

```String* myString = fastInitString("hallo");```c
```String* myString2 = fastInitStringfs(myString);```

The Init function returns a Pointer to a String Object. The fs at the and of the fucntion *fastInitStringfs()* stands for *from string*. The first fucntion takes a char pointer and the second a String pointer. One does not worry about the len of the char or the string.

alternativ way:

```String* myString = initString();```

Here the function takes no argument and the string is empty.

---

### the String struct

The struct has three fields.

- char* s
- int len
- int maxLen

The s Field holds the pointer to the char field. The len field is an integer how indicates the len of the current string. The maxLen indicates how big the current capasity of the s pointer is.

---

### add new values to the string

There are several fuctions avaliable to add new content to the string.

- ```void addString(String* s, String* s2)```
- ```void addStringLen(String*, String* s2, int len)```
- ```void addStringwithOffset(String* s, String* s2, int len, int offset)```

The first fuction add the content of the second String to the first one. Similar does the second but only a defined range of the second string, starting at the start of the string. The third function alsow takes the offset form the beginning of the string.

- ```void addChar(String* s, char* c, int len)```

With this function one can add a charsequenc, the length must be provided. One can use the *lenChar(char*)* method to get the length of the charsequence.

- ```void addCharwithOffset(String* s, char* c, int len , int offset)```

Similar to the *addStringwithOffset* function, one can does the same with a charsequence.

---

### get information about the string

- ```int getIndexOfCharstart(String* s, char* c)```

This method returns the index of the char from the start. If the char is not in the string, the fucntion returns -1. The char can only be one lether long.

- ```int getIndexofChar(String* s, char* c, int offset)```

This method is similar to the las one but takes an offset, from witch it should begin the search.

- ```int cmpCharSeq(String* s, int offset, char* int len)```

This mehtod compare the charsequence with the length of len, at the position of the offset in the string. If it is similar then the response is 1, otherwise 0.

- ```int cmpChar(String* s, char* c)```

This method compares a string and a charsequence. The char can be longer than one and the length must not be provided.

- ```int stringcmp(String* s, String* s2)```

This method compares two strings.

- ```getIndexofCharSeq(String* s, char* c, int len)```

Returns the index of a charsequence. The lenght of the charsequence must be provided.

- ```int* getIndexListofChar(String* s, char* c)```

This function returns a list of indices of the char. Here again the char can only be one letter long. A corresponding function for char with more then one letter doesn't exist yet.

- ```int searchReverseCharOffsetNum(String* s, char* c, int offset, int num)```

This function returns the index of a singel letter by reverse searching the string from the offset on. The num variable is how many letters we want to jump over. 0 means we want to seach the first letter c. 1 means we want to search the seccond letter c. This and some following function my seems a bit wierd why they are included in a string libary. They have all a very particular usage in the calculator project.

- ```int getIndexBorderofCharList(String* s, char** list, int lenList, int offset)```

This function returns the index of the first character in the string from the offset uppwards, hows in the list. The list conatains singel carracters and the length of the list must be proviedet.

-```int getReverseIndexBorderofCharList(String* s, char** list, int lenList, int offset)```

The same function as above just searchin in reverse order.

---

### manipulating the string

- ```String** splitString(String* s, int i)```

This method splits a string at the index i. The letter at i will be includet at in the upper splitstring. The returntype is a list with tow Stringpointers to the corresponding String. The string at position 0 in the list points to the stringslice bevor i and the string at position 1 to the stringslice after i.

- ```String* splitStringcut(String* s, int i)```

The same method but the letter at i will not be included on any of the two splitstrings.

- ```void decString(String* s, int i)```

This function will decrement the string by the nummber i.

- ```String** splitStringOffset(String* s, int i, int gap)```

Similar function as *splitStringcut* but it deletes a hole gap.

- ```String* getInsertChar(String* s, char* c, int len, int i)```

This method insert a char with the length len at the index i and returns the new String. Attention this one is one of the function that does delet the original s string. Most of the other functions do not touch the original string.

- ```String* getreaplaceChar(String* s, char* oldc, int lenold, char* newc, int lennew)```

This method replaces the first charsegment in the string and replces it with a new char. The length of the chars must not be identical but it must be providet of both, the old end the new char. This function alsow delets the original string.

- ```String* getreaplaceString(String* s, String* olds, String* news)```

This mehtod replaces the hole string olds in the string with the news string. This function does not delet the original string.

- ```String* getCharSeqFromSTring(String* s, int i, int i2)```

This function returns a slice of a string with the indexbounderies i and i2. The returntype is a string not a char.

### other functions

You will see in the source code, there are other functions you can use:

- ```int lenChar(char*)```

Takes a charpointer and returs the len of the char as an integer.

- ```int testIfStringFull(String* s, int size)```

This fuction takes a Stringpoiner an the size of the charsequence, one want to add. The returntype is an integer. But it indicates only if the sting would be full with the new chararray. 1 means yes, the string is full and 0 not.

- ```String* createNewString(String* s)```

This function takes the Stringpointer and creates a new chararray with zwice the size of the old chararray and copies the old stuff into the new one.

- ```void nullString(String* s)```

This fuction delelets all stuff in the string.

- ```printString(String* s)```

This method takes the string and prints the content.

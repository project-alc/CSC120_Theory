//     _    _     ____ 
//    / \  | |   / ___|
//   / _ \ | |  | |    
//  / ___ \| |__| |___ 
// /_/   \_\_____\____|
//
//
// This program is an assignment for Professor Anderson's CSC 120 class at Mesa Community College
// The author of this program is Austin Covingon
//
// To build this program, you must have a C compliler (cygwin on windows, X-Code on mac, clang or gcc on linux or bsd)
// and library implementation of the below libraries. This program was build in a linux machine
// running Artix linux and built using the gcc compliler with the glibc libraries.
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

void printTitle()
{
  printf(" _____                        __  _   _                     \n");
  printf("|  ___|   _ _ __   __      __/ / | \\ | |_   _ _ __ ___  ___ \n");
  printf("| |_ | | | | '_ \\  \\ \\ /\\ / / /  |  \\| | | | | '_ ` _ \\/ __|\n");
  printf("|  _|| |_| | | | |  \\ V  V / /   | |\\  | |_| | | | | | \\__ \\\n");
  printf("|_|   \\__,_|_| |_|   \\_/\\_/_/    |_| \\_|\\__,_|_| |_| |_|___/\n");
  printf("\n\n\n");
  printf("Welcome to Fun w/ Nums! This program allows users to convert numbers between different bases such as\n");
  printf("base 10 (decimal) and base 16 (hexadecimal). Additionally, you can add and subtract numbers of any base\n");
  printf("in this program. This program has a base range of 2 to 62 (all digits and letters, capital and lowercase)\n");
  printf("There is even a \"Tutorial\" mode that shows you step by step how to perform the \n");
  printf("operations.\n\n\n");
  printf("Program by Austin Covington for CSC120: Digital Design at Mesa Community College\n\n\n");
}

// int min(int s1, int s2)
// {
//   return s1 <= s2 ? s1 : s2;
// }
// The following function takes in the full list of values this program accepts as input
// [0-z] and prints the valid values for the base the user chose (ie if base 16, [0-F].
// The table printed is read in pairs from left to right, top to bottom with the first value of
// the pair being the decimal value and the second being the base value (ie 15 | F). Pairs are
// split up with || symbol.
void listValues(char* list[], int base)
{
  printf("\n\n\n--------------------------------------------\n");
  printf("--------------------------------------------\n");
  printf("\tValue table for base %d\n", base);
  switch (base)
  {
    case 2: 
      printf("| Value | Base Num ||\t | Value | Base NUM ||");
      printf("\n----------------------------------------------\n");
      break;
    case 3: 
      printf("| Value | Base Num ||\t | Value | Base NUM ||\t | Value | Base NUM ||");
      printf("\n----------------------------------------------------------------------\n");
      break;
    case 4: 
      printf("| Value | Base Num ||\t | Value | Base NUM ||\t | Value | Base NUM ||\t | Value | Base NUM ||");
      printf("\n----------------------------------------------------------------------------------------------\n");
      break;
    default: 
      printf("| Value | Base Num ||\t | Value | Base NUM ||\t | Value | Base NUM ||\t | Value | Base NUM ||\t | Value | Base NUM ||");
      break;
  }
  for(int i = 0; i < base; i++)
  {
    if( ((i % 5) == 0) && (base > 4) )
      printf("\n----------------------------------------------------------------------------------------------------------------------\n");
    printf("| %5d | %8s ||\t ", i, list[i]);
    if( (i) == (base-1) )
      printf("\n");
  }
  printf("***TIP***\n");
  printf("Add one to the value to get the respective base that value shows up in (e.g. A's value is 10,\n but shows up in base 11)");
}

int convertToTen(char* list[], int base, char word[], int size)
{
  int value = 0;
  for(int i = 1; i <= size; i++)
  {
    // printf("looking for value %c\n", word[size - (i)]);
    for(int j = 0; j < base; j++)
    {
      if(word[size - (i)] == *list[j])
      {
        value += j * (int)(pow(base, (i-1) ));
        // printf("found value %c and converted it to %d\n", *list[j], j);
        break;
      }
    }
  }
  // printf("%d\n", value);
  return value;
}

int checkNum(char* list[], int base, char word[], int size)
{
  if(strlen(word) != size)
  {
    printf("You entered a value of size %lu which does not match the value of %d\n", strlen(word), size);
    printf("Please enter a valid number: ");
    return 0;
  }
  int checked = 1;
  for(int i = 0; i < size; i++)
  {
    for(int j = 0; j <= base; j++)
    {
      if(j == base)
      {
        checked = 0;
        break;
      }
      if(word[i] == *list[j])
      {
        break;
      }
    }
  }
  if( checked == 0)
  {
    printf("The number you entered is not possible in this base\n");
    printf("Possible values are listed below\n");
    listValues(list, base);
    printf("Please enter a valid number: ");
  }
  return checked;
}

void convert(char* list[], char* originalWord, int originalBase, char* targetWord, int targetBase, int size)
{
  free(targetWord);
  int numb10 = convertToTen(list, originalBase, originalWord, size);
  int i = numb10;
  int newWordSize = 1;
  int newNumIndex;
  // printf("i is %d\n", i);
  while((i / targetBase) >= 1)
  {
    i = i / targetBase; 
    // printf("i is %d\n", i);
    newWordSize++;
  }
  // printf("New word size is %d\n", newWordSize);
  targetWord = malloc(newWordSize + 1);
  targetWord[newWordSize] = '\0';
  for(int j = 1; j <= newWordSize; j++)
  {
    // printf("Starting numb10 is %d\n", numb10);
    newNumIndex = numb10 % targetBase;
    // printf("%d mod %d is %d\n", numb10, targetBase, newNumIndex);
    numb10 = numb10 / targetBase;
    // printf("New numb10 is %d\n", numb10);
    // printf("Prepending %c to %s at index position %d\n", *list[newNumIndex], targetWord, (newWordSize+1-j));
    targetWord[newWordSize - j] = *list[newNumIndex];
  }
  printf("\n\n\n*********************************************************************\n");
  printf("%s in base %d is equal to %s in base %d\n", originalWord, originalBase, targetWord, targetBase);
  printf("*********************************************************************\n");
}

void complement(char* list[], char* originalWord, int originalBase, char* targetWord, int size)
{
  // printf("%s is being changed and has size %d\n", originalWord, size);
  free(targetWord);
  int carry = 1;
  //char* maxWord = malloc(size + 1);
  targetWord = malloc(size + 1);
  targetWord[size] = '\0';
  // maxWord[size] = '\0';
  // for (int i = 1; i <= size; i++) {
  //   maxWord[size - i] = *list[originalBase - 1];
  // }
  int indexArray[size];
  // printf("HERE!!!\n");
  // printf("%s is being complemented!!!\n", originalWord);
  // for(int i = 0; i < size; i++)
  // {
  //   // printf("og value %c is at index %d\n", originalWord[i], i);
  //   for(int j = 0; j < originalBase; j++)
  //   { 
  //     if(originalWord[i] == *list[j])
  //     {
  //       // printf("list value %c is at index %d\n", *list[j], j);
  //       indexArray[i] = originalBase - 1 - j;
  //     }
  //   }
  // }
  for(int i = size - 1; i >= 0; i--)
  {
    // printf("%d is the index\n", i);
    // printf("%c is the character\n", originalWord[i]);
    // printf("%s is the thing\n", originalWord);
    // printf("%lu is the the size\n", strlen(originalWord));
    for(int j = 0; j < originalBase; j++)
    {
      // printf("%c is ? to %c\n", *list[j], originalWord[i]);
      if(originalWord[i] == *list[j])
      {
        // printf("found letter\n");
        indexArray[i] = originalBase - 1 - j;
        // printf("inserted letter\n");
        break;
      }
    }
  }
  // printf("HERE!");

  
  for(int i = size - 1; i >= 0; i--)
  {
    if((indexArray[i] + carry) == originalBase)
    {
      targetWord[i] = *list[0];
      carry = 1;
    } else
    {
      targetWord[i] = *list[indexArray[i] + carry];
      carry = 0;
    }
    // printf("Replaced index %d with %c\n", i, *list[indexArray[i] + carry]);
  }
  printf("\n\n\n*********************************************************************\n");
  printf("%s in base %d complemented is %s\n", originalWord, originalBase, targetWord);
  printf("*********************************************************************\n");
  // printf("The compement function is returning %s\n", targetWord);
  // printf("The compement function is returning %s\n", targetWord);
  // printf("The compement function is returning %s\n", targetWord);
  // printf("The compement function is returning %s\n", targetWord);
  // printf("The compement function is returning %s\n", targetWord);
  // printf("The compement function is returning %s\n", targetWord);
}

void add(char* list[], char* add1, int base1, int size1, char* add2, int base2, int size2, int targetBase, int sub )
{ 
  int ten1 = convertToTen(list, base1, add1, size1);
  int ten2 = convertToTen(list, base2, add2, size2);
  char* complementedadd2;
  char* tempWord;
  int swap = 0;
  int newWordSize = 0;
  //int minBase = min(min(base1, base2), targetBase);
  // printf("-------------------------------------------------------------------\n");
  // printf("-------------------------------------------------------------------\n");
  // printf("-------------------------------------------------------------------\n");
  char* newBaseadd1 = malloc(1);
  char* newBaseadd2 = malloc(1);
  // printf("size of %s is %lu\n", newBaseadd1, strlen(newBaseadd1));
  // printf("size of %s is %lu\n", newBaseadd2, strlen(newBaseadd2));
  //if(base1 != targetBase)
    convert(list, add1, base1, newBaseadd1, targetBase, size1);
  //if(base2 != targetBase)
    convert(list, add2, base2, newBaseadd2, targetBase, size2);

  if(strlen(newBaseadd1) > strlen(newBaseadd2))
  {
  newWordSize = strlen(newBaseadd1);
  } else
  {
  newWordSize = strlen(newBaseadd2);
  }
  if(sub == 1)
  {
    complementedadd2 = malloc(1);
    if(ten2 > ten1)
    {
      // printf("%s and %s\n", newBaseadd1, newBaseadd2);
      tempWord = malloc(newWordSize+1);
      strcpy(tempWord, newBaseadd2);
      // printf("switching words!\n");
      // printf("%s and %s\n", newBaseadd1, newBaseadd2);
      free(newBaseadd2);
      newBaseadd2 = malloc(newWordSize + 1);
      strcpy(newBaseadd2, newBaseadd1);
      // printf("switching words!\n");
      // printf("%s and %s\n", newBaseadd1, newBaseadd2);
      free(newBaseadd1);
      newBaseadd1 = malloc(newWordSize + 1);
      strcpy(newBaseadd1, tempWord);
      // printf("%s and %s\n", newBaseadd1, newBaseadd2);
      // printf("switching words!\n");
      swap = 1;
    }
    // printf("***complementadd2 is %s\n", complementedadd2);
    complement(list, newBaseadd2, targetBase, complementedadd2, (int)(strlen(newBaseadd2)));
    // printf("I am here!\n");
    // printf("\n\nThe complement functions returned: %s\n\n", complementedadd2);
    free(newBaseadd2);
    newBaseadd2 = malloc(strlen(complementedadd2) + 1);
    strcpy(newBaseadd2, complementedadd2);
  }
  printf("\n\n\n*********************************************************************\n");
  printf("%s is now %s and %s is now %s\n", add1, newBaseadd1, add2, newBaseadd2);
  printf("*********************************************************************\n");
  // printf("size of %s is %lu\n", newBaseadd1, strlen(newBaseadd1));
  // printf("size of %s is %lu\n", newBaseadd2, strlen(newBaseadd2));
  // printf("size of %s is %lu\n", newBaseadd1, sizeof(newBaseadd1));
  // printf("size of %s is %lu\n", newBaseadd2, sizeof(newBaseadd2));
  // printf("newWordSize is %d\n", newWordSize);
  int indexArray1[newWordSize];
  int indexArray2[newWordSize];
  int carry = 0;
  char* targetWord;
  targetWord = malloc(newWordSize + 2);
  // printf("Allocated %d bite(s) of memory for targetWord!\n", newWordSize + 2);
  targetWord[newWordSize + 1] = '\0';
  // printf("Target Word Created!\n");
  int buffCheck = 0;
  int pad;
  if(sub == 1)
  {
    pad = targetBase - 1;
  } else
  {
    pad = 0;
  }

  for(int i = 0; i < newWordSize; i++)
  {
    // printf("In the first for loop with index %d\n", i);
    buffCheck = i + strlen(newBaseadd1) - newWordSize;
    // printf("buffCheck is %d\n", buffCheck);
    if(buffCheck < 0)
    {
      indexArray1[i] = 0;
      // printf("buffered indexArray1 with a 0\n");
    }
    else
    { 
      for(int j = 0; j < targetBase; j++)
      {
        if(newBaseadd1[buffCheck] == *list[j])
          indexArray1[i] = j;
      }
    }
  }

  for(int i = 0; i < newWordSize; i++)
  {
    // printf("In the second for loop with index %d\n", i);
    buffCheck = i + strlen(newBaseadd2) - newWordSize;
    // printf("buffCheck is %d\n", buffCheck);
    if(buffCheck < 0)
    {
      indexArray2[i] = pad;
    }
    else
    { 
      for(int j = 0; j < targetBase; j++)
      {
        if(newBaseadd2[buffCheck] == *list[j])
          indexArray2[i] = j;
      }
    }
  }

  // printf("Both indexArrays have been populated\n");
  for(int i = newWordSize - 1; i >= 0; i--)
  {
    // printf("In final for loop with index %d\n", i);
    if((indexArray1[i] + indexArray2[i] + carry) >= targetBase)
    {
      // printf("indexArray1[%d] is %d and indexArray2[%d] is %d\n", i, indexArray1[i], i, indexArray2[i]);
      targetWord[i+1] = *list[indexArray1[i] + indexArray2[i] + carry - targetBase];
      carry = 1;
    } else
    {
      // printf("indexArray1[%d] is %d and indexArray2[%d] is %d\n", i, indexArray1[i], i, indexArray2[i]);
      targetWord[i+1] = *list[indexArray1[i] + indexArray2[i] + carry];
      carry = 0;
    }
  }
  if(carry == 1)
  {
    if(sub == 1)
    {
      targetWord[0] = '0';
    }else
    {
      printf("\n\n\n*********************************************************************\n");
      printf("You had a carry value of 1!\n");
      printf("*********************************************************************\n");
      targetWord[0] = '1';
    }
  } else
  {
    if(sub ==1)
    {
      printf("You did not have a carry during subtraction!\n");
    }
    printf("\n\n\n*********************************************************************\n");
    printf("The carry value is 0\n");
    printf("*********************************************************************\n");
    targetWord[0] = '0';
  }

  // if(sub == 1)
  // {
  //   printf("In sub\n");
  //   if(tC == -1)
  //   {
  //     printf("In tc == -1\n");
  //     for(int j = 0; j < newWordSize; j++)
  //     {
  //       if(indexArray2[j] != 0)
  //       {
  //         printf("Found non-padded number at index %d\n", j);
  //         for(int i = 0; i < targetBase; i++)
  //         {
  //           if(targetWord[j] == *list[i])
  //           {
  //             printf("targetWord at index %d is %c", j, targetWord[j]);
  //             targetWord[j] = *list[i - 1];
  //             break;
  //           }
  //         }
  //         break;
  //       } else
  //       {
  //         printf("padded 0\n");
  //       }
  //     }
  //   } else
  //   {
  //     printf("In tc != -1, where tC is %d and newWordSize is %d\n", tC, newWordSize);
  //     for(int j = 1; j < targetBase; j++)
  //     {
  //       if(targetWord[tC - 1] == *list[j])
  //         targetWord[tC - 1] = *list[j-1];
  //     }
  //   }
  // }
  if(swap == 1)
  {
    printf("In swap!\n");
    free(tempWord);
    tempWord = malloc(strlen(targetWord) + 1);
    complement(list, targetWord, targetBase, tempWord, (int)(strlen(targetWord)));
    free(targetWord);
    targetWord = malloc(newWordSize + 1);
    strcpy(targetWord, tempWord);
  }
  printf("\n\n\n*********************************************************************\n");
  printf("The %s of %s in base %d and %s in base %d yielded %s in base %d\n",
         ((sub == 0) ? "addition" : "subtraction"), add1, base1, add2, base2, targetWord, targetBase);
  printf("*********************************************************************\n");
}


int main( void )
{
  int wordSize = 0;
  int wordSize2 = 0;
  int base1 = 0;
  int base2 = 0;
  char *word1 = malloc(1);
  char *word2 = malloc(1);
  int checkValid = 0;
  int checkSize = 0;
  int opt = 1;
  int sub = 0;
  int targetB;
  char* mode = malloc(1);
  char* valueList[62] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
                         "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
                         "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
                         "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m",
                         "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};
  printTitle();

  while(opt != 0)
  {
    printf("What would you like to do?\n");
    printf("1: Convert a number from one base to another\n");
    printf("2: Perform a complement of a given number and base\n");
    printf("3: Add two numbers\n");
    printf("4: Subtract two numbers\n");
    printf("5: Turn on tutorial mode\n");
    printf("6: Print title\n");
    printf("7: Print Full list of values (Base 62)\n");
    // printf("\n\n-1: Quit the program\n\n");
    printf("Please enter a valid option: ");
    scanf("%d", &opt);
    switch (opt) {
      case 1:
        while(base1 < 2 || base1 > 62)
        {
        printf("Enter the base you would like to convert from: ");
        scanf("%d", &base1);
        }
        while(base2 < 2 || base2> 62)
        {
        printf("Enter the base you would like to convert to: ");
        scanf("%d", &base2);
        }
        printf("Please enter a size for your number (1010 has a size of 4): ");
        scanf("%d", &wordSize);
        printf("Enter the value you want to convert: ");
        while(checkValid != 1)
        {
          if(word1 != NULL)
            free(word1);
          word1 = malloc(wordSize + 1);
          scanf("%s", word1);
          checkValid = checkNum(valueList, base1, word1, wordSize);
        }
        word2 = malloc(wordSize + 1);
        convert(valueList, word1, base1, word2, base2, wordSize);
        break;
      case 2:
        printf("Enter the base you want to work in: ");
        scanf("%d", &base1);
        printf("Please enter a size for your number (1010 has a size of 4): ");
        scanf("%d", &wordSize);
        printf("Enter the value you want to complement: ");
        while(checkValid != 1)
        {
          if(word1 != NULL)
            free(word1);
          word1 = malloc(wordSize + 1);
          scanf("%s", word1);
          checkValid = checkNum(valueList, base1, word1, wordSize);
        }
        word2 = malloc(wordSize + 1);
        complement(valueList, word1, base1, word2, wordSize);
        break;
      case 3:
        printf("Enter the base of your first number: ");
        scanf("%d", &base1);
        printf("Please enter a size for your number (1010 has a size of 4): ");
        scanf("%d", &wordSize);
        printf("Enter your first value: ");
        while(checkValid != 1)
        {
          if(word1 != NULL)
            free(word1);
          word1 = malloc(wordSize + 1);
          scanf("%s", word1);
          checkValid = checkNum(valueList, base1, word1, wordSize);
        }
        checkValid = 0;
        printf("Enter the base of your second number: ");
        scanf("%d", &base2);
        printf("Please enter a size for your number (1010 has a size of 4): ");
        scanf("%d", &wordSize2);
        printf("Enter your second value: ");
        while(checkValid != 1)
        {
          if(word2 != NULL)
            free(word2);
          word2 = malloc(wordSize2 + 1);
          scanf("%s", word2);
          checkValid = checkNum(valueList, base2, word2, wordSize2);
        }
        printf("Enter a base for your final answer: ");
        scanf("%d", &targetB);
        printf("You entered %s for your first number and %s for your second number. The target base is %d\n",
               word1, word2, targetB);
        add(valueList, word1, base1, wordSize, word2, base2, wordSize2, targetB, sub);
        break;
      // case 4:
      //   sub = 1;
      //   printf("Enter the base of your first number: ");
      //   scanf("%d", &base1);
      //   printf("Please enter a size for your number (1010 has a size of 4): ");
      //   scanf("%d", )
      //   printf("Enter the base you would like to convert to: ");
      //   scanf("%d", &base2);
      //   printf("Please enter a size for your number (1010 has a size of 4): ");
      //   scanf("%d", &wordSize);
      //   printf("Enter the value you want to convert: ");
      //   while(checkValid != 1)
      //   {
      //     if(word1 != NULL)
      //       free(word1);
      //     word1 = malloc(wordSize + 1);
      //     scanf("%s", word1);
      //     checkValid = checkNum(valueList, base1, word1, wordSize);
      //   }
      //   word2 = malloc(wordSize + 1);
      //   convert(valueList, word1, base1, word2, base2, wordSize);
      //   break;
      // case 2:
      //   printf("Enter the base you want to work in: ");
      //   scanf("%d", &base1);
      //   printf("Please enter a size for your number (1010 has a size of 4): ");
      //   scanf("%d", &wordSize);
      //   printf("Enter the value you want to complement: ");
      //   while(checkValid != 1)
      //   {
      //     if(word1 != NULL)
      //       free(word1);
      //     word1 = malloc(wordSize + 1);
      //     scanf("%s", word1);
      //     checkValid = checkNum(valueList, base1, word1, wordSize);
      //   }
      //   word2 = malloc(wordSize + 1);
      //   complement(valueList, word1, base1, word2, wordSize);
      //   break;
      // case 3:
      //   printf("Enter the base of your first number: ");
      //   scanf("%d", &base1);
      //   printf("Please enter a size for your number (1010 has a size of 4): ");
      //   scanf("%d", &wordSize);
      //   printf("Enter your first value: ");
      //   while(checkValid != 1)
      //   {
      //     if(word1 != NULL)
      //       free(word1);
      //     word1 = malloc(wordSize + 1);
      //     scanf("%s", word1);
      //     checkValid = checkNum(valueList, base1, word1, wordSize);
      //   }
      //   checkValid = 0;
      //   printf("Enter the base of your second number: ");
      //   scanf("%d", &base2);
      //   printf("Please enter a size for your number (1010 has a size of 4): ");
      //   scanf("%d", &wordSize2);
      //   printf("Enter your second value: ");
      //   while(checkValid != 1)
      //   {
      //     if(word2 != NULL)
      //       free(word2);
      //     word2 = malloc(wordSize2 + 1);
      //     scanf("%s", word2);
      //     checkValid = checkNum(valueList, base2, word2, wordSize2);
      //   }
      //   printf("Enter a base for your final answer: ");
      //   scanf("%d", &targetB);
      //   printf("You entered %s for your first number and %s for your second number. The target base is %d\n",
      //          word1, word2, targetB);
      //   add(valueList, word1, base1, wordSize, word2, base2, wordSize2, targetB, sub);
      //   break;
      case 4:
        sub = 1;
        printf("Enter the base of your first number: ");
        scanf("%d", &base1);
        printf("Please enter a size for your number (1010 has a size of 4): ");
        scanf("%d", &wordSize);
        printf("Enter your first value: ");
        while(checkValid != 1)
        {
          if(word1 != NULL)
            free(word1);
          word1 = malloc(wordSize + 1);
          scanf("%s", word1);
          checkValid = checkNum(valueList, base1, word1, wordSize);
        }
        checkValid = 0;
        printf("Enter the base of your second number: ");
        scanf("%d", &base2);
        printf("Please enter a size for your number (1010 has a size of 4): ");
        scanf("%d", &wordSize2);
        printf("Enter your second value: ");
        while(checkValid != 1)
        {
          if(word2 != NULL)
            free(word2);
          word2 = malloc(wordSize2 + 1);
          scanf("%s", word2);
          checkValid = checkNum(valueList, base2, word2, wordSize2);
        }
        printf("Enter a base for your final answer: ");
        scanf("%d", &targetB);
        printf("You entered %s for your first number and %s for your second number. The target base is %d\n",
               word1, word2, targetB);
        add(valueList, word1, base1, wordSize, word2, base2, wordSize2, targetB, sub);
        break;
      case 5:
        break;
      case 6:
        printTitle();
      case 7:
        listValues(valueList, 62);
        break;
      default:
        continue;
    }
    free(word1);
    free(word2);
    char *word1 = malloc(1);
    char *word2 = malloc(1);
    base1 = 0;
    base2 = 0;
    checkValid = 0;
    printf("\n\n\n");
    printf("Would you like to continue?\nEnter 1 for yes and 0 for no: ");
    scanf("%d", &opt);
    printf("\n\n\n");
  }

  return 0;
}
                                                            
                    

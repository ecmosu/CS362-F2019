#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
  //Generate random character between ' ' 32 and '~' 126
  //(126 - 32) + 1 = 95
  return (rand() % 95) + 32;
}

char *inputString()
{
  static char randomString[6];
  for(int i = 0; i < 5; i++)
  {
    //Generate random character between 'r' (114) and 't' (116)
    //(116 - 114) + 1 = 3 + 1 (for e when 0) = 4
    int randomChar = (rand() % 4);
    if(randomChar == 0)
    {
      randomString[i] = 'e'; 
    }
    else
    {
      randomString[i] = randomChar + 113;
    }    
  }
  randomString[5] = '\0';
  return randomString;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}

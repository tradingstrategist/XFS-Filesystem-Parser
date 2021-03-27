#include <stdio.h>

char * strcat(char * dest, const char * src)
{
    char *tmp = dest;
    while (*dest)
        dest++;
    while ((*dest++ = *src++) != '\0')
        ;
    return tmp;
}

int execmd(char* cmd,char* result) {
    char buffer[128];                                   
    FILE* pipe = popen(cmd, "r"); 
    if (!pipe)
        return 0;
                                
    while(!feof(pipe)) {
        if(fgets(buffer, 128, pipe)){
            strcat(result,buffer);
        }
    }
    pclose(pipe);
 
    return 1; 
}


char* strtok(char *s, const char *delim)
{
  const char *spanp;
  int c, sc;
  char *tok;
  static char *last;
 
  if (s == NULL && (s = last) == NULL)
    return (NULL);

 cont:
  c = *s++;
  for (spanp = delim; (sc = *spanp++) != 0;) {
    if (c == sc)
      goto cont;
  }
  

  if (c == 0) {                 /* no non-delimiter characters */
    last = NULL;
    return (NULL);
  }
  tok = s - 1;    
 

  for (;;) {
    c = *s++;
    spanp = delim;

    do {
      if ((sc = *spanp++) == c) {
        if (c == 0)
          s = NULL;
        else
          s[-1] = 0;
        last = s;
        return (tok);
      }
    } while (sc != 0);
  }
  /* NOTREACHED */
}

char* strstr(const char *str1, const char *str2)
{
    char *cp = (char *)str1;
    char *s1, *s2;
    if (!*str2)
        return((char *)str1);
    while (*cp)
    {
        s1 = cp;
        s2 = (char *)str2;
        while (*s2 && !(*s1 - *s2))
            s1++, s2++;
        if (!*s2)
            return(cp);
        cp++;
    }
    return(NULL);
}

int main(){
    char result[1024*4]="";
    if(1==execmd("xfs_db -r /dev/sda3 -c sb -c p",result)){
        printf("********************************************SuperBlock*******************************************");
        printf(result);
    }

    char *delim = "\n";
    char *p;

    strtok(result, delim);
    while((p = strtok(NULL, delim)))
    {

        if(strstr(p,"blocksize")) 
        {
            printf("*********************************Blocksize Parsed*************************************\n");
            printf("%s \n", p);
        }
        break;
    }    
} 

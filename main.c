#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void reverse_number(char* number)
{
  char temp;
  int size = strlen(number) - 1;
  int j = size;
  for(int i = 0; i < size/2+1; i++)
  {
    temp = *(number+j);
    *(number+j) = *(number+i);
    *(number+i) = temp;
    j--;
  }
}

int validate(const char *number)
{
  if(number==NULL)return -1;
  int size=strlen(number);
  if(size==0)return 2;
  if(size==1 && *(number+0)=='-' )return 2;
  if(size!=1 && *(number+0) == '0' )return 2;
  if(size>1 && *(number+0) == '-' && *(number+1)=='0' )return 2;
  for(int i=0;i<size;i++)
  {
    if( isdigit( *(number+i) ) == 0) 
    {
      if(i==0)
      {
        if(*(number+i) != '-')
        {
          return 2;
        }
      }
      else
      {
        return 2;
      }
    }
  }
  return 0;
}

int compare(const char* number1, const char* number2)
{
  if(number1==NULL || number2==NULL) return 2;
  if( validate(number1) != 0 || validate(number2) != 0 ) return 3;
  int size1=strlen(number1);
  int size2=strlen(number2);
  
  if(*number1=='-' && *number2!='-')return -1;;
  if(*number2=='-' && *number1!='-')return 1;;

  if(*(number1+0)!='-' && *(number2+0)!='-')  
  {
    if(size1>size2)
    {
      return 1;
    }
    if(size2>size1)
    {
      return -1;
    }
  }
  if(*(number1+0)=='-' && *(number2+0)=='-')  
  {
    if(size1>size2)
    {
      return -1;
    }
    if(size2>size1)
    {
      return 1;
    }
  }

  int x = strcmp(number1,number2);
  if(*(number1+0)=='-' && *(number2+0)=='-')  x=-x;
  if(x<0)return -1;
  else if(x>0)return 1;
  return 0;
}


int dodawanie(const char *number1, const char *number2, char** result, int minus)
{
  if(number1==NULL || number2==NULL || result==NULL) return 1;
  if( validate(number1) != 0 || validate(number2) != 0 ) return 2;
  int size1=strlen(number1);
  int size2=strlen(number2);
  int size_to_alloc=2;
  *result=malloc(size_to_alloc);
  if(*result==NULL)return 3;
  char*temp;
  int i=0;
  int koniec;
  if(size1 > size2)
  {
    koniec = size1;
  }
  else
  {
    koniec = size2;
  }
  for(i=0; i<koniec; i++,size_to_alloc++)
  {
    temp=realloc(*result,size_to_alloc);
    if(temp == NULL)
    {
      free(*result);
      return 3;
    }
    *result=temp;
    *(*result+i)=0;
    if(i<size1)
    {
      *(*result+i) += *(number1 + size1-1-i );
    }
    if(i<size2)
    {
      *(*result+i) += *(number2 + size2-1-i );
    }
    if(i<size1 && i<size2 )
    {
    *(*result+i) -= '0' ;
    }
  }
  *(*result+i)='\0';
  for(i=0;i<size_to_alloc-2;i++)
  {
    if( *(*result+i) > '9')
    {
      if(i==size_to_alloc-3)
      {
        size_to_alloc++;
        temp=realloc(*result,size_to_alloc);
        if(temp == NULL)
        {
          free(*result);
          return 3;
        }
        *result=temp;
        *(*result+i)=*(*result+i)-10;
        *(*result+i+1)='1';
        *(*result+i+2)='\0';
        break;
      }
        *(*result+i)=*(*result+i)-10;
        *(*result+i+1) += 1;
    }
  }
   if( minus==1 )
   {
      temp=realloc(*result,size_to_alloc);
      if(temp == NULL)
      {
        free(*result);
        return 3;
      }
    *result=temp;
     int size=strlen(*result);
     *(*result+size) = '-';
     *(*result+size+1)='\0';
   }

  reverse_number(*result);
  return 0;
}

int odejmowanie(const char *number1, const char *number2, char** result,int minus)
{
  if(number1==NULL || number2==NULL || result==NULL) return 1;
  if( validate(number1) != 0 || validate(number2) != 0 ) return 2;
  
  int size1=strlen(number1);
  int size2=strlen(number2);
  int size_to_alloc=2;
  *result=malloc(size_to_alloc);
  if(*result==NULL)return 3;
  char* temp;
  int i=0;
  int koniec;
  if(size1 > size2)
  {
    koniec = size1;
  }
  else
  {
    koniec = size2;
  }

  for(i=0; i<koniec; i++,size_to_alloc++)
  {
    temp=realloc(*result,size_to_alloc);
    if(temp == NULL)
    {
      free(*result);
      return 3;
    }
    *result=temp;
    *(*result+i)=0;
    if(i<size1)
    {
      *(*result+i) += *(number1 + size1-1-i );
    }
    if(i<size2)
    {
      *(*result+i) -= *(number2 + size2-1-i );
    }
    if(i<size1 && i<size2 )
    {
      *(*result+i) += '0' ;
    }
  }
  *(*result+i)='\0';

    for(i=0;i<size_to_alloc-2;i++)
    {
      if( *(*result+i) < '0')
      {
        if( i==size_to_alloc-3 )
        {
          size_to_alloc++;
          temp=realloc(*result,size_to_alloc);
          if(temp == NULL)
          {
            free(*result);
            return 3;
          }
          *result=temp;
          *(*result+i+1)= 10 +  ( *(*result+i) );
          *(*result+i+2)='-';
          *(*result+i+3)='\0';
          break;
        }
        *(*result+i)= 10 + ( *(*result+i) );
        *(*result+i+1) -= 1;
      }
    }
  
  while(1)
  {
    int size=strlen(*result);
    if(*(*result+size-1)=='0')*(*result+size-1)='\0';
    else
    {
      break;
    }
  }

  if( minus==1 )
  {
    temp=realloc(*result,size_to_alloc);
    if(temp == NULL)
    {
      free(*result);
      return 3;
    }
    *result=temp;
    int size=strlen(*result);
    *(*result+size) = '-';
    *(*result+size+1)='\0';
  }

  reverse_number(*result);
  for(i=1;i<size_to_alloc-2;i++)
  {
    if(*(*result+i)<'0' || *(*result+i)>'9')
    {
      *(*result+i)='\0';
    }
  }
  return 0;
}



int add(const char *number1, const char *number2, char** result)
{
  if(number1==NULL || number2==NULL || result==NULL) return 1;
  if( validate(number1) != 0 || validate(number2) != 0 ) return 2;
  int size1=strlen(number1);
  int size2=strlen(number2);
  if( *(number1+0) != '-' && *(number2+0) != '-' )
  {
    return dodawanie(number1,number2,result,0);
  }

  else if( (*(number1+0) == '-' && *(number2+0) == '-') )
  {
    return dodawanie(number1+1,number2+1,result,1);
  }

  else if( *(number1) == '-' )
  {
    if(size1-1>size2)
    {
      return odejmowanie(number1+1,number2,result,1);
    }
    else if(size2>size1-1)
    {
      return odejmowanie(number2,number1+1,result,0);
    }
    else
    {
      int x = compare(number1+1,number2);
      if(x==0)
      {
        *result=malloc(2);
        *(*result+0)='0';
        *(*result+1)='\0';
      } 
      else if( x<0 )
      {
        return odejmowanie(number2,number1+1,result,0);
      }
      else
      {
        return odejmowanie(number1+1,number2,result,1);
      }
    }
    
    
  }
  else if( *(number2) == '-')
  {
    if(size1>size2-1)
    {
      return odejmowanie(number1,number2+1,result,0);
    }
    else if(size2-1>size1)
    {
      return odejmowanie(number2+1,number1,result,1);
    }
    else
    {
      int x = compare(number1,number2+1);
      if(x==0)
      {
        *result=malloc(2);
        *(*result+0)='0';
        *(*result+1)='\0';
      } 
      else if(x<0)
      {
        return odejmowanie(number2+1,number1,result,1);
      }
      else
      {
        return odejmowanie(number1,number2+1,result,0);
      }
    }
    
  }
  return 0;
}

int subtract(const char* number1, const char* number2, char** result)
{
  if(number1==NULL || number2==NULL || result==NULL) return 1;
  if( validate(number1) != 0 || validate(number2) != 0 ) return 2;

  int size1=strlen(number1);
  int size2=strlen(number2);
  if( *(number1+0) != '-' && *(number2+0) != '-' )
  {
    if(size1>size2)
    {
      return odejmowanie(number1,number2,result,0);
    }
    else if(size2>size1)
    {
      return odejmowanie(number2,number1,result,1);
    }
    else
    {
      int x = compare(number1,number2);
      if(x==0)
      {
        *result=malloc(2);
        *(*result+0)='0';
        *(*result+1)='\0';
      } 
      else if(x<0)
      {
        return odejmowanie(number2,number1,result,1);
      }
      else
      {
        return odejmowanie(number1,number2,result,0);
      }
    }
  }

  else if( (*(number1+0) == '-' && *(number2+0) == '-') )
  {
    if(size1>size2)
    {
      return odejmowanie(number1+1,number2+1,result,1);
    }
    else if(size2>size1)
    {
      return odejmowanie(number2+1,number1+1,result,0);
    }
    else
    {
      int x = compare(number1+1,number2+1);
      if(x==0)
      {
        *result=malloc(2);
        *(*result+0)='0';
        *(*result+1)='\0';
      } 
      else if(x<0)
      {
        return odejmowanie(number2+1,number1+1,result,0);
      }
      else
      {
        return odejmowanie(number1+1,number2+1,result,1);
      }
    }
  }

  else if( *(number1) == '-' )
  {
    return dodawanie(number1+1,number2,result,1);
  }

  else if( *(number2) == '-')
  {
    return dodawanie(number1,number2+1,result,0);
  }
  return 0;
}


int validate_expression(const char *expr)
{
  if(expr==NULL)return 2;
  int liczba_poczatek=0;
  int size=strlen(expr);
  if( isdigit( *(expr+size-1) ) == 0 )return 1;
  if(*(expr+0) =='+' || *(expr+0) =='*')return 1;
  for(int i=0;i<size;i++)
  {
    if( isdigit( *(expr+i))== 0 )
    {
      if( *(expr+i) == '-' || *(expr+i) == '*' || *(expr+i) == '+' )
      {
        if(  isdigit( *(expr+i+1) ) == 0 && *(expr+i+1)!='-' )
        {
          return 1;
        }
      }
      else
      {
        return 1;
      }
    liczba_poczatek=0;
    }
    else if(liczba_poczatek == 0)
    {
      if( *(expr+i) == '0' && isdigit( *(expr+i+1) ) !=0 )
      {
        return 1;
      }
      liczba_poczatek=1;
    }
  }
  return 0;
}

int mnozenie(const char* number1, const char* number2, char** result ,int minus)
{
  if(number1==NULL || number2==NULL || result==NULL) return 1;
  if( validate(number1) != 0 || validate(number2) != 0 ) return 2;
  int size1=strlen(number1);
  int size2=strlen(number2);
  int size_result=size1+size2+1;
  *result=(char*)malloc(size_result);
  if(*result==NULL)
  {
    return 3;
  }
  int k=0;
  int temp_k=0;
  for(int i=0;i<size_result;i++)
  {
    *(*result+i)='0';
  }

  *(*result+size_result-1)='\0';
  for(int i=size1-1;i>=0;i--,temp_k++)
  {
    k=temp_k;
    for(int j=size2-1;j>=0;j--)
    {
      int reszta = ((*(number1+i) - '0') * ( *(number2+j) -'0') + *(*result+k) -'0') % 10;
      int podaj_dalej = ( ( *(number1+i) - '0') * ( *(number2+j) -'0') + *(*result+k)-'0' )/10;

      *(*result+k) = reszta + '0';
      *(*result+k+1) += podaj_dalej;
      k++;
    }
    
  }

  while(1)
  {
    int size=strlen(*result);
    if(*(*result+size-1)=='0')*(*result+size-1)='\0';
    else
    {
      break;
    }
  }


  if( minus==1 )
  {
    size_result++;
    char* temp=realloc(*result,size_result);
    if(temp == NULL)
    {
      free(*result);
      return 3;
    }
    *result=temp;
    int size=strlen(*result);
    *(*result+size) = '-';
    *(*result+size+1)='\0';
  }

  reverse_number(*result);
  return 0;
}

int multiply(const char* number1, const char* number2, char** result)
{
  if(number1==NULL || number2==NULL || result==NULL) return 1;
  if( validate(number1) != 0 || validate(number2) != 0 ) return 2;

  if( *(number1+0) == '0' || *(number2+0) == '0' )
  {
    *result=malloc(2);
    if(*result==NULL)return 3;
    *(*result+0)='0';
    *(*result+1)='\0';
    return 0;
  }

  if( *(number1+0) != '-' && *(number2+0) != '-' )
  {
    return mnozenie(number1, number2, result,0);
  }
  else if( (*(number1+0) == '-' && *(number2+0) == '-') )
  {
    return mnozenie(number1+1, number2+1, result,0);
  }
  else if( *(number1+0) == '-' )
  {
    return mnozenie(number1+1, number2, result,1);
  }
  else if( *(number2+0) == '-')
  {
    return mnozenie(number1, number2+1, result,1);
  }
  return 0;
}

int calculate(const char* expr, char **result)
{
  if(expr==NULL || result==NULL) return 1;
  if(validate_expression(expr)) return 2;
  int start=0;
  int len=0;
  char opcja;
  char* liczba=NULL;
  char* new_result=NULL;
  for(int i=0;i<=(int)strlen(expr);i++ )
  {
    if( (isdigit( *(expr+i) ) == 0 && len!=0) || i==(int)strlen(expr))
    {
      if(start==0)
      {
        *result=malloc(len+1);
        if(*result==NULL)return 3;
        strncpy(*result,expr,len);
        *(*result+len)='\0';
        start=1;
        len=0;
      }
      else
      {
        liczba=malloc(len+1);
        if(liczba==NULL)
        {
          free(*result);
          return 3;
        }
        int x=i-len;
        strncpy(liczba,expr+x,len);
        *(liczba+len)='\0';
        if(opcja=='+')
        {
          add(*result, liczba, &new_result);
        }
        else if(opcja=='-')
        {
          subtract(*result, liczba, &new_result);
        }
        else if(opcja=='*')
        {
          multiply(*result, liczba, &new_result);
        }
        free(*result);
        free(liczba);
        *result=new_result;
        new_result=NULL;
        len=0;
      }
      opcja=*(expr+i);
    }
    else
    {
      len++;
    }
    
  }

return 0;
}




int main(void) {
  char* expr=malloc(501);
  char* result;
  if(expr==NULL)
  {
    printf("Failed to allocate memory\n");
    return 8;
  }
  printf("Podaj wyrazenie: ");
  scanf("%500s",expr);
  if( validate_expression(expr) == 1)
  {
    free(expr);
    printf("Incorrect input");
    return 1;
  }
  if( calculate(expr, &result) == 3)
  {
    free(expr);
    printf("Failed to allocate memory\n");
    return 8;
  }
  printf("%s",result);
  free(expr);
  free(result);

  return 0;
}
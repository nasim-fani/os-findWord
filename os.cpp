#include <stdio.h>
#include <sys/types.h>
#include<unistd.h>

int lineLen=0;
int lineNum=1;
int toFindLen=0,toFindCursor=0;


void findWord(char line[],char toFind[],int find[]){
  toFindLen=0;toFindCursor=0;
  int counter=0;


  for(int i = 0 ; i<150;i++){
    if(line[i]=='\0') break;
    lineLen++;
  }
  for(int i = 0 ; i<150;i++){
    if(toFind[i]=='\0') break;
    toFindLen++;
  }
  for(int i = 0 ; i < lineLen  ; i++ ){

      if(line[i]==toFind[toFindCursor]) {
        toFindCursor++;
        if(toFindCursor==toFindLen){
          find[counter]=i-toFindLen+1;
          counter++;
          toFindCursor=0;

        }
      }
      else toFindCursor = 0;

  }
}


int main ( int argc,char* argv[] )
{

pid_t pid;
  int find[128];
  for (int i = 0 ; i<128;i++){
    find[i]=-1;
  }
  char *toFind =argv[2];

         char const *const filename = argv[1];
   FILE *file = fopen ( filename, "r" );
   if ( file != NULL )
   {
      char line [ 128 ]; /* or other suitable maximum line size */
      while ( fgets ( line, sizeof line, file ) != NULL ) /* read a line */
      {
          pid=fork();
          if(!pid){
         int findLen=0;
         findWord(line,toFind,find);

         for(int i = 0 ; i < 100 ; i ++){
           if(find[i]==-1){
             break;
       }
       findLen++;
     }

     for(int i = 0 ; i < findLen ; i ++){



         int f = find[i];

         int k = f;
         int backSpace=0;
         for(int a = 0 ; filename[a]!='\0';a++)
            printf("%c",filename[a]);
         printf(" : line %d : ",lineNum);
             while(k!=0&&backSpace<6){
                 if(line[k] == ' ') backSpace++;
                 k--;
             }

             if(backSpace<6){
             for(int j = k ; j<f;j++){
                 printf("%c",line[j]);
             }
             }
             else{
                 for(int j = k+2 ; j<f;j++){
                 printf("%c",line[j]);
                 }
             }




         int space=0;

           while(space<6 && f!=lineLen-1){
               printf("%c",line[f]);
               f++;
               if(line[f]==' ') space++;
           }

           printf("\n");
     }


        for(int i = 0 ; i < 128 ; i++){
          line[i]='\0';
          find[i]=-1;
    }




      _exit(0);
      }
      lineNum++;
  }

      fclose ( file );
   }
   else
   {
      perror ( filename ); /* why didn't the file open? */
   }

   scanf("%c");
   return 0;
}

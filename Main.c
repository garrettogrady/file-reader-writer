#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curses.h>

int main()
{
  char fname[128];
  printf("Enter .txt file name\n");
  scanf("%123s",fname);
  strcat(fname,".txt");
  int c;
  FILE *file;
  file = fopen(fname,"r");
  if(file==NULL) 
        {
          printf("File couldn't be opened ");
          exit(0);
        }
  char choice;
  // menu from http://cboard.cprogramming.com/c-programming/72943-creating-menu-using-c.html
  do {
    printf("\n");
    printf("\nPlease make a choice: \n"
            "(f/F) search the document for a word/phrase \n"
            "(p/P) print the document on the screen\n"
            "(r/R) replace a word/phrase in the document \n"
            "(q/Q) quit the program \n");     
    scanf(" %c", &choice);
    if (choice == 'f' || choice == 'F') {
      printf("Please enter a word or phrase to search for:  ");
      printf("\n");
      char findme[100];
      scanf("%s",findme);
      printf("\n");
      printf("Searching for: %s",findme);
      printf("\n");
      char buff[BUFSIZ];      // the input line

       // search from http://cboard.cprogramming.com/c-programming/8575-how-find-replace-string-file.html
      while ( fgets( buff, BUFSIZ, file ) != NULL ) {
        if ( strstr( buff, findme ) != NULL ) 
        {
          printf("%s found inn... ", findme);
          printf("%s",buff);

        } 
      }

      file = fopen(fname,"r");
    }
    //print from http://stackoverflow.com/questions/3463426/in-c-how-should-i-read-a-text-file-and-print-all-strings
    else if (choice == 'p' || choice == 'P')
    {
        printf("printing");
         printf("\n");
        if (file) {
          while ((c = getc(file)) != EOF) 
          { 
            putchar(c); 
          }
          
    }
            printf("\n");
            file = fopen(fname,"r");
    

     }

      // Find and replace from http://www.codextream.com/write-a-c-program-to-find-and-replace-a-string-from-a-file/
     else if (choice == 'r' || choice == 'R') {
            fclose(file);
            char Buffer[4095];
            char InputFileName[20] ;
            char *TemporaryFileName = "newfile.txt";
            char Find[20];
            char saveNewFile;
            char Replace[20];
            int line = 0;
            FILE *Input,*Output;
            Input = fopen(fname, "r");
            Output = fopen(TemporaryFileName, "w");
            printf("Enter the word to find :");
            printf("\n");
            scanf("%s",Find);
            printf("Enter the New word to replace :");
            printf("\n");
            scanf("%s",Replace);
         
            if(NULL == Input)
            {
                printf("\nCould not open file");
                return 1;
            }
         
            printf("Find:    %s\n", Find);
            printf("Replace: %s\n", Replace);
         
            // For each line...
            while(NULL != fgets(Buffer, 4095, Input))
            {
                char *Stop = NULL;
                char *Start = Buffer;
                while(1)
                {
         
                  /*getting the first location of the source string*/
                  Stop = strstr(Start, Find);
                  if(NULL == Stop)
                  {
                      fwrite(Start, 1, strlen(Start), Output);
                      break;
                  }
                  printf("\n@found at Line  <%d>",line);

                  /*writting data till the source string location*/
                  fwrite(Start, 1, Stop - Start, Output);
                  /*writting Replacement string to the output file**/
                  fwrite(Replace, 1, strlen(Replace), Output);
                  /*moving the pointer to the next char of source string*/
                  Start = Stop + strlen(Find);
                }
                line++;
            }
         
            fclose(Input);
            fclose(Output);
            do { 
                printf("\nWould you like to save this change? (Y/N) ");     
                scanf(" %c", &saveNewFile);
                if (saveNewFile == 'Y' || saveNewFile == 'y')
                {
                  /*Remove the old file*/
                  remove(fname);
                  /*rename the temporary file*/
                  rename(TemporaryFileName, fname);
                  printf("changes saved");
                  break;
                }
                else if (saveNewFile == 'N' || saveNewFile == 'n') {

                  printf("changes not saved");

                  break;

                }

                else {
                  printf("Invalid choice");
                }
            } while (saveNewFile != 'N' || saveNewFile != 'n' || saveNewFile != 'y' || saveNewFile != 'Y');
            file = fopen(fname,"r");

       }
     else if (choice == 'q' || choice == 'Q') {

      break;
     
     }
     else {
          printf("Invalid Choice");
          }
  } while (choice != 'q' || choice != 'Q'); 

   printf("Thank you, Have a nice day!");

  
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "books.h"

int main(int argc, char *argv[]) {

    book b = NULL, tempBook;
    list books = NULL;
    int opt, id;
    char option;
   
  
    
    if(argc != 2){
        printf("Wrong parameters number. Usage: ./programName file.dat\n");
        return -1;
    }
    
    // open the file for reading
    loadBooks(argv[1], &books);
    printf("\n");
    printf("The file '%s' has opened\n",argv[1]);
    printf("\n");
    
    //main program loop
    do{

        printMenu();
        
        //the %c%*c is used  to read a character and discard the ENTER caracter(stack help!!)
        //http://stackoverflow.com/questions/2155518/what-is-scanfs-and-scanfd-format-identifiers
        printf("Input: ");
        scanf("%c%*c", &option);
        
        /* check if the option entered is a digit, this is  done 
         * comparing the entered value as a char with the values from 0 to 9
         * as chars too
         * */
        if(option < '0' || option > '9'){
            
            printf("Wrong option\n");
            continue;
            
        }
        
        /* we can transform a char number into an integer value just by 
         * substracting the character zero from it, thus '9' - '0' = 9
         * is the "distance" between ASCII characters.
         * http://stackoverflow.com/questions/868496/how-to-convert-char-to-integer-in-c
         * */
        opt = option - '0';
        b = NULL;
        
        switch (opt) {
            case 1:
                printf("add book\n");
                // create a book node every time
                b = (book) malloc(sizeof(struct bookR));                
                addBook(b, &books);
                
            break;
        
            case 2:
                printf("Enter id to search: ");
                scanf("%d%*c", &id);
                b = (book) malloc(sizeof(struct bookR));
                b->id = id;
				//print the result of the find function to the print fuction 
				printf("\n");
				printf("__________ Print Book _________________\n");
                print(findBook(b, books));
                printf("_______________________________________\n");
                printf("\n");
            break;
        
            case 3:
                printf("Enter id modify: ");
                scanf("%d%*c", &id);
                b = (book) malloc(sizeof(struct bookR));
                b->id = id;
                tempBook = findBook(b, books);
                if(tempBook != NULL)
                    updateBook(tempBook, books);
                else
                	printf("Error!!!\n");
                    printf("The id is not in the list \n");
                    printf("\n");
                    printf("\n");
                
            break;

            case 4:
                printf("Enter id to delete: ");
                scanf("%d%*c", &id);
                b = (book) malloc(sizeof(struct bookR));
                b->id = id;
                tempBook = findBook(b, books);
                if(tempBook != NULL)
                    deleteBook(tempBook, books);
                else
                	printf("Error!!!\n");
                    printf("The id is not in the list\n");
                	printf("\n");
                    printf("\n");
                
            break;

            case 5:
                printf("\n");
                printf("_______________Print all books_____________");
                printf("\n");
                printf("\n");
                printBooks(books);
                printf("____________________________________________");
                printf("\n");

            break;
        }


    }while(opt != 6);
    
    //write all data from the list in to the file in binary format
    printf("Saving...\n");
    save(argv[1], books);
    printf("All data is saved to the file  '%s' \n", argv[1]);
    return 0;
}


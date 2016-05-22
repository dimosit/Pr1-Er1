#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "books.h"


//main menu 
void printMenu (){
    printf("---------MAIN MENU----------\n");
    printf("1 -> Adda a book            \n");
    printf("2 -> Search for a book      \n");
    printf("3 -> Modify a book 			\n");
    printf("4 -> Delete a book   		\n");
    printf("5 -> Print all books 		\n");
    printf("6 -> Save and exit   		\n");
    printf("----------------------------\n");
}

//prints all books from the list
void printBooks(list bList){
    list current = bList;
    while (current != NULL) {
        
        /*for every node we call the print function 
         * and we pass it the copy of the book*/
        print(current->copy);
        printf("\n");
        current = current->next;
    }
    
    
}

//add a book to the list
void addBook (book b, list *bList){
    int lines;
    book aux = NULL;
    char genre;
    
     
    do{
        printf("id: ");
	    //the %d%*c is used  to read a decimal and discard the ENTER caracter(stack help!!)
	    scanf("%d%*c", &b->id);

        aux = findBook(b, *bList);
        if(aux != NULL)
            printf("id: %d already exits!\n", b->id);
    }while(aux != NULL);
    
    printf("author:");
    fgets(b->author, MAXSTRING, stdin);
    
    //the genre is read as an int because thats what it really is
    
    do{
        printf("Genre: (1)Fiction, (2)Scientific, (3)Politics: ");
        scanf("%c%*c", &genre);
    }while (genre < '1' || genre > '3');
    
    
    b->genre = genre - '0';
    
    /*to read the review we keep reading lines until we reach the MAXLINES
     *or the user writes "END" in an empty line
     * */
    printf("review: (write \"end\" on an empy line to finish): \n");
    
    lines = 0;
    fgets(b->review[lines], MAXSTRING, stdin);
    // count the lines that we read to break the loop 
    while(lines < (MAXLINES - 1)){
        if(strcmp(b->review[lines], "end\n")==0) {
            //this is a way to truncate a string
            b->review[lines][0] = '\0';
            break;
        }
        lines++;
        fgets(b->review[lines], MAXSTRING, stdin);
    };
    //create new node in the list
    list temp = (list) malloc(sizeof(struct node));
    
    //then copy the incomming the book pointer  into the copy field
    temp->copy = b;
    
    //update the links in the list
    temp->next = *bList;
    *bList = temp;

}

//print evry filld for evry book
void print(book b){
  
    if(b != NULL){
        int i;
        printf("id: %d\n", b->id);
        
        printf("author: %s", b->author);
        
        /* the genre field is  an int field so 
         * we need to print the value as a string manually*/
        switch(b->genre){
            case fiction:
                printf("genre: Fiction\n");
            break;
            case scientific:
                printf("genre: Scientific\n");
            break;
            case politics:
                printf("genre: Politics\n");
            break;
        }
        
        /*the review field is a set of MAXLINES lines, 
         * so we iterate through the string array*/
        printf("review: ");
        for(i = 0; i < MAXLINES; i++){
            // we stop if the line if empty (strlen = 0)
            if(strlen(b->review[i]) == 0)
                break;
            printf("%s", b->review[i]);
        }
        printf("\n");
    }else{
        // if the book is NULL then  print an error message
        printf("Book not found in the list\n");
        printf("\n");
        printf("\n");

    }
}

// search for a book 
book findBook (book b, list bList){
    list current = bList;
    // traverse the book list 
    while (current != NULL) {
        //if the incomming id equals the current id than break the loop 
        if(current->copy->id == b->id)
            break;
        current = current->next;
    }
    
    //if the current node is not null  return the book else  return NULL 
    if(current != NULL)
        return current->copy;
    else
        return NULL;
}
//delete a book record
void deleteBook(book b, list bList) {
    list current = bList;
    list previous = NULL;
    
    // traverse the book list
    while (current != NULL) {
        if (current->copy->id == b->id) {
            /*if it's the first node, we forward it and
             * delete the incoming list*/
            if (previous == NULL) {
                current = current->next;
                free(bList);
            } else {
                //skip the current node and then delete it
                previous->next = current->next;
                free(current);
                current = previous->next;
            }
        } else {
            // continue the search and update the nodes/
            previous = current;
            current = current->next;
        }
    }    
}

void updateBook (book b, list bList){
    int lines, var;
    book tempBook = NULL, aux;
    char genre;
    do{
        tempBook = (book) malloc(sizeof(struct bookR));
        
        printf("id:");
        scanf("%d%*c", &tempBook->id);

        aux = findBook(tempBook, bList);
        
        if(aux != NULL)
            printf("id: %d already exits!\n", aux->id);
        else
            b->id = tempBook->id;
        free(tempBook);
        
    }while(aux != NULL);
    
    printf("author:"); 
    fgets(b->author, MAXSTRING, stdin);
    
    do{
        printf("Genre: (1)Fiction, (2)Scientific, (3)Politics: ");
        scanf("%c%*c", &genre);
    }while (genre < '1' || genre > '3');
    
    
    b->genre = genre - '0';
    
    printf("review: (write \"end\" to finish): ");
    
    lines = 0;
    fgets(b->review[lines], MAXSTRING, stdin);
    while(lines < (MAXLINES - 1))
    {
        if(strcmp(b->review[lines], "end\n")==0) {
            b->review[lines][0] = '\0';
            break;
        }
        lines++;
        fgets(b->review[lines], MAXSTRING, stdin);
    };
} 

void save (char * filename, list bList){
    FILE *data;
    list tempList;
    data = fopen(filename, "wb");
    
    if(!data){
        
        printf("Error opening the file: %s to save data", filename);
        return;
    }
    
    //traverse the book list
    tempList = bList;
    while(tempList != NULL){
        // write all books in the list into the file 
        fwrite(tempList->copy, sizeof(struct bookR), 1, data);
        tempList = tempList->next;
    }
    
    
    fclose(data);
}


// load books from the file into the list
void loadBooks(char * filename, list *bList){
    book b;
    FILE *data;
    data = fopen(filename, "rb");
    
    if(data){
        b = (book) malloc(sizeof(struct bookR));
        fread(b, sizeof(struct bookR), 1, data);
    
        while(!feof(data)){
            list temp = (list) malloc(sizeof(struct node));

            temp->copy = b;
    
            // update the links in the list
            temp->next = *bList;
            *bList = temp;
            b = (book) malloc(sizeof(struct bookR));
            fread(b, sizeof(struct bookR), 1, data);
        }
    
        fclose(data);
    
    }

}
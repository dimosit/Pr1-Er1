#define MAXSTRING 50
#define MAXLINES 4

// enumeration to get a human format for genres, starting with 1
enum genres { fiction=1, scientific, politics };

struct bookR{
    int id;
    char author[MAXSTRING];
    enum genres genre;
    char review[MAXLINES][MAXSTRING];
    
};

typedef struct bookR *book;

/* node structure to use in the list, contains 
 * a copy of the book and a link to the next node */
typedef struct node {
    book copy;
    struct node * next;
} node_t;


typedef node_t *list;


//prints the main menu
void printMenu ();

//Print book details
void print (book b);

//Retrieve book list from a file
list load (char * filename, list bList); 

// Save the book list file
void save (char * filename, list bList); 

//Add book to the list
void addBook (book b, list *bList);

// Search by b-> id
book findBook (book b, list bList); 

// Delete by b-> id
void deleteBook (book b, list bList);

// Renewal by b-> id
void updateBook (book b, list bList);

// Prints all books in the list
void printBooks(list bList);

//read books from the file and load them into the book list
void loadBooks(char * filename, list *bList);
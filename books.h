#define MAXLINES 10
#define MAXSTRING 100

enum genres
{
	FICTION,
	SCIENTIFIC,
	POLITICS
};

struct bookR{

   char author[MAXSTRING];

   enum genres genre;

   int id;

   char review[MAXLINES][ MAXSTRING];

};

typedef struct bookR* book; 

void printMenu();

void print(book b);

book load(char *filename);

void save(char *filename);

void addBook(void);

book findBook(int id);

void deleteBook(int id);

void updateBook(int id);
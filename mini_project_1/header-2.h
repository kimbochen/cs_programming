#ifndef header_2_h
#define header_2_h

/*
 the only type: integer
 everything is an expression
 statement   := END | expr END
 expr        := term expr_tail
 expr_tail   := ADDSUB term expr_tail | NIL
 term        := factor term_tail
 term_tail := MULDIV factor term_tail | NIL
 factor      := INT | ADDSUB INT | ADDSUB ID | ID ASSIGN expr | ID | LPAREN expr RPAREN
 */

#define MAXLEN 256
#define TBLSIZE 65536

typedef enum {UNKNOWN, END, INT, ID, ADDSUB, MULDIV, ASSIGN, LPAREN, RPAREN} TokenSet;

typedef struct {
    char name[MAXLEN];
    int val;
} Symbol;

typedef struct _Node {
    char lexeme[MAXLEN];
    TokenSet token;
    int val;
    struct _Node *left, *right;
} BTNode;

typedef struct {
    int val, isVac;
} Reg;

typedef struct {
    int val, rewrite;
} Mem;

typedef struct {
    int num;
    char var;
} Data;

Reg regs[8];
Mem mems[3];
Data input[MAXLEN], prein[MAXLEN];

Symbol table[TBLSIZE];
int sbcount = 0;

void statement(void);
BTNode* expr(void);
BTNode* term(void);
BTNode* factor(void);
int getval(void);
void error(void);

/* Lexical-related function */
int match (TokenSet token);
void advance(void);
char* getLexeme(void);
static TokenSet getToken(void);
static TokenSet lookahead = UNKNOWN;
static char lexeme[MAXLEN];

/* Tree-related function*/
BTNode* makeNode(TokenSet tok, const char *lexe);
void freeTree(BTNode *root);
void printInfix(BTNode *root);

/* Assembly code-relating functions */
void preCheck(BTNode *cur);
void checkTree(BTNode *cur);
void parseTree(BTNode *cur);
void genCode(void);
void endMove(void);

int isOpr(char c);
int varReg(BTNode *cur);

#endif /* header_2_h */

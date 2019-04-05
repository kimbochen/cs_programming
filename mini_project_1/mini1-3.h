#ifndef mini1_3_h
#define mini1_3_h

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
    int val, assigned;
    struct _Node *left, *right;
} BTNode;

typedef struct {
    int val, isVac;
} Reg;

typedef struct {
    int val, rewrite, init;
} Mem;

typedef struct {
    int num;
    char var;
} Data;

Reg regs[8];
Mem mems[3];
Data input[MAXLEN];
char prein[MAXLEN];
int ini;
Symbol table[TBLSIZE];
int sbcount = 0;

/* lexical-related function */
void statement(void);
BTNode* expr(void);
BTNode* term(void);
BTNode* factor(void);
int getval(void);
void error(void);

int match (TokenSet token);
void advance(void);
char* getLexeme(void);
static TokenSet getToken(void);
static TokenSet lookahead = UNKNOWN;
static char lexeme[MAXLEN];

/* tree-related functions */
BTNode* makeNode(TokenSet tok, const char *lexe);
void freeTree(BTNode *root);
void printInfix(BTNode *root);

/* syntax-related functions */
void checkSyntax(void);
void STATEMENT(void);
void EXPR(void);
void EXPRTAIL(void);
void TERM(void);
void TERMTAIL(void);
void FACTOR(void);

/* code-generating functions */
void genCode(BTNode *cur);
void calNode(BTNode *cur);
void endMove(int exit);
void checkMath(BTNode *cur);
void initRegMem(void);
int varReg(BTNode *cur);
int isOpr(char c);

#endif /* mini1_3_h */

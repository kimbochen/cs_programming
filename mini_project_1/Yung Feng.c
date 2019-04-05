#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define MAXLEN 256
#define TBLSIZE 65535
typedef enum {UNKNOWN, END, INT, ID, ADDSUB, MULDIV, ASSIGN,
    LPAREN, RPAREN, ENDFILE} TokenSet;
typedef enum {MISPAREN, NOTNUMID, NOTFOUND, RUNOUT} ErrorType;

typedef struct {
    char name[MAXLEN];
    int val;
} Symbol;
Symbol table[TBLSIZE];


typedef struct _Node {
    char lexeme[MAXLEN];
    TokenSet data;
    int val;
    struct _Node *left, *right;
} BTNode;
int q = 3;
static TokenSet getToken(void);
static TokenSet lookahead = UNKNOWN;
static char lexeme[MAXLEN];
extern int getval(void);
extern int setval(char *str, int val);
extern BTNode* makeNode(TokenSet tok, const char *lexe);
extern void freeTree(BTNode *root);
extern BTNode* factor(void);
extern BTNode* term(void);
extern BTNode* expr(void);
extern void statement(void);
extern void error(ErrorType errorNum);
extern int evaluateTree(BTNode *root);
extern void printPrefix(BTNode *root);
extern int match (TokenSet token);
extern void advance(void);
extern char* getLexeme(void);
int main()
{
    //printf(">> ");
    while (1) {
        q = 3;
        statement();
    }
    //printf("EXIT 0\n");
    return 0;
}
int r[8];int trash = 0;

int evaluateTree(BTNode *root)
{
    int retval = 0, lv, rv;
    
    if (root != NULL)
    {
        /*if(root->right!=NULL){
         if(strcmp(root->right->lexeme,"=") == 0)
         error(RUNOUT);
         }*/
        
        switch (root->data)
        {
            case ID:
                if(trash != 1){
                    //    if(q<=7){
                    if(strcmp(root->lexeme, "x") == 0){
                        printf("MOV r%d r0 \n",q,root->val);
                    }
                    else if(strcmp(root->lexeme, "y") == 0){
                        printf("MOV r%d r1 \n",q,root->val);
                    }
                    else if(strcmp(root->lexeme, "z") == 0){
                        printf("MOV r%d r2 \n",q,root->val);
                    }
                    q++;
                    //    }
                    /*    else{
                     q = 3;
                     if(strcmp(root->lexeme, "x") == 0){
                     printf("MOV r%d r0 \n",q,root->val);
                     }
                     else if(strcmp(root->lexeme, "y") == 0){
                     printf("MOV r%d r1 \n",q,root->val);
                     }
                     else if(strcmp(root->lexeme, "z") == 0){
                     printf("MOV r%d r2 \n",q,root->val);
                     }
                     q++;
                     }*/
                }
                trash = 0;
                retval = root->val;
                break;
            case INT:
                //    if(q<=7){
                printf("MOV r%d %d \n",q,root->val);
                q++;
                //    }
                /* else{
                 q = 3;
                 printf("MOV r%d %d \n",q,root->val);
                 q++;
                 }*/
                retval = root->val;
                break;
            case ASSIGN:
            case ADDSUB:
            case MULDIV:
                if(strcmp(root->lexeme, "=") == 0){
                    trash = 1;
                }
                lv = evaluateTree(root->left);
                rv = evaluateTree(root->right);
                if (strcmp(root->lexeme, "+") == 0){
                    printf("ADD r%d r%d\n",q-2,q-1);
                    q--;
                    retval = lv + rv;
                }
                else if (strcmp(root->lexeme, "-") == 0){
                    printf("SUB r%d r%d\n",q-2,q-1);
                    q--;
                    retval = lv - rv;
                }
                else if (strcmp(root->lexeme, "*") == 0){
                    printf("MUL r%d r%d\n",q-2,q-1);
                    q--;
                    retval = lv * rv;
                }
                else if (strcmp(root->lexeme, "/") == 0){
                    printf("DIV r%d r%d\n",q-2,q-1);
                    q--;
                    retval = lv / rv;
                }
                else if (strcmp(root->lexeme, "=") == 0){
                    if(strcmp(root->left->lexeme, "x") == 0){
                        printf("MOV r0 r%d\n",q-1);
                        printf("MOV [0] r0\n");
                    }
                    else if(strcmp(root->left->lexeme, "y") == 0){
                        printf("MOV r1 r%d\n",q-1);
                        printf("MOV [4] r1\n");
                    }
                    else if(strcmp(root->left->lexeme, "z") == 0){
                        printf("MOV r2 r%d\n",q-1);
                        printf("MOV [8] r2\n");
                    }//q--;
                    retval = setval(root->left->lexeme, rv);
                }
                break;
            default:
                retval = 0;
        }
    }
    return retval;
}


/* print a tree by pre-order. */
void printPrefix(BTNode *root)
{
    if (root != NULL)
    {
        //printf("%s ", root->lexeme);
        printPrefix(root->left);
        printPrefix(root->right);
    }
}
int sbcount = 0;
int getval(void)
{
    int i, retval, found;
    
    if (match(INT)) {
        retval = atoi(getLexeme());
    } else if (match(ID)) {
        i = 0; found = 0; retval = 0;
        while (i<sbcount && !found) {
            if (strcmp(getLexeme(), table[i].name)==0) {
                retval = table[i].val;
                found = 1;
                break;
            } else {
                i++;
            }
        }
        if (!found) {
            if (sbcount < TBLSIZE) {
                strcpy(table[sbcount].name, getLexeme());
                table[sbcount].val = 0;
                sbcount++;
            } else {
                error(RUNOUT);
            }
        }
    }
    return retval;
}
int setval(char *str, int val)
{
    int i, retval;
    i = 0;
    while (i<sbcount) {
        if (strcmp(str, table[i].name)==0) {
            table[i].val = val;
            retval = val;
            break;
        } else {
            i++;
        }
    }
    return retval;
}
/* create a node without any child.*/
BTNode* makeNode(TokenSet tok, const char *lexe){
    BTNode *node = (BTNode*) malloc(sizeof(BTNode));
    strcpy(node->lexeme, lexe);
    node->data = tok;
    node->val = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}
/* clean a tree.*/
void freeTree(BTNode *root){
    if (root!=NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}
/*factor := INT | ADDSUB INT | ADDSUB ID | ID ASSIGN expr | ID | LPAREN expr RPAREN*/
BTNode* factor(void)
{
    BTNode* retp = NULL;
    char tmpstr[MAXLEN];
    
    if (match(INT)) {
        retp =  makeNode(INT, getLexeme());
        retp->val = getval();
        advance();
    } else if (match(ID)) {
        BTNode* left = makeNode(ID, getLexeme());
        left->val = getval();
        strcpy(tmpstr, getLexeme());
        advance();
        if (match(ASSIGN)) {
            retp = makeNode(ASSIGN, getLexeme());
            advance();
            retp->right = expr();
            retp->left = left;
        } else {
            retp = left;
        }
    } else if (match(ADDSUB)) {
        strcpy(tmpstr, getLexeme());
        advance();
        if (match(ID) || match(INT)) {
            retp = makeNode(ADDSUB, tmpstr);
            if (match(ID))
                retp->right = makeNode(ID, getLexeme());
            else
                retp->right = makeNode(INT, getLexeme());
            retp->right->val = getval();
            retp->left = makeNode(INT, "0");
            retp->left->val = 0;
            advance();
        } else {
            error(NOTNUMID);
        }
    } else if (match(LPAREN)) {
        advance();
        retp = expr();
        if (match(RPAREN)) {
            advance();
        } else {
            error(MISPAREN);
        }
    } else {
        error(NOTNUMID);
    }
    return retp;
}
/*  term        := factor term_tail
 term_tail := MULDIV factor term_tail | NIL*/
BTNode* term(void)
{
    BTNode *retp, *left;
    retp = left = factor();
    
    while (match(MULDIV)) {
        retp = makeNode(MULDIV, getLexeme());
        advance();
        retp->right = factor();
        /*if(strcmp(retp->right->lexeme,"=") == 0)
         error(RUNOUT);*/
        retp->left = left;
        left = retp;
    }
    return retp;
}
/*  expr        := term expr_tail
 expr_tail   := ADDSUB term expr_tail | NIL*/
BTNode* expr(void)
{
    BTNode *retp, *left;
    //int retval;
    retp = left = term();
    while (match(ADDSUB)) {
        retp = makeNode(ADDSUB, getLexeme());
        advance();
        retp->right = term();
        /* if(strcmp(retp->right->lexeme,"=") == 0)
         error(RUNOUT);*/
        retp->left = left;
        left = retp;
    }
    return retp;
}
/*statement   := END | expr END*/
void statement(void)
{
    BTNode* retp;
    
    if (match(ENDFILE)) {
        printf("EXIT 0\n");
        exit(0);
    } else if (match(END)) {
        //printf(">> ");
        advance();
    } else {
        retp = expr();
        if(retp->lexeme[0]!='=')error(RUNOUT);
        if (match(END)) {
            printf("MOV r0 [0]\n");
            printf("MOV r1 [4]\n");
            printf("MOV r2 [8]\n");
            //printf("%d\n", evaluateTree(retp));
            evaluateTree(retp);
            //    printPrefix(retp); printf("\n");
            freeTree(retp);
            
            //printf(">> ");
            advance();
        }
    }
}
void error(ErrorType errorNum)
{
    printf("EXIT 1\n");
    /*switch (errorNum) {
     case MISPAREN:
     fprintf(stderr, "Mismatched parenthesis\n");
     break;
     case NOTNUMID:
     fprintf(stderr, "Number or identifier expected\n");
     break;
     case NOTFOUND:
     fprintf(stderr, "%s not defined\n", getLexeme());
     break;
     case RUNOUT:
     fprintf(stderr, "Out of memory\n");
     }*/
    exit(0);
}


TokenSet getToken(void)
{
    int i;
    char c;
    
    while ( (c = fgetc(stdin)) == ' ' || c== '\t' );  // 忽略空白字元
    
    if (isdigit(c)) {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (isdigit(c) && i<MAXLEN) {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return INT;
    } else if (c == '+' || c == '-') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return ADDSUB;
    } else if (c == '*' || c == '/') {
        lexeme[0] = c;
        lexeme[1] = '\0';
        return MULDIV;
    } else if (c == '\n') {
        lexeme[0] = '\0';
        return END;
    } else if (c == '=') {
        strcpy(lexeme, "=");
        return ASSIGN;
    } else if (c == '(') {
        strcpy(lexeme, "(");
        return LPAREN;
    } else if (c == ')') {
        strcpy(lexeme, ")");
        return RPAREN;
    } else if (isalpha(c) || c == '_') {
        lexeme[0] = c;
        c = fgetc(stdin);
        i = 1;
        while (isalpha(c) || isdigit(c) || c == '_') {
            lexeme[i] = c;
            ++i;
            c = fgetc(stdin);
        }
        ungetc(c, stdin);
        lexeme[i] = '\0';
        return ID;
    } else if (c == EOF) {
        return ENDFILE;
    } else {
        return UNKNOWN;
    }
}

void advance(void)
{
    lookahead = getToken();
}

int match(TokenSet token)
{
    if (lookahead == UNKNOWN) advance();
    return token == lookahead;
}

char* getLexeme(void)
{
    return lexeme;
}

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "header-2.h"

int isOpr(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int varReg(BTNode *cur)
{
    return (cur -> lexeme[0]) - 'x';
}


void endMove(void)
{
    for (int i = 0; i < 3; i ++) {
        if (mems[i].rewrite) {
            mems[i].val = regs[i].val;
            printf("MOV [%d] r%d\n", 4 * i, i);
        }
        if (regs[i].isVac) {
            regs[i].val = mems[i].val;
            printf("MOV r%d [%d]\n", i, 4 * i);
        }
    }
//    printf("%d %d %d\n", mems[0].val, mems[1].val, mems[2].val);
}

void initRegMem(void)
{
    for (int i = 0; i < 8; i ++) {
        regs[i].isVac = 1;
    }
    for (int i = 0; i < 3; i ++) {
        mems[i].rewrite = 0;
    }
}

void genCode(void)
{
    static int size = 0;
    char c = input[1].var;
    int i = 1, vari = input[0].var - 'x';
    
    if (size == 0) {
        while (regs[size].isVac == 0) size ++;
    }
    
    while (c != '=') {
        if (isOpr(c)) {
            if (c == '+') {
                regs[size - 2].val += regs[size - 1].val;
                printf("ADD");
            }
            else if (c == '-') {
                regs[size - 2].val -= regs[size - 1].val;
                printf("SUB");
            }
            else if (c == '*') {
                regs[size - 2].val *= regs[size - 1].val;
                printf("MUL");
            }
            else if (c == '/') {
                regs[size - 2].val /= regs[size - 1].val;
                printf("DIV");
            }
            printf(" r%d r%d\n", size - 2, size - 1);
            
            size --;
            regs[size].isVac = 1;
        }
        else if (isdigit(c)) {
            regs[size].val = input[i].num;
            printf("MOV r%d %d\n", size, input[i].num);
            regs[size ++].isVac = 0;
        }
        else if (isalpha(c) && mems[c - 'x'].rewrite == 0) {
            if (mems[c - 'x'].rewrite) {
                regs[size].val = input[i].num;
            }
            printf("MOV r%d [%d]\n", size, c - 'x');
            regs[size ++].isVac = 0;
        }
        else error();
        
        c = input[++ i].var;
    }
    
    regs[vari].val = regs[size - 1].val;
    mems[vari].rewrite = 1;
    regs[vari].isVac = 0;
    printf("MOV r%d r%d\n", vari, size - 1);
}

void preCheck(BTNode *cur)
{
    if (cur -> token != ASSIGN) error();
    
    char c = cur -> left -> lexeme[0];
    if (c < 'x' || c > 'z') error();
}

void checkTree(BTNode *cur)
{
    TokenSet tok = cur -> token;
    
    if (tok == INT || tok == ID) {
        if (cur -> left != NULL || cur -> right != NULL) {
            error();
        } else return;
    }
    else if (tok == ADDSUB || tok == MULDIV) {
        if (cur -> left == NULL || cur -> right == NULL) {
            error();
        }
    }
    else if (tok == ASSIGN) {
        if (cur -> left == NULL || cur -> right == NULL) {
            error();
        } else if (cur -> left -> token != ID ) {
            error();
        }
    }
    else error();
    
    checkTree(cur -> left);
    checkTree(cur -> right);
}

void parseTree(BTNode *cur)
{
    if (cur != NULL) {
        parseTree(cur -> left);
        parseTree(cur -> right);
    } else return;
    
    static int i = 0;
    
    if (cur -> token == INT) {
        input[i].num = cur -> val;
//        printf("(%d)", input[i].num);
    }
    else if (cur -> token == ID && mems[varReg(cur)].rewrite) {
        input[i].num = mems[varReg(cur)].val;
//        printf("(%d)", input[i].num);
    }
    
    input[i ++].var = cur -> lexeme[0];
//    printf("%c ", input[i - 1].var);
    
}



void statement(void)
{
    BTNode* retp;
    
    if (match(END)) {
        advance();
    } else {
        retp = expr();
        if (match(END)) {
            for (int i = 0; i < 14; i ++) {
                printf("%c ", prein[i].var);
            }
            preCheck(retp);
            checkTree(retp);
            parseTree(retp);
//            genCode();
//            printInfix(retp);
            freeTree(retp);
            advance();
        }
    }
}

BTNode* expr(void)
{
    //  expr        := term expr_tail
    //  expr_tail   := ADDSUB term expr_tail | NIL
    BTNode *retp, *left;
    retp = left = term();
    while (match(ADDSUB)) { // tail recursion => while
        retp = makeNode(ADDSUB, getLexeme());
        advance();
        retp->right = term();
        retp->left = left;
        left = retp;
    }
    return retp;
}

BTNode* term(void)
{
    //  term        := factor term_tail
    //  term_tail := MULDIV factor term_tail | NIL
    BTNode *retp, *left;
    retp = left = factor();
    while (match(MULDIV)) { // tail recursion => while
        retp = makeNode(MULDIV, getLexeme());
        advance();
        retp->right = factor();
        retp->left = left;
        left = retp;
    }
    return retp;
}

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
            error();
        }
    } else if (match(LPAREN)) {
        advance();
        retp = expr();
        if (match(RPAREN)) {
            advance();
        }
    } else {
        error();
    }
    return retp;
}

int getval(void)
{
    int i, found, retval = 0;
    
    if (match(INT)) {
        retval = atoi(getLexeme());
    } else if (match(ID)) {
        i = 0;
        found = 0;
        retval = 0;
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
                table[sbcount].val = 1;
                sbcount++;
            } else {
                error();
            }
        }
    }
    return retval;
}

void error(void)
{
    /* TODO:
     *
     * Error-Handler,
     * You should deal with the error that happened in calculator
     * An example is x = 5 / 0, which is divide zero error.
     * You should call error() when any error occurs
     *
     */
    
    printf("EXIT 1\n");
    exit(0);
}



int match(TokenSet token)
{
    if (lookahead == UNKNOWN) advance();
    return token == lookahead;
}

void advance(void)
{
    lookahead = getToken();
}

char* getLexeme(void)
{
    return lexeme;
}

TokenSet getToken(void)
{
    int i;
    char c = fgetc(stdin);
    
    if (c == EOF) {
        endMove();
        printf("EXIT 0\n");
        exit(0);
    }
    
    while (c == ' ' || c== '\t' ) c = fgetc(stdin);
    
    static int now = 0;
    prein[now ++].var = c;
    
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
    } else if (isalpha(c)) {
        if (c == 'x' || c == 'y' || c == 'z') {
            lexeme[0] = c;
            lexeme[1] = '\0';
        } else error();
        return ID;
    } else {
        error();
        return UNKNOWN;
    }
}



BTNode* makeNode(TokenSet tok, const char *lexe)
{
    /* create a node without any child */
    BTNode *node = (BTNode*) malloc(sizeof(BTNode));
    strcpy(node->lexeme, lexe);
    node->token= tok;
    node->val = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void freeTree(BTNode *root)
{
    if (root!=NULL) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

void printInfix(BTNode *root)
{
    printf("%s ", root -> lexeme);
    if (root -> left != NULL) printInfix(root -> left);
    if (root -> right != NULL) printInfix(root -> right);
}

int main(void)
{
    initRegMem();
    while (1) {
        statement();
    }
    return 0;
}

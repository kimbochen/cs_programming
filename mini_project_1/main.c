#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "header.h"
#include "codeGen.h"

void statement(void)
{
    BTNode* retp;
    
    if (match(END)) {
        advance();
    } else {
        retp = expr();
        if (match(END)) {
            preCheck(retp);
            checkSyntax(retp);
            compressTree(retp);
            codeGen(retp);
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
        if (match(ID)) error();
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
        printf("EXIT 0\n");
        exit(0);
    }
    
    while (c == ' ' || c== '\t' ) c = fgetc(stdin);
    
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

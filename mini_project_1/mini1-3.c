#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "mini1-3.h"

void initRegMem(void)
{
    for (int i = 0; i < 8; i ++) {
        regs[i].isVac = 1;
        regs[i].val = 0;
    }
    for (int i = 0; i < 3; i ++) {
        mems[i].rewrite = 0;
        mems[i].init = 1;
    }
    mems[0].val = 104729;
    mems[1].val = 104723;
    mems[2].val = 104717;
}
int varReg(BTNode *cur)
{
    return (cur -> lexeme[0]) - 'x';
}
int isOpr(char c)
{
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

void endMove(int exit)
{
    for (int i = 0; i < 3; i ++) {
        if (mems[i].rewrite) mems[i].val = regs[i].val;
        if (regs[i].isVac && exit) {
            regs[i].val = mems[i].val;
            printf("MOV r%d [%d]\n", i, 4 * i);
        }
    }
    for (int i = 0; i < ini + 1; i ++) {
        prein[i] = '\0';
    }
    ini = 0;
    //    printf("%d %d %d\n", mems[0].val, mems[1].val, mems[2].val);
}

void genCode(BTNode *cur)
{
    static int size = 0;
    if (cur != NULL) {
        genCode(cur -> right);
        genCode(cur -> left);
    }
    else return;
    
    char c = cur -> lexeme[0];
    
    if (isdigit(c)) {
        regs[size].val = cur -> val;
        regs[size].isVac = 0;
        printf("MOV r%d %d\n", size, regs[size].val);
        size ++;
    }
    else if (isalpha(c)) {
        if (cur -> assigned == 0) {
            if (mems[varReg(cur)].rewrite) {
                regs[size].val = mems[varReg(cur)].val;
            }
            regs[size].isVac = 0;
            mems[varReg(cur)].init = 0;
            printf("MOV r%d [%d]\n", size, 4 * varReg(cur));
            size ++;
        }
    }
    else if (isOpr(c)) {
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
            if (regs[size - 1].val != 0) {
                regs[size - 2].val /= regs[size - 1].val;
            }
            printf("DIV");
        }
        printf(" r%d r%d\n", size - 2, size - 1);
        
        size --;
        regs[size].isVac = 1;
    }
    else if (c == '=') {
        if (size - 1 != varReg(cur -> left)) {
            regs[varReg(cur -> left)].val = regs[size - 1].val;
            regs[size - 1].isVac = 1;
            printf("MOV r%d r%d\n", varReg(cur -> left), size - 1);
        }
        regs[varReg(cur -> left)].isVac = 0;
        mems[varReg(cur -> left)].rewrite = 1;
        
        for (int i = 0; i < 8; i ++) {
            if (regs[i].isVac) {
                size = i;
                break;
            }
        }
        endMove(0);
    }
    else error();
}

void calNode(BTNode *cur)
{
    if (cur != NULL) {
        calNode(cur -> right);
        calNode(cur -> left);
    }
    else return;
    
    char c = cur -> lexeme[0];
    
    if (isOpr(c)) {
        BTNode *lf = cur -> left, *rt = cur -> right;
        int lfv = lf -> val, rtv = rt -> val;
        
        if (isdigit(lf -> lexeme[0]) && isdigit(rt -> lexeme[0])) {
            if (c == '+') cur -> val = lfv + rtv;
            else if (c == '-') cur -> val = lfv - rtv;
            else if (c == '*') cur -> val = lfv * rtv;
            else if (c == '/' && rtv != 0) cur -> val = lfv / rtv;
            else error();
            
            free(lf);
            free(rt);
            cur -> left = cur -> right = NULL;
            cur -> lexeme[0] = '9';
//            printf("%d = %d %c %d\n", cur -> val, lfv, c, rtv);
        }
    }
    else if (isalpha(c)) {
        if (mems[c - 'x'].rewrite) {
            cur -> val = mems[c - 'x'].val;
            cur -> lexeme[0] = '9';
        }
        cur -> assigned = 0;
    }
    else if (c == '=') {
        cur -> left -> assigned = 1;
    }
    else return;
}

void checkMath(BTNode *cur)
{
    if (cur != NULL) {
        checkMath(cur -> left);
        checkMath(cur -> right);
    }
    else return;
    
    char c = cur -> lexeme[0];
    
    if (isOpr(c)) {
        BTNode *lf = cur -> left, *rt = cur -> right;
        int lfv = lf -> val, rtv = rt -> val;
        
        if (c == '+') cur -> val = lfv + rtv;
        else if (c == '-') cur -> val = lfv - rtv;
        else if (c == '*') cur -> val = lfv * rtv;
        else if (c == '/' && rtv != 0) cur -> val = lfv / rtv;
        else error();
    }
    else if (isalpha(c)) {
        cur -> val = mems[c - 'x'].val;
    }
}

void checkSyntax(void)
{
    ini = 0;
    STATEMENT();
    if (ini != strlen(prein) - 1) error();
    
    for (int j = 0; j < strlen(prein); j ++) {
        if (prein[j] == '=' && j != 1) error();
    }
    
    if (prein[0] != 'x' && prein[0] != 'y' && prein[0] != 'z') {
        error();
    }
}
void STATEMENT(void)
{
    if (prein[ini] != '\0') {
        EXPR();
    }
    else return;
}
void EXPR(void)
{
    TERM();
    EXPRTAIL();
}
void EXPRTAIL(void)
{
    if (prein[ini] == '+' || prein[ini] == '-') {
        ini ++;
        TERM();
        EXPRTAIL();
    }
    else return;
}
void TERM(void)
{
    FACTOR();
    TERMTAIL();
}
void TERMTAIL(void)
{
    if (prein[ini] == '*' || prein[ini] == '/') {
        ini ++;
        FACTOR();
        TERMTAIL();
    }
    else return;
}
void FACTOR(void)
{
    char c = prein[ini], nx = prein[ini + 1];
    
    if (isdigit(c)) {
        ini ++;
    }
    else if (c == 'x' || c == 'y' || c == 'z') {
        if (nx == '=') {
            ini += 2;
            EXPR();
        }
        else ini ++;
    }
    else if (c == '+' || c == '-') {
        if (isdigit(nx) || nx == 'x' || nx == 'y' || nx == 'z') {
            ini += 2;
        }
        else error();
    }
    else if (c == '(') {
        ini ++;
        EXPR();
        if (prein[ini] == ')') {
            ini ++;
        }
        else error();
    }
}

void statement(void)
{
    BTNode* retp;
    
    if (match(END)) {
        advance();
    } else {
        retp = expr();
        if (match(END)) {
            checkSyntax();
            checkMath(retp);
            calNode(retp);
            genCode(retp);
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
        endMove(1);
        printf("EXIT 0\n");
        exit(0);
    }
    
    while (c == ' ' || c== '\t' ) c = fgetc(stdin);
    prein[ini ++] = c;
    
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

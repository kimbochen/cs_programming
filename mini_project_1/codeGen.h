#ifndef codeGen_h
#define codeGen_h

#include <stdio.h>
#include <stdlib.h>
#include "header.h"

int getReg(void)
{
    for (int i = 0; i < 8; i ++) {
        if (regs[i].isVac) {
            regs[i].isVac = 0;
            return i;
        }
    }
    return -39;
}
int varReg(BTNode *var)
{
    int i = (var -> lexeme[0]) - 'x';
    return i;
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
    initRegMem();
}


void preCheck(BTNode *cur)
{
    if (cur -> token != ASSIGN) error();
    
    char c = cur -> left -> lexeme[0];
    if (c < 'x' || c > 'z') error();
}

void checkSyntax(BTNode *cur)
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
    
    checkSyntax(cur -> left);
    checkSyntax(cur -> right);
}

void compressTree(BTNode *cur)
{
    if (cur != NULL) {
        compressTree(cur -> left);
        compressTree(cur -> right);
    }
    else return;
    
    BTNode *lf = cur -> left, *rt = cur -> right;
    
    if (cur -> token == ADDSUB || cur -> token == MULDIV){
        if (lf -> val == -1 || rt -> val == -1) {
            cur -> val = -1;
            return;
        }
        else if (cur -> lexeme[0] == '+') {
            cur -> val = (lf -> val) + (rt -> val);
        }
        else if (cur -> lexeme[0] == '-') {
            cur -> val = (lf -> val) - (rt -> val);
        }
        else if (cur -> lexeme[0] == '*') {
            cur -> val = (lf -> val) * (rt -> val);
        }
        else if (cur -> lexeme[0] == '/') {
            if (rt -> val == 0) error();
            else cur -> val = (lf -> val) / (rt -> val);
        }
        
        free(cur -> left);
        free(cur -> right);
        cur -> left = cur -> right = NULL;
    }
    else if (cur -> token == ASSIGN) {
        lf -> assigned = 1;
    }
    else if (cur -> token == ID) {
        cur -> val = -1;
    }
    else return;
    //    printf("%c %d\n", cur -> lexeme[0], cur -> val);
}


void moveInt(BTNode *cur)
{
    int i = getReg();
    printf("MOV r%d %d\n", i, cur -> val);
    cur -> regi = i;
}

void moveVar(BTNode *cur)
{
    if (cur -> assigned) {
        mems[varReg(cur)].rewrite = 1;
        cur -> regi = varReg(cur);
    } else {
        int i = getReg(), j = 4 * varReg(cur);
        printf("MOV r%d [%d]\n", i, j);
        cur -> regi = i;
    }
}

void assign(BTNode *cur, BTNode *lf, BTNode *rt)
{
    int i = varReg(lf), j = rt -> regi;
    mems[i].val = regs[i].val = lf -> val;
    regs[i].isVac = 0;
    
    lf -> val = rt -> val;
    
    if (i != j) {
        if (rt -> token == INT) {
            printf("MOV r%d %d\n", i, rt -> val);
        }
        else if (rt -> token == ADDSUB || rt -> token == MULDIV || rt -> token == ID) {
            regs[j].isVac = 1;
            rt -> regi = -1;
            printf("MOV r%d r%d\n", i, j);
        }
        else error();
    }
    
    endMove();
}

void operVal(BTNode *cur, BTNode *lf, BTNode *rt)
{
    if (cur -> val != -1) {
        moveInt(cur);
        return;
    }
    
    int i = lf -> regi, j = rt -> regi;
    
    cur -> regi = i;
    regs[j].isVac = 1;
    rt -> regi = -1;
    
    if (cur -> lexeme[0] == '+') printf("ADD");
    else if (cur -> lexeme[0] == '-') printf("SUB");
    else if (cur -> lexeme[0] == '*') printf("MUL");
    else if (cur -> lexeme[0] == '/') printf("DIV");
    else error();
    
    printf(" r%d r%d\n", i, j);
}

void codeGen(BTNode *cur)
{
    if (cur != NULL) {
        codeGen(cur -> right);
        codeGen(cur -> left);
    }
    else return;
    
    switch (cur -> token) {
        case ADDSUB:
        case MULDIV:
            operVal(cur, cur -> left, cur -> right);
            break;
        case ASSIGN:
            assign(cur, cur -> left, cur -> right);
            break;
        case ID:
            moveVar(cur);
            break;
        case INT:
            moveInt(cur);
            break;
        default:
            error();
            break;
    }
}

#endif /* codeGen_h */

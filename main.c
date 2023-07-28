#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int value;
} Node;

typedef enum
{
    ADD,
    SUB,
    MUL,
    DIV
} Operation;

int getOp(void *op)
{
    if (!op)
        return 0;

    if (sizeof(op) == sizeof(int *))
        return *((int *)op);
    else if (sizeof(op) == sizeof(Node *))
        return ((Node *)op)->value;

    return 0;
}

int add(void *op1, void *op2)
{
    return getOp(op1) + getOp(op2);
}

int subtract(void *op1, void *op2)
{
    return getOp(op2) - getOp(op1);
}

int multiply(void *op1, void *op2)
{
    return getOp(op1) * getOp(op2);
}

int divide(void *op1, void *op2)
{
    return getOp(op2) / getOp(op1);
}

typedef int (*OperationFunc)(void *, void *);

OperationFunc makeFunc(Operation op)
{
    switch (op)
    {
    case ADD:
        return add;
    case SUB:
        return subtract;
    case MUL:
        return multiply;
    case DIV:
        return divide;
    default:
        return NULL;
    }
}

int calc(Node *node)
{
    int a = 0, b = 1, fib = 0;

    for (int i = 2; i < node->value; ++i)
    {
        fib = a + b;
        a = b;
        b = fib;
    }

    return fib;
}

int main()
{
    int x = 10, y = 6, z = 5, k = 4;
    Node *add = (Node *)malloc(sizeof(Node));
    Node *mul = (Node *)malloc(sizeof(Node));
    Node *sub = (Node *)malloc(sizeof(Node));
    Node *fibo = (Node *)malloc(sizeof(Node));

    add->value = (*makeFunc(ADD))(&x, &y);
    mul->value = (*makeFunc(MUL))(&z, &k);
    sub->value = (*makeFunc(SUB))(mul, add);
    fibo->value = (*makeFunc(SUB))(sub, NULL);

    printf("%d\n%d\n%d\n%d\n", add->value, mul->value, sub->value, calc(fibo));

    free(add);
    free(mul);
    free(sub);
    free(fibo);

    return 0;
}

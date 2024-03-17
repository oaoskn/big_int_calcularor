#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


typedef struct node {
    char data;
    struct node* next;
} node;

typedef struct {
    node* head, * tail;
} queue;

typedef struct {
    node* top;
} stack;

void initQueue(queue* q) {
    q->head = q->tail = NULL;
}

void enqueue(queue* q, char value) {
    node* newnode = malloc(sizeof(node));
    if (!newnode) return;
    newnode->data = value;
    newnode->next = NULL;
    if (q->tail) q->tail->next = newnode;
    q->tail = newnode;
    if (!q->head) q->head = newnode;
}

char dequeue(queue* q) {
    if (!q->head) return '\0';
    node* temp = q->head;
    char value = temp->data;
    q->head = q->head->next;
    if (!q->head) q->tail = NULL;
    free(temp);
    return value;
}

void initStack(stack* s) {
    s->top = NULL;
}

void push(stack* s, char value) {
    node* newnode = malloc(sizeof(node));
    if (!newnode) return;
    newnode->data = value;
    newnode->next = s->top;
    s->top = newnode;
}

char pop(stack* s) {
    if (!s->top) return '\0';
    node* temp = s->top;
    char value = temp->data;
    s->top = s->top->next;
    free(temp);
    return value;
}

char top(stack* s) {
    return s->top ? s->top->data : '\0';
}

int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

void convertToRPN(char* exp, queue* output) {
    stack opStack;
    initStack(&opStack);
    for (int i = 0; exp[i]; i++) {
        if (isdigit(exp[i])) {
            enqueue(output, exp[i]);
        }
        else if (exp[i] == '(') {
            push(&opStack, exp[i]);
        }
        else if (exp[i] == ')') {
            while (top(&opStack) != '(') {
                enqueue(output, pop(&opStack));
            }
            pop(&opStack); // Удаляем '('
        }
        else if (isOperator(exp[i])) {
            while (opStack.top && precedence(top(&opStack)) >= precedence(exp[i]) && top(&opStack) != '(') {
                enqueue(output, pop(&opStack));
            }
            push(&opStack, exp[i]);
        }
    }

    while (opStack.top) {
        enqueue(output, pop(&opStack));
    }
}

void printQueue(queue* q) {
    node* current = q->head;
    while (current) {
        printf("%c", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    char exp[] = "1+(2-5)*3";
    /*char exp[] = "100-5+4";*/


    queue output;
    initQueue(&output);

    convertToRPN(exp, &output);
    printf("RPN: ");
    printQueue(&output);

    return 0;
}
//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <ctype.h>
//#include <stddef.h>
//typedef struct {
//    int digits[10000];
//    long long int len;
//    char sign[1];
//} big_int;
//
//typedef struct node {
//    big_int data;
//    struct node* next;
//} node;
//
//typedef struct {
//    node* head, * tail;
//} queue;
//
//typedef struct {
//    node* top;
//} stack;
//
//void initQueue(queue* q) {
//    q->head = q->tail = NULL;
//}
//
//void enqueue(queue* q, big_int value) {
//    node* newnode = malloc(sizeof(node));
//    if (!newnode) return;
//    newnode->data = value;
//    newnode->next = NULL;
//    if (q->tail) q->tail->next = newnode;
//    q->tail = newnode;
//    if (!q->head) q->head = newnode;
//}
//
//big_int dequeue(queue* q) {
//    big_int error;
//    error.len = -1; // Используем len = -1 как индикатор ошибки
//
//    if (!q->head) return error;
//    node* temp = q->head;
//    big_int value = temp->data;
//    q->head = q->head->next;
//    if (!q->head) q->tail = NULL;
//    free(temp);
//    return value;
//}
//
//void initStack(stack* s) {
//    s->top = NULL;
//}
//
//void push(stack* s, char value) {
//    node* newnode = malloc(sizeof(node));
//    if (!newnode) return;
//
//    big_int biValue;
//    biValue.len = 1; // Здесь предполагается, что value - это одиночный символ, поэтому len = 1
//    biValue.digits[0] = value - '0'; // Преобразование char в int
//    biValue.sign[0] = '+';
//
//    newnode->data = biValue;
//    newnode->next = s->top;
//    s->top = newnode;
//}
//
//char pop(stack* s) {
//    if (!s->top) return '\0';
//    node* temp = s->top;
//    big_int value = temp->data;
//    s->top = s->top->next;
//    free(temp);
//
//    // Предполагаем, что big_int всегда хранит однозначные числа
//    return value.digits[0] + '0'; // Преобразование обратно в char
//}
//
//char top(stack* s) {
//    return s->top ? s->top->data.digits[0] + '0' : '\0'; // Аналогичное преобразование
//}
//
//int isOperator(char ch) {
//    if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
//        return 1;
//    }
//    return 0;
//}
//
//int precedence(char op) {
//    if (op == '+' || op == '-') return 1;
//    if (op == '*' || op == '/') return 2;
//    return 0;
//}
//
//void convertToRPN(char* exp, queue* output) {
//    stack opStack;
//    initStack(&opStack);
//    for (int i = 0; exp[i]; i++) {
//        if (isdigit(exp[i])) {
//            big_int number;
//            number.len = 0;
//            while (isdigit(exp[i])) {
//                number.digits[number.len++] = exp[i] - '0';
//                i++;
//            }
//            i--; // Компенсируем инкремент в цикле
//            number.sign[0] = '+';
//            enqueue(output, number);
//        }
//        else if (exp[i] == '(') {
//            push(&opStack, exp[i]);
//        }
//        else if (exp[i] == ')') {
//            while (top(&opStack) != '(') {
//                big_int op;
//                op.len = 1;
//                op.digits[0] = pop(&opStack);
//                op.sign[0] = '+';
//                enqueue(output, op);
//            }
//            pop(&opStack); // Удаляем '('
//        }
//        else if (isOperator(exp[i])) {
//            while (opStack.top && precedence(top(&opStack)) >= precedence(exp[i]) && top(&opStack) != '(') {
//                big_int op;
//                op.len = 1;
//                op.digits[0] = pop(&opStack);
//                op.sign[0] = '+';
//                enqueue(output, op);
//            }
//            push(&opStack, exp[i]);
//        }
//    }
//
//    while (opStack.top) {
//        big_int op;
//        op.len = 1;
//        op.digits[0] = pop(&opStack);
//        op.sign[0] = '+';
//        enqueue(output, op);
//    }
//}
//
//void printBigInt(big_int num) {
//    if (num.len == -1) {
//        printf("Error\n");
//        return;
//    }
//
//    for (int i = 0; i < num.len; ++i) {
//        printf("%d", num.digits[i]);
//    }
//}
//
//void printQueue(queue* q) {
//    node* current = q->head;
//    while (current) {
//        printBigInt(current->data);
//        current = current->next;
//    }
//    printf("\n");
//}
//
//int main() {
//    char exp[] = "123+(45-678)*9";
//
//    queue output;
//    initQueue(&output);
//
//    convertToRPN(exp, &output);
//    printf("RPN: ");
//    printQueue(&output);
//
//    return 0;
//}
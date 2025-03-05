#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE 100

typedef struct {
    const char *function;
    const char *file;
    int line;
} StackFrame;

typedef struct {
    StackFrame frames[STACK_SIZE];
    int top;
} CallStack;

CallStack callStack = {.top = -1};

void push_stack(const char *func, const char *file, int line) {
    if (callStack.top < STACK_SIZE - 1) {
        callStack.top++;
        callStack.frames[callStack.top] = (StackFrame){func, file, line};
    } else {
        fprintf(stderr, "Stack overflow: too many function calls\n");
    }
}

void pop_stack() {
    if (callStack.top >= 0) {
        callStack.top--;
    } else {
        fprintf(stderr, "Stack underflow: no function calls to pop\n");
    }
}

void print_stack_trace() {
    printf("Stack trace:\n");
    for (int i = callStack.top; i >= 0; i--) {
        printf("  at %s (%s:%d)\n", callStack.frames[i].function, callStack.frames[i].file, callStack.frames[i].line);
    }
}

#define TRACE_ENTER() push_stack(__func__, __FILE__, __LINE__)
#define TRACE_EXIT() pop_stack()

void functionC() {
    TRACE_ENTER();
    printf("Inside functionC\n");
    TRACE_EXIT();
}

void functionB() {
    TRACE_ENTER();
    functionC();
    TRACE_EXIT();
}

void functionA() {
    TRACE_ENTER();
    functionB();
    TRACE_EXIT();
}

int main() {
    TRACE_ENTER();
    functionA();
    print_stack_trace();
    TRACE_EXIT();
    return 0;
}

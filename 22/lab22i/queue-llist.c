#include <stdlib.h>
#include <stdio.h>
#include "mylib.h"
#include "queue.h"


typedef struct q_item *q_item;

struct q_item {
    double item;
    q_item next;
};

struct queue {
    q_item first;
    q_item last;
    int length;
};

queue queue_new() {
    queue result = emalloc(sizeof *result);
    result->first = NULL;
    result->last = NULL;
    result->length = 0;
    return result;
}

void enqueue(queue q, double item) {
    q_item temp;
    temp = emalloc(sizeof *temp);
    temp->item = item;
    temp->next = NULL;
    q->length++;
    if (q->first == NULL) {
        q->first = temp;
        q->last = temp;
    }else {
        q->last->next = temp;
        q->last = temp;
    }
}

double dequeue (queue q) {
    double rm = q->first->item;
    q_item temp = q->first;
    if (q->length > 0) {
        if (q->length == 1) {
            q->first = NULL;
            q->last = NULL;
        }else{
            q->first = q->first->next;
        }
        free(temp);
    }
    q->length--;
    return rm;
}

int queue_size (queue q) {
    if (q->length != 0) {
        return q->length;
    }else {
        return 0;
    }
}

void queue_print (queue q) {
    q_item temp = q->first;
    while (temp != NULL) {
        printf("%0.2f\n", temp->item);
        temp = temp->next;
    }
}

void queue_print_info(queue q) {
    if (q->length ==0) {
        printf("The queue is empty\n");
    }else {
        printf("first %0.2f, last %0.2f, length %d\n", q->first->item,
               q->last->item, q->length);
    }
}

queue queue_free(queue q) {
    q_item temp = q->first;
    while (temp != NULL) {
        q_item i = temp;        
        temp = temp->next;
        free(i);
    }
    free(q);

    return q;
}


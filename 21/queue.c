#include <stdlib.h>
#include <stdio.h>
#include "mylib.h"
#include "queue.h"

struct queue  {
    int *items;
    int head;
    int capacity;
    int num_items;
};

queue queue_new() {
    queue result = emalloc(sizeof *result);
    result->capacity = 30;
    result->head = 0;
    result->num_items = 0;
    result->items = emalloc(result->capacity * sizeof result->items[0]);
    return result;
}

void enqueue(queue q, int item) {
    if (q->num_items < q->capacity) {
        q->items[q->head + (q->num_items % q->capacity)] = item;
        q->num_items++;
    }
}

int dequeue (queue q) {
    int rm = 0;
    rm = q->head;
    if (q->num_items > 0) {
        q->num_items--;
        q->head++;
        return q->items[rm];
    }else {
        return 0;
    }
}

int queue_size (queue q) {
    if (q->num_items != 0) {
        return q->num_items;
    }else {
        return 0;
    }
}

void queue_print (queue q) {
    int i = 0;
    if (q->num_items != 0) {
        while (i < q->num_items) {
            printf("%d\n", q->items[q->head + i]);
            i++;
        }
    }
}

queue queue_free(queue q) {
    free(q->items);
    free(q);

    return q;
}

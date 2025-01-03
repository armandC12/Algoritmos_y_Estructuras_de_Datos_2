#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "queue.h"

struct s_queue {
    struct s_node *first;
    struct s_node *last;
    unsigned int size;
};

struct s_node {
    queue_elem elem;
    struct s_node *next;
};

typedef struct s_node * node;

static struct s_node *
create_node(queue_elem e) {
    struct s_node *new_node=malloc(sizeof(struct s_node));
    assert(new_node!=NULL);
    new_node->elem = e;
    new_node->next = NULL;
    return new_node;
}

static struct s_node *
destroy_node(struct s_node *node) {
    node->next=NULL;
    free(node);
    node=NULL;
    return node;
}


static bool
invrep(queue q) {
    return (q != NULL && q->first != NULL && q->last != NULL && q->size != 0) 
        || (q == NULL && q->first == NULL && q->last == NULL && q->size == 0);
}

queue queue_empty(void) {
    queue q=NULL;
    q = malloc(sizeof(struct s_queue));
    q->first = NULL;
    q->last = NULL;
    q->size = 0u;
    assert(invrep(q) && queue_is_empty(q));
    return q;
}

queue queue_enqueue(queue q, queue_elem e) {
    assert(invrep(q));
    struct s_node *new_node = create_node(e);
    if (q->first==NULL) {
        q->first = new_node;
        q->last = q->first;
    } else {
        q->last->next = new_node;;
        q->last = new_node;
    }
    q->size++;

    assert(invrep(q) && !queue_is_empty(q));
    return q;
}

bool queue_is_empty(queue q) {
    assert(invrep(q));
    return q->first == NULL;
}

queue_elem queue_first(queue q) {
    assert(invrep(q) && !queue_is_empty(q));
    return q->first->elem;
}
unsigned int queue_size(queue q) {
    assert(invrep(q));
    unsigned int size=0;
    if (q->first != NULL) {
        size = q->size;
    }
    return size;
}

queue queue_dequeue(queue q) {
    assert(invrep(q) && !queue_is_empty(q));
    struct s_node * killme=q->first;
    q->first = q->first->next;
    killme = destroy_node(killme);
    q->size--;
    assert(invrep(q));
    return q;

}

queue queue_destroy(queue q) {
    assert(invrep(q));
    struct s_node *node=q->first;
    while (node != NULL) {
        struct s_node *killme=node;
        node = node->next;
        killme = destroy_node(killme);
    }
    free(q);
    q = NULL;
    assert(q == NULL);
    return q;
}


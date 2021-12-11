#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (q) {
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* TODO: How about freeing the list elements and the strings? */
    if (!q) {
        return;
    }
    struct ELE *cur = q->head;
    struct ELE *pre = NULL;
    while (cur) {
        if (pre != NULL) {
            free(pre->value);
            free(pre);
        }
        pre = cur;
        cur = cur->next;
    }
    if (pre != NULL) {
        free(pre->value);
        free(pre);
    }
    /* Free queue structure */
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    /* TODO: What should you do if the q is NULL? */
    if (!q) {
        return false;
    }

    struct ELE *newh = malloc(sizeof(list_ele_t));
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    if (!newh) {
        return false;
    }
    size_t length = strlen(s) + 1;
    newh->value = (char *) malloc(length * sizeof(char));
    if (!newh->value) {
        free(newh);
        return false;
    }
    snprintf(newh->value, length, "%s", s);
    newh->next = q->head;
    q->head = newh;
    if (q->size == 0) {
        q->tail = newh;
    }
    q->size++;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* TODO: You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL) {
        return false;
    }
    struct ELE *newt = malloc(sizeof(list_ele_t));
    if (!newt) {
        return false;
    }
    size_t length = strlen(s) + 1;
    newt->value = malloc(sizeof(char) * length);
    if (!newt->value) {
        free(newt);
        return false;
    }
    snprintf(newt->value, length, "%s", s);
    newt->next = NULL;
    if (!q->head) {
        q->head = newt;
        q->tail = newt;
        q->size++;
    } else {
        q->tail->next = newt;
        q->tail = newt;
        q->size++;
    }
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* TODO: You need to fix up this code. */
    if (!q || !q->head) {
        return false;
    }

    struct ELE *remove = q->head;
    if (sp) {
        snprintf(sp, bufsize, "%s", remove->value);
    }
    q->head = q->head->next;
    free(remove->value);
    free(remove);
    q->size--;
    return true;

}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (!q || !q->head) {
        return 0;
    }
    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (q && q->head) {
        struct ELE *pre = NULL;
        struct ELE *cur = q->head;
        q->tail = q->head;
        while (cur) {
            struct ELE *tmp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = tmp;
        }
        q->head = pre;
    }
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
/*
void q_sort(queue_t *q)
{
    if (!q || q->head == q->tail) {
        return;
    }

    // Merge sort
    q->head=mergesort(q->head);

    while (q->tail->next) {
        q->tail = q->tail->next;
    }
}
struct ELE* merge(struct ELE *l, struct ELE *r)
{   struct ELE *dummy = malloc(sizeof(list_ele_t));
    dummy->next = NULL;
    struct ELE *cur=dummy;
    while(l && r){
        if (strcmp(l->value, r->value) < 0) {
            cur->next = l;
            cur = cur->next;
            l = l->next;
        }
        else{
            cur->next = r;
            cur = cur->next;
            r = r->next;
        }
    }
    if(l) {
        cur->next = l;
    }
    if(r) {
        cur->next = r;
    }
    cur = dummy->next;
    free(dummy);
    return cur;
}
struct ELE* mergesort(struct ELE *head1)
{
    if (!(head1)->next) {
        return head1;
    }
    struct ELE *fast = (head1)->next;
    struct ELE *slow = (head1);
    while(fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    struct ELE *head2 = (slow->next);
    slow->next = NULL;
    head1 = mergesort(head1);
    head2 = mergesort(head2);
    struct ELE *newHead = merge(head1,head2);
    return newHead;
}
*/
void merge_sort(list_ele_t **head)
{
    if (!(*head) || !((*head)->next))
        return;

    list_ele_t *l1 = (*head)->next;  // faster pointer
    list_ele_t *l2 = *head;          // slower pointer

    // split list
    while (l1 && l1->next) {
        l2 = l2->next;
        l1 = l1->next->next;
    }
    l1 = l2->next;
    l2->next = NULL;
    l2 = *head;

    // Recursively split until each list exist one element
    merge_sort(&l2);  // the left linked list
    merge_sort(&l1);  // the right linked list

    // merge sorted l1 and sorted l2
    // reuse head to record the head of new list
    *head = NULL;
    list_ele_t **tmp = head;

    while (l1 && l2) {
        if (strcmp(l1->value, l2->value) < 0) {  // l1 < l2
            *tmp = l1;
            l1 = l1->next;
        } else {
            *tmp = l2;
            l2 = l2->next;
        }
        tmp = &((*tmp)->next);
    }

    // Either l1 or l2 will left
    *tmp = l1 ? l1 : l2;
}

void q_sort(queue_t *q)
{
    // if q has only one element or q is empty, q->head == q->tail
    if (!q || q->head == q->tail) {
        return;
    }

    // Merge sort
    merge_sort(&q->head);

    while (q->tail->next) {
        q->tail = q->tail->next;
    }
}


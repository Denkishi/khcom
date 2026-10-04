#include "listpool.h"
#include <stddef.h>

void ListAppend(ListNode* node, ListNode** head, ListNode** tail) {
    if (*head == NULL) {
        *head = node;
    }

    node->prev = *tail;

    if (*tail != NULL) {
        (*tail)->next = node;
    }

    node->next = NULL;
    *tail = node;
}

void ListInsertAfter(ListNode* node, ListNode** head, ListNode** tail, ListNode* after) {
    ListNode* next;

    if (after != NULL) {
        node->prev = after;
        next = after->next;
        node->next = next;
        after->next = node;

        if (next != NULL) {
            next->prev = node;
        } else {
            *tail = node;
        }
    } else {
        ListAppend(node, head, tail);
    }
}

void ListInsertBefore(ListNode* node, ListNode** head, ListNode** tail, ListNode* before) {
    ListNode* prev;

    if (before != NULL) {
        node->next = before;
        prev = before->prev;
        node->prev = prev;
        before->prev = node;

        if (prev != NULL) {
            prev->next = node;
        } else {
            *head = node;
        }
    } else {
        ListAppend(node, head, tail);
    }
}

void ListRemove(ListNode* node, ListNode** head, ListNode** tail) {
    if (node->prev == NULL) {
        if (node->next == NULL) {
            *head = NULL;
            *tail = NULL;
        } else {
            node->next->prev = node->prev;
            *head = node->next;
        }
    } else {
        if (node->next == NULL) {
            *tail = node->prev;
            node->prev->next = node->next;
        } else {
            node->next->prev = node->prev;
            node->prev->next = node->next;
        }
    }
}

void ListPoolInit(void* pool) {
    ListPool* list = pool;

    list->freeHead = NULL;
    list->freeTail = NULL;
    list->activeHead = NULL;
    list->activeTail = NULL;
}

void ListPoolAddFree(void* p, void* pool, void* owner) {
    ListNode* node = p;
    ListPool* list = pool;

    ListAppend(node, &list->freeHead, &list->freeTail);
    node->owner = owner;
    node->flags = 0;
}

void ListPoolActivate(void* a, void* b) {
    ListNode* node;
    ListPool* list;

    node = a;
    list = b;
    ListRemove(node, &list->freeHead, &list->freeTail);
    ListAppend(node, &list->activeHead, &list->activeTail);
    node->flags |= LIST_NODE_FLAG_ACTIVE;
    node->self = node;
}

void ListPoolActivateAfter(void* p, void* pool, void* position) {
    ListNode* node = p;
    ListPool* list = pool;
    ListNode* after = position;

    ListRemove(node, &list->freeHead, &list->freeTail);
    ListInsertAfter(node, &list->activeHead, &list->activeTail, after);
    node->flags |= LIST_NODE_FLAG_ACTIVE;
    node->self = node;
}

void ListPoolActivateBefore(void* p, void* pool, void* position) {
    ListNode* node = p;
    ListPool* list = pool;
    ListNode* before = position;

    ListRemove(node, &list->freeHead, &list->freeTail);
    ListInsertBefore(node, &list->activeHead, &list->activeTail, before);
    node->flags |= LIST_NODE_FLAG_ACTIVE;
    node->self = node;
}

void* ListPoolRelease(void* p, void* pool) {
    ListNode* node = p;
    ListPool* list = pool;
    ListNode* next;

    next = node->next;
    ListRemove(node, &list->activeHead, &list->activeTail);
    ListAppend(node, &list->freeHead, &list->freeTail);
    node->flags &= ~LIST_NODE_FLAG_ACTIVE;

    if (next != NULL) {
        return next->owner;
    }

    return NULL;
}

void* ListPoolFirst(void* pool) {
    ListPool* list = pool;
    ListNode* n;
    void* result;

    n = list->activeHead;

    if (n != NULL) {
        if (n->flags & LIST_NODE_FLAG_SKIP) {
            return ListPoolNext(n);
        }

        result = n->owner;
    } else {
        result = NULL;
    }

    return result;
}

void* ListPoolLast(void* pool) {
    ListPool* list = pool;
    ListNode* n;
    void* result;

    n = list->activeTail;

    if (n != NULL) {
        if (n->flags & LIST_NODE_FLAG_SKIP) {
            return ListPoolPrev(n);
        }

        result = n->owner;
    } else {
        result = NULL;
    }

    return result;
}

void* ListPoolNext(void* p) {
    ListNode* node = p;
    ListNode* n;
    void* result;

    n = node->next;

    if (n != NULL) {
        if (n->flags & LIST_NODE_FLAG_SKIP) {
            return ListPoolNext(n);
        }

        result = n->owner;
    } else {
        result = NULL;
    }

    return result;
}

void* ListPoolPrev(void* p) {
    ListNode* node = p;
    ListNode* n;
    void* result;

    n = node->prev;

    if (n != NULL) {
        if (n->flags & LIST_NODE_FLAG_SKIP) {
            return ListPoolPrev(n);
        }

        result = n->owner;
    } else {
        result = NULL;
    }

    return result;
}

void* ListPoolFirstFree(void* pool) {
    ListPool* list = pool;
    ListNode* n;

    n = list->freeHead;

    if (n != NULL) {
        return n->owner;
    }

    return NULL;
}

void func_08000D1C() {
}

void ListNodeInit(void* p, void* pool, void* owner) {
    ListNode* node = p;

    node->owner = owner;
    node->flags = 0;
}

void ListPoolAppend(void* p, void* pool) {
    ListNode* node = p;
    ListPool* list = pool;

    ListAppend(node, &list->activeHead, &list->activeTail);
    node->flags |= LIST_NODE_FLAG_ACTIVE;
    node->self = node;
}

void ListPoolInsertAfter(void* p, void* pool, void* position) {
    ListNode* node = p;
    ListPool* list = pool;
    ListNode* after = position;

    ListInsertAfter(node, &list->activeHead, &list->activeTail, after);
    node->flags |= LIST_NODE_FLAG_ACTIVE;
    node->self = node;
}

void ListPoolInsertBefore(void* p, void* pool, void* position) {
    ListNode* node = p;
    ListPool* list = pool;
    ListNode* before = position;

    ListInsertBefore(node, &list->activeHead, &list->activeTail, before);
    node->flags |= LIST_NODE_FLAG_ACTIVE;
    node->self = node;
}

void* ListPoolRemove(void* p, void* pool) {
    ListNode* node = p;
    ListPool* list = pool;
    ListNode* next;

    next = node->next;
    ListRemove(node, &list->activeHead, &list->activeTail);
    node->flags &= ~LIST_NODE_FLAG_ACTIVE;

    if (next != NULL) {
        return next->owner;
    }

    return NULL;
}

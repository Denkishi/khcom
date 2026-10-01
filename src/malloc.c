#include "listpool.h"
#include "malloc.h"
#include <stddef.h>
#include "types.h"

static const u8 sEwramHeapName[12] = "HEAP_SYSTEM";

static const u8 sIwramHeapName[16] = "HEAPCPU_SYSTEM";

static Heap sEwramHeap;
static Heap sIwramHeap;

void HeapUnlinkFreeBlock(HeapBlock* b) {
    b->prevFree->nextFree = b->nextFree;
    b->nextFree->prevFree = b->prevFree;
}

u8 HeapContains(const void* p, Heap* heap) {
    if (p != NULL && (u8*)p > (u8*)heap->start && (u8*)p < (u8*)heap->end) {
        return 1;
    }

    return 0;
}

HeapBlock* HeapFindFreeBlock(s32 size, Heap* heap) {
    HeapBlock* b;

    b = heap->start->nextFree;

    while (b != NULL && b != heap->end) {
        if (b->size >= size) {
            return b;
        }

        b = b->nextFree;
    }

    return NULL;
}

void HeapInit(void* addr, u32 size, Heap* heap) {
    HeapBlock* head;
    HeapBlock* tail;
    HeapBlock* first;
    const void* name;
    u32 last;

    size &= ~31;
    head = addr;

    do {
        last = size - 32;
    } while (0);

    tail = (HeapBlock*)((u8*)addr + last);
    heap->start = head;
    heap->end = tail;
    first = head + 1;
    head->size = -32;
    head->prevFree = NULL;
    head->nextFree = first;
    head->prev = NULL;
    head->next = first;
    name = heap->name;
    head->name = name;
    head->self = head;
    tail->size = -1;
    tail->prevFree = first;
    tail->nextFree = NULL;
    tail->prev = first;
    tail->next = NULL;
    tail->name = name;
    tail->self = tail;
    first->size = size - 64;
    first->prevFree = head;
    first->nextFree = tail;
    first->prev = head;
    first->next = tail;
    first->name = name;
    first->self = first;
    heap->allocFlag = 0;
}

void EwramHeapInit(void* addr, u32 size) {
    SetEwramHeapName(sEwramHeapName);
    HeapInit(addr, size, &sEwramHeap);
}

void IwramHeapInit(void* addr, u32 size) {
    SetIwramHeapName(sIwramHeapName);
    HeapInit(addr, size, &sIwramHeap);
}

void* HeapAlloc(u32 size, Heap* heap) {
    HeapBlock* b;
    HeapBlock* prev;
    s32 rem;

    if (size == 0) {
        return NULL;
    }

    size = (size + 63) & ~31;
    b = HeapFindFreeBlock(size, heap);

    if (b == NULL) {
        return NULL;
    }

    if (b->size < (s32)(size + 64)) {
        size = b->size;
        HeapUnlinkFreeBlock(b);
    } else {
        prev = b;
        rem = prev->size - size;
        prev->size = rem;
        b = (HeapBlock*)((u8*)prev + rem);
        b->next = prev->next;
        b->prev = prev;
        prev->next = b;
        b->next->prev = b;
    }

    b->size = -size;
    b->prevFree = NULL;
    b->nextFree = NULL;

    if (heap->allocFlag != 0) {
        b->allocFlag = 1;
    } else {
        b->allocFlag = 0;
    }

    b->name = heap->name;
    b->self = b;

    return b + 1;
}

void* EwramAlloc(u32 size) {
    return HeapAlloc(size, &sEwramHeap);
}

void* IwramAlloc(u32 size) {
    return HeapAlloc(size, &sIwramHeap);
}

void HeapFree(const void* p, Heap* heap) {
    HeapBlock* b;
    HeapBlock* n;
    HeapBlock* head;
    s32 size;

    if (p == NULL) {
        return;
    }

    b = (HeapBlock*)p - 1;

    if (b->self != b) {
        return;
    }

    if (!HeapContains(p, heap)) {
        return;
    }

    size = -b->size;

    if (size < 0) {
        return;
    }

    b->size = size;
    n = b->prev;

    if (n->size > 0) {
        HeapUnlinkFreeBlock(n);
        n->size += size;
        n->next = b->next;
        b->next->prev = n;
        b->prev = NULL;
        b->next = NULL;
        b = n;
    }

    n = b->next;

    if (n->size > 0) {
        HeapUnlinkFreeBlock(n);
        b->size += n->size;
        b->next = n->next;
        n->next->prev = b;
        n->prev = NULL;
        n->next = NULL;
    }

    head = heap->start;
    b->prevFree = head;
    b->nextFree = head->nextFree;
    head->nextFree->prevFree = b;
    head->nextFree = b;
    b->self = NULL;
}

void EwramFree(const void* p) {
    HeapFree(p, &sEwramHeap);
}

void IwramFree(const void* p) {
    HeapFree(p, &sIwramHeap);
}

s32 HeapGetBlockSize(void* p, Heap* heap) {
    s32 size;

    if (HeapContains(p, heap)) {
        size = -((HeapBlock*)p - 1)->size;

        if (size > 0) {
            return size;
        }
    }

    return 0;
}

s32 EwramGetBlockSize(void* p) {
    return HeapGetBlockSize(p, &sEwramHeap);
}

s32 IwramGetBlockSize(void* p) {
    return HeapGetBlockSize(p, &sIwramHeap);
}

s32 HeapGetFreeTotal(Heap* heap) {
    HeapBlock* b;
    s32 total;

    b = heap->start->nextFree;
    total = 0;

    while (b != NULL && b->size > 0) {
        total += b->size;
        b = b->nextFree;
    }

    return total;
}

s32 EwramGetFreeTotal() {
    return HeapGetFreeTotal(&sEwramHeap);
}

s32 IwramGetFreeTotal() {
    return HeapGetFreeTotal(&sIwramHeap);
}

void func_08000A60(Heap* heap) {
    HeapBlock* b;

    for (b = heap->start; b != NULL; b = b->next) {
        *(volatile s32*)&b->size;
    }
}

void func_08000A70() {
    func_08000A60(&sEwramHeap);
}

void func_08000A80() {
    func_08000A60(&sIwramHeap);
}

void SetEwramHeapAllocFlag(u8 v) {
    sEwramHeap.allocFlag = v;
}

void SetIwramHeapAllocFlag(u8 v) {
    sIwramHeap.allocFlag = v;
}

void func_08000AA8(Heap* heap) {
    HeapBlock* b;

    for (b = heap->start; b != NULL; b = b->next) {
        *(volatile s32*)&b->size;
    }
}

void func_08000AB8() {
    func_08000AA8(&sEwramHeap);
}

void func_08000AC8() {
    func_08000AA8(&sIwramHeap);
}

void SetEwramHeapName(const void* name) {
    sEwramHeap.name = name;
}

void SetIwramHeapName(const void* name) {
    sIwramHeap.name = name;
}

const void* GetEwramHeapName() {
    return sEwramHeap.name;
}

const void* GetIwramHeapName() {
    return sIwramHeap.name;
}

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

/**
 * malloc.c
 * Heap Memory Allocator
 */

#include "malloc.h"
#include <stddef.h>
#include "types.h"

static const u8 sEwramHeapName[12] = "HEAP_SYSTEM";

static const u8 sIwramHeapName[16] = "HEAPCPU_SYSTEM";

static Heap sEwramHeap;
static Heap sIwramHeap;

void HeapUnlinkFreeBlock(HeapBlock* block) {
    block->prevFree->nextFree = block->nextFree;
    block->nextFree->prevFree = block->prevFree;
}

u8 HeapContains(const void* ptr, Heap* heap) {
    if (ptr != NULL && (u8*)ptr > (u8*)heap->start && (u8*)ptr < (u8*)heap->end) {
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

    // fakematch
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

void HeapFree(const void* ptr, Heap* heap) {
    HeapBlock* b;
    HeapBlock* n;
    HeapBlock* head;
    s32 size;

    if (ptr == NULL) {
        return;
    }

    b = (HeapBlock*)ptr - 1;

    if (b->self != b) {
        return;
    }

    if (!HeapContains(ptr, heap)) {
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

void EwramFree(const void* ptr) {
    HeapFree(ptr, &sEwramHeap);
}

void IwramFree(const void* ptr) {
    HeapFree(ptr, &sIwramHeap);
}

s32 HeapGetBlockSize(void* ptr, Heap* heap) {
    s32 size;

    if (HeapContains(ptr, heap)) {
        size = -((HeapBlock*)ptr - 1)->size;

        if (size > 0) {
            return size;
        }
    }

    return 0;
}

s32 EwramGetBlockSize(void* ptr) {
    return HeapGetBlockSize(ptr, &sEwramHeap);
}

s32 IwramGetBlockSize(void* ptr) {
    return HeapGetBlockSize(ptr, &sIwramHeap);
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

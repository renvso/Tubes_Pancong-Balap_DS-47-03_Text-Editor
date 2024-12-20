#ifndef TRIAL2_H_INCLUDED
#define TRIAL2_H_INCLUDED
#include <iostream>
#include "trial2.h"

#include <iostream>

using namespace std;

typedef char infotype;
typedef struct elmList *address;
typedef int countOfChar;
struct elmList {
    infotype info;
    address prev;
    address next;
};

struct List {
    address first;
    address last;
    address pointer;
};

const int nMax = 2024;
typedef int index;

struct infoStack {
    string operation;         // Jenis operasi: "insert" atau "delete"
    address target;           // Pointer ke elemen yang dihapus/dimasukkan
    address cursorBefore;     // Posisi cursor sebelum operasi
};

struct Stack {
    infoStack info[nMax];
    index top;
};

// Fungsi untuk List
void createList(List &L);
address createElm(infotype data);
void insertFirst(List &L, address p);
void insertTextLast(List &L, address p);
void insertTextAfter(List &L, address prec, address p);
void deleteTextFirst(List &L, address &p);
void deleteTextLast(List &L, address &p);
void deleteAfterPointer(List &L, address prec, address &p);
void deleteBeforePointer(List &L, address &p);


// Fungsi untuk Stack
void createStack(Stack &S);
bool isStackEmpty(Stack S);
bool isStackFull(Stack S);
void push(Stack &S, infoStack data);
void pop(Stack &S, infoStack &data);

// Fungsi Display
void display(List L);
void displayWithPointer(List L); // Menampilkan teks dengan posisi pointer

// Fungsi Manipulasi Pointer
void movePointerLeft(List &L);   // Memindahkan pointer ke kiri
void movePointerRight(List &L);  // Memindahkan pointer ke kanan

// Fungsi Undo dan Redo
void undo(List &L, Stack &undo, Stack &redo);
void redo(List &L, Stack &undo, Stack &redo);

// fungsi tambahan
countOfChar countCharacters(List L);
#endif // TRIAL4_H_INCLUDED

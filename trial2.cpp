#include "trial2.h"

void createList(List &L) {
    L.first = nullptr;
    L.last = nullptr;
    L.pointer = nullptr;
}

address createElm(infotype data) {
    address p = new elmList;
    p->info = data;
    p->next = nullptr;
    p->prev = nullptr;
    return p;
}

void insertFirst(List &L, address p) {
    if (L.first == nullptr) {
        L.first = L.last = L.pointer = p;
    } else {
        p->next = L.first;
        L.first->prev = p;
        L.first = p;
        L.pointer = p;
    }
}

void insertTextLast(List &L, address p) {
    if (L.last == nullptr) {
        insertFirst(L, p);
    } else {
        L.last->next = p;
        p->prev = L.last;
        L.last = p;
        L.pointer = p;
    }
}

void insertTextAfter(List &L, address prec, address p) {
    if (prec == L.last) {
        insertTextLast(L, p);
    } else {
        p->next = prec->next;
        p->prev = prec;
        prec->next->prev = p;
        prec->next = p;
        L.pointer = p;
    }
}

void deleteTextFirst(List &L, address &p) {
    if (L.first == nullptr) return;
    p = L.first;
    if (L.first == L.last) {
        L.first = L.last = L.pointer = nullptr;
    } else {
        L.first = L.first->next;
        L.first->prev = nullptr;
        if (L.pointer == p) L.pointer = L.first;
    }
    p->next = nullptr;
}

void deleteTextLast(List &L, address &p) {
    if (L.last == nullptr) return;
    p = L.last;
    if (L.first == L.last) {
        L.first = L.last = L.pointer = nullptr;
    } else {
        L.last = L.last->prev;
        L.last->next = nullptr;
        if (L.pointer == p) L.pointer = L.last;
    }
    p->prev = nullptr;
}

void deleteAfterPointer(List &L, address prec, address &p) {
    if (prec == nullptr || prec->next == nullptr) {
      return;
    }
    p = prec->next;
    prec->next = p->next;
    L.pointer = prec;
    if (p->next != nullptr) {
        p->next->prev = prec;
    } else {
        L.last = prec;
    }
    p->prev = p->next = nullptr;
}

void deleteBeforePointer(List &L, address &p) {
    if (L.pointer == nullptr || L.pointer->prev == nullptr) {
      return; // Tidak ada elemen sebelum pointer
    }
    p = L.pointer->prev; // Elemen yang akan dihapus
    if (p == L.first) {
        // Jika elemen yang akan dihapus adalah elemen pertama
        L.first = L.pointer;
        L.first->prev = nullptr;
    } else {
        // Jika elemen yang akan dihapus ada di tengah
        p->prev->next = L.pointer;
        L.pointer->prev = p->prev;
    }
    p->next = nullptr; // Putuskan koneksi elemen
    p->prev = nullptr;
}


void deleteTextBefore(List &L, address &p) {
    if (L.pointer == nullptr || L.pointer->prev == nullptr) {
      return;
    }
    p = L.pointer->prev;
    if (p == L.first) {
        L.first = L.pointer;
        L.first->prev = nullptr;
    } else {
        p->prev->next = L.pointer;
        L.pointer->prev = p->prev;
    }
    p->next = nullptr;
    p->prev = nullptr;
}

void createStack(Stack &S) {
    S.top = 0;
}

bool isStackEmpty(Stack S) {
    return S.top == 0;
}

bool isStackFull(Stack S) {
    return S.top == nMax;
}

void push(Stack &S, infoStack data) {
    if (!isStackFull(S)) {
        S.info[S.top++] = data;
    } else {
        cout << "Stack is full!" << endl;
    }
}

void pop(Stack &S, infoStack &data) {
    if (!isStackEmpty(S)) {
        data = S.info[--S.top];
    } else {
        cout << "Stack is empty!" << endl;
    }
}

void display(List L) {
    address temp = L.first;
    cout << "Text: ";
    while (temp) {
        cout << temp->info;
        temp = temp->next;
    }
    cout << endl;
}

void displayWithPointer(List L) {
    address temp = L.first;
    cout << "Text: ";
    while (temp) {
        cout << temp->info;
        temp = temp->next;
    }
    cout << endl;

    cout << "Pointer is at: ";
    if (L.pointer) {
        cout << L.pointer->info << endl;
    } else {
        cout << "(none)" << endl;
    }

    int count = countCharacters(L);
    cout << "[" << count << "] Total characters typed: " << count << endl;
}


void movePointerLeft(List &L) {
    if (L.pointer && L.pointer->prev) {
        L.pointer = L.pointer->prev;
    }
}

void movePointerRight(List &L) {
    if (L.pointer && L.pointer->next) {
        L.pointer = L.pointer->next;
    }
}

void undo(List &L, Stack &undo, Stack &redo) {
    if (!isStackEmpty(undo)) {
        infoStack lastOp;
        pop(undo, lastOp);
        push(redo, lastOp);

        if (lastOp.operation == "insert") {
            if (lastOp.target == L.first) {
                address temp;
                deleteTextFirst(L, temp);
            } else if (lastOp.target == L.last) {
                address temp;
                deleteTextLast(L, temp);
            } else {
                address temp;
                deleteAfterPointer(L, lastOp.target->prev, temp);
            }
        } else if (lastOp.operation == "delete") {
            if (lastOp.cursorBefore == nullptr) {
                insertFirst(L, lastOp.target);
            } else if (lastOp.cursorBefore == L.last) {
                insertTextLast(L, lastOp.target);
            } else {
                insertTextAfter(L, lastOp.cursorBefore, lastOp.target);
            }
        }
    }
}

void redo(List &L, Stack &undo, Stack &redo) {
    if (!isStackEmpty(redo)) {
        infoStack lastOp;
        pop(redo, lastOp);
        push(undo, lastOp);

        if (lastOp.operation == "insert") {
            if (L.pointer == nullptr) {
                insertFirst(L, lastOp.target);
            } else if (L.pointer == L.last) {
                insertTextLast(L, lastOp.target);
            } else {
                insertTextAfter(L, L.pointer, lastOp.target);
            }
        } else if (lastOp.operation == "delete") {
            if (L.pointer == L.first) {
                address temp;
                deleteTextFirst(L, temp);
            } else if (L.pointer == L.last) {
                address temp;
                deleteTextLast(L, temp);
            } else {
                address temp;
                deleteAfterPointer(L, lastOp.target->prev, temp);
            }
        }
    }
}

countOfChar countCharacters(List L) {
    countOfChar count = 0;
    address temp = L.first;
    while (temp != nullptr) {
        count++;
        temp = temp->next;
    }
    return count;
}

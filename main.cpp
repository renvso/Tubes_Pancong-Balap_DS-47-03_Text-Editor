#include "trial2.h"
#include <conio.h> // for _getch() buat bisa live typing

int main() {
    List text;
    Stack undoStack, redoStack;
    createList(text);
    createStack(undoStack);
    createStack(redoStack);

    char input;
    cout << "Simple Text Editor\n";
    cout << "Commands:\n";
    cout << "Type to insert characters.\n";
    cout << "Backspace to delete.\n";
    cout << "Arrow keys to move cursor.\n";
    cout << "Ctrl+Z for Undo, Ctrl+Y for Redo.\n";
    cout << "Press ESC to exit.\n";

    do {
        system("cls"); // Clear screen for live update
        displayWithPointer(text);
        input = _getch();

        if (input == 27) break; // ESC key to exit

        if (input == 8) { // Backspace key
            if (text.pointer) {
                infoStack undoOp = {"delete", text.pointer, text.pointer->prev};
                push(undoStack, undoOp);
                address temp;
                if (text.pointer == text.last) {
                    deleteTextLast(text, temp);
                    text.pointer = text.last;
                } else if (text.pointer == text.first) {
                    deleteTextFirst(text, temp);
                    text.pointer = text.first;
                } else {
                    deleteAfterPointer(text, text.pointer->prev, temp);
                }
            }
        } else if (input == -32) { // Arrow keys
            input = _getch();
            if (input == 75) { // Left arrow
                movePointerLeft(text);
            } else if (input == 77) { // Right arrow
                movePointerRight(text);
            }
        } else if (input == 26) { // Ctrl+Z (Undo)
            undo(text, undoStack, redoStack);
        } else if (input == 25) { // Ctrl+Y (Redo)
            redo(text, undoStack, redoStack);
        } else if (input >= 32 && input <= 126) { // Printable characters
            address newChar = createElm(input);
            if (!text.pointer || text.pointer == text.last) {
                insertTextLast(text, newChar);
            } else {
                insertTextAfter(text, text.pointer, newChar);
            }
            infoStack undoOp = {"insert", newChar, text.pointer};
            push(undoStack, undoOp);
            createStack(redoStack); // Clear redo stack on new operation
        }

    } while (true);

    return 0;
}

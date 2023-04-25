// I agree to abide by the Stevens Honor System - Jett Tinik

#include <iostream>
using namespace std;

class Node {
 public:
  int value;
  Node *next;

  Node() {
    value = 0;
    next = NULL;
  }
};

class Stack {
 public:
  Node *top;

  Stack() { top = NULL; }
  void push(int val) {
    if (top == NULL) {
      top = new Node;
      top->value = val;
    } else {
      Node *temp;
      temp = new Node;
      temp->value = val;
      temp->next = top;
      top = temp;
    }
  }

  void pop() {
    if (top == NULL) {
      cout << "Nothing to delete in Stack\n";
    } else {
      Node *temp = top->next;
      cout << "deleting " << top->value << endl;
      delete top;
      top = temp;
    }
  }

  void displayContents() {
    if (top == NULL) {
      cout << "No stack to display" << endl;
    } else {
      Node *temp = top;
      while (temp != NULL) {
        cout << temp->value << ", ";
        temp = temp->next;
      }
    }
  }
};

int main() {
  Stack stack;
  int choice = 0;

  while (1) {
    cout << "1 - add, 2 - delete, 3 - display" << endl;
    cin >> choice;
    switch (choice) {
      case 1:
        cout << "What do you want to add?" << endl;
        cin >> choice;

        stack.push(choice);
        break;

      case 2:
        stack.pop();
        break;

      case 3:
        stack.displayContents();
        break;
    }
  }

  return 0;
}

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

class AddFront {
 public:
  Node *head;
  AddFront() { head = NULL; }

  void enqueue(int val) {
    if (head == NULL) {
      head = new Node;
      head->value = val;
    } else {
      Node *temp = new Node;
      temp->value = val;
      temp->next = head;
      head = temp;
    }
  }

  void dequeue() {
    if (head == NULL) {
      cout << "Empty";  // nothing to delete in queue
    }

    else if (head->next == NULL) {
      Node *temp = head->next;
      head->next = NULL;
      cout << "deleting " << temp->value << endl;
      delete temp;
    }

    else {
      Node *follow, *chase;  // *pointer
      follow = chase = head;
      while (chase->next != NULL) {
        follow = chase;
        chase = chase->next;
      }
      follow->next = NULL;
      cout << "deleting " << chase->value << endl;
      delete chase;
    }
  }
  void printContents() {
    if (head == NULL) {
      cout << "There is no queue to display" << endl;
    } else {
      Node *temp = head;
      while (temp != NULL) {
        cout << temp->value << ", ";
        temp = temp->next;
      }
    }
  }
};

class AddBack {
 public:
  Node *head;

  AddBack() { head = NULL; }

  void enqueue(int val) {
    if (head == NULL) {
      head = new Node;
      head->value = val;
    } else {
      Node *chase, *follow;
      chase = follow = head;
      while (chase != NULL) {
        follow = chase;
        chase = chase->next;
      }
      chase = new Node;
      chase->value = val;
      follow->next = chase;
    }
  }

  void dequeue() {
    if (head == NULL) {
      cout << "Nothing to delete from Queue" << endl;
    } else {
      Node *temp = head->next;
      cout << "deleting: " << head->value << endl;
      delete head;
      head = temp;
    }
  }

  void printContents() {
    if (head == NULL) {
      cout << "There is no queue to display" << endl;
    } else {
      Node *temp = head;
      while (temp != NULL) {
        cout << temp->value << ",  ";
        temp = temp->next;
      }
    }
  }
};

int main() {
  AddFront queueFront;  // add to front remove from back
  AddBack queueBack;    // add to front remove from back
  int choice = 0;

  cout << "1 - add to front/remove from back "
       << "2 - add to back/remove from front " << endl;
  cin >> choice;

  if (choice == 1) {
    while (1) {
      cout << "1 - add, 2 - delete, 3 - display" << endl;
      cin >> choice;
      switch (choice) {
        case 1:
          cout << "What do you want to add?" << endl;
          cin >> choice;

          queueFront.enqueue(choice);
          break;

        case 2:
          queueFront.dequeue();
          break;

        case 3:
          queueFront.printContents();
          break;
      }
    }
  }

  else if (choice == 2) {
    while (1) {
      cout << "1 - add to front/remove from back "
           << "2 - add to back/remove from front " << endl;
      cin >> choice;
      switch (choice) {
        case 1:
          cout << "What do you want to add?";
          cin >> choice;

          queueBack.enqueue(choice);
          break;

        case 2:
          queueBack.dequeue();
          break;

        case 3:
          queueBack.printContents();
          break;
      }
    }
  }
  return 0;
}

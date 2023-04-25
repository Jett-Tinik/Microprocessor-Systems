//
//  Linked List.cpp
//  HW 2
//
//  Created by Jayden Pereira on 3/13/19.
//  Copyright © 2019 Jayden Pereira. All rights reserved.
//

#include <iostream>
using namespace std;

// Node class
class Node {
 public:
  int value;
  Node *next;

  Node() {
    value = 0;
    next = NULL;
  }
};

// Linked List
class LinkedList {
 public:
  Node *head;
  int length;

  LinkedList() {
    head = NULL;
    length = 0;
  }

  // add
  void insertAtHead(int val) {
    if (head == NULL && length == 0) {
      head = new Node;
      head->value = val;
    } else {
      Node *temp = new Node;
      temp->value = val;
      temp->next = head;
      head = temp;
    }

    length++;
  }

  void insertAtPos(int pos, int val) {
    if (pos > 0 && pos <= length + 1) {
      Node *temp;
      temp = new Node;
      temp->value = val;

      // pos is at front
      if (pos == 1) {
        temp->next = head;
        head = temp;
      }
      // pos is at end
      else if (pos == length + 1) {
        // edge case @ length == 1
        if (length == 1) {
          head->next = temp;
        } else {
          Node *helper = head;
          while (helper->next != NULL) {
            helper = helper->next;
          }
          helper->next = temp;
        }
      }
      // pos is somewhere in LL
      else {
        Node *helper = head;
        for (int i = 1; i < pos - 1; i++) {
          helper = helper->next;
        }
        temp->next = helper->next;
        helper->next = temp;
      }

      length++;
    } else {
      cout << "invalid position, cannot add " << val << " there\n";
    }
  }

  // delete
  void removeFromPos(int pos) {
    if (pos > 0 && pos <= length) {
      // pos is at front
      if (pos == 1) {
        Node *temp = head;
        cout << "deleting: " << head->value << endl;
        delete head;
        head = temp;
      }
      // pos is at end
      else if (pos == length) {
        // edge case @ length == 1
        if (length == 1) {
          Node *temp = head;
          cout << "deleting: " << head->value << endl;
          delete head;
          head = temp;
        } else {
          Node *chase, *follow;
          chase = follow = head;
          while (chase->next != NULL) {
            follow = chase;
            chase = chase->next;
          }
          follow = NULL;
          cout << "deleting: " << chase->value << endl;
          delete chase;
        }
      }
      // pos is somewhere in LL
      else {
        Node *chase, *follow;
        chase = follow = head;
        for (int i = 1; i < pos; i++) {
          follow = chase;
          chase = chase->next;
        }
        follow->next = chase->next;
        cout << "deleting: " << chase->value << endl;
        delete chase;
      }

      length--;
    } else {
      cout << "invalid position, cannot delete at " << pos << endl;
    }
  }

  // display
  void display() {
    if (head == NULL) {
      cout << "nothing to display\n";
    } else {
      Node *temp = head;
      while (temp != NULL) {
        cout << temp->value << " | ";
        temp = temp->next;
      }
    }
  }
};

int main() {
  LinkedList list;
  int choice = 0;

  while (1) {
    cout << "\nPress 1 to add, 2 to delete, and 3 to display\n";
    cin >> choice;
    switch (choice) {
      case 1:
        cout << "press 1 to add to the front or 2 for a specific position";
        cin >> choice;
        if (choice == 1) {
          cout << "what would you like to add?\n";
          cin >> choice;

          list.insertAtHead(choice);
        } else {
          int pos;
          cout << "what would you like to add?\n";
          cin >> choice;
          cout << "what position would you like to add too?\n";
          cin >> pos;

          list.insertAtPos(pos, choice);
        }

        break;

      case 2:
        cout << "what position would you like to delete?\n";
        cin >> choice;
        list.removeFromPos(choice);
        break;

      case 3:
        list.display();
        break;
    }
  }

  return 0;
}

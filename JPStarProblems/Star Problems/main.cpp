//
//  main.cpp
//  Star Problems
//
//  Created by Jayden Pereira on 4/8/19.
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

  /***********************************************

                  STAR PROBLEMS

   **********************************************/

  // Detect and remove loops
  void removeLoop() {
    Node *follow, *chase;
    follow = chase = head;
    // check for loop
    while (true) {
      if (chase == NULL || chase->next == NULL) {
        return;
      } else if (chase == follow || chase->next == follow) {
        break;
      }
      chase = chase->next->next;
      follow = follow->next;
    }
    // identify loop
    chase = head;
    while (chase->next != follow->next) {
      chase = chase->next;
      follow = follow->next;
    }
    Node *start = chase->next;
    // remove loop
    chase = start;
    while (chase->next != start) {
      chase = chase->next;
    }
    chase->next = NULL;
  }

  // reverse the linked list
  void reverseList() {
    Node *behind, *current, *forward;
    behind = NULL;
    current = head;
    while (current != NULL) {
      forward = current->next;
      current->next = behind;
      behind = current;
      current = forward;
    }
    head = behind;
  }

  // delete every other node
  void deleteEveryOther() {
    Node *helper, *remover;
    helper = remover = head;
    // go through list and remove next element
    while (helper != NULL && helper->next != NULL) {
      remover = helper->next;
      helper->next = remover->next;
      delete remover;
      if (helper != NULL) {
        helper = helper->next;
      }
    }
  }
};

int main() {
  // removeLoop test
  LinkedList loopTest;
  loopTest.insertAtHead(4);
  loopTest.insertAtHead(3);
  loopTest.insertAtHead(2);
  loopTest.insertAtHead(1);
  Node *looper = loopTest.head;
  looper->next->next->next->next = looper->next;
  // loopTest.display();

  cout << endl;
  loopTest.removeLoop();
  loopTest.display();

  cout << "\n\n";
  // reverseList test
  LinkedList reverseTest;
  reverseTest.insertAtHead(4);
  reverseTest.insertAtHead(3);
  reverseTest.insertAtHead(2);
  reverseTest.insertAtHead(1);
  reverseTest.display();

  cout << endl;
  reverseTest.reverseList();
  reverseTest.display();

  cout << "\n\n";
  // deleteEveryOther test
  LinkedList everyOtherTest;
  everyOtherTest.insertAtHead(4);
  everyOtherTest.insertAtHead(4);
  everyOtherTest.insertAtHead(3);
  everyOtherTest.insertAtHead(3);
  everyOtherTest.insertAtHead(2);
  everyOtherTest.insertAtHead(2);
  everyOtherTest.insertAtHead(1);
  everyOtherTest.insertAtHead(1);
  everyOtherTest.display();

  cout << endl;
  everyOtherTest.deleteEveryOther();
  everyOtherTest.display();

  return 0;
}

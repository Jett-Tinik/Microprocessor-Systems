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

class LinkedList {
 public:
  Node *head;
  int length;
  LinkedList() {
    head = NULL;
    length = 0;
  }

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

  void insertAtPos(int loc, int val) {
    if (loc > 0 && loc <= length + 1) {
      Node *temp;
      temp = new Node;
      temp->value = val;

      if (loc == 1) {
        temp->next = head;
        head = temp;
      }

      else if (loc == length + 1) {  // if length is 1
        if (length == 1) {
          head->next = temp;
        }

        else {
          Node *helper = head;
          while (helper->next != NULL) {
            helper = helper->next;
          }
          helper->next = temp;
        }
      }

      else {
        Node *helper = head;
        for (int i = 1; i < loc - 1; i++) {
          helper = helper->next;
        }
        temp->next = helper->next;
        helper->next =
            temp;  // continue until you find location needed to add new value
      }
      length++;  // increase length by 1
    } else {
      cout << "Error, invalid spot " << endl;
      ;
    }
  }

  void removeFromPos(int loc) {
    if (loc > 0 && loc <= length) {
      if (loc == 1) {
        Node *temp = head;
        cout << "deleting " << head->value << endl;
        delete head;
        head = temp;
      }

      else if (loc == length) {
        if (length == 1) {
          Node *temp = head;
          cout << "deleting " << head->value << endl;
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
          cout << "deleting " << chase->value << endl;
          delete chase;
        }
      } else {
        Node *chase, *follow;
        chase = follow = head;
        for (int i = 1; i < loc; i++) {
          follow = chase;
          chase = chase->next;
        }
        follow->next = chase->next;
        cout << "deleting: " << chase->value << endl;
        delete chase;
      }
      length--;
    } else {
      cout << "Error, invlid spot " << endl;
    }
  }

  void displayContents() {
    if (head == NULL) {
      cout << "There is no list to display" << endl;  // if there is nothing in
                                                      // list, then display this
    } else {
      Node *temp = head;
      while (temp != NULL) {
        cout << temp->value << ", ";
        temp = temp->next;
      }
    }
  }
};

int main() {
  LinkedList list;
  int choice = 0;
  while (1) {
    cout << "1 - add, 2 - remove, 3 - display" << endl;
    cin >> choice;
    switch (choice) {
      case 1:
        cout << "1 - front, 2 - other location";
        cin >> choice;
        if (choice == 1) {
          cout << "What do you want to add?";
          cin >> choice;
          list.insertAtHead(choice);
        }

        else {
          int loc;
          cout << "What do you want to add?" << endl;
          cin >> choice;
          cout << "Which position do you want to add too?" << endl;
          cin >> loc;
          list.insertAtPos(loc, choice);
        }
        break;

      case 2:
        cout << "Which position would you like to delete?" << endl;
        cin >> choice;
        list.removeFromPos(choice);
        break;

      case 3:
        list.displayContents();
        break;
    }
  }

  return 0;
}

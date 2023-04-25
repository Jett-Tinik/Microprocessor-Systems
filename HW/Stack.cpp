//
//  Stack.cpp
//  HW 2
//
//  Created by Jayden Pereira on 3/13/19.
//  Copyright © 2019 Jayden Pereira. All rights reserved.
//

#include <iostream>
using namespace std;

//Node class
class Node {
public:
    int value;
    Node *next;
    
    Node() {
        value = 0;
        next = NULL;
    }
};

//Stack
class Stack {
public:
    Node *top;
    
    Stack() {
        top = NULL;
    }
    
    //add
    void push(int val) {
        if(top == NULL) {
            top = new Node;
            top -> value = val;
        }
        else {
            Node *temp;
            temp = new Node;
            temp -> value = val;
            temp -> next = top;
            top = temp;
        }
    }
    
    //delete
    void pop() {
        if(top == NULL) {
            cout << "Nothing to delete\n";
        }
        else {
            Node *temp = top -> next;
            cout << "deleting: " << top -> value << endl;
            delete top;
            top = temp;
        }
    }
    
    //display
    void display() {
        if(top == NULL) {
            cout << "Nothing to display\n";
        }
        else {
            Node *temp = top;
            while (temp != NULL) {
                cout << temp -> value << " | ";
                temp = temp -> next;
            }
        }
    }
};

int main() {
    
    Stack stack;
    int choice = 0;
    
    while(1) {
        cout << "\nPress 1 to add, 2 to delete, and 3 to display\n";
        cin >> choice;
        switch (choice) {
            case 1:
                cout << "what would you like to add?\n";
                cin >> choice;
                
                stack.push(choice);
                break;
                
            case 2:
                stack.pop();
                break;
                
            case 3:
                stack.display();
                break;
        }
    }
    
    return 0;
}

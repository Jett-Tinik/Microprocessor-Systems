//
//  Queue.cpp
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

//Queue (adding to front | deleting from end)
class QueueAddToFront {
public:
    Node *head;
    
    QueueAddToFront() {
        head = NULL;
    }
    
    //add
    void enqueue(int val) {
        if(head == NULL) {
            head = new Node;
            head -> value = val;
        }
        else {
            Node *temp = new Node;
            temp -> value = val;
            temp -> next = head;
            head = temp;
        }
    }
    
    //delete
    void dequeue() {
        if(head == NULL) {
            cout << "nothing to delete\n";
        }
        else if(head -> next == NULL) {
            Node *temp = head -> next;
            head -> next = NULL;
            cout << "deleting: " << temp -> value << endl;
            delete temp;
        }
        else {
            Node *follow, *chase;
            follow = chase = head;
            while(chase -> next != NULL) {
                follow = chase;
                chase = chase -> next;
            }
            follow -> next = NULL;
            cout << "deleting: " << chase -> value << endl;
            delete chase;
        }
    }
    
    //display
    void display() {
        if(head == NULL) {
            cout << "nothing to display\n";
        }
        else {
            Node *temp = head;
            while (temp != NULL) {
                cout << temp -> value << " | ";
                temp = temp -> next;
            }
        }
    }
};

//Queue (adding to end | deleting from front)
class QueueAddToBack {
public:
    Node *head;
    
    QueueAddToBack() {
        head = NULL;
    }
    
    //add
    void enqueue(int val) {
        if(head == NULL) {
            head = new Node;
            head -> value = val;
        }
        else {
            Node *chase, *follow;
            chase = follow = head;
            while(chase != NULL) {
                follow = chase;
                chase = chase -> next;
            }
            chase = new Node;
            chase -> value = val;
            follow -> next = chase;
        }
    }
    
    //delete
    void dequeue() {
        if(head == NULL) {
            cout << "nothing to delete\n";
        }
        else {
            Node *temp = head -> next;
            cout << "deleting: " << head -> value << endl;
            delete head;
            head = temp;
        }
    }
    
    //display
    void display() {
        if(head == NULL) {
            cout << "nothing to display\n";
        }
        else {
            Node *temp = head;
            while (temp != NULL) {
                cout << temp -> value << " | ";
                temp = temp -> next;
            }
        }
    }
};

int main() {
    
    QueueAddToFront queueFront;
    QueueAddToBack queueBack;
    int choice = 0;
    
    cout << "Press 1 for a queue that adds to the front and deletes from the end, 2 for a queue that adds to the end and deletes from the front\n";
    cin >> choice;
        
    if(choice == 1) {
        while(1) {
            cout << "\nPress 1 to add, 2 to delete, and 3 to display\n";
            cin >> choice;
            switch (choice) {
                case 1:
                    cout << "what would you like to add?\n";
                    cin >> choice;
                    
                    queueFront.enqueue(choice);
                    break;
                    
                case 2:
                    queueFront.dequeue();
                    break;
                    
                case 3:
                    queueFront.display();
                    break;
            }
        }
    }
                
                
    else if(choice == 2) {
        while(1) {
            cout << "\nPress 1 to add, 2 to delete, and 3 to display\n";
            cin >> choice;
            switch (choice) {
                case 1:
                    cout << "what would you like to add?\n";
                    cin >> choice;
                    
                    queueBack.enqueue(choice);
                    break;
                    
                case 2:
                    queueBack.dequeue();
                    break;
                    
                case 3:
                    queueBack.display();
                    break;
            }
        }
    }
    
    
    return 0;
}

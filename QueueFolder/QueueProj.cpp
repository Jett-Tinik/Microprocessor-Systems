#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

using namespace std;

// Node class
class Node {
 public:
  int in_time;
  int order_time;
  Node *next;
  Node *parent;

  Node(int it, int ot) {
    in_time = it;
    order_time = ot;
    next = NULL;
    parent = NULL;
  }
};

// Queue (adding to front | deleting from end)
class Queue {
 public:
  Node *head;
  Node *tail;
  int size;

  Queue() {
    head = NULL;
    tail = NULL;
    size = 0;
  }

  // add
  void enqueue(int it, int ot) {
    if (head == NULL) {
      head = tail = new Node(it, ot);
    } else {
      Node *temp = new Node(it, ot);
      tail->next = temp;
      temp->parent = tail;
      tail = temp;
    }
    size += 1;
  }

  // delete
  void dequeue() {
    if (head == NULL) {
      cout << "nothing to delete\n";
    }

    else {
      Node *temp;
      temp = head;
      head = head->next;
      if (size == 1) {
        tail = NULL;
      }

      else {
        head->parent = NULL;
      }
      delete temp;
      size -= 1;
    }
  }

  Node peak() { return *head; }
  int getSize() { return size; }
  bool isEmpty() { return size == 0; }
};

int main() {
  srand(time(NULL));
  int hoursBetween = 17;
  int minBetween = hoursBetween * 60;
  // question 1
  int totalWaitTime = 0;
  // question 2
  int totalServiceTime = 0;
  // question 3
  int totalQueueLength = 0;
  int totalCustomers = 0;

  int bestWaitTime = minBetween;
  int worstWaitTime = 0;
  int bestServiceTime = minBetween;
  int worstServiceTime = 0;
  int bestQueueLength = minBetween;
  int worstQueueLength = 0;
  int ibWT = 0;
  int iwWT = 0;
  int ibST = 0;
  int iwST = 0;
  int ibQL = 0;
  int iwQL = 0;

  double percentages[7] = {.3, .1, .4, .1, .25, .2, .1};
  int timesForPercentage[7][2] = {
      {0, 120},   {120, 210}, {210, 330},  {330, 570},
      {570, 720}, {720, 900}, {900, 1020},
  };

  int index = 0;
  int cashierTime;
  bool cashierBusy = false;
  Queue *queue = new Queue();
  int i = 0;

  for (i = 0; i < minBetween; i++) {
    if (timesForPercentage[index][1] < i) {
      index += 1;
    }
    if (rand() % 100 < percentages[index] * 100) {
      int transtime = rand() % 6 + 1;
      queue->enqueue(i, transtime);
      totalCustomers += 1;
    }

    if (cashierBusy) {
      if (cashierTime == i) {
        cashierBusy = false;
        if (queue->getSize()) {
          cashierBusy = true;
          Node customer = queue->peak();
          cashierTime = customer.order_time + i;
          totalWaitTime += i - customer.in_time;
          totalServiceTime += (i + customer.order_time) - customer.in_time;
          queue->dequeue();
          if (i - customer.in_time > worstWaitTime) {
            worstWaitTime = i - customer.in_time;
            iwWT = customer.in_time;
          }
          if (i - customer.in_time < bestWaitTime) {
            bestWaitTime = i - customer.in_time;
            ibWT = customer.in_time;
          }

          if ((i + customer.order_time) - customer.in_time > worstServiceTime) {
            worstServiceTime = (i + customer.order_time) - customer.in_time;
            iwST = customer.in_time;
          }
          if ((i + customer.order_time) - customer.in_time < bestServiceTime) {
            bestServiceTime = (i + customer.order_time) - customer.in_time;
            ibST = customer.in_time;
          }
        }
      }
    }

    else if (queue->getSize()) {
      cashierBusy = true;
      Node customer = queue->peak();
      cashierTime = customer.order_time + i;
      totalWaitTime += i - customer.in_time;
      totalServiceTime += (i + customer.order_time) - customer.in_time;
      queue->dequeue();

      if (i - customer.in_time > worstWaitTime) {
        worstWaitTime = i - customer.in_time;
        iwWT = customer.in_time;
      }
      if (i - customer.in_time < bestWaitTime) {
        bestWaitTime = i - customer.in_time;
        ibWT = customer.in_time;
      }

      if ((i + customer.order_time) - customer.in_time > worstServiceTime) {
        worstServiceTime = (i + customer.order_time) - customer.in_time;
        iwST = customer.in_time;
      }
      if ((i + customer.order_time) - customer.in_time < bestServiceTime) {
        bestServiceTime = (i + customer.order_time) - customer.in_time;
        ibST = customer.in_time;
      }
    }
    if (queue->getSize() > worstQueueLength) {
      worstQueueLength = queue->getSize();
      iwQL = i;
    }
    if (queue->getSize() < bestQueueLength) {
      bestQueueLength = queue->getSize();
      ibQL = i;
    }
    totalQueueLength += queue->getSize();
    cout << "After minute " << i << ", the queue has size " << queue->getSize()
         << '\n';
  }
  while (queue->getSize()) {
    if (cashierBusy) {
      if (cashierTime == i) {
        cashierBusy = false;
        if (queue->getSize()) {
          cashierBusy = true;
          Node customer = queue->peak();
          cashierTime = customer.order_time + i;
          totalWaitTime += i - customer.in_time;
          totalServiceTime += (i + customer.order_time) - customer.in_time;
          queue->dequeue();
          if (i - customer.in_time > worstWaitTime) {
            worstWaitTime = i - customer.in_time;
            iwWT = customer.in_time;
          }
          if (i - customer.in_time < bestWaitTime) {
            bestWaitTime = i - customer.in_time;
            ibWT = customer.in_time;
          }

          if ((i + customer.order_time) - customer.in_time > worstServiceTime) {
            worstServiceTime = (i + customer.order_time) - customer.in_time;
            iwST = customer.in_time;
          }
          if ((i + customer.order_time) - customer.in_time < bestServiceTime) {
            bestServiceTime = (i + customer.order_time) - customer.in_time;
            ibST = customer.in_time;
          }
        }
      }
    }

    else if (queue->getSize()) {
      cashierBusy = true;
      Node customer = queue->peak();
      cashierTime = customer.order_time + i;
      totalWaitTime += i - customer.in_time;
      totalServiceTime += (i + customer.order_time) - customer.in_time;
      queue->dequeue();

      if (i - customer.in_time > worstWaitTime) {
        worstWaitTime = i - customer.in_time;
        iwWT = customer.in_time;
      }
      if (i - customer.in_time < bestWaitTime) {
        bestWaitTime = i - customer.in_time;
        ibWT = customer.in_time;
      }

      if ((i + customer.order_time) - customer.in_time > worstServiceTime) {
        worstServiceTime = (i + customer.order_time) - customer.in_time;
        iwST = customer.in_time;
      }
      if ((i + customer.order_time) - customer.in_time < bestServiceTime) {
        bestServiceTime = (i + customer.order_time) - customer.in_time;
        ibST = customer.in_time;
      }
    }
    if (queue->getSize() > worstQueueLength) {
      worstQueueLength = queue->getSize();
      iwQL = i;
    }
    if (queue->getSize() < bestQueueLength) {
      bestQueueLength = queue->getSize();
      ibQL = i;
    }
    totalQueueLength += queue->getSize();
    i += 1;
  }
  cout << totalCustomers << endl;
  cout << "The average customer wait time is " << totalWaitTime / totalCustomers
       << "min" << endl;
  cout << "The average service time is " << totalServiceTime / totalCustomers
       << "min" << endl;
  cout << "The average queue length was " << totalQueueLength / i << "customers"
       << endl;
  cout << "The worst wait time for a customer was " << worstWaitTime
       << " minutes at " << iwWT << " minutes since opening" << endl;
  cout << "The best wait time for a customer was " << bestWaitTime
       << " minutes at " << ibWT << " minutes since opening" << endl;
  cout << "The worst service time for a customer was " << worstServiceTime
       << " minutes at " << iwST << " minutes since opening" << endl;
  cout << "The best service time for a customer was " << bestServiceTime
       << " minutes at " << ibST << " minutes since opening" << endl;
  cout << "The worst queue length for a customer was " << worstQueueLength
       << " customers at " << iwQL << " minutes since opening" << endl;
  cout << "The best queue length for a customer was " << bestQueueLength
       << " customers at " << ibQL << " minutes since opening" << endl;
  while (1) {
  }
}

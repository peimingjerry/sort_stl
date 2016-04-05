
#include <iostream>

#ifdef USE_STL_PRIORITY_QUEUE
#include <queue>
#else
#include "priority_queue.h"
#endif

#include "data.h"

#define MAX_SIZE 10

int main() {
    typedef Element<double, int> element;

    double array[MAX_SIZE] = {0.3, 0.1, 0.8, 0.5, 0.1, 0.4, 0.9, 0.7, 0.2, 0.6};
    element list[MAX_SIZE];

    cout<<"Push into priority queue:"<<endl;
    priority_queue<element> queue;
    for (int i=0;i<MAX_SIZE;i++) {
        list[i].key = array[i];
        list[i].value = i;
        list[i].display();
        cout<<"  ";
        queue.push(list[i]);
    }
    cout<<endl<<endl;

#ifdef _DEBUG
#ifndef USE_STL_PRIORITY_QUEUE
    queue.display();
#endif
#endif

    cout<<"Pop from priority queue:"<<endl;
    while (!queue.empty()) {
        element el = queue.top();
        el.display();
        queue.pop();
        cout<<"  ";
    }
    cout<<endl<<endl;

    return 0;
}

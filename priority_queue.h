
#include <vector>
using std::vector;
using std::iterator_traits;
#include <iostream>
using std::cout;
using std::endl;
#include "heap.h"

template < typename _Tp, typename _Sequence=vector<_Tp> >
class priority_queue {
public:
    typedef _Tp value_type;
    typedef _Tp & reference;

    priority_queue(): c() {}

    void push(const _Tp el) {
        c.push_back(el);
        my_push_heap(c.begin(), c.end());
    }

    void pop() {
        my_pop_heap(c.begin(), c.end());
        c.pop_back();
    }

    reference top() {
        return c.front();
    }

    bool empty() {
        return c.empty();
    }

#ifdef _DEBUG
    void display() {
        typedef typename _Sequence::iterator iterator;
        cout<<"Display elements inside priority_queue:"<<endl;
        for (iterator i=c.begin();i!=c.end();i++) {
            i->display();
            cout<<"  ";
        }
        cout<<endl<<endl;
    }
#endif
private:
    _Sequence c;
};


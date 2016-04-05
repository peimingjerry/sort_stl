
#include "sort.h"
#include "heap.h"

template <typename Random_Iterator>
void heap_select(Random_Iterator first, Random_Iterator nth, Random_Iterator last) {
    typedef typename iterator_traits<Random_Iterator>::difference_type difference_type;
    difference_type len = nth-first;

#define DEBUG_PRINT_heap_select {\
        for(Random_Iterator _k=first;_k!=nth;++_k) {\
            _k->display();\
            cout<<"  ";\
        }\
        cout<<"|  ";\
        for(Random_Iterator _k=nth;_k!=last;++_k) {\
            _k->display();\
            cout<<"  ";\
        }\
        cout<<endl<<endl;\
}

    make_max_heap(first, nth);
#ifdef _DEBUG
    DEBUG_PRINT_heap_select
    cout<<"-----------------------------------"<<endl;
#endif

    for (Random_Iterator i=nth;i!=last;++i) {
        if (*i<*first) {
            std::iter_swap(i, first);
            adjust_heap(first, difference_type(0), len);
        }
#ifdef _DEBUG
        DEBUG_PRINT_heap_select
#endif
    }
}

template <typename Random_Iterator>
void select_nth_element(Random_Iterator first, Random_Iterator nth, Random_Iterator last) {
    int depth_limit = std::__lg(last-first) * 2;

#ifdef _DEBUG
    Random_Iterator save_first = first, save_last = last;
#endif
    while (last-first>3) {
 
        if (depth_limit == 0) {
#ifdef _DEBUG
            cout<<"Heap select:"<<endl;
#endif
            heap_select(first, nth+1, last);
            std::iter_swap(first, nth);

            return;
        }
        depth_limit--;

        Random_Iterator _cut = _partition(first, last, 
                std::__median(*first, *(last-1), *(first+(last-first)/2)));
#ifdef _DEBUG
        cout<<"Partitioning:"<<endl;
        for(Random_Iterator _k=save_first;_k!=first;++_k) {
            _k->display();
            cout<<"  ";
        }
        cout<<"{  ";
        for(Random_Iterator _k=first;_k!=last;++_k) {
            if (_k == _cut) {
                cout<<" [";
                _k->display();
                cout<<"] ";
            } else
                _k->display();
            cout<<"  ";
        }
        cout<<"}  ";
        for(Random_Iterator _k=last;_k!=save_last;++_k) {
            _k->display();
            cout<<"  ";
        }
        cout<<endl<<endl;
#endif
        if (_cut <= nth) {
            first = _cut;
        } else {
            last = _cut;
        }
    }

#ifdef _DEBUG
    cout<<"Insertion sort:"<<endl;
#endif
    insert_sort(first, last);
}

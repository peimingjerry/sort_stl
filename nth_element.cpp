
#include <sys/time.h>
#include "nth_element.h"

//#define SCALE       100000000
//#define KEY_RANGE   30000000
//#define SCALE       50
//#define KEY_RANGE   50
#define SCALE       20
#define KEY_RANGE   10

#define DISPLAY {\
    for (iterator _k=list.begin();_k!=list.end();++_k) {\
        _k->display();\
        cout<<"  ";\
    }\
    cout<<endl<<endl;\
}

int main() {
    typedef vector< Element<int, int> > myVector;
    typedef myVector::iterator iterator;
    typedef iterator_traits<iterator>::difference_type iterator_difference;
    myVector list;
    timeval start, stop;

    for (int i=0;i<SCALE;i++) {
        Element<int, int> el(std::rand()%KEY_RANGE, 0);
        list.push_back(el);
    }
#ifdef STABLE_CHECK
    for (int i=0;i<KEY_RANGE;i++) {
        int count = 0;
        for(int j=0;j<SCALE;j++) {
            if (list[j].key == i) {
                list[j].value = count++;
            }
        }
    }
#endif

#ifdef DETAILS
    cout<<"Print array:"<<endl;
    DISPLAY
#endif

    iterator_difference nth = 1;
    //iterator_difference nth = 1000;
    //iterator_difference nth = SCALE;

    gettimeofday(&start, 0);

    iterator nth_elem = list.begin() + nth - 1;
    //cout<<"Using STL nth_element:"<<endl;
    //std::nth_element(list.begin(), nth_elem, list.end());
    cout<<"Using self nth_element:"<<endl;
    select_nth_element(list.begin(), nth_elem, list.end());

    gettimeofday(&stop, 0);
    double timeuse  = 1000000*(stop.tv_sec - start.tv_sec) + stop.tv_usec - start.tv_usec;
    cout<<"Time Use: "<<timeuse/1000<<" ms"<<endl;

    cout<<"Selected the "<<nth<<"th element:"<<endl;
    nth_elem->display();
    cout<<endl<<endl;
#ifdef DETAILS
    cout<<"New array:"<<endl;
    DISPLAY
#endif

    return 0;
}


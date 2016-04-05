
#include <sys/time.h>
#include "sort.h"

//#define COUNT       16777216
//#define KEY_RANGE   5000000
//#define COUNT       65536
//#define KEY_RANGE   30000
//#define COUNT       16
//#define KEY_RANGE   12
#define COUNT       19
#define KEY_RANGE   12

#ifdef DETAILS
#define DISPLAY {\
	for(Vector::iterator _iter=list.begin();_iter!=list.end();++_iter)\
		cout<<"("<<_iter->key<<", "<<_iter->value<<")  ";\
	cout<<endl<<endl;\
}
#endif
	
int main() {
	typedef vector< Element<int, int> > Vector;
	Vector list;
    timeval start, stop;

    // randomly generate the list to sort
    for (int k=0;k<COUNT;k++) {
        int key = std::rand() % KEY_RANGE;
        list.push_back(Element<int, int>(key, 0));
    }

#ifdef STABLE_CHECK
    // for duplicated keys, assign acsending values
    const int max_key = KEY_RANGE-1;
    const int min_key = 0;
    for (int i=min_key;i<=max_key;i++) {
        Vector::iterator first=list.begin();
        Vector::iterator last=list.end();
        int count=0;
        while (true) {
            Vector::iterator iter;
            iter = std::find(first, last, i);
            if (iter != last) {
                iter->value = count++;
                first = iter+1;
            } else
                break;
        }
    }
#endif

#ifdef DETAILS
	cout<<"Before sorting:"<<endl;
	DISPLAY
#endif
	
    gettimeofday(&start, 0);

    //cout<<"Using STL sort():"<<endl;
	//std::sort(list.begin(), list.end());
    //cout<<"Using STL stable_sort():"<<endl;
	//std::stable_sort(list.begin(), list.end());
    //cout<<"Using basic insertion sort:"<<endl;
	//insert_sort(list.begin(), list.end());
    //cout<<"Using basic selection sort:"<<endl;
    //select_sort(list.begin(), list.end());
    //cout<<"Using quick sort:"<<endl;
    //quick_sort(list.begin(), list.end());
    //cout<<"Using merge sort:"<<endl;
    //merge_sort(list.begin(), list.end());
    cout<<"Using heap sort:"<<endl;
    heap_sort(list.begin(), list.end());
    //cout<<"Using shell sort:"<<endl;
    //shell_sort(list.begin(), list.end());

    gettimeofday(&stop, 0);
    double timeuse  = 1000000*(stop.tv_sec - start.tv_sec) + stop.tv_usec - start.tv_usec;
    cout<<"Time Use: "<<timeuse/1000<<" ms"<<endl;

#ifdef DETAILS
	cout<<"After sorting:"<<endl;
	DISPLAY
#endif

	return 0;
}


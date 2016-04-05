
#include "heap.h"

//#define S_threshold 1
#define S_threshold 16

////////////////////////////////////////////////////////////////////////////////////////////
template <typename Random_Iterator>
void insert_sort(Random_Iterator first, Random_Iterator last) {
	typedef typename iterator_traits<Random_Iterator>::value_type value_type;

	for (Random_Iterator i=first+1;i!=last;++i) {
		value_type tmp = *i;
		if (tmp<*first) {
			for(Random_Iterator j=i;j>first;--j) {
				*j=*(j-1);
			}
			*first = tmp;
		} else {
			Random_Iterator j = i-1;
			for (;tmp<*j;--j) {
				*(j+1) = *j;
			}
			*(j+1) = tmp;
		}
#ifdef _DEBUG
		for(Random_Iterator _k=first;_k!=last;++_k) {
			_k->display();
			cout<<"  ";
            if (_k == i)
                cout<<"|  ";
		}
		cout<<endl<<endl;
#endif
	}
}

////////////////////////////////////////////////////////////////////////////////////////////
template <typename Random_Iterator>
void select_sort(Random_Iterator first, Random_Iterator last) {
    typedef typename iterator_traits<Random_Iterator>::value_type value_type;

    for (Random_Iterator i=first;i!=(last-1);++i) {
        Random_Iterator min = i;
        value_type tmp = *i;
        for (Random_Iterator j=i+1;j!=last;++j) {
            if (*j<tmp) {
                min = j;
                tmp = *j;
            }
        }
        if (min != i) {
            std::iter_swap(min, i);
        }
#ifdef _DEBUG
		for(Random_Iterator _k=first;_k!=last;++_k) {
			_k->display();
			cout<<"  ";
            if (_k == i)
                cout<<"|  ";
		}
		cout<<endl<<endl;
#endif
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
// Help function for quick_sort
template <typename Random_Iterator, typename _Tp>
Random_Iterator _partition(Random_Iterator first, Random_Iterator last, _Tp pivot) {
    while (true) {
        while (*first < pivot)
            ++first;
        --last;
        while (*last > pivot)
            --last;
        if (!(first<last))
            return first;
        std::iter_swap(first, last);
        ++first;
    }
}

// Help function for quick_sort
template <typename Random_Iterator, typename Size>
void _basic_quick_sort(Random_Iterator first, Random_Iterator last, Size depth_limit) {
    typedef typename iterator_traits<Random_Iterator>::value_type value_type;

    while ( ( last - first) > S_threshold ) {
        if (depth_limit != 0 ) {
            //--depth_limit;
            value_type mid_value = std::__median(*first, *(first+(last-first)/2), *(last-1));
            Random_Iterator _cut = _partition(first, last, mid_value);
#ifdef _DEBUG
            cout<<"{  ";
            for(Random_Iterator _k=first;_k!=last;++_k) {
                if (_k == _cut) {
                    cout<<"[";
                    _k->display();
                    cout<<"]";
                } else
                    _k->display();
                cout<<"  ";
            }
            cout<<"}"<<endl<<endl;
#endif
            _basic_quick_sort(_cut, last, depth_limit);
            last = _cut;
        }
    }
}

template <typename Random_Iterator>
void quick_sort(Random_Iterator first, Random_Iterator last) {
    cout<<"    Partition:"<<endl;
    _basic_quick_sort(first, last, std::__lg(last-first)*2);
#ifdef _DEBUG
    cout<<"    After partitioning:"<<endl;
	for(Random_Iterator _k=first;_k!=last;++_k) {
		_k->display();
		cout<<"  ";
	}
	cout<<endl<<endl;
#endif
    cout<<"    Final insertion sort:"<<endl;
    insert_sort(first, last);
}

////////////////////////////////////////////////////////////////////////////////////////////
//#define MERGE_SORT_REC
#ifdef MERGE_SORT_REC

// Help function for merge_sort
template <typename Random_Iterator1, typename Random_Iterator2>
void _merge(Random_Iterator1 first, Random_Iterator1 mid, Random_Iterator1 last, Random_Iterator2 buf) {
    Random_Iterator2 end_buf = buf + (last - first);
    Random_Iterator2 i = buf;
    Random_Iterator1 k;
    for (k=first;k<mid;k++)
        *i++ = *k;
    for (k=last-1;k>=mid;k--)
        *i++ = *k;

#ifdef _DEBUG
    assert(i == end_buf);
#endif

    k = first;
    i = buf;
    Random_Iterator2 j = end_buf - 1;
    while (i<=j) {
        if (*i <= *j) {
            *k++ = *i++;
        } else {
            *k++ = *j--;
        }
    }
}

// Help function for merge_sort
template <typename Random_Iterator1, typename Random_Iterator2>
void _merge_sort_loop(Random_Iterator1 first, Random_Iterator1 last, Random_Iterator2 buf) {
#define USE_INSERT_IN_MERGE_SORT
#ifdef USE_INSERT_IN_MERGE_SORT
    if ( last - first > S_threshold ) {
#else
    if ( last - first > 1 ) {
#endif
        Random_Iterator1 mid = first + (last - first)/2;
        _merge_sort_loop(first, mid, buf);
        _merge_sort_loop(mid, last, buf);
        _merge(first, mid, last, buf);
#ifdef _DEBUG
        cout<<"{  ";
        for(Random_Iterator1 _k=first;_k!=last;++_k) {
            _k->display();
            cout<<"  ";
        }
        cout<<"}"<<endl<<endl;
#endif
    } 
#ifdef USE_INSERT_IN_MERGE_SORT
    else {
        insert_sort(first, last);
    }
#endif
}

template <typename Random_Iterator>
void merge_sort(Random_Iterator first, Random_Iterator last) {
    typedef typename iterator_traits<Random_Iterator>::pointer pointer;
    typedef typename iterator_traits<Random_Iterator>::value_type value_type;
    typedef typename iterator_traits<Random_Iterator>::difference_type difference_type;

    difference_type len = last - first;
    pointer buf = new value_type[len];

    _merge_sort_loop(first, last, buf);
}

#else //MERGE_SORT_REC

// Help function for merge_sort
template <typename Random_Iterator1, typename Random_Iterator2>
Random_Iterator2 _merge(Random_Iterator1 first, Random_Iterator1 mid, Random_Iterator1 last, Random_Iterator2 result) {
    Random_Iterator1 i = first;
    Random_Iterator1 j = mid;
    Random_Iterator2 k = result;

    while (i<mid && j<last) {
        if (*i<=*j)
            *k++ = *i++;
        else
            *k++ = *j++;
    }
    while (i<mid)
        *k++ = *i++;
    while (j<last)
        *k++ = *j++;

    return k;
}

// Help function for merge_sort
template <typename Random_Iterator1, typename Random_Iterator2, typename Distance>
void _merge_sort_loop(Random_Iterator1 first, Random_Iterator1 last, Random_Iterator2 result, Distance step) {
    const Distance twoStep = 2 * step;

    while (last-first >= twoStep) {
#ifdef _DEBUG
        Random_Iterator2 result_save = result;
#endif
        result = _merge(first, first+step, first+twoStep, result);
        first += twoStep;

#ifdef _DEBUG
        cout<<"{  ";
        for (Random_Iterator2 _k=result_save;_k<result;_k++) {
            _k->display();
            cout<<"  ";
        }
        cout<<"}  ";
#endif
    }

#ifdef _DEBUG
    Random_Iterator2 result_save = result;
#endif
    step = std::min(last-first, step);
    result = _merge(first, first+step, last, result);

#ifdef _DEBUG
    if (result_save != result) {
        cout<<"{  ";
        for (Random_Iterator2 _k=result_save;_k<result;_k++) {
            _k->display();
            cout<<"  ";
        }
        cout<<"}  ";
    }
    cout<<endl<<endl;
#endif
}

template <typename Random_Iterator>
void merge_sort(Random_Iterator first, Random_Iterator last) {
    typedef typename iterator_traits<Random_Iterator>::pointer pointer;
    typedef typename iterator_traits<Random_Iterator>::value_type value_type;
    typedef typename iterator_traits<Random_Iterator>::difference_type difference_type;

    difference_type len = last - first;
    pointer buf = new value_type[len];
    pointer end_buf = buf + len;

#define USE_INSERT_IN_MERGE_SORT
#ifdef USE_INSERT_IN_MERGE_SORT

#ifdef _DEBUG
    difference_type step = 4;
#else
    difference_type step = S_threshold;
#endif
    cout<<"    Insert_sort if the scale is smaller than "<<step<<":"<<endl;
    Random_Iterator i = first;
    Random_Iterator j = first + step;
    while (j<last) {
#ifdef _DEBUG
        cout<<"------------------------------"<<endl;
#endif
        insert_sort(i, j);
        i = j;
        j = i + step;
    }
#ifdef _DEBUG
        cout<<"------------------------------"<<endl;
#endif
    difference_type remains = std::min(last-i, step);
    insert_sort(i, i+remains);

#else //USE_INSERT_IN_MERGE_SORT
    difference_type step = 1;
#endif //USE_INSERT_IN_MERGE_SORT

    cout<<"    None-recursive merge:"<<endl;
    while (step < len) {
        _merge_sort_loop(first, last, buf, step);
        step = step * 2;
        _merge_sort_loop(buf, end_buf, first, step);
        step = step * 2;
    }
}

#endif //MERGE_SORT_REC

////////////////////////////////////////////////////////////////////////////////////////////
template <typename Random_Iterator>
void heap_sort(Random_Iterator first, Random_Iterator last) {
    typedef typename iterator_traits<Random_Iterator>::difference_type difference_type;

    cout<<"    heap_sort:"<<endl;
    make_max_heap(first, last);

    Random_Iterator _last = last;
    while ((_last-first) > 1) {
#ifdef _DEBUG
        for(Random_Iterator _k=first;_k!=_last;++_k) {
            _k->display();
            cout<<"  ";
        }
        cout<<"|  ";
        for(Random_Iterator _k=_last;_k!=last;++_k) {
            _k->display();
            cout<<"  ";
        }
        cout<<endl<<endl;
#endif
        std::iter_swap(first, _last-1);
        adjust_heap(first, difference_type(0), difference_type(_last-1-first));
        --_last;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////
template <typename Random_Iterator>
void shell_sort(Random_Iterator first, Random_Iterator last) {
    typedef typename iterator_traits<Random_Iterator>::difference_type difference_type;
    typedef typename iterator_traits<Random_Iterator>::value_type value_type;
    difference_type step = last-first;
    value_type tmp;
    Random_Iterator i, j;

    while (step > 1) {
        step = step/3+1;
        for (i=first+step;i<last;i+=step) {
            tmp = *i;
            if (tmp<*first) {
                for (j=i-step;j>=first;j-=step) {
                    *(j+step) = *j;
                }
                *first = tmp;
            } else {
                for (j=i-step;tmp<*j;j-=step) {
                    *(j+step) = *j;
                }
                *(j+step) = tmp;
            }
        }
#ifdef _DEBUG
        cout<<"step = "<<step<<":"<<endl;
        for(Random_Iterator _k=first;_k<last;_k+=step) {
			_k->display();
			cout<<"  ";
        }
		cout<<endl<<endl;
#endif
    }
}


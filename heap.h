
#ifndef HEAP_H
#define HEAP_H

template <typename Random_Iterator, typename _Distance, typename _Tp>
void _push_heap(Random_Iterator first, _Distance hole_index, _Distance top_index, _Tp value) {
   typedef typename iterator_traits<Random_Iterator>::difference_type difference_type;
   difference_type parent = (hole_index-1)/2;

   while (hole_index>top_index && *(first+parent)<value) {
       *(first+hole_index)= *(first+parent);
       hole_index = parent;
       parent = (parent-1)/2;
   }
   *(first+hole_index) = value;
}

template <typename Random_Iterator, typename Distance>
void adjust_heap(Random_Iterator first, Distance hole_index, Distance len) {
    typedef typename iterator_traits<Random_Iterator>::value_type value_type;
    Distance parent = hole_index;
    Distance leftChild = 2*hole_index+1;
#define ADJUST_HEAP_IMPROVEMENT
#ifdef ADJUST_HEAP_IMPROVEMENT
    value_type tmp = *(first + hole_index);
#endif

    while (leftChild < len) {
        Distance rightChild = leftChild + 1;
        if ((rightChild < len) && (*(first + leftChild )<*(first + rightChild))) {
            leftChild = rightChild;
        }
#ifdef ADJUST_HEAP_IMPROVEMENT
        *(first + parent) = *(first + leftChild);
        parent = leftChild;
        leftChild = 2*parent + 1;
#else
        if (*(first + parent)<*(first + leftChild))
            std::iter_swap(first + parent, first + leftChild);
        else
            break;
        parent = leftChild;
        leftChild = 2*parent + 1;
#endif
    }
#ifdef ADJUST_HEAP_IMPROVEMENT
    // Here parent is leaf node
    _push_heap(first, parent, hole_index, tmp);
#endif
}

template <typename Random_Iterator>
void make_max_heap(Random_Iterator first, Random_Iterator last) {
    typedef typename iterator_traits<Random_Iterator>::difference_type difference_type;

    /* Use difference_type instead of Random_Iterator 
     * as loop variable, as well as return if len<2,
     * can improve efficiency significantly */
    difference_type len = last-first;
    if (len < 2)
        return;

    difference_type parent = (len-2)/2;
    while (parent >= 0) { 
        adjust_heap(first, parent, len);
        --parent;
    }
}

template <typename Random_Iterator>
void my_push_heap(Random_Iterator first, Random_Iterator last) {
   typedef typename iterator_traits<Random_Iterator>::difference_type difference_type;
   typedef typename iterator_traits<Random_Iterator>::value_type value_type;

   value_type tmp = *(last-1);
   _push_heap(first, difference_type(last-first-1), difference_type(0), tmp);
}

template <typename Random_Iterator>
void _pop_heap(Random_Iterator first, Random_Iterator last, Random_Iterator result) {
   typedef typename iterator_traits<Random_Iterator>::difference_type difference_type;
   std::iter_swap(first, result);
   adjust_heap(first, difference_type(0), difference_type(last-first));
}

template <typename Random_Iterator>
void my_pop_heap(Random_Iterator first, Random_Iterator last) {
   --last;
   _pop_heap(first, last, last);
}

#endif


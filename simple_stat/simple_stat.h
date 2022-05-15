// append function uses source code from
// https://www.geeksforgeeks.org/problem-in-comparing-floating-point-numbers-
// and-how-to-compare-them-correctly/ to determine equality of double type
//
// The objective of this project is to represent a series of numeric type (both
//    integer and double) data (is called "data object" from now on) that
//    offers access to few statistics (mentioned below)  according to below
//    properties:
//
// Typical data object has a lot of duplicate entries
// There is no limit to the number of unique data elements inside
//    data object supports simple statistics such as mean, standard deviation,
//    min and max
// Fastest possible access to above statistics is paramount; theta(1) access
//    so above statistics also represent a part of the state of the data object
// Both fast access and saving space is paramount; developer must strive to use
//    the smallest space possible for storage and must give theta(1) access to
//    abovestatistics when demanded
//
// In addition to above mentioned states, your data structure must support
//    below operations:
//    Update operations: not frequent compared to  frequent demands of
//       statistics. Therefore, okey if they are expensive operations like
//       O(n):
//       append: append new data.  Update exist number of duplication or append
//          from the end if new
//       removem: remove m number of a given data element only if m is less
//          than or equal to current amount of repetitions, n
//       empty: delete all data
//       feed: append from from any standard C++ container (any that supports
//          iteration) data type (std::array, std::vector, std::set, etc)).
//          Only one feed method is allowed: this means no overloaded feed
//          methods
//    search: must return the location of the first occurrence and repetition.
//       For example, if the first occurrence of the search data value, 20
//       is 3 and there are 10 of 20s, then you must return 3 and 10 as
//       the search result of 20
//    array index operator, []: access each unique element through an index:
//       overload the array index operator ([]) so that the ith data element
//       in an instance of your data object, db can be accessed like db[i]
//    length_unique: number of unique elements in your data object
//    length_total: total number of elements in your data object
//    unique_set: return all the unique elements as an std::set
//    getters (all must be ) and in floating point type:
//       get_ mean: returns the mean value of the current entire data set
//       get_SD: returns the standard deviation  of the current entire data
//          set
//       get_min: returns the minimum data item in the current entire data
//          set
//       get_max: returns the maximum data item in the current entire data
//          set
//
// Understand
// input: for append, integer or double
//        for feed, standard C++ container date type containing integer or
//           double values for elements
//        for removem: a data element and number of repetitions of that element
// output: returns from search, length_unique, length_total, unique_set and
//    getters
// restrictions:
//    The principle data structure must be the most qualified linear structure
//       we discussed so far in the class. So in the implementation you must
//       use the code provided in Canvas
//    Updates (append, feed, removem) to the data object is possible though
//        rare. However, the demands for above statistics is very frequent
//    Though you must try to save space, your most important task is to give
//       access to above statistics; we are sacrificing the space for speed. In
//       regard of this you are allowed to use other data structures and
//       algorithms provided in the standard C++. You are not allowed to use
//       any third party or external libraries (like boost)
//    Calculation of above statistics must be private internal operations. This
//       means you have to calculate and update them as you create, insert,
//       append, removem, and feed operations
//    Creation: only two constructors:
//       default: just empty data object
//       create by adding data items from any standard C++ container (any that
//          supports iteration) data type (std::array, std::vector, std::set)
//    Removem: remove 1 to any (m) number of data item from the data object.
//       You must validate the existence of m number of data item before the
//       removal
//    The data is heavily duplicated. In situations like this we discussed
//       storing pointers as a solution in the class
//    You are not allowed to use any C/C++ math libraries
//
// Match
// Class for data object including vector for data, statistics variables
// Generic iterator for feed method that calls append method
//
// Plan
//
// 1. Definition and implementation of simple_stats class
//    a. Private members:
//          1. data_obj: doubly linked list std:pair auto value, int count
//          2. data_mean: mean of data set
//          3. data_sd: standard deviation of data set
//          4. data_min: minimum value in data set
//          5. data_max: maximum value in data set
//          6. data_sum: sum of all values in set
//          7. data_count: count of all elements
//          8. calc_stats(new_element):
//                data_sum += new_element
//                data_count += 1
//                data_mean = data_sum/data_count
//                data_sd =
//                  sqrt((data_sd + (pow(new_element - data_mean, 2))/
//                  data_count)
//                data_min =
//                  if new_element < data_min then data_min = new_element
//                data_max =
//                  if new_element > data_max then data_max = new_element
//    b. Public members:
//          1.  default constructor: create empty data object
//          2.  constructor that calls feed with undefined iterable data object
//          3.  [] overload operator: if index is >=  data_count
//                 than return NULL, else iterate through data_obj.count until
//                 index supplied is within range and return the data_obj.value
//                 for that index value.
//          4.  append: iterate through data_obj.value, if found, increment
//                      data_obj.count, calc_stats.  else append data_obj and
//                      set data_obj.count = 1
//          5.  removem: check if value is >= data_min and <= data_max, then
//                       iterate through data_obj.value and if m =
//                       data_obj.count, delete data_obj object, else if
//                       < data_obj.count -= m, else return not error
//          6.  empty: clear data_obj, and all stats
//          7.  search: iterate through data_obj.value, increment index_count
//                      with data_obj.count and if found return index_count-1
//                      and data_obj.count
//          8.  length_unique: return data_obj.length
//          9.  length_total: return data_count
//          10. unique_set: iterate through data_obj.value and append to set.
//          11. feed: iterate through any data object and call append on each
//              element
//          12. get_mean: return data_mean.
//          13. get_sd: return data_sd.
//          14. get_min: return data_min.
//          15. get_max: return data_max.
#ifndef SIMPLE_STAT_H
#define SIMPLE_STAT_H
#include <set>
#include <dllist.h>
template <class L, class N>
class simple_stat {
private:
    DLList<std::pair<N, int>>* data_obj;
    double data_mean = 0.0;
    double data_sd = 0.0;
    N data_min = 0.0;
    N data_max = 0.0;
    N data_sum = 0.0;
    int data_count = 0;

    void calc_stats(N new_element) {
        data_sum += new_element;
        data_count++;
        data_mean = data_sum/data_count*1.0;
        data_sd = sqrt(data_sd + ((pow(new_element - data_mean, 2))
                  /data_count));
        if(this->data_obj.length() == 0 || new_element < data_min)
            data_min = new_element;
        if(this->data_obj.length() == 0 || new_element > data_max)
            data_max = new_element;
    }



public:
    simple_stat(){
        new DLList(data_obj);
    }

    simple_stat(L data_feed){
        feed(data_feed);
    }

    ~simple_stat(){
        empty();
    }

    void append(N num){
        if (search(num, this->data_obj) != std::pair(0,0)) {
                    this->data_obj.second++;
                    calc_stats(num);
                    return;
                }

        this->data_obj.append(std::pair(num,1));
        calc_stats(num);
    }

    void removem(N m, int reps){
        if (search(m, this->data_obj) != std::pair(0,0)) {
                if (reps < this->data_obj.second) {
                    this->data_obj.second -= reps;
                } else if (reps == this->data_obj.second) {
                    this->data_obj->remove();
                }
            }
    }

    void empty() {
        delete data_obj;
        data_obj = NULL;
        data_sum = NULL;
        data_count = NULL;
        data_mean = NULL;
        data_sd = NULL;
        data_min = NULL;
        data_max = NULL;
    }

    std::pair<int, int> search(N num){
        if (this->data_obj.length() > 0) {
            if ((num - data_min) >= 1e-9 || (num - data_max) <= 1e-9) {
                for (auto i:data_obj) {
                    // check if num is in data_obj, require checking for double
                    // precision on equality
                    if (abs(num - i.first) < 1e-9) {
                        return std::pair(this->data_obj->currPos(),
                                         this->data_obj.second);
                    }
                }
            }
        }
        return std::pair(0,0);
    }

    int length_unique() {
        return this->data_obj->length();
    }

    int length_total() {
        int sum_elements = 0;
        if (this->data_obj.length() > 0){
            for (auto i:data_obj) {
                sum_elements += i.second;
            }
        }
        return sum_elements;
    }

    std::set<N> unique_set() {
        std::set<N> uni_set;
        for (auto i:data_obj) {
            uni_set.insert(i.first);
        }
    }

    void feed(L data_feed){
        for (auto num=data_feed.begin(); num !=data_feed.end();++num){
            append(num);
        }
    }

    double get_mean(){
        return data_mean;
    }

    double get_sd(){
        return data_sd;
    }

    N get_min(){
        return data_min;
    }

    N get_max(){
        return data_max;
    }

};
#endif // SIMPLE_STAT_H

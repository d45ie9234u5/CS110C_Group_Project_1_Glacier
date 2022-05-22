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
//        for search: the value to search for
// output: returns pair of integers from search, length_unique, length_total,
//         unique_set and getters
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
//          1. data_obj: linked list std:pair auto value, int count
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
//          7.  search: check if key to
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
#include <math.h>
#include <llist.h>


template <class L, class N = typename L::value_type> class Simple_stat: public LList<N> {
private:
    LList<N>* data_obj;
    const double EQFL = 1e-9;
    double data_mean = 0.0;
    double data_sd = 0.0;
    N data_min = 0;
    N data_max = 0;
    double data_sum = 0.0;
    int data_count = 0;

    void calc_stats(N new_element) {
        data_count++;
        data_mean = data_sum/data_count*1.0;
        data_sd = sqrt((data_sd + (std::pow(new_element - data_mean, 2))
                  /data_count));
        if(this->data_obj->length() == 1 || new_element < data_min) {
            data_min = new_element;
            std::cout << "data_min" << data_min << std::endl;
        }
        if(this->data_obj->length() == 1 || new_element > data_max) {
            data_max = new_element;
            std::cout << "data_max" << data_max << std::endl;
        }
    }



public:
    Simple_stat(){
         data_obj = new LList<N>;
    }


    Simple_stat(const L& data_feed) {
        data_obj = new LList<N>;
        feed(data_feed);
    }

    ~Simple_stat(){
        empty();
    }

    auto operator[](int indexnum) {
        this->data_obj->moveToPos(indexnum);
        this->data_obj->getValue();
    }

    void append(N num) {
        std::pair found_index = search(num);
        std::cout << "Index: " << found_index.first << std::endl;
        if (found_index.first > 0) {
            this->data_obj->moveToPos(found_index.first);
            std::cout << "Inserting at position " << this->data_obj->currPos()
                      << std::endl;
            this->data_obj->insert(num);
            calc_stats(num);
            return;
        }
        std::cout << num << std::endl;
        if (num <= data_min || data_obj->length() == 0){
            this->data_obj->moveToStart();
            std::cout << "Moving to start." << std::endl;
            std::cout << "Inserting " << num << " at position "
                      << this->data_obj->currPos() << std::endl;
            this->data_obj->insert(num);
        } else if (num >= data_max) {
            this->data_obj->moveToPos(this->data_obj->length());
            std::cout << "Appending " << num << " at position "
                      << this->data_obj->currPos() << std::endl;
            this->data_obj->append(num);
        } else if (num > data_min && num < data_max){
            this->data_obj->moveToStart();
            std::cout << "Moving to start." << std::endl;
            while (num < this->data_obj->getValue() &&
                   this->data_obj->currPos() < this->data_obj->length()) {
                    this->data_obj->next();
                }
        }
            std::cout << "Inserting " << num << " at position "
                      << this->data_obj->currPos() << std::endl;
            this->data_obj->insert(num);

        calc_stats(num);
    }

    void removem(N m, int reps){
        std::pair found_index = search(m);
        if (found_index.first != 0 && reps <= found_index.second) {
                this->data_obj->moveToPos(found_index.first);
                for (int i = found_index.first; i < found_index.first+reps; i++)
                {
                    this->data_obj->remove();
                    this->data_obj->next;
                }
            }
    }

    void empty() {
        delete data_obj;
        data_obj = NULL;
        data_sum = 0;
        data_count = 0;
        data_mean = 0;
        data_sd = 0;
        data_min = 0;
        data_max = 0;
    }

    std::pair<int,int> search(N num){
        std::cout << "The number we are searching for is: " << num << std::endl;
        int numindex = 0;
        int numcount = 0;

        if (this->data_obj->length() > 0 && num > data_min && num < data_max) {
            this->data_obj->moveToStart();

            for (int i = 0; i < this->data_obj->length();i++) {
                std::cout << "Index: " << this->data_obj->currPos()
                          << " Value: " << this->data_obj->getValue()
                          << " length: " << this->data_obj->length()
                          << std::endl;

                if (num == this->data_obj->getValue()) {
                    std::cout << "Found it!" << std::endl;
                    if (numcount == 0) {
                        numcount++;
                        numindex = this->data_obj->currPos();
                        std::cout << "Duplicate found at: " << numindex
                                  << std::endl;
                    }
                    numcount++;
                }
                std::cout << "NEXT" << std::endl;
                this->data_obj->next();
                std::cout << "AFTER NEXT" << std::endl;

            }
//            if ((num - data_min) >= EQFL && (num - data_max) <= EQFL) {
//                std::cout << num << ": " << this->data_obj->getValue();
//                while (num - this->data_obj->getValue() > EQFL){
//                    this->data_obj->next();
//                }
//                if (num - this->data_obj->getValue() <= EQFL) {
//                    std::cout << num << ": " << this->data_obj->getValue();
//                    numindex = this->data_obj->currPos();
//                    while (num - this->data_obj->getValue() <= EQFL) {
//                        numcount++;
//                        std::cout << num << ": " << this->data_obj->getValue();
//                        this->data_obj->next();
//                    }
//                }
//                std::cout << "Search found " << numindex << " " << numcount <<
//                             std::endl;
//                return std::pair(numindex,numcount);

//                while (num - this->data_obj->getValue() < EQFL){
//                    std::cout << num << ": " << this->data_obj->getValue();
//                    this->data_obj->prev();
//                }
//                if (num - this->data_obj->getValue() <= EQFL) {
//                    numindex = this->data_obj->currPos();
//                    while (num - this->data_obj->getValue() <= EQFL) {
//                        std::cout << num << ": " << this->data_obj->getValue();
//                        numcount++;
//                        this->data_obj->prev();
//                    }
//                }
//            }
        }
        std::cout << "Search found " << numindex << " " << numcount <<
                     std::endl;
        return std::pair(numindex,numcount);
    }

    int length_unique() {
        return unique_set().size();
    }

    int length_total() {
        return this->data_obj->length();
    }

    std::set<N> unique_set() {
        std::set<N> uni_set;
        this->data_obj->moveToStart();
        while (this->data_obj->currPos() < this->data_obj->length()) {
            uni_set.insert(this->data_obj->getValue());
            this->data_obj->next();
        }
        return uni_set;
    }

    void feed(const L& data_feed){
        for (auto& num:data_feed){
            std::cout << "feeding " << num << std::endl;
            append(num);
        }
    }

    double get_mean(){
        return data_mean;
    }

    double get_SD(){
        return data_sd;
    }


    auto get_min(){
        return data_min;
    }

    auto get_max(){
        return data_max;
    }

};
#endif // SIMPLE_STAT_H

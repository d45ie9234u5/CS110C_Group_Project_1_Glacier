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
//       statistics. Therefore, okay if they are expensive operations like
//       O(n):
//       append: append new data.  Update existing number of duplication or
//          append from the end if new
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
// Understand:
// input: for append, integer or double
//        for feed, standard C++ container date type containing integer or
//           double values for elements
//        for removem: a data element and number of repetitions of that element
//        for search: the value to search for
// output: returns pair of integers from search, single integer for
//         length_unique and length_total, a set for unique_set and doubles
//         for all of the statistics (except minimum and maximum which will
//         be generic types.)
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
// Match:
// Class for data object including vector for data, statistics variables
// Generic iterator for feed method that calls append method
//
// Plan:
// 1. Definition and implementation of simple_stats class
//    a. Private members:
//          1. data_obj: linked list of generic type
//          2. data_mean: mean of all values in data object
//          3. data_sd: standard deviation of all values in data object
//          4. data_min: minimum value in data object
//          5. data_max: maximum value in data object
//          6. data_sum: sum of all values in data object
//          7. data_sqsum: the square sum of all values in data object
//          8. data_var: the variance of all values in data object
//          9. calc_stats(new_element, toggle value for add or delete of value):
//                delta_mean = new_element - data_mean;
//                data_sum if add (+= new_element) if delete (-= new_element)
//                data_mean = if add (+= delta mean/data_obj.length())
//                            if delete (-= delta mean/data_obj.length())
//                data_sqsum = add (+=delta mean * (new_element - new data_mean)
//                          delete (-=delta mean * (new_element - new data_mean)
//                data_sd =
//                  sqrt((data_sqsum/data_obj.length())
//                data_min (also check for new minimum on removem function) =
//                  if new_element < data_min then data_min = new_element
//                data_max (also check for new minimum on removem function)
//                  if new_element > data_max then data_max = new_element
//    b. Public members:
//          1.  default constructor: create empty data object
//          2.  constructor that calls feed with undefined iterable data object
//          3.  [] overload operator: if index is >=  data_count
//                 than return NULL, else iterate through data_obj.count until
//                 index supplied is within range and return the data_obj.value
//                 for that index value.
//          4.  append: search for new element in data_obj, if found, add within
//                      range of duplicate, calc_stats.  else insert in correct
//                      range within data_obj
//          5.  removem: call search and check if repitions requested to be
//                       removed is less than or equal to number of duplicates.
//          6.  empty: clear data_obj, and all stats
//          7.  search: check if value is >= data_min and <= data_max, then
//                       iterate through data_obj and then count duplicates and
//                       return pair with index and number reps
//          8.  length_unique: return unique_set.size()
//          9.  length_total: return data_obj.length()
//          10. unique_set: iterate through data_obj and append to set.
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


template <class L, class N = typename L::value_type> class Simple_stat:
        public LList<N> {
private:
    LList<N>* data_obj;         // Linked list of generic type
    double data_mean = 0.0;     // Mean of all values in data_obj
    double data_sqsum = 0.0;    // Square of sums of all values in data_obj
    double data_var = 0.0;      // Variance of all values in data_obj
    double data_sd = 0.0;       // Standard deviation of all values in data_obj
    N data_min = 0;             // Minimum value in data object
    N data_max = 0;             // Maximum value in data object
    double data_sum = 0.0;      // Sum of all values in data object

    // input: new element that has been inserted into data object and toggle
    //        value 1 for value that is added to object and 0 for value that is
    //        deleted from object.
    void calc_stats(N new_element, int addval) {
        // Delta of new element and the previous mean.
        double delta_mean = new_element - data_mean;

        // Calculate stats if value is added to data object.
        if (addval == 1) {
            data_sum += new_element;
            data_mean += delta_mean/this->data_obj->length()*1.0;
            data_sqsum += delta_mean * (new_element - data_mean);
            // data_min and data_max are recalcuated in removem function
            // after checking if there are no duplicates left of value
            // removed.
            if(this->data_obj->length() == 1 || new_element < data_min) {
                data_min = new_element;
            }
            if(this->data_obj->length() == 1 || new_element > data_max) {
                data_max = new_element;
            }
        } else {
            // Calculate stats if value is removed from data object.
            data_sum -= new_element;
            data_mean -= delta_mean/this->data_obj->length()*1.0;
            data_sqsum -= delta_mean * (new_element - data_mean);
        }

        data_sd = sqrt(data_sqsum/data_obj->length()*1.0);


    }



public:
    // Default constructor
    Simple_stat(){
         data_obj = new LList<N>;
    }

    // Constructor accepts data container of generic type and calls feed
    // function to feed the values from container into linked list.
    Simple_stat(const L& data_feed) {
        data_obj = new LList<N>;
        feed(data_feed);
    }

    ~Simple_stat(){
        empty();
    }

    // Moves position in linked list to requested index and returns value.
    auto operator[](int indexnum) {
        this->data_obj->moveToPos(indexnum);
        return this->data_obj->getValue();
    }

    // Calls search function to see if new value is in data object already and
    // inserts the value in correct order and call calc_stats.
    void append(N num) {
        std::pair found_index = search(num);
        // If value found already in object, insert the value at the found
        // found index.
        if (found_index.second > 0) {
            this->data_obj->moveToPos(found_index.first);
            this->data_obj->insert(num);
        // If the value is less than data_min or data object is empty, insert
        // at start of data object.
        } else if (num < data_min || this->data_obj->length() == 0){
            this->data_obj->moveToStart();
            this->data_obj->insert(num);
        // If the value is greater than data_max, insert at end of data object.
        } else if (num > data_max) {
            this->data_obj->moveToEnd();
            this->data_obj->insert(num);
        // If the value is between data_min and data_max but not in data object
        // insert in correct order so data remains sorted.
        } else if (num > data_min && num < data_max) {
            this->data_obj->moveToStart();
            while (this->data_obj->currPos() < this->data_obj->length()) {
                    this->data_obj->next();
                    if (num < this->data_obj->getValue()) {
                        break;
                    }
                }
            this->data_obj->insert(num);
        }
        calc_stats(num,1);
    }

    // Searches for requested value in data object and removes requested number
    // of duplicates if less or equal to number of duplicates in data object.
    void removem(N m, int reps){
        std::pair found_index = search(m);

        // Number of duplicates requested to delete are less than or equal to
        // found number of duplicates in data object of value, then remove
        // that number of duplicates of value from data_object.
        if (reps <= found_index.second) {
                this->data_obj->moveToPos(found_index.first);
                for (int i = found_index.first; i < found_index.first+reps;i++)
                {
                    N delitem = this->data_obj->getValue();
                    this->data_obj->remove();
                    calc_stats(m,0);
                    this->data_obj->next();
                }
        }

        // If the number of duplicates deleted are equal to all duplicates
        // found then calculate new data_min or data_max if value deleted
        // was one of those values.
        if (reps == found_index.second && m == data_min) {
            this->data_obj->moveToStart();
            data_min = this->data_obj->getValue();
        } else if (reps == found_index.second && m == data_max) {
            this->data_obj->moveToEnd();
            data_max = this->data_obj->getValue();
        }

    }

    void empty() {
        delete data_obj;
        data_obj = NULL;
        data_sum = 0;
        data_mean = 0;
        data_sd = 0;
        data_min = 0;
        data_max = 0;
    }

    // Searches for the requested value in data object and return pair with
    // firstvalue being index and second value being the number of repetitions
    // of value in data object.
    std::pair<int,int> search(N num){
        int numindex = 0;
        int numcount = 0;

        // Check if data object is empty and that the value is between
        // data_min and data_max, then iterate through data object,
        // find the index of first occurence and number repetitions and return
        // pair with those values, otherwise returns 0 for both values.
        if (this->data_obj->length() > 0
                && num >= data_min && num <= data_max) {
            this->data_obj->moveToStart();

            while (this->data_obj->currPos() < this->data_obj->length()) {
                // Check if value is duplicate, subtracting from value found
                // in data object for float equality.
                if (abs(num - this->data_obj->getValue()) <= 1e-9 ) {
                    if (numcount == 0) {
                        numindex = this->data_obj->currPos();
                    }
                    numcount++;
                } else if (num < this->data_obj->getValue()) {
                    return std::pair(numindex,numcount);
                    break;
                }
                this->data_obj->next();
            }
        }
        return std::pair(numindex,numcount);
    }

    // Inserts the data object into set by calling unique_set function and
    // then return the size of the set.
    int length_unique() {
        return unique_set().size();
    }

    int length_total() {
        return this->data_obj->length();
    }

    // Iterates through data object and inserts into set.
    std::set<N> unique_set() {
        std::set<N> uni_set;
        this->data_obj->moveToStart();
        while (this->data_obj->currPos() < this->data_obj->length()) {
            uni_set.insert(this->data_obj->getValue());
            this->data_obj->next();
        }
        return uni_set;
    }

    // Appends values from generic data container with generic type values
    // into data object.
    void feed(const L& data_feed){
        for (auto& num:data_feed){
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

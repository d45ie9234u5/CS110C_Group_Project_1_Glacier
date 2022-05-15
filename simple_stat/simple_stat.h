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
//       append: append new data. Update exist number of duplication or append
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
//          1. simple_dataset: array of data
//          2. data_mean: mean of data set
//          3. data_sd: standard deviation of data set
//          4. data_min: minimum value in data set
//          5. data_max: maximum value in data set
//          6. data_sum: sum of all values in set
//          6. calc_stats(new_element):
//                data_sum += new_element
//                data_mean = data_sum/# of elements
//                data_sd =
//                  sqrt((data_sd + (pow(new_element - data_mean, 2))/# of elem)
//    b. Public members:
//          1. default constructor: create empty data object
//          2. constructor that calls feed with undefined iterable data object
//          3. append: append single element to array, calculate stats and
//                update private members
//          4. removem:
#ifndef SIMPLE_STAT_H
#define SIMPLE_STAT_H

#endif // SIMPLE_STAT_H

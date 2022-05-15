# CS110C_Group_Project_1_Glacier
CCSF CS110C Section 002 - Spring, 2022 - Glacier Group Project - Simple_Stat

This project is written to store a data object containing both integer and double types and the associated mean, standard deviation, minimum and maximum of all elements.  The data object will contain many duplicate values.
The following operations are available:
  append: Update existing element duplicate or append to end if new.
  removem: Remove m number of data element only if m is less than the current amount of duplicates of that element.
  empty: delete all data.
  feed: append data from any standard c++ data container type.
  search: return the index of first occurrence of data element and the number of repetitions of that element.
  length_unique: the number of unique elements in the data object.
  length_total: the total number of elements in the data object.
  unique_set: returns a std:set of the (unique) elements in data object.
  get_mean: returns the mean value of all elements in data object.
  get_SD: returns the standard deviation of all elements in data object.
  get_minimum: returns the minimum value of all elements in data object.
  get_maximum: returns the maximum value of all elements in data object.
  [] operator: returns the unique element referenced in index value.
  

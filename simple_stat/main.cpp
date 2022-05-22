#include <iostream>
#include <stdlib.h>
#include <vector>
#include <simple_stat.h>
#include <chrono>
#include <random>
#include <algorithm>




int main() {

    std::vector<int> int_vec;

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); // Seed value is drawn from current time to guarantee a different seed value
    std::default_random_engine generator (seed); // Default random number generator algorithm.
    std::uniform_int_distribution<int> int_distribution (90, 100);
    for (int i=0;i < 1000;i++) {
        int_vec.push_back(int_distribution(generator));
    }

    Simple_stat<std::vector<int>> *simpstat;
    simpstat = new Simple_stat(int_vec);

    std::cout << "Length unique is: " << simpstat->length_unique() << std::endl;

}


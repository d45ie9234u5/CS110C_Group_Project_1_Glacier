#include <iostream>
#include <stdlib.h>
#include <vector>
#include <simple_stat.h>
#include <chrono>
#include <random>
#include <algorithm>

template <typename N>
void printstats(Simple_stat<N>& simp) {
    std::cout << "Length unique is: " << simp.length_unique() << std::endl;
    std::cout << "Length total is: " << simp.length_total() << std::endl;
    std::cout << "Mean is: " << simp.get_mean() << std::endl;
    std::cout << "Minimum value is: " << simp.get_min() << std::endl;
    std::cout << "Maximum value is: " << simp.get_max() << std::endl;
    std::cout << "Standar deviation is: " << simp.get_SD() << std::endl;
}

int main() {

    std::vector<int> int_vec;
    std::vector<int> int_vec2;
    std::vector<double> dbl_vec;

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); // Seed value is drawn from current time to guarantee a different seed value
    std::default_random_engine generator (seed); // Default random number generator algorithm.
    std::uniform_int_distribution<int> int_distribution (90, 100);
    for (int i=0;i < 1000;i++) {
        int_vec.push_back(int_distribution(generator));
    }


    Simple_stat<std::vector<int>> *simpstat;
    simpstat = new Simple_stat(int_vec);
    printstats(*simpstat);
    std::uniform_int_distribution<int> int_distribution2 (90, 100);
    for (int i=0;i < 10;i++) {
        int_vec2.push_back(int_distribution2(generator));
    }
    simpstat->feed(int_vec2);
    printstats(*simpstat);
    delete simpstat;


    std::uniform_real_distribution<double> dbl_distribution (90.0, 100.0);
    for (int i=0;i < 1000;i++) {
        dbl_vec.push_back(dbl_distribution(generator));
    }

    Simple_stat<std::vector<double>> *simpstatdbl;
    simpstatdbl = new Simple_stat(dbl_vec);
    printstats(*simpstatdbl);
    delete simpstatdbl;
}



#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <iostream>


int calculate_next(int value) {
    std::cout << "started" << std::endl;
    int next_value = 1;
    for (int i = 2; i < 1000000000; i++) {
        next_value += i;
        if (next_value % 10 == 3) {
            next_value += value;
        }
    }
    std::cout << "finished" << std::endl;
    return next_value;
}


int main() {
    std::string command;
    while (std::cin >> command) {
        if (command == "show") {
            
        } else if (command == "next") {
            
        }
    }
    return 0;
}

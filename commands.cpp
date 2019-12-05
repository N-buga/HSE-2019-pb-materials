#include<pthread.h>
#include<stdio.h>
#include <unistd.h>
#include<string>
#include<iostream>

pthread_mutex_t m;
pthread_cond_t cond;  // Guarded by m.

int value = 0;  // Guarded by m.
bool do_next = false;  // Guarded by m.

int calculate_next(int value) {
	usleep(10000000);
	std::cout << "finished";
	return value + 1;
}

void* next_value(void*) {
	while (true) {
		pthread_mutex_lock(&m);
        while (!do_next) {
            pthread_cond_wait(&cond, &m);
        }
        int value_snapshot = value;
        pthread_mutex_unlock(&m);
        int next_value = calculate_next(value_snapshot);
        pthread_mutex_lock(&m);
        value = next_value;
        do_next = false;
        pthread_mutex_unlock(&m);
	}
}

int main() {
	pthread_mutex_init(&m, NULL);
    pthread_cond_init(&cond, NULL);

	pthread_t id;
    assert(pthread_create(&id, NULL, next_value, NULL) == 0);

    std::string command;
    while (std::cin >> command) {
    	if (command == "show") {
	    		pthread_mutex_lock(&m);
	    		std::cout << "Value is " << value << std::endl;
	    		pthread_mutex_unlock(&m);
	    } else if (command == "next") {
    		if (do_next) {
    			std::cout << "Value is still calculating." << std::endl;
    		}
    		pthread_mutex_lock(&m);
    		do_next = true;
    		pthread_cond_signal(&cond);
    		pthread_mutex_unlock(&m);	
    	} 
    }



	pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&m);
    return 0;
}
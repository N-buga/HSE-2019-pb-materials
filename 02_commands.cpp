#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <string>
#include <iostream>


int value_to_show = 1;
pthread_mutex_t mutex;
pthread_cond_t cond_calculate_next; // Guarded by mutex.
bool is_finished = true;  // Guarded by mutex.
bool is_program_finished = false;  // Guarded by mutex.

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


void* calculate_next_service(void*) {
    bool is_program_finished_snapshot = false;
    while (!is_program_finished_snapshot) {
        pthread_mutex_lock(&mutex);
        if (is_program_finished) {
            break;
        }
        pthread_cond_wait(&cond_calculate_next, &mutex);
        if (is_program_finished) {
            break;
        }
        int value_snapshot = value_to_show;
        is_finished = true;
        pthread_mutex_unlock(&mutex);
        
        calculate_next(value_snapshot);

        pthread_mutex_lock(&mutex);
        value_to_show = value_snapshot;
        is_program_finished_snapshot = is_finished;
        pthread_mutex_unlock(&mutex);
    }
    return nullptr;
}

int main() {
    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&cond_calculate_next, nullptr);
    pthread_t id;    
    assert(pthread_create(&id, nullptr, calculate_next_service, nullptr) == 0);

    std::string command;
    while (std::cin >> command) {
        if (command == "show") {
            pthread_mutex_lock(&mutex);
            std::cout << "Value is " << value_to_show << std::endl;
            pthread_mutex_unlock(&mutex);
        } else if (command == "next") {
            pthread_mutex_lock(&mutex);
            if (is_finished) {            
                pthread_cond_signal(&cond_calculate_next);
                is_finished = false;
            } else {
                std::cout << "Still calculating" << std::endl;
            }
            pthread_mutex_unlock(&mutex);            
        } else if (command == "exit") {
            pthread_mutex_lock(&mutex);
            is_program_finished = true;
            pthread_cond_signal(&cond_calculate_next);
            pthread_mutex_unlock(&mutex);
            break;
        }
    }

    assert(pthread_join(id, nullptr) == 0);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_calculate_next);

    return 0;
}

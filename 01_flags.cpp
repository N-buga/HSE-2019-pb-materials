#include <assert.h>
#include <pthread.h>
#include <iostream>


const int MAXN = 100000;


pthread_mutex_t mutex;
pthread_cond_t cond_flag_changed;
int flag;

void* consumer(void*) {
    bool is_finished = false;
    while (!is_finished) {
        while (flag == 0) {
        }
        std::cout << "Flag changed to " << flag << std::endl;
        if (flag == -1) {
            is_finished = true;
        }
        flag = 0;
    }
    return nullptr;
}

int main() {
    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&cond_flag_changed, nullptr);
    pthread_t id;
    assert(pthread_create(&id, nullptr, consumer, nullptr) == 0);
    for (int i = 1; i <= MAXN; i++) {
        flag = i;
    }
    flag = -1;
    assert(pthread_join(id, nullptr) == 0);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_flag_changed);
    return 0;
}


#include <assert.h>
#include <pthread.h>
#include <iostream>


const int MAXN = 100000;


pthread_mutex_t mutex;
pthread_cond_t cond_flag_changed;
pthread_cond_t cond_flag_changed_write;
int flag;

void* consumer(void*) {
    bool is_finished = false;
    while (!is_finished) {
        pthread_mutex_lock(&mutex);
        while (flag == 0) {
            pthread_cond_wait(&cond_flag_changed, &mutex);
        }
        std::cout << "Flag changed to " << flag << std::endl;
        if (flag == -1) {
            is_finished = true;
        }
        flag = 0;
        pthread_cond_signal(&cond_flag_changed_write);
        pthread_mutex_unlock(&mutex);
    }
    return nullptr;
}

int main() {
    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&cond_flag_changed, nullptr);
    pthread_cond_init(&cond_flag_changed_write, nullptr);
    pthread_t id;
    assert(pthread_create(&id, nullptr, consumer, nullptr) == 0);
    for (int i = 1; i <= MAXN; i++) {
        pthread_mutex_lock(&mutex);
        flag = i;
        pthread_cond_signal(&cond_flag_changed);
        while (flag != 0) {
            pthread_cond_wait(&cond_flag_changed_write, &mutex);
        }
        pthread_mutex_unlock(&mutex);
    }
    pthread_mutex_lock(&mutex);
    flag = -1;
    pthread_cond_signal(&cond_flag_changed);
    pthread_mutex_unlock(&mutex);
    assert(pthread_join(id, nullptr) == 0);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond_flag_changed_write);
    pthread_cond_destroy(&cond_flag_changed);

    return 0;
}

// pthread_mutex_lock(&mutex);
// pthread_mutex_unlock(&mutex);
// pthread_cond_wait(&cond_flag_changed, &mutex);
// pthread_cond_signal(&cond_flag_changed);

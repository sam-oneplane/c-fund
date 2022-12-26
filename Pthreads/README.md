# assembly .s file creation
    gcc -S mutex.c   

# complie mutex.c file into mutex
    gcc -g -pthread mutex.c -o mutex


# condition varaible
    pthread_cond_wait
    pthread_cond_signal
    pthread_cond_broadcast

    
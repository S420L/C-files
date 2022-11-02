#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

void* routine(){
    printf("Test from threads s*Wgga\n");
    sleep(3);
    printf("end of thread \n");
    return 0;
}

int main(int argc, char* argv[]){
    pthread_t t1,t2,t3,t4,t5,t6,t7;
    if(pthread_create(&t1,NULL,&routine,NULL)!=0){
        return 4;
    }
    if(pthread_create(&t2,NULL,&routine,NULL)!=0){
        return 5;
    }
    if(pthread_create(&t3,NULL,&routine,NULL)!=0){
        return 6;
    }
    if(pthread_create(&t4,NULL,&routine,NULL)!=0){
        return 7;
    }
    if(pthread_create(&t5,NULL,&routine,NULL)!=0){
        return 8;
    }
    if(pthread_create(&t6,NULL,&routine,NULL)!=0){
        return 9;
    }
    if(pthread_create(&t7,NULL,&routine,NULL)!=0){
        return 10;
    }
    pthread_join(t1,NULL);
    pthread_join(t2,NULL);
    return 0;
}
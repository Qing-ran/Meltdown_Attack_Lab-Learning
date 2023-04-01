#include <emmintrin.h>
#include <x86intrin.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

uint8_t array[256*4096];
int temp;
char secret = 94;

/* cache hit time threshold assumed*/
#define CACHE_HIT_THRESHOLD 80
#define DETLA 1024

void flushSideChannel(){
    int i;

    // Write to array to bring it to RAM to prevent Copy-on-write
    for (i=0; i<256; i++){
        array[i*4096 + DETLA] =  1;
    }

    // Flush the values of the array from cache
    for (i=0; i<256; i++){
        _mm_clflush(&array[i*4096 + DETLA]);
    }
}

void victim(){
    temp = array[secret*4096 + DETLA];
}

void reloadSideChannel(){
    int junk = 0;
    register uint64_t time1, time2;
    volatile uint8_t *addr;
    int i;
    for(i=0; i<256; i++){
        addr = &array[i*4096 + DETLA];
        time1 = __rdtscp(&junk);
        junk = *addr;
        time2 = __rdtscp(&junk) - time1;
        if(time2 <= CACHE_HIT_THRESHOLD){
            printf("array[%d*4096 + %d] is cache.\n", i, DETLA);
            printf("The Secret = %d\n", i);
        }
    }
}

int main(int argc, const char **argv){
    flushSideChannel();  // Step1
    victim(); // Step2
    reloadSideChannel();  // Step3
    return 0;
}

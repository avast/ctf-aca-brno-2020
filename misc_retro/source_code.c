#include <stdio.h> 
#include <time.h> 
#include <string.h>
#include <signal.h>


void handler(int nSignum, siginfo_t* si, void* vcontext) {
  printf("avastCTF{seg_faults_for_days_75509}");
}

int main () 
{ 
    struct sigaction action;
    memset(&action, 0, sizeof(struct sigaction));
    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = handler;
    sigaction(SIGSEGV, &action, NULL);

    time_t seconds; 
    int size = 100000;
    int ints[size];
    int i;
    
    for (i = 0; i < size ; i++){ 
        ints[i] = 0; 
    } 

    int flag = 44500128;
    ints[7688] = flag;

    long int t;
      
    seconds = time(NULL); 
    t = (int) (time(NULL));
    int index = t / 100000;

    printf("Accessing array at index: %d, value: %d.\n", index, ints[index]);
    if (ints[index] != flag) {
        printf("Nope. Try again later.\n");
    } else {
        printf("Bingo.\n");
    }
      
    return(0); 
} 


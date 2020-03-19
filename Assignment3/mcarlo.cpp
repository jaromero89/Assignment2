/* James L. Romero
 * Professor: Tom Springer
 * CPSC 380 Operating Systems
 * Date: 3/19/2020
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <math.h>

//Function Prototypes
void calculatePointsInsideCircle();

// Let us create a global variable to change it in threads
int g = 0;
//Total count
int npoints = 0;
//Counter
int counter = 0;
int z = 0;
// mutex for syncronization
pthread_mutex_t mutex;

/* Generates a double precision random number */
double random_double() {
    return random() / ((double) RAND_MAX + 1);
}

//Check for points inside circle
void calculatePointsInsideCircle(void) {
    int i;
    int hit_count = 0.0;
    double x = 0.0, y = 0.0;

    for (i = 0; i < z; i++) { //npoints : Number of points
/* generate random numbers between -1.0 and +1.0 (exclusive) */
        x = random_double() * 2.0 - 1.0;
        y = random_double() * 2.0 - 1.0;

        if (sqrt(x * x + y * y) < 1.0)
            ++hit_count;
    }
    g = hit_count;
}
//Child Tread
void * Child(void *ptr)
{
    pthread_mutex_lock(&mutex); // lock resource
    calculatePointsInsideCircle();   // generate number and store count in globle_var
    pthread_mutex_unlock(&mutex); //unlock resource
}
//Parent Tread
void * Parent(void *ptr)
{
    double pi;
    pthread_mutex_lock(&mutex);
    // Calculate PI
    pi= (double)g / z * 4;
    //Display
    printf("PI estimation is %g \n",pi);
    pthread_mutex_unlock(&mutex); //unlock resource
}
int main(int argc, char *argv[]) {
    if (argc != 2) {
        perror("Expected input: ./mcarlo <number of points>");
        return 1;
    }
    z = atoi(argv[1]);
    int *myid = (int *)argv;
    //Two treads required
    pthread_t numP, pie;
    pthread_mutex_init(&mutex, NULL);

    //Creates Child tread
    pthread_create(&numP,0,Child,0);
    //Creates Parent Tread
    pthread_create(&pie,0,Parent,0);
    //waits for the completion of child
    pthread_join(pie,0);
    //waits for the completion of parent
    pthread_join(numP,0);
   // pthread_mutex_destroy(&mutex); // distroy mutex
    pthread_exit(NULL); // exit thread
    return 0;
}




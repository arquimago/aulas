/* Backprop I: The Chosen One               */
/* autor: Denis Vereš                       */
/* email: sinedko@gmail.com                 */
/* year: 2015                               */
/* usage: gcc <filename> -Ofast -ffast-math */

/*  Basic includes   */
#include <stdio.h>   // printf
#include <stdlib.h>  // rand, srand
#include <math.h>    // exp, abs
#include <time.h>    // clock

/* Definition of neural network */
#define IN 2                    // number of input neurons
#define H1 4                   // number of neurons in first hidden layer
#define OUT 1                   // number of output neurons
#define N (1+IN+OUT+H1)         // number of total neurons

/*      Numbers of neurons      */
#define F1H 1+IN                // no. of first neuron in first hidden layer
#define L1H F1H+H1-1            // no. of last neuron in first hidden layer
#define FO F1H+H1               // no. of first neuron in output layer
#define LO FO+OUT-1             // no. of last neuron in output layer

/* Definition of learning */
#define gamma 0.2         // learning rate
#define epochs 100000      // number of learning epochs
#define tPoints 2000      // number of training points

/*             Activation function and its first derivation             */
#define f(x) (1.0/(1.0+exp((-1.0)*x)))                                  // sigmoidal activation function
#define df(x) (exp((-1.0)*x)/((1.0+exp((-1.0)*x))*(1.0+exp((-1.0)*x)))) // derivation of sigmoidal function

/* Structure of neural network */
typedef struct nn {            // --------------------
    double x[N];               // inputs in neurons
    double y[N];               // activations of inputs
    double d[N];               // error signal (difference)
    double w[N][N];            // weights matrix
    double dv[OUT];            // desired value on output
} NN;

NN network = {}; // declaration of neural network

/*   Some useful definitions   */
#define x(i) network.x[i]      // inputs
#define y(i) network.y[i]      // activations
#define d(i) network.d[i]      // deltas
#define w(i,j) network.w[i][j] // weights
#define dv(i) network.dv[i]    // desired outputs

/* Function for initialize random weights in interval <min,max> */
void initWeights(double min, double max) {                      // --------------------
    y(0) = -1;                                                  // initialize the input of bias
                                                                // --------------------
    for (int i = 0; i < N; i++)                                 // go through array
        for (int j = 0; j < N; j++)                             // same
            w(i,j) = rand() / (RAND_MAX/(max-min)) + min;       // sets random number to the array
}

/*      Function for passing individual layers    */
void layerRun(int from[], int to[]) {             // --------------------
    for (int j = from[0]; j < to[0]; j++) {       // from first neuron in specific layer to last
        //printf("\nx(%d) = w(0,%d) * y(0) + ",j,j);// --------------------
        x(j) = w(0,j) * y(0);                     // adding bias to the sum
        for (int i = from[1]; i <= to[1]; i++) {  // from first neuron to last neuron specific layer
            x(j) += w(i,j) * y(i);                // using formula to compute neuron inputs
            //printf("w(%d)(%d) * y(%d) + ",i,j,i); // --------------------
        }                                         // --------------------
        y(j) = f(x(j));                           // using activation function with neuron inputs to gain activations
    }
    //printf("\n---------");
}

/* Function for passing over the network (forward pass) */
void forwardRun() {
    int from[2], to[2]; // declarations of auxiliary arrays
    
    /* Going through first hidden layer  */
    from[0] = F1H; to[0] = L1H + 1;      // definitions from-to for j (from first to last in first hidden layer)
    from[1] =   1; to[1] = IN;           // definitions from-to for i (from first to last in input layer)
    layerRun(from,to);                   // runs function
    
    /*     Going through output layer    */
    from[0] =  FO; to[0] = LO + 1;       // definitions from-to for j (from first to last in output layer)
    from[1] = F1H; to[1] = L1H;          // definitions from-to for i (from first to last in second hidden layer)
    layerRun(from,to);                   // runs function
}

/* Function for passing over a network to compute deltas */
void deltaRun(int from[], int to[]) {                    // --------------------
    for (int i = from[0]; i <= to[0]; i++) {             // from first neuron in specific layer to last
        d(i) = 0;                                        // clear old delta
        //printf("\nd(%d) = ",i);                        // --------------------
        for (int j = from[1]; j <= to[1]; j++) {         // from first neuron in specific layer to last
            //printf("d(%d) * w(%d)(%d) + ",j,i,j);      // --------------------
            d(i) += d(j) * w(i,j);                       // using formula to compute delta
        }                                                // --------------------
        d(i) *= df(x(i));                                // multiply with first derivation of activation function
    }
}

/* Function for passing over the network (backward pass) */
void backwardRun() {
    int from[2],to[2]; // declarations of auxiliary arrays
    
    /*      Compute deltas in output layers      */
    for (int i = FO, j = 0; i <= LO; i++, j++) { // from first to last neuron in output layer
        d(i) = (dv(j) - y(i)) * df(x(i));        // using formula to compute deltas on output layer
        //printf("\nd(%d) = (dv(%d) - y(%d)) * df(x(%d))",i,j,i,i);
    }
    //printf("\n---------");
    
    /* Compute deltas in first hidden layer  */
    from[0] = F1H; to[0] = L1H;              // definitions from-to for j (from first to last in first hidden layer)
    from[1] =  FO; to[1] =  LO;              // definitions from-to for i (from first to last in second hidden layer)
    deltaRun(from,to);                       // runs function
}

/* Function for passing over the network and update weights */
void weightsRun(int from[], int to[]) {                     // --------------------
    for (int i = from[0]; i <= to[0]; i++)                  // from first neuron in specific layer to last
        for (int j = from[1]; j<= to[1]; j++) {             // same
            w(i,j) += (d(j) * y(i) * gamma);                // using formula for updating weights
            //printf("\nw(%d)(%d) += d(%d) * y(%d) * gamma",i,j,j,i);
        }
}

/* Function for passing over the network (updating weights) */
void weightsUpdate() {
    int from[2], to[2]; // declarations of auxiliary arrays
    
    /*    Changing weights for bias     */
    from[0] =   0;  to[0] =  0;         // --------------------
    from[1] = F1H; to[1]  = LO;         // definitions from-to for i (from first to last neuron in network)
    weightsRun(from,to);                // runs function
    
    /* Changing weights for input layer */
    from[0] =   1; to[0] =  IN;         // definitions from-to for j (from first to last in input layer)
    from[1] = F1H; to[1] = L1H;         // definitions from-to for i (from first to last in first hidden layer)
    weightsRun(from,to);                // runs function
    
    /* Going through first hidden layer */
    from[0] = F1H; to[0] = L1H;         // definitions from-to for j (from first to last in first hidden layer)
    from[1] =  FO; to[1] =  LO;         // definitions from-to for i (from first to last in second hidden layer)
    weightsRun(from,to);                // runs function
}

/* Structure of training data */
typedef struct TDATA {        // --------------------
    int  x[tPoints];          // first input neuron
    int  y[tPoints];          // second input neuron
    int dv[tPoints];          // desired output
} tdata;

tdata training = {}; // declaration of training datas

/*       Function for load training data       */
void trainData () {                            // --------------------
    FILE *train = fopen("misc/tset.txt","r");  // loads file which contains training data
    int size;                                  // variable for storing lines of training data file
    fscanf(train,"%d",&size);                  // reads number of lines in file
                                               // --------------------
    for (int i = 0; i <= size; i++)            // store all training data in array
        fscanf(train,"%d %d %d",&training.x[i],&training.y[i],&training.dv[i]);
    fclose(train);                             // close the file
}

int main () {
    int XOR[4][3] = {{0,0,0,},{0,1,1,},{1,0,1,},{1,1,0,}};	// XOR data
    clock_t t;             // auxiliary variable for compute running time
    float sec;             // auxiliary variable for compute seconds
                           // --------------------
    srand(42);             // seed for random numbers
    initWeights(-0.1,0.1); // initialize weights
    //trainData();
    t = clock();           // start timer
    
    printf("\nEpoch:  Output  Des.out. (Error)\n"); // --------------------
    printf("--------------------------------\n");   // --------------------
                                                    // --------------------
    for (int epoch = 0; epoch <= epochs; epoch++) { // for every epoch
        for (int p = 0; p < 4; p++) {			    // for every pattern
            y(1)  =  XOR[p][0];				        // input 1 (XOR data)
            y(2)  =  XOR[p][1];				        // input 2 (XOR data)
            dv(0) =  XOR[p][2];				        // desired output (XOR data)
                                                    // --------------------
            //y(1)  =  training.x[p] / 100;         // input 1 (spiral data)
            //y(2)  =  training.y[p] / 100;         // input 2 (spiral data)
            //dv(0) = training.dv[p];               // desired output (spiral data)
                                                    // --------------------
            forwardRun();                           // train
            backwardRun();                          // train
            weightsUpdate();                        // train
                                                    // --------------------
            if (epoch % 1000==0) {				    // every 20000 ep. print error
                if (p == 0 && epoch != 0)           // --------------------
                    printf("\n");		            // --------------------
                forwardRun();                       // runs network
                double J=fabs(dv(0) - y(FO));		// compute the error
                if (p % 500 == 0) printf("%5d: %f %f (%.3f)",epoch,y(FO),dv(0),J);
            }
        }
    }
    
    t = clock() - t;                 // stop timer
    sec = ((float)t)/CLOCKS_PER_SEC; // conversion to seconds
    
    //printf("--------------------------------\n%.3f sec\n\n",sec);
    printf("\n%.3f ",sec);
    return 0;
}
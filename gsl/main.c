#include <stdio.h>
#include <gsl/gsl_cblas.h>
#include <math.h>
#include <stdlib.h>
#define _PRECISION_ 100

double factorial(size_t n) {
  static double f[_PRECISION_] = {1, 1, 2, 6};
  if (f[n] == 0) {
    f[n] = factorial(n-1) * (double)n;
    // printf("%lf\n", f[n]);
  }
  return f[n];
}

void mcpy(const double *A, size_t length, double *B) {
  for(size_t i = 0; i < length; i++) {
    B[i] = A[i];
  }
}

void setI(double *A, size_t dimension) {
  for(size_t i = 0; i < dimension; i++) {
    A[i + i*dimension] = 1;
  }
}

void addMatrix(double *A, size_t dimension, const double *B, double beta) {
  for (size_t i = 0; i < dimension * dimension; i++){
    A[i] += beta*B[i];
  }
}

void printMatrix(const double *A, size_t dimension){
  printf("[ ");
  for (size_t i = 0; i < dimension; i++) {
    for (size_t j = 0; j < dimension; j++) {
      printf("%g, ", A[i*dimension + j]);
    }
    (i + 1) == dimension ? printf("]\n\n") : printf("\n");
  }
}

void mExponetial(const double *G, size_t dimension, double **A, size_t p) {
  *A = calloc(dimension * dimension, sizeof (double));
  setI(*A, dimension);
  double *Ap = malloc(dimension * dimension * sizeof(double));
  mcpy(G, dimension * dimension, Ap);

  addMatrix(*A, dimension, Ap, 1);

  double wtf[9] = {0};
  for(size_t i = 2; i < p; i++){
    cblas_dgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, dimension, dimension, dimension, 1, Ap, dimension, G, dimension, 0, wtf, dimension); //Ap = Ap * G
    mcpy(wtf, dimension * dimension, Ap);
    addMatrix(*A, dimension, Ap, 1/factorial(i)); //A = A + Ap/n! 
  }
  // printf("A: \n");
  // printMatrix(*A, n);
  free(Ap);
}

double *getTime(const double *G, const double *initP, size_t dimension, double time) {
  double *timeG = malloc(dimension * dimension * sizeof(double));
  for(size_t i = 0; i < dimension * dimension; i++) {
    timeG[i] = G[i] * time;
  }

  double *A;
  mExponetial(timeG, dimension, &A, _PRECISION_);
  double *finalP = malloc(dimension * dimension * sizeof(double));
  cblas_dgemv(CblasRowMajor, CblasNoTrans, dimension, dimension, 1, A, dimension, initP, 1, 0, finalP, 1);

  free(A);
  free(timeG);
  return finalP;
}

double *findGenerator(const double *jumpChain, const double *leavingRates, size_t dimension) {
  double *generator = malloc(dimension * dimension * sizeof(double));
  for(size_t i = 0; i < dimension; i++) {
    for(size_t j = 0; j < dimension; j++) {
      if(i != j) {
      generator[i*dimension+j] = jumpChain[i*dimension+j] * leavingRates[j];
      } else {
        generator[i*dimension+j] = -leavingRates[j];
      }
    }
  }
  return generator;
}

void printInterval(const double *G, const double *initialPosition, size_t dimension, double initialT, double finalT, double timeStep) {
  //made some bad structure decisions so kind of need to throw around some copies for this to work (also wanted as many inputs to be const and return outparameters)
  double *B = malloc(dimension * dimension * sizeof(double));
  mcpy(G, dimension*dimension, B);
  addMatrix(B, dimension, B, (timeStep - 1));
  double *A;
  mExponetial(B, dimension, &A, _PRECISION_);
  free(B);

  double *position = malloc(dimension * sizeof(double));
  mcpy(initialPosition, dimension, position);
  double *nextPosition = malloc(dimension * sizeof(double));
  for(double i = initialT; i < finalT; i += timeStep) {  
    cblas_dgemv(CblasRowMajor, CblasNoTrans, dimension, dimension, 1, A, dimension, position, 1, 0, nextPosition, 1);
    printf("P(%lf) = [", i);
    for(size_t j = 0; j < (dimension - 1); j++) {
      printf("%lf, ", position[j]);
    }
    printf("%lf]\n", position[dimension - 1]);
    mcpy(nextPosition, dimension, position);
  }

  free(nextPosition);
  free(position);
}

int main(int argc, char *argv[]) {
  
  double jumpChain[] = {
    0, 0, 0.5,
    1, 0, 0.5,
    0, 1, 0
  };
  double leavingRates[] = {2, 1, 3}; 
  size_t dimension = 3;
  double initialPosition[] = {1, 0, 0};
  
  double *generator = findGenerator(jumpChain, leavingRates, dimension);
  printMatrix(generator, 3);

  for(double i = 0; i < 10; i+=0.3) {
    double *finalPosition = getTime(generator, initialPosition, dimension, i);
    printf("P(%lf) = [%lf, %lf, %lf]\n", i, finalPosition[0], finalPosition[1], finalPosition[2]);
    free(finalPosition);
  }

  puts("******************");

  // double *finalPosition = getTime(generator, initialPosition, dimension, 0);
  // double holder[3] = {finalPosition[0], finalPosition[1], finalPosition[2]};
  // for(double i = 0; i < 10; i+=0.3) {
  //   free(finalPosition);
  //   finalPosition = getTime(generator, holder, dimension, 0.3);
  //   holder[0] = finalPosition[0];
  //   holder[1] = finalPosition[1];
  //   holder[2] = finalPosition[2];
  //   printf("P(%lf) = [%lf, %lf, %lf]\n", i, finalPosition[0], finalPosition[1], finalPosition[2]);
  // }
  // free(finalPosition);
  //this would be the same as doing mexponential(t=0.3)
  //then multiplying by v, printing, multiplying by new v


  printInterval(generator, initialPosition, dimension, 0, 10, 0.3);


  printf("Calculated algebraically, the stable position should be\n");
  printf("[3/19, 12/19, 4/19] or\n");
  printf("[%lf, %lf, %lf]\n", (double)3/19, (double)12/19, (double)4/19);
  

  free(generator);
  return 0;
}



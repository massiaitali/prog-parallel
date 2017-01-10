#include <stdio.h>
int main(int argc, char const *argv[])
{
  int A[2][2] = {{1,6},{2,9}}; 
 int B[2][1]= {{9},{4}};
 int C[2][1];
 int N = 2, M = 2, P = 1; 
 int I, J, K; 

// calcul
 for (I=0; I<N; I++)
     for (J=0; J<P; J++)
         {
          C[I][J]=0;
          for (K=0; K<M; K++)
               C[I][J] += A[I][K]*B[K][J];
         }
// Resultat
 printf("Vecteurs resultat  :\n");
 for (I=0; I<N; I++)
    {
     for (J=0; J<P; J++)
          printf("%7d", C[I][J]);
     printf("\n");
    }
  return 0;
}
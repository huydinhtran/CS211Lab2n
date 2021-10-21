#include "../include/for_you_to_do.h"

int get_block_size(){
    //return the block size you'd like to use 
    /*add your code here */
    return 128;
  
}

/**
 * 
 * this function computes LU factorization
 * for a square matrix
 * 
 * syntax 
 *  
 *  input : 
 *      A     n by n , square matrix
 *      ipiv  1 by n , vector
 *      n            , length of vector / size of matrix
 *  
 *  output :
 *      return -1 : if the matrix A is singular (max pivot == 0)
 *      return  0 : return normally 
 * 
 **/


int mydgetrf(double *A, int *ipiv, int n) 
{
    /* add your code here */
    int maxind;
    double max;
    int temps;
    double tempv[n];
    int i, t, j, k;
    int a, b, c;
    for (i = 1 ; i < n-1 ; i++){
        maxind = i; 
        max = abs(A[i*n+i]); 
        for (t = i+1 ; t <= n ; t++){
            if (abs(A[t*n+i]) > max ) {
                maxind = t; 
                max = abs(A[t*n+i]); 
            }
        }
    }
    
    if (max==0) 
        return -1; 
    else 
        if (maxind != i ) {
            temps = ipiv[i]; 
            ipiv[i] = ipiv[maxind]; 
            ipiv[maxind] = temps;
            for (a=0 ; a <=n ; a++) tempv[a] = A[i*n+a]; 
            for (b=0 ; b <=n ; b++) A[i*n+b] = A[maxind*n+b]; 
            for (c=0 ; c <=n ; c++) A[maxind*n+c] = tempv[c];
        }
    
    for (j = i+1 ; j <= n ; j++) {
        A[j*n+i] = A[j*n+i]/A[i*n+i];
        for (k = i+1 ; k <=n ; k++)
            A[j*n+k] = A[j*n+k] - A[j*n+i] * A[i*n+k]; 
    } 
    
    return 0;
}

/**
 * 
 * this function computes triangular matrix - vector solver
 * for a square matrix . according to lecture slides, this
 * function computes forward AND backward subtitution in the
 * same function.
 * 
 * syntax 
 *  
 *  input :
 *      UPLO  'L' or 'U' , denotes whether input matrix is upper
 *                         lower triangular . ( forward / backward
 *                         substitution )
 * 
 *      A     n by n     , square matrix
 * 
 *      B     1 by n     , vector
 * 
 *      ipiv  1 by n     , vector , denotes interchanged index due
 *                                  to pivoting by mydgetrf()
 * 
 *      n                , length of vector / size of matrix
 *  
 *  output :
 *      none
 * 
 **/
void mydtrsv(char UPLO, double *A, double *B, int n, int *ipiv)
{
    /* add your code here */
    //forward substitution for lower triangular
    double y[n], x[n];

    if (UPLO == 'L'){
        int i;
        int a;
        double sum;
        y[1] = B[ipiv[1]];
        for (i=2 ; i<=n ; i++){
            for (a=1 ; a<=i-1 ; a++){
                sum += y[a] * A[i*m+a];
            }
            y[i] = B[ipiv[i]] - sum;
        }
    }
    //backward substitution for upper triangular
    if (UPLO == 'U'){
        int i;
        int a;
        double sum;
        x[n] = y[n] / A[n*n+n];
        for (i=n-1 ; i<=1 ; i--){
            for (a=i+1 ; a <= n ; a++){
                sum += x[a] * A[i*n+a];
            }
            x[i] = (y[i] - sum) / A[i*n+i];
        }
    }
    return;
}

/**
 * 
 * Same function as what you used in lab1, cache_part4.c : optimal( ... ).
 * 
 **/
void mydgemm(double *A, double *B, double *C, int n, int i, int j, int k, int b)
{
    /* add your code here */
    /* please just copy from your lab1 function optimal( ... ) */
    int i1, j1, k1;
    for (i = 0; i < n; i+=b)
        for (j = 0; j < n; j+=b)
            for (k = 0; k < n; k+=b)
             /* B x B mini matrix multiplications */
                for (i1 = i; i1 < i+b; i1++)
                    for (j1 = j; j1 < j+b; j1++)
                        for (k1 = k; k1 < k+b; k1++){
                            C[i*n + j]         = A[i*n + k] * B[k*n + j] + A[i*n + k+1] * B[(k+1)*n + j] + C[i*n + j];                                       
                            C[(i+1)*n + j]     = A[(i+1)*n + k] * B[k*n + j] + A[(i+1)*n + k+1] * B[(k+1)*n + j] + C[(i+1)*n + j];                    
                            C[i*n + (j+1)]     = A[i*n + k] * B[k*n + (j+1)] + A[i*n + k+1] * B[(k+1)*n + (j+1)] + C[i*n + (j+1)];                    
                            C[(i+1)*n + (j+1)] = A[(i+1)*n + k] * B[k*n + (j+1)] + A[(i+1)*n + k+1] * B[(k+1)*n + (j+1)] + C[(i+1)*n + (j+1)];
                        } 
    return;
}

/**
 * 
 * this function computes LU decomposition
 * for a square matrix using block gepp introduced in course
 * lecture .
 * 
 * just implement the block algorithm you learned in class.
 * 
 * syntax 
 *  
 *  input :
 *      
 * 
 *      A     n by n     , square matrix
 * 
 *    
 * 
 *      ipiv  1 by n     , vector , denotes interchanged index due
 *                                  to pivoting by mydgetrf()
 * 
 *      n                , length of vector / size of matrix
 *     
 *      b                , block size   
 *  output :
 *      return -1 : if the matrix A is singular (max pivot == 0)
 *      return  0 : return normally 
 * 
 **/
int mydgetrf_block(double *A, int *ipiv, int n, int b) 
{
    return 0;
}


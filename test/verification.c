/**
 * @file verification.c
 * author Yujia Zhai (yzhai015@ucr.edu)
 * @brief 
 * @version 0.1
 * @date 2019-10-07
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#include "../include/lu_test.h"
#include "../include/util.h"
#include "../include/lu_functions.h"
#include "../include/for_you_to_do.h"

/**
 * @brief test all functions
 * 
 * @return int 
 */

int test_all_lu_functions()
{
    int block_size=get_block_size();
    int ni, nList[] = {1000,2000,3000,4000,5000};
//     int ni, nList[] = {4};
    for (ni = 0; ni < sizeof(nList) / sizeof(nList[0]); ni++) {
        int n = nList[ni], i, j;

        // feel free to modify the block size by yourself.
        if (n % block_size !=0){
            n+=block_size-(n%block_size);
        } 

        printf(" n = %d \n", n);
        double *A1, *A2, *B1, *B2, *A3, *B3;
        double t0, t1;

        A1 = (double *) malloc(sizeof(double) * n * n);
        B1 = (double *) malloc(sizeof(double) * n);

        A2 = (double *) malloc(sizeof(double) * n * n);
        B2 = (double *) malloc(sizeof(double) * n);

        A3 = (double *) malloc(sizeof(double) * n * n);
        B3 = (double *) malloc(sizeof(double) * n);
        
        if ( randomize_matrix(A1, n, n) ) return -1;
        if ( randomize_matrix(B1, n, 1) ) return -1;

        if ( matrix_copy(A2, A1, n, n) ) return -1;
        if ( matrix_copy(A3, A1, n, n) ) return -1;

        if ( matrix_copy(B2, B1, n, 1) ) return -1;
        if ( matrix_copy(B3, B1, n, 1) ) return -1;

        t0 = get_sec();    
        lapack_lu(A1, B1, n);
        t1 = get_sec();
        printf("Elapsed time, MKL LAPACK: %lf seconds\n", t1 - t0);

        
        t0 = get_sec();    
        naive_lu(A2, B2, n);
        t1 = get_sec();
        printf("Elapsed time, naive LU: %lf seconds\n", t1 - t0);

        if (verify_matrix(A1, A2, n, n) || verify_matrix(B1, B2, n, 1))
            printf("my naive LU is incorrect.\n");

        t0 = get_sec();    
        block_lu(A3, B3, n,  block_size);
        t1 = get_sec();
        printf("Elapsed time, block LU: %lf seconds\n", t1 - t0);

        if (verify_matrix(A1, A3, n, n) || verify_matrix(B1, B3, n, 1))
            printf("my block LU is incorrect.\n");
        
        
//         int a, b;
//         printf("A1\n");
//         for (a = 0; a < n; a++){
//             for (b = 0; b < n; b++){
//                 printf("%f ", A1[a*n+b]);
//             }
//             printf("\n");
//         }
//         printf("\n");
        
    
//         printf("B1\n");
//         for (a = 0; a < n; a++) printf("%f ", B1[a]);
//         printf("\n"); printf("\n");
        
        
//         printf("A3\n");
//         for (a = 0; a < n; a++){
//             for (b = 0; b < n; b++){
//                 printf("%f ", A3[a*n+b]);
//             }
//             printf("\n");
//         }
//         printf("\n");
        
    
//         printf("B3\n");
//         for (a = 0; a < n; a++) printf("%f ", B3[a]);
//         printf("\n"); printf("\n");
        

        free(A1);
        free(A2);
        free(A3);
        free(B1);
        free(B2);
        free(B3);
    }

    return 0;
}

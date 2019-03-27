/**
* Copyright 2014 NVIDIA Corporation.  All rights reserved.
*
* Please refer to the NVIDIA end user license agreement (EULA) associated
* with this source code for terms and conditions that govern your use of
* this software. Any use, reproduction, disclosure, or distribution of
* this software and related documentation outside the terms of the EULA
* is strictly prohibited.
*
*/

#if !defined(_GEMV_H_)
#define _GEMV_H_

#include <cuda.h> // CUDA_VERSION
#include <cublas_v2.h>
#include "error_util.h"

//#define DISABLE_GEMV

void gemm(cublasHandle_t cublasHandle,int numCpy, int m, int n, double alpha, 
            const double *A, const double *x,
                               double beta, double *y)
{
//		std::cout<<"\nSTART gemm double"<<std::endl<<std::flush;
    checkCublasErrors( cublasDgemm (cublasHandle, 
                      CUBLAS_OP_T,
                      CUBLAS_OP_N,
                      n,
                      numCpy,
                      m,
                      &alpha, 
                      A, 
                      m,
                      x,
                      m, 
                      &beta, 
                      y,
                      n) );
//		std::cout<<"\nEND gemm"<<std::endl<<std::flush;

}
void gemv(cublasHandle_t cublasHandle, int m, int n, double alpha, 
            const double *A, const double *x,
                               double beta, double *y)
{
//		std::cout<<"\nSTART gemv"<<std::endl<<std::flush;
#ifdef DISABLE_GEMV
    checkCublasErrors( cublasDgemm (cublasHandle, 
                      CUBLAS_OP_T,
                      CUBLAS_OP_N,
                      n,
                      1,
                      m,
                      &alpha, 
                      A, 
                      m,
                      x,
                      m, 
                      &beta, 
                      y,
                      m) );
#else
    checkCublasErrors( cublasDgemv(cublasHandle, CUBLAS_OP_T,
                                  m, n,
                                  &alpha,
                                  A, m,
                                  x, 1,
                                  &beta,
                                  y, 1) );    
#endif
//		std::cout<<"\nEND gemv"<<std::endl<<std::flush;
};

void gemm(cublasHandle_t cublasHandle,int numCpy, int m, int n, float alpha, 
            const float *A, const float *x,
                               float beta, float *y)
{
//		std::cout<<"\nSTART gemm float"<<std::endl<<std::flush;
    checkCublasErrors( cublasSgemm (cublasHandle, 
                      CUBLAS_OP_T,
                      CUBLAS_OP_N,
                      n,
                      numCpy,
                      m,
                      &alpha, 
                      A, 
                      m,
                      x,
                      m, 
                      &beta, 
                      y,
                      n) );
//		std::cout<<"\nEND gemm"<<std::endl<<std::flush;
}
void gemv(cublasHandle_t cublasHandle, int m, int n, float alpha, 
            const float *A, const float *x,
                               float beta, float *y)
{
//		std::cout<<"\nSTART gemv"<<std::endl<<std::flush;
#ifdef DISABLE_GEMV
    checkCublasErrors( cublasSgemmBatched (cublasHandle, 
                      CUBLAS_OP_T,
                      CUBLAS_OP_N,
                      n,
                      1,
                      m,
                      &alpha, 
                      A, 
                      m,
                      x,
                      m, 
                      &beta, 
                      y,
                      m) );
#else
    checkCublasErrors( cublasSgemv(cublasHandle, CUBLAS_OP_T,
                                  m, n,
                                  &alpha,
                                  A, m,
                                  x, 1,
                                  &beta,
                                  y, 1) );    
#endif
//		std::cout<<"\nEND gemv"<<std::endl<<std::flush;
};

#if defined(CUDA_VERSION) && (CUDA_VERSION > 7000)

#if (CUDA_VERSION < 8000)
#define  CUDA_R_16F CUBLAS_DATA_HALF
#endif
//I dont find cublasSgemmEx's batched version
/*void gemm(cublasHandle_t cublasHandle,int numCpy, int m, int n, float alpha, 
            const half1 **A, const half1 **x,
                               float beta, half1 **y)
{
		std::cout<<"\nSTART gemm half1"<<std::endl<<std::flush;
    checkCublasErrors( cublasHgemmBatched  ( cublasHandle, 
                                      CUBLAS_OP_T,
                                      CUBLAS_OP_N, 
                                      n,
                                      1,
                                      m,
                                      &alpha, 
                                      A,  
                                      m,
                                      x,
                                      m, 
                                      &beta, 
                                      y,
                                      m,numCpy) );
		std::cout<<"\nEND gemm"<<std::endl<<std::flush;
};*/
void gemv(cublasHandle_t cublasHandle, int m, int n, float alpha, 
            const half1 *A, const half1 *x,
                               float beta, half1 *y)
{
//		std::cout<<"\nSTART gemv"<<std::endl<<std::flush;
    checkCublasErrors( cublasSgemmEx  ( cublasHandle, 
                                      CUBLAS_OP_T,
                                      CUBLAS_OP_N, 
                                      n,
                                      1,
                                      m,
                                      &alpha, 
                                      A,  
                                      CUDA_R_16F,
                                      m,
                                      x,
                                      CUDA_R_16F,
                                      m, 
                                      &beta, 
                                      y,
                                      CUDA_R_16F,
                                      m) );
//		std::cout<<"\nEND gemv"<<std::endl<<std::flush;
};
#endif

#endif  // _GEMV_H_

#ifndef __KALMAN_H
#define __KALMAN_H
#include "sys.h"


#define T  1
#define M  100

extern float X[2][1];

void kalman(float S);

/*
		matrix[0][0] = matrix[0][0] + F[0][0] * P[0][0];
		matrix[0][0] = matrix[0][0] + F[0][1] * P[1][0];
		matrix[0][1] = matrix[0][1] + F[0][0] * P[0][1];
		matrix[0][1] = matrix[0][1] + F[0][1] * P[1][1];
		matrix[1][0] = matrix[1][0] + F[1][0] * P[0][0];
		matrix[1][0] = matrix[1][0] + F[1][1] * P[1][0];
		matrix[1][1] = matrix[1][1] + F[1][0] * P[0][1];
		matrix[1][1] = matrix[1][1] + F[1][1] * P[1][1];
		即
		matrix[0][0] = matrix[0][0] + F[0][0] * P[0][0] + F[0][1] * P[1][0];
		matrix[0][1] = matrix[0][1] + F[0][0] * P[0][1] + F[0][1] * P[1][1];
		matrix[1][0] = matrix[1][0] + F[1][0] * P[0][0] + F[1][1] * P[1][0];
		matrix[1][1] = matrix[1][1] + F[1][0] * P[0][1] + F[1][1] * P[1][1];
		
		
		matrix1[0][0] = matrix1[0][0] + matrix[0][0] * FT[0][0];
		matrix1[0][0] = matrix1[0][0] + matrix[0][1] * FT[1][0];
		matrix1[0][1] = matrix1[0][1] + matrix[0][0] * FT[0][1];
		matrix1[0][1] = matrix1[0][1] + matrix[0][1] * FT[1][1];
		matrix1[1][0] = matrix1[1][0] + matrix[1][0] * FT[0][0];
		matrix1[1][0] = matrix1[1][0] + matrix[1][1] * FT[1][0];
		matrix1[1][1] = matrix1[1][1] + matrix[1][0] * FT[0][1];
		matrix1[1][1] = matrix1[1][1] + matrix[1][1] * FT[1][1];
		即
		matrix1[0][0] = matrix1[0][0] + matrix[0][0] * FT[0][0] + matrix[0][1] * FT[1][0];
		matrix1[0][1] = matrix1[0][1] + matrix[0][0] * FT[0][1] + matrix[0][1] * FT[1][1];
		matrix1[1][0] = matrix1[1][0] + matrix[1][0] * FT[0][0] + matrix[1][1] * FT[1][0];
		matrix1[1][1] = matrix1[1][1] + matrix[1][0] * FT[0][1] + matrix[1][1] * FT[1][1];
		代入上一式得
		matrix1[0][0] = matrix1[0][0] + matrix[0][0] * FT[0][0] + (matrix[0][1] + F[0][0] * P[0][1] + F[0][1] * P[1][1]) * FT[1][0];
		matrix1[0][1] = matrix1[0][1] + matrix[0][0] * FT[0][1] + (matrix[0][1] + F[0][0] * P[0][1] + F[0][1] * P[1][1]) * FT[1][1];
		matrix1[1][0] = matrix1[1][0] + matrix[1][0] * FT[0][0] + (matrix[1][1] + F[1][0] * P[0][1] + F[1][1] * P[1][1]) * FT[1][0];
		matrix1[1][1] = matrix1[1][1] + matrix[1][0] * FT[0][1] + (matrix[1][1] + F[1][0] * P[0][1] + F[1][1] * P[1][1]) * FT[1][1];
		即
		matrix1[0][0] = matrix1[0][0] + matrix[0][0] * FT[0][0] + matrix[0][1] * FT[1][0] + F[0][0] * P[0][1] * FT[1][0] + F[0][1] * P[1][1] * FT[1][0];
		matrix1[0][1] = matrix1[0][1] + matrix[0][0] * FT[0][1] + matrix[0][1] * FT[1][1] + F[0][0] * P[0][1] * FT[1][1] + F[0][1] * P[1][1] * FT[1][1];
		matrix1[1][0] = matrix1[1][0] + matrix[1][0] * FT[0][0] + matrix[1][1] * FT[1][0] + F[1][0] * P[0][1] * FT[1][0] + F[1][1] * P[1][1] * FT[1][0];
		matrix1[1][1] = matrix1[1][1] + matrix[1][0] * FT[0][1] + matrix[1][1] * FT[1][1] + F[1][0] * P[0][1] * FT[1][1] + F[1][1] * P[1][1] * FT[1][1];
*/

#endif

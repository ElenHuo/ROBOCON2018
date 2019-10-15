#include "kalman.h"

float P[2][2] = {{1, 0}, {0, 1}};
float X[2][1] = {{0}, {0}};
int F[2][2] = {{1, T}, {0, 1}};
int FT[2][2] = {{1, 0}, {T, 1}};
float Q[2][2] = {{0.001, 0},{ 0, 0.001}};
int H[1][2] = {1 , 0};
int HT[2][1] = {{1} ,{0}};
int R = 1;
int I[2][2] = {{1, 0},{0,1}};
float X_[2][1];
float P_[2][2];
float K[2][1] = {{0}, {0}};


void kalman(float S)
{
	float matrix[M][M];
	float matrix1[M][M];
	
	X_[0][0] = X[0][0] + X[1][0] * T;
	X_[1][0] = X[1][0];
	
	//协方差转移
	for (int i = 0;i<2;i++)
	{
		for (int j = 0;j<2;j++) {
			matrix[i][j] = 0;
		}
	}
	for (int i = 0;i<2;i++)
	{
		for (int j = 0;j<2;j++)
		{
			for (int k = 0;k<2;k++)
			{
				matrix[i][j] = matrix[i][j] + F[i][k] * P[k][j];
			}
		}
	}

	for (int i = 0;i<2;i++)
	{
		for (int j = 0;j<2;j++) 
		{
			matrix1[i][j] = 0;
		}
	}
	for (int i = 0;i<2;i++)
	{
		for (int j = 0;j<2;j++)
		{
			for (int k = 0;k<2;k++)
			{
				matrix1[i][j] = matrix1[i][j] + matrix[i][k] * FT[k][j];
			}
		}
	}

	for (int i = 0;i<2;i++)
	{
		for (int j = 0;j<2;j++)
		{
			P_[i][j] = matrix1[i][j] + Q[i][j];
		}
	}
	
	//协方差转移
	//计算K
	for (int i = 0;i<2;i++)
	{
		for (int j = 0;j<2;j++) {
			matrix[i][j] = 0;
		}
	}
	for (int i = 0;i<2;i++)
	{
		for (int j = 0;j<1;j++)
		{
			for (int k = 0;k<2;k++)
			{
				matrix[i][j] = matrix[i][j] + P[i][k] * HT[k][j];
			}
		}
	}

	for (int i = 0;i<2;i++)
	{
		for (int j = 0;j<2;j++) {
			matrix1[i][j] = 0;
		}
	}
	for (int i = 0;i<1;i++)
	{
		for (int j = 0;j<1;j++)
		{
			for (int k = 0;k<2;k++)
			{
				matrix1[i][j] = matrix1[i][j] + H[i][k] * matrix[k][j];
			}
		}
	}

	K[0][0] = matrix[0][0] / (matrix1[0][0] + R);
	K[1][0] = matrix[1][0] / (matrix1[0][0] + R);
	//计算K
	
	//X
	X[0][0] = X_[0][0] + K[0][0] * (S - X_[0][0]);
	X[1][0] = X_[1][0] + K[1][0] * (S);
	//X

	//P
	for (int i = 0;i<2;i++)
	{
		for (int j = 0;j<2;j++) {
			matrix[i][j] = 0;
		}
	}
	for (int i = 0;i<2;i++)
	{
		for (int j = 0;j<2;j++)
		{
			for (int k = 0;k<1;k++)
			{
				matrix[i][j] = matrix[i][j] + K[i][k] * H[k][j];
			}
		}
	}

	for (int i = 0;i<2;i++)
	{
		for (int j = 0;j<2;j++) {
			matrix1[i][j] = 0;
		}
	}
	for (int i = 0;i<2;i++)
	{
		for (int j = 0;j<2;j++)
		{
			for (int k = 0;k<2;k++)
			{
				matrix1[i][j] = matrix1[i][j] + matrix[i][k] * P_[k][j];
			}
		}
	}

	for (int i = 0;i<2;i++)
	{
		for (int j = 0;j<2;j++)
		{
			P[i][j] = P_[i][j] - matrix1[i][j];
		}
	}
	//P
	
}


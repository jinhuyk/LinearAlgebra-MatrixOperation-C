/* written by JinHuyk. Mun */


#include <stdio.h>
#include <stdlib.h>
#include <math.h>


//functions for convenience
double** allocateMemory(int m, int n); 
void releaseMemory(double** A, int m);
void printMatrix(double** A, int m, int n, char name[]);

//functions to implement in prj0 
double** transposeMatrix(double** A, int m, int n);
double** normalizeVector(double** v, int n);
double calculateLength(double** v, int n);
double** scaleMatrix(double** A, int m, int n, double c);
double** multiplyTwoMatrices(double** A, int m, int n, double** B, int l, int k);
double** addTwoMatrices(double** A, int m, int n, double** B, int l, int k);



int main() {
	double** A;
	double** H;
	double** B;
	double** C;
	double** v; //vector
	double** w;	//vector
	double** T_A;
	double** S_A;
	double** MultiAC;
	double** SumAB;

	int m = 4; 	//number of rows
	int n = 3;	//number of columns
	int l = 4;
	int k = 3;
	int p = 3;
	int q = 4;
	double c = 5.0;
	A = allocateMemory(m,n);
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			A[i][j] = (double) i*j+1;
	B = allocateMemory(l, k);
	for (int i = 0; i < l; i++)
		for (int j = 0; j < k; j++)
			B[i][j] = (double)i + j*2;
	C = allocateMemory(p, q);
	for (int i = 0; i < p; i++)
		for (int j = 0; j < q; j++)
			C[i][j] = (double)i + j * 2;
	v = allocateMemory(m, 1);
	for (int i = 0; i < m; i++)
		v[i][0] = i;
	
	printf("2. (a) ");
	
	printMatrix(A,m,n,"A");
	printMatrix(B, l, k, "B");
	printMatrix(C, p, q, "C");
	printMatrix(v, m, 1, "v");

	T_A = transposeMatrix(A, m, n);
	printMatrix(T_A, n, m, "A_transposed");
	

	w = normalizeVector(v,m);
	printMatrix(w,m,1,"v_normalized");

	printf("\n(the length of v) = %f\n", calculateLength(v, m));
	
	S_A = scaleMatrix(A, m, n, c);
	printMatrix(S_A, m, n, "A_scaled(5.0)");

	MultiAC = multiplyTwoMatrices(A, m, n, C, p, q);
	printMatrix(MultiAC, m, q, "multiply A and C");

	SumAB = addTwoMatrices(A, m, n, B, l, k);
	printMatrix(SumAB, m, n, "add A and B");


	//2. 
	printf("\n\n2. (b) \n");

	A = allocateMemory(2, 2);
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			A[i][j] = (i+1)*(j+1);
		}
	}
	H = allocateMemory(2, 2);
	H[0][0] = 1/sqrt(2);
	H[0][1] =1/sqrt(2);
	H[1][0] = 1 / sqrt(2);
	H[1][1] = -1 / sqrt(2);


	printMatrix(A, 2, 2, "A");
	B = multiplyTwoMatrices(
			multiplyTwoMatrices(
				transposeMatrix(H, 2, 2),2, 2, A, 2, 2), 2, 2,H, 2, 2);
	printMatrix( B,2,2,"B");

	C = multiplyTwoMatrices(
			multiplyTwoMatrices(H, 2, 2, B, 2, 2), 2, 2, 
				transposeMatrix(H, 2, 2), 2, 2);
	printMatrix(C,2,2,"C");
	
	
	
	
	
	releaseMemory(A, m);
	releaseMemory(B, 2);
	releaseMemory(C, 2);
	releaseMemory(H, 2);
	releaseMemory(v, m);
	releaseMemory(w, m);
	releaseMemory(T_A, m);
	releaseMemory(S_A, m);
	releaseMemory(MultiAC, m);
	releaseMemory(SumAB, m);


	return 0;
}

double** allocateMemory(int m, int n) {
	double** A;
	A = (double**) malloc(sizeof(double*) * m);
	for (int i = 0; i < m; i++) {
		A[i] = (double*) malloc(sizeof(double) * n);
	}
	return A;
}


void releaseMemory(double** A, int m) {
	for (int i = 0; i < m; i++)
		free(A[i]);
}

void printMatrix(double** A, int m, int n, char name[]) {
	printf("\n  %s = \n", name);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++)
			printf("%8.3lf ", A[i][j]);
		printf("\n");
	}
}

double** transposeMatrix(double **A, int m, int n) {
	double** B = allocateMemory(n, m);

	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			B[j][i] = A[i][j];	
	
	return B;
}	

double** normalizeVector(double** v, int m) {
	double** w;
	double len = 0.0;

	for (int i = 0; i < m; i++)
		len += v[i][0]*v[i][0];	
	len = sqrt(len);

	w = allocateMemory(m,1);
	for (int i = 0; i < m; i++)
		w[i][0] = v[i][0]/len;
	
	return w;
}
double calculateLength(double** v, int m) {
	double length = 0.0;
	for (int i = 0; i < m; i++) {
		length += v[i][0] * v[i][0];
	}
	length = sqrt(length);
	return length;
}

double** scaleMatrix(double** A, int m, int n, double c) {
	double** S = allocateMemory(m, n);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			S[i][j] = A[i][j]*c;
		}
	}
	return S;

}
double** multiplyTwoMatrices(double** A, int m, int n, double** B, int l, int k) {
	if (n != l) {
		return NULL;
	}
	double** S = allocateMemory(m, k);
	double temp;

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < k; j++) {
			temp = 0.0;
			for (int p = 0; p < n; p++) {
				temp += A[i][p] * B[p][j];
			}
			S[i][j] = temp;
		}
	}
	return S;
}

double** addTwoMatrices(double** A, int m, int n, double** B, int l, int k) {
	if (m != l || n != k) {
		return NULL;

	}
	double** S = allocateMemory(m, n);
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			S[i][j] = A[i][j] + B[i][j];
		}
	}
	return S;
}

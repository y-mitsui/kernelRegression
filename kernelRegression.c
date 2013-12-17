#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <math.h>
#include "kernelRegression.h"
#include "error.h"
#include "mesch12b/matrix.h"
#include "mesch12b/matrix2.h"

double kernel(double *x1,double *x2,int num,double gamma){
	VEC *xVector,*yVector,*diffVector;
	int i;

	xVector=v_get(num);
	memcpy(xVector->ve,x1,sizeof(double)*num);
	yVector=v_get(num);
	memcpy(yVector->ve,x2,sizeof(double)*num);

	diffVector=v_sub(xVector,yVector,NULL);

	double sum=0.0;
	for(i=0;i<num;i++){
		sum+=diffVector->ve[i]*diffVector->ve[i];
	}

	v_free(diffVector);
	v_free(xVector);
	v_free(yVector);
	
	return exp(-gamma*sum);
}

// kernelRegression
// x:data
// dimention: x's dimention
// y: label of x 
// num: number of data
// result: coeffience
double *kernelRegression(double **x,int dimention,double *y,int num,double gamma,double regilarization){
	VEC *label;
	MAT *gram,*ident,*inv;
	int i,j;
	double *result;

	ident = m_get(num,num);
	label = v_get(num);
	memcpy(label->ve,y,sizeof(double)*num);
	gram = m_get(num,num);
	ident = m_get(num,num);
	for(i=0;i<num;i++){
		for(j=0;j<num;j++){
			gram->me[i][j]=kernel(x[i],x[j],dimention,gamma);
		}
	}
	inv=m_add(gram,sm_mlt(regilarization,m_ident(ident),NULL),NULL);
	inv=m_inverse(inv,NULL); //memory leak.
	VEC *coefficient=v_get(num);
	mv_mlt(inv,label,coefficient);
	result=malloc(sizeof(double)*num);
	memcpy(result,coefficient->ve,sizeof(double)*num);

	m_free(ident);
	m_free(gram);
	m_free(inv);
	v_free(label);
	v_free(coefficient);
	return result;
}



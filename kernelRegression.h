double *kernelRegression(double **x,int dimention,double *y,int num,double amma,double regilarization);
double kernel(double *x1,double *x2,int num,double gamma);

#define dfopen(fp,fileName,mode,errorProcess)	{	\
		if((fp=fopen(fileName,mode))==NULL){	\
			perror(fileName);		\
			errorProcess;			\
		}					\
}

#define dmalloc(p,size)	{				\
		if((p=malloc(size))==NULL){		\
			fatalError("out of memory");	\
		}					\
}

#define dcalloc(p,size)	{				\
		if((p=calloc(1,size))==NULL){		\
			fatalError("out of memory");	\
		}					\
}

#define dstrdup(p,str)	{				\
		if((p=strdup(str))==NULL){		\
			fatalError("out of memory");	\
		}					\
}


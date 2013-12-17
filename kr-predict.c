#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "kernelRegression.h"
#include "error.h"

int readTestFile(const char *fileName,double ***x){
	FILE *fp;
	int line,clumn,i;
	double **xData;
	char buf[1024],*p;

	dfopen(fp,fileName,"r",exit(EXIT_FAILURE));

	fgets(buf,sizeof(buf),fp);
	strtok(buf,"\t ");
	line=clumn=1;
	while(strtok(NULL,"\t ")) clumn++;
	while(fgets(buf,sizeof(buf),fp)) line++;
	rewind(fp);
	
	xData=malloc(sizeof(double)*line);
	for(line=0;fgets(buf,sizeof(buf),fp);line++){
		dmalloc(xData[line],sizeof(double)*clumn);
		xData[line][0]=atof(strtok(buf,"\t "));
		for(i=1;i<clumn;i++){
			if((p=strtok(NULL,"\t "))==NULL) fatalError("breaken csv file.");
			xData[line][i]=atof(p);
		}
	}

	fclose(fp);

	*x=xData;
	return line;
}
static void usage(void){
	fprintf(stderr,"Usage: kr-predict [model file] [test file]\n");
  	exit(1);
}
int main(int argc,char **argv){
	int i,j;
	double sum;
	double **x,**xTest,*coefficient,gamma;
	int dataNum,num,xDimention;
	FILE *fp;
	char buf[1024];

	if(argc!=3) usage();

	dfopen(fp,argv[1],"r",exit(EXIT_FAILURE));
	fgets(buf,sizeof(buf),fp);
	num=atoi(strtok(buf,","));
	xDimention=atoi(strtok(NULL,","));
	gamma=atof(strtok(NULL,","));
	rewind(fp);

	coefficient=malloc(sizeof(double)*num);
	x=malloc(sizeof(double*)*num);

	fgets(buf,sizeof(buf),fp);
	for(i=0;i<num;i++){
		fgets(buf,sizeof(buf),fp);
		coefficient[i]=atof(buf);
	}
	for(i=0;i<num;i++){
		fgets(buf,sizeof(buf),fp);
		x[i]=malloc(sizeof(double)*xDimention);
		x[i][0]=atof(strtok(buf,"\t "));
		for(j=1;j<xDimention;j++){
			x[i][j]=atof(strtok(NULL,"\t "));
		}
	}
	fclose(fp);

	dataNum=readTestFile(argv[2],&xTest);
	
	for(i=0;i<dataNum;i++){
		sum=0.0;
		for(j=0;j<num;j++){
			sum+=coefficient[j]*kernel(xTest[i],x[j],xDimention,gamma);
		}
		for(j=0;j<xDimention;j++){
			printf("%lf ",xTest[i][j]);
		}
		printf("%lf\n",sum);
	}
	return EXIT_SUCCESS;
}

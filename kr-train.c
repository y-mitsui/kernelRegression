#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "kernelRegression.h"
#include "error.h"

int readDataFile(const char *fileName,double ***x,double **y,int *xDimention){
	FILE *fp;
	int line,clumn,i;
	double **xData,*yData;
	char buf[1024],*p;

	dfopen(fp,fileName,"r",exit(EXIT_FAILURE));

	fgets(buf,sizeof(buf),fp);
	strtok(buf,"\t ");
	line=clumn=1;
	while(strtok(NULL,"\t ")) clumn++;
	while(fgets(buf,sizeof(buf),fp)) line++;
	rewind(fp);
	
	xData=malloc(sizeof(double)*line);
	yData=malloc(sizeof(double)*line);
	for(line=0;fgets(buf,sizeof(buf),fp);line++){
		dmalloc(xData[line],sizeof(double)*clumn-1);
		xData[line][0]=atof(strtok(buf,"\t "));
		for(i=1;i<clumn-1;i++){
			if((p=(char*)strtok(NULL,"\t "))==NULL)
				fatalError("breaken csv file.");
			xData[line][i]=atof(p);
		}
		yData[line]=atof(strtok(NULL,"\t "));
	}

	fclose(fp);

	*x=xData;
	if(xDimention) *xDimention=clumn-1;
	if(y) *y=yData;
	return line;
}
static void usage(void){
	fprintf(stderr,"Usage: kr-train [option] [data file] [model file (output)]\n");
	fprintf(stderr," -g [gamma (using kernel function)]\n");
	fprintf(stderr," default 1.0\n");
	fprintf(stderr," -r [regularization]\n");
	fprintf(stderr," default 1.0\n");
  	exit(1);
}

int main(int argc,char **argv){
	int i,j;
	double **x,*y,*coefficient;
	double gamma,regilarization;
	int xDimention,dataNum;

	int		ch;
	extern char	*optarg;
	extern int	optind, opterr;


	gamma=1.0;
	regilarization=0.1;
	while ((ch = getopt(argc, argv, "g:r:")) != -1){
    		switch (ch){
    		case 'g':
			gamma=atof(optarg);
			break;
		case 'r':
			regilarization=atof(optarg);
			break;
		default:
		      usage();
		}
	}
	argc -= optind;
	argv += optind;

	if(argc!=2) usage();

	dataNum=readDataFile(argv[0],&x,&y,&xDimention);
	coefficient=kernelRegression(x,xDimention,y,dataNum,gamma,regilarization);

	FILE *fp;
	
	dfopen(fp,argv[1],"w",exit(EXIT_FAILURE));
	fprintf(fp,"%d,%d,%lf\n",dataNum,xDimention,gamma);
	for(i=0;i<dataNum;i++){
		fprintf(fp,"%lf\n",coefficient[i]);
	}
	for(i=0;i<dataNum;i++){
		for(j=0;j<xDimention;j++){
			fprintf(fp,"%lf ",x[i][j]);
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
	
	return EXIT_SUCCESS;
}

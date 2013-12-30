kernelRegression
================

A kernel regression tool.

install:  

you require gmake  

> make  

usage:  
> kr-train.exe data.txt model.txt
> kr-predict.exe model.txt test.txt > result.txt
> gnuplot
> splot "result.txt"

data.txt format:  
x1[TAB]x2[TAB] ...  y  
x1[TAB]x2[TAB] ...  y  
.  
.  
.  

test.txt format:  
x1[TAB]x2[TAB] ...  
x1[TAB]x2[TAB] ...  
.  
.  
.  

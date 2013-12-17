CFLAGS=-Wall -g
LOADLIBES=-lm
all:kr-train kr-predict
kr-train: kernelRegression.o error.o meschach.a
kr-predict: kernelRegression.o error.o meschach.a

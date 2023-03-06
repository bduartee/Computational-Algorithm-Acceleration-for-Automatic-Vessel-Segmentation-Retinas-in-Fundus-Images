#ifndef KERNEL_H
#define KERNEL_H
#include <iostream>

using namespace std;

class KERNEL 
{ 

public: 
  	
    KERNEL();

    void calcula(double *data, double *data_mask, double *data_S, double *data_So, int pn_lins, int pn_cols);
    
    void inversao(double *data, int pn_lins, int pn_cols);

private:
	int media ;
	int krn[15][15];
    double *angSo;
	
    double get_value(double *data, int x, int y, int n_cols) {
		return *(data + x * n_cols + y);}

    void set_value(double *data, int i, int j, int n_cols, double& value) {
		*(data + i * n_cols + j) = value;}
	
	//arrays l0,l15,l30,l45,l60,l75, l90,l105, l120, l135, l150, l165;
	//arrays3 lort0,lort15,lort30,lort45,lort60,lort75, lort90,lort105, lort120, lort135, lort150, lort165;

    void Linhas(int ang, double *data);				
	

    void orto (int ang, double *data);

   
    double  media_linhas(double *data, double *ptr, int pn_lin, int pn_cols);

    double media_linhas1(double *data, double *ptr, int pn_lin, int pn_cols);

}; 

#endif //KERNEL_H

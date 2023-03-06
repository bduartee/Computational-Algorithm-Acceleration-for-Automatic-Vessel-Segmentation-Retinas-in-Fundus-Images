#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <cmath>

#include "kernel1.h"
//using namespace std;



  	
    KERNEL::KERNEL(){
    	
    }

void KERNEL::inversao(double *data, int pn_lins, int pn_cols){
	double valor, inv;
	int n_lins=pn_lins;
	int n_cols=pn_cols;
	for (int i=0;i<n_lins; ++i){
		for (int j=0; j<n_cols; ++j){
			valor=get_value(data, i, j, n_cols);
			inv=255 - valor;
			set_value(data, i, j, n_cols, inv);
		}
	}
}


void KERNEL::Linhas(int ang, double *data){//Criar as linhas para qualquer angulo

	float angr = (ang*M_PI)/180;
	float m = tan(angr);
	int n_cols = 15;
	double valor;

//=====Criar os arrays para receber as coords=====//

	for (int i=0; i<15; i++){
		int a = i+1; //Para calcular o valor da ordenada
		valor = int(i);
		if (ang <= 45 or ang >=135){
				
			float y = ((-8 * m)+8) + m*a;

			double x = int(round(y)-1); //x
			set_value(data, int(0),i, n_cols, x);

			set_value(data, int(1), i, n_cols, valor); //y
		} 
		else{
				
			float x = ((a-8)/m) + 8;
			set_value(data, 0,i, n_cols, valor); //x

			double y = int(round(x)-1);
			set_value(data, 1, i, n_cols, y); //y
		}
	}
}



	

void KERNEL::orto (int ang, double *data){ //criar as ortogonais para qualquer angulo
	
	double x= 7;
	double y= 7;
	int n_cols = 3;

	set_value(data, 0, 0, n_cols, x);
	set_value(data, 1, 0, n_cols, y);

	double coord6 = 6;
	double coord8 = 8;
	double coord7 = 7;

	
	if (ang < 22.5 or ang > 157.5 ){

		set_value(data,0, 1, n_cols, coord6);
		set_value(data, 0, 2, n_cols, coord8);
		set_value(data,1, 1, n_cols, coord7);
		set_value(data,1,2, n_cols, coord7);
	}
		
	if (ang > 22.5 and ang < 67.5 ){

		set_value(data,0, 1, n_cols, coord6);
		set_value(data, 0, 2, n_cols, coord8);
		set_value(data,1, 1, n_cols, coord8);
		set_value(data,1,2, n_cols, coord6);
	}
		
	if (ang > 67.5 and ang < 112.5 ){

		set_value(data,0, 1, n_cols, coord7);
		set_value(data, 0, 2, n_cols, coord7);
		set_value(data,1, 1, n_cols, coord6);
		set_value(data,1,2, n_cols, coord8);
	}

	if (ang > 112.5 and ang < 157.5 ){

		set_value(data,0, 1, n_cols, coord6);
		set_value(data, 0, 2, n_cols, coord8);
		set_value(data,1, 1, n_cols, coord6);
		set_value(data,1,2, n_cols, coord8);
	}
}

   
double  KERNEL::media_linhas(double *data, double *ptra, int pn_lin, int pn_cols){
	
	double sum, media_lin;
	int n_lin= pn_lin;
	int n_cols= pn_cols;
	int K= n_lin;
	int x,y;
	sum = 0;
	
	for (int i=0; i<15; i++){ //I < N_COLS

		x = (int) get_value(ptra, 0, i, n_cols);
		

		y = (int) get_value(ptra,1 , i, n_cols);
		

		sum += get_value(data,x,y,n_cols);
		
}

		media_lin = sum / K;
		
	return media_lin;
 
}

double KERNEL::media_linhas1(double *data, double *ptrb, int pn_lins, int pn_cols){ //Recebe um array de 3
	int x, y;
	double sum, media_ortogonais;
	int K= 3;
	sum = 0;
	int n_lin= pn_lins;
	int n_cols= pn_cols;

	//double *ptr = &linhas;

	for (int i=0; i<3; i++){
		x = (int) get_value(ptrb, 0, i, n_cols);
		//x = linhas.xx[i];
		y = (int) get_value(ptrb, 1, i, n_cols);
		//y = linhas.yy[i];
		sum += get_value(data,x,y,n_cols); 
		//cout << "x: "<<x<<" ; y: "<<y<<" ;Valor: "<<arr[x][y]<<" ; sum: "<<sum<<endl; 
	}
	media_ortogonais = (sum)/K;
	

	return media_ortogonais; 
}


void KERNEL::calcula(double *data, double *data_mask, double *data_S, double *data_So, int pn_lins, int pn_cols){
	
	int kernel=15;
	double valor, S, So;
	int a,b, m_k = (int)(kernel / 2.0);

	double n_cols = pn_cols;
	int n_lins = pn_lins;
	double KernelS[15][15]= {};
	double *ptrkernel = &KernelS[0][0];
	double sum;
	double Nn;
	int p= 7;
	int q= 7;

	//double *angSo;
	//preenche();



	double linhas0[2][15]={};
	double *ptr0= &linhas0[0][0];
	Linhas(0, ptr0);


	double linhas15[2][15]={};
	double *ptr15= &linhas15[0][0];
	Linhas(15, ptr15);


	double linhas30[2][15]={};
	double *ptr30= &linhas30[0][0];
	Linhas(30, ptr30);


	double linhas45[2][15]={};
	double *ptr45= &linhas45[0][0];
	Linhas(45, ptr45);


	double linhas60[2][15]={};
	double *ptr60= &linhas60[0][0];
	Linhas(60, ptr60);


	double linhas75[2][15]={};
	double *ptr75= &linhas75[0][0];
	Linhas(75, ptr75);


	double linhas90[2][15]={};
	double *ptr90= &linhas90[0][0];
	Linhas(90, ptr90);


	double linhas105[2][15]={};
	double *ptr105= &linhas105[0][0];
	Linhas(105, ptr105);


	double linhas120[2][15]={};
	double *ptr120= &linhas120[0][0];
	Linhas(120, ptr120);


	double linhas135[2][15]={};
	double *ptr135= &linhas135[0][0];
	Linhas(135, ptr135);


	double linhas150[2][15]={};
	double *ptr150= &linhas150[0][0];
	Linhas(150, ptr150);


	double linhas165[2][15]={};
	double *ptr165= &linhas165[0][0];
	Linhas(165, ptr165);


	double otg0[2][3]={};
	double *p0= &otg0[0][0];
	orto(0, p0);


	double otg15[2][3]={};
	double *p15= &otg15[0][0];
	orto(15, p15);


	double otg30[2][3]={};
	double *p30= &otg30[0][0];
	orto(30, p30);


	double otg45[2][3]={};
	double *p45= &otg45[0][0];
	orto(45, p45);


	double otg60[2][3]={};
	double *p60= &otg60[0][0];
	orto(60, p60);


	double otg75[2][3]={};
	double *p75= &otg75[0][0];
	orto(75, p75);


	double otg90[2][3]={};
	double *p90= &otg90[0][0];
	orto(90, p90);


	double otg105[2][3]={};
	double *p105= &otg105[0][0];
	orto(105, p105);


	double otg120[2][3]={};
	double *p120= &otg120[0][0];
	orto(120, p120);


	double otg135[2][3]={};
	double *p135= &otg135[0][0];
	orto(135, p135);


	double otg150[2][3]={};
	double *p150= &otg150[0][0];
	orto(150, p150);


	double otg165[2][3]={};
	double *p165= &otg165[0][0];
	orto(165, p165);




	double andala[15][15]={};
	double *datala= &andala[0][0];

	double m0;
	double m15;
	double m30;
	double m45;
	double m60;
	double m75;
	double m90;
	double m105;
	double m120;
	double m135;
	double m150;
	double m165;
	


	
	for(int i = p; i < n_lins - p; ++i){
		for(int j = p; j < n_cols - p; ++j) {
			if (get_value(data_mask,i,j,n_cols) > 0){
			
				sum=0;
				for (int n = i-p, r=0; n < i+p+1 && r<15; ++n, ++r){
                	for (int m = j-p, l=0; j < j+p+1 && l<15; ++m, ++l ){
					
						valor = get_value(data, n, m, n_cols);
						sum+= valor;
						//sKernelS[r][l]=valor;
						set_value(ptrkernel,r,l,15,valor);
					}
				}
			
			

			Nn= sum/(kernel*kernel);

	
				
			
			m0= media_linhas(ptrkernel, ptr0,15,15);
			m15= media_linhas(ptrkernel, ptr15,15,15);
			m30= media_linhas(ptrkernel, ptr30,15,15);
			m45= media_linhas(ptrkernel, ptr45,15,15);
			m60= media_linhas(ptrkernel, ptr60,15,15);
			m75= media_linhas(ptrkernel, ptr75,15,15);
			m90= media_linhas(ptrkernel, ptr90,15,15);
			m105= media_linhas(ptrkernel, ptr105,15,15);
			m120= media_linhas(ptrkernel, ptr120,15,15);
			m135= media_linhas(ptrkernel, ptr135,15,15);
			m150= media_linhas(ptrkernel, ptr150,15,15);
			m165= media_linhas(ptrkernel, ptr165,15,15);


			double maxis[12] = {m0,m15,m30,m45,m60,m75,m90,m105,m120,m135,m150,m165}; //RETORNA UM MAXIMO
			double *angs[12] = {p0,p15,p30,p45,p60,p75,p90,p105,p120,p135,p150,p165};
			double maximo= m0;		
	
			for (int i=0; i<12; ++i){ //Ver o máximo
				maximo= max(maxis[i], maximo);
												}
			
				for (int j=0; j<12; j++){ //Ver que ângulo utilizar no calculo das ortogonais, depois de descobrir a linha com média maxima
					if (maximo == maxis[j]){
						angSo = angs[j];
					}
				}


			double medSo = media_linhas1(ptrkernel, angSo ,15, 15);
			S= maximo - Nn;
			So= medSo - Nn;
			set_value(data_S,i,j,n_cols,S);
			set_value(data_So,i,j,n_cols,So);
			maximo=0;
			medSo=0;

			}
		}
	}
}

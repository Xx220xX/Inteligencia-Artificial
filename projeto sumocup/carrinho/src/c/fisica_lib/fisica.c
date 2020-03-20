#include "fisica.h"
#include <math.h>


/**
Essa biblioteca em c é para cálculos pesados de fisica entre dois objetos quadrados
*/

#include <stdio.h>
#include<stdlib.h>
void plotClear(){
	FILE *f = fopen("plot/values.js","w");
	fprintf(f,"var value = [];");
	fclose(f);
	
}

double PmultInte(P u, P v){
	return u.x*v.x + u.y*v.y;
}
void plotLine(double x0,double y0,double x1, double y1){
	FILE *f = fopen("plot/values.js","a");
	fprintf(f,"\n value.push({x0:%lf,y0:%lf,x1:%lf,y1:%lf,});\n",x0,-y0,x1,-y1);
	fclose(f);
	
}
void plotShow(){
	system("start plot/index.html");
}


double dabs(double n){return n<0 ?-n:n;}
P Psub(P p1, P p2){
	P ans = {p1.x-p2.x,p1.y-p2.y};
	return ans;
}
P Padd(P p1, P p2){
	P ans = {p1.x+p2.x,p1.y+p2.y};
	return ans;
}
P PmulEsc(P p,double escalar){
	p.x*=escalar;
	p.y*=escalar;
	return p;
}
double Pangle(P p){
	return atan2(p.y, p.x);
}
P PbyAngle(double radAngle){
	P ans = {cos(radAngle),sin(radAngle)};
	return ans;
}
double Pabs(P p){
	return sqrt(p.x*p.x+p.y*p.y);
}
P PsetMag(P p,double mag){
	p = PmulEsc(p, mag/Pabs(p));
	return p;
}

double retaParalelas(P d1,P d2){
	d1 = PmulEsc(d1, 1.0/Pabs(d1));
	d2 = PmulEsc(d2, 1.0/Pabs(d2));
	return d1.x==d2.x && d1.y == d2.y;
	
}
double distanciaPontoReta( P q, P d, P p){
	P p2 = Padd(p,d);
	double  a = p.y - p2.y,
			b = p.x - p2.x,
			c = p.x*p2.y - p2.x*p.y;
	//printf("%g %g %g\n",a,b,c);
	return dabs(a*q.x+b*q.y+c)/sqrt(a*a+b*b);
	
}
double distanciaRetas(P d1,P p1,P d2, P p2){
	
	if(!retaParalelas(d1,d2))return 0;
	/**
	 a x + b y + c = 0
	 x = t 
	 y = - c/b - a/b t 
	 
   1 x  y  1 x
	 x0 y0 1
   1 x1 y1 1 x1
	
	x*(y0 - y1) + y*(x1 - x0) + (x0*y1 -y0*x1) 
	
    
	*/
    
	double  a = d2.x,
			b = -d2.y,
			c = p2.x*(p2.y+d2.y) - (p2.x+d2.x)*p2.y,
	        cl = p1.x*(p1.y+d1.y) - (p1.x+d1.x)*p1.y;
	return dabs(c-cl)/sqrt(a*a+b*b);
}

Solucao encontroDeRetas(P d1,P p1, P d2,P p2){
	/** encontrar solucao por Cramer
	
	[D1] t + [P1] = [D2] s + [P2]

	d1x t + p1x =  d2x s + p2x
	d1y t + p1y =  d2y s + p2y
	
	d1x t  =  d2x s + p2x - p1x
	d1y t  =  d2y s + p2y - p1yp1y
	
	
	d1x t  -  d2x s = p2x - p1x
	d1y t  -  d2y s = p2y - p1y
	
	| d1x  - d2x |   |t s|   | p2x - p1x |
	| d1y  - d2y | *       = | p2y - p1.y  |
	*/
	double delta,deltat,deltas;
	delta = - d1.x *d2.y + d2.x*d1.y;
	deltat = (p2.x -p1.x)*-d2.y+d2.x *(p2.y -p1.y);
	deltas = d1.x *(p2.y -p1.y) - (p2.x - p1.x)*d1.y;
	Solucao s ; 
	s.existe = 1;
	if(dabs(delta)==0.0 )s.existe = -1; 
	else if(isinf(delta) || isnan(delta))s.existe = -2;
	else {
		s.s = deltas/delta;
		s.t = deltat/delta;
		if(isinf(s.t)||isnan(s.t)){
			s.ans.x = d2.x*s.s +p2.x;
			s.ans.y = d2.y*s.s +p2.y;
		}else{
			s.ans.x = d1.x*s.t +p1.x;
			s.ans.y = d1.y*s.t +p1.y;
		}
	}
	return s;
}

P ProtEixo(P p,double radAngle){
	p.x = p.x*cos(radAngle) + p.y*sin(radAngle);
	p.y = -p.x*sin(radAngle) + p.y*cos(radAngle);
	return p;
}




void getConers(P coners[4],P c1, P p1,double larg,double  comp){
	coners[0] = PsetMag( ProtEixo((p1,c1) ,-atan2(larg/2,comp/2)), sqrt(larg*larg+comp*comp)/2);
	coners[1] = PsetMag( ProtEixo((p1,c1) ,+atan2(larg/2,comp/2)), sqrt(larg*larg+comp*comp)/2);
	coners[2] = Psub(c1,coners[0]);
	coners[3] = Psub(c1,coners[1]);	
}


Solucao colidiuQuadrado(P c1,P p1,P c2,P p2,double largura,double comprimento){
	/** equacionar matriz e resolver por cramer
	@hipoteses 
	  - quadrado possui 2 Retas e 4 condicoes 
	*/
	
/**	equacao quadrado
	[d1] t + [p1] = reta 1 
	[d2] s + [p1] = reta 2
	t E (a,b)
	s E (c,d)
	
	come�a em p1 e � 90� a d1
	
	^ da1
	|
	|
	|
	pa ----- > da2
*/	
	P pa,pa1;
	int i ,dentro;
	double angle,angleb;
	P coners1b[4], coners2b[4];
	P coners1[4], coners2[4];
	
	getConers(coners1,c1,p1,largura,comprimento);
	getConers(coners2,c1,p1,largura,comprimento);
	copyVet(coners1b,coners2,0,4);copyVet(coners2b,coners1,0,4);
	
	//  considerando carrinho 1
	// transladar para pa
	// pa � o elemento 3 do vetor
	pa = coners1[2];
	pa1 = coners1b[2];
	for(i=0;i<4;i++){
		coners1[i] = Psub(coners1[i],pa);
		coners2[i] = Psub(coners2[i],pa);
		coners1b[i] = Psub(coners1b[i],pa1);
		coners2b[i] = Psub(coners2b[i],pa1);
		
	}
	// rotacionar para o angulo do vetor  conners[3] referente a da2
	angle = Pangle(coners1[3]);
	angleb = Pangle(coners1b[3]);
	for(i=0;i<4;i++){
		coners1[i] = ProtEixo(coners1[i],angle);
		coners2[i] = ProtEixo(coners2[i],angle);
	}
	// agora verificar se algum dos cantos do segundo esta dentro do primeiro
	int reta = 0;
	
	double angulo_do_segundo;
	P diretor_segundo,ponto_segundo;
	P center_2;
	Solucao s[4]={0};
	int menor=-1;
	for(i=0;i<4;i++){
		if(coners2[i].x<0 || coners2[i].x> largura)continue; //esta fora
		if(coners2[i].y<0 || coners2[i].y> comprimento)continue;// esta fora 
		// esta dentro
		
		diretor_segundo = ProtEixo(Psub(Psub(p2,c2),pa),angle);
		ponto_segundo = ProtEixo(Psub(p2,pa),angle);
		center_2 = ProtEixo(Psub(c2,pa),angle);
		s[0] = encontroDeRetas(coners1[0],coners1[1],diretor_segundo,ponto_segundo);
		s[1] = encontroDeRetas(coners1[1],coners1[2],diretor_segundo,ponto_segundo);
		s[2] = encontroDeRetas(coners1[2],coners1[3],diretor_segundo,ponto_segundo);
		s[3] = encontroDeRetas(coners1[3],coners1[0],diretor_segundo,ponto_segundo);
		for(i=0;i<4;i++){
			if(menor==-1 && s[i].existe)menor=i;
			if(s[i].existe && DISTANCE(s[i].ans,center_2)<DISTANCE(s[menor].ans,center_2)){
				menor = i;
			}
		}
		printf("%d\n",menor);
		s[menor].ans = Padd(ProtEixo(s[menor].ans,-angle),pa);
		return s[menor];
	}
	Solucao no = {0};
	return no;
	
}



#include <stdio.h>
int f_main(){
	P c1 ={ 1,0},
	  p1 = {8,9},
	  c2 = {9,3},
	  p2 = {19,3};
	Solucao s = colidiuQuadrado(c1,p1,c2,p2,10,10);
	printf("%d\n(%g,%g)\n",s.existe,s.ans.x,s.ans.y);
	 return 0;
}




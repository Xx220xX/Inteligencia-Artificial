#include <math.h>

#define or ||
#define and &&

/**
Essa biblioteca em c é para cálculos pesados de fisica entre dois objetos quadrados
*/




typedef struct {double x,y;} P;

typedef struct {P ans ;double t,s;int existe;} Solucao ;



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
	
	começa em p1 e é 90° a d1
	
	^ da1
	|
	|
	|
	pa ----- > da2
*/	
	Solucao  s;
	P da1=Psub(p1,c1),da2;
	 da2 = PbyAngle(Pangle(da1)-M_PI/2.0);//volta 90°
	P pa =Padd(c1, PsetMag(PbyAngle(Pangle(da1)+M_PI*(5/4)) ,sqrt(largura*largura+comprimento*comprimento)/2));
	
	
	
	return s;
	
}

#include <stdio.h>
int main(){
	P c1 ={ 1,0},
	  p1 = {0,0},
	  c2 = {1,0},
	  p2 = {0,3};
	Solucao s;
	long long int i;
	double d;
	//for(i=0;i<=80000000000000;i++){
	 d = distanciaRetas(c1,p1,c2, p2);
	// }
	 
	 //printf("%lld \n",i);
	 printf("%g ",d);
	//printf("%d  ( %g , %g ) t=%g ,s =%g\n",s.existe,s.ans.x,s.ans.y,s.s,s.t); 
	 return 0;
}

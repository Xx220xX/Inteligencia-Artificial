import Constantes as CTE
class Carro:
    largura = 0.1
    comprimento = 0.1
    img = None
    def __init__(self,c,p):
        self.c = c
        self.p = p
        
        self.alive = True
        
    def show(self):
        if not self.alive :
            return
        angle = atan2(self.p.y - self.c.y,self.p.x - self.c.x) 
        with push():
            translate(self.c.x*CTE.SCL,self.c.y*CTE.SCL)
            rotate(angle);
            rect(-Carro.largura/2*CTE.SCL,-Carro.comprimento/2*CTE.SCL,Carro.largura*CTE.SCL,Carro.comprimento*CTE.SCL)
            circle(0,-Carro.comprimento/2*CTE.SCL,0.02*CTE.SCL)    
            #image(Carro.img,-Carro.largura/2*CTE.SCL,-Carro.comprimento/2*CTE.SCL,Carro.largura*CTE.SCL,Carro.comprimento*CTE.SCL)
            

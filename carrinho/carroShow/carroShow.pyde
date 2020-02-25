import Carro ,Stream,Constantes as CTE


carros_a,carros_b = None, None
def setup():
    size(800,800)
    carros_a,carros_b = Stream.load("../stream/init.car")
   
def draw():
    background(255)
    translate(0,CTE.SCL)
    circle(CTE.RAIO*CTE.SCL,-CTE.RAIO*CTE.SCL,2*CTE
           .RAIO*CTE.SCL)
    for c in carros_a:
        c.show()
    Stream.update("../stream/update.car",carros_a,carros_b)

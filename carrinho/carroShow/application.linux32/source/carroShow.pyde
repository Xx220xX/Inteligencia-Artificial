import Carro ,Stream,Constantes as CTE


carros = []
def setup():
    size(800,800)
    # carros = Stream.load("../stream/init.car")
   
def draw():
    background(255)
    translate(0,CTE.SCL)
    circle(CTE.RAIO*CTE.SCL,-CTE.RAIO*CTE.SCL,2*CTE
           .RAIO*CTE.SCL)
    for c in carros:
        c.show()
    Stream.update("../stream/update.car",carros)

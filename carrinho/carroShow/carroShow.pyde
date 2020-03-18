import Carro ,Stream,Constantes as CTE


carros_a,carros_b = {}, {}
def setup():
    size(800,800)
    global carros_a
    global carros_b
    carros_a,carros_b = Stream.load("../stream/init.car")
def draw():
    background(255)
    translate(0,CTE.SCL)
    circle(CTE.RAIO*CTE.SCL,-CTE.RAIO*CTE.SCL,2*CTE
           .RAIO*CTE.SCL)
    carros_a[0].show()
    #print(carros_a[0])
    #line(0.41*CTE.SCL,-0.94*CTE.SCL,0.42*CTE.SCL,-0.89*CTE.SCL)
    for v in carros_a:
        carros_a[v].show()
        carros_b[v].show()
    Stream.update("../stream/update.car",carros_a,carros_b)

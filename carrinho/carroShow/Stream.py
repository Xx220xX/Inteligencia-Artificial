import Carro
def load(file):
    carros_a,carros_b = {},{}
    with open(file,'r') as f:
        for line in f:
            eval(line)
    return carros_a,carros_b

def update(file,carros_a,carros_b):
    try:
        with open(file,'r') as f:
            for line in f:
                eval(line)
        with open(file,'w') as f:
            f.write("read")
    except Exception as e:
        print(e)
        

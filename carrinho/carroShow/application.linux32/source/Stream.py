import Carro
def load(file):
    carros = []
    with open(file,'r') as f:
        for line in f:
            carros.append(eval(line));
    return line

def update(file,carros):
    try:
        with open(file,'r') as f:
            for line in f:
                carros.append(eval(line));
        with open(file,'w') as f:
            f.write("read")
    except Exception as e:
        print(e)
        

import Carro
def load(file):
    carros_a,carros_b = {},{}
    with open(file,'r') as f:
        for line in f:
            line = line.strip().split(',')
            if len(line)<5: continue
            for i in range(2,len(line)):
                line[i] = float(line[i])
            if line[0]=='a':
                carros_a[int(line[1])] = Carro.Carro(PVector(line[2],line[3]),PVector(line[4],line[5]))
            else:
                carros_b[int(line[1])] = Carro.Carro(PVector(line[2],line[3]),PVector(line[4],line[5]))            
    return carros_a,carros_b

def update(file,carros_a,carros_b):
    try:
        with open(file,'r')as f:
            for line in f:
                line = line.strip().split(',')
                if len(line)<6: continue
                for i in range(2,6):
                    line[i] = float(line[i])
                if line[0]=='a':
                    carros_a[int(line[1])].update(PVector(line[2],line[3]),PVector(line[4],line[5]),int(line[6])==1)
                else:
                    carros_b[int(line[1])].update(PVector(line[2],line[3]),PVector(line[4],line[5]),int(line[6])==1)            
    except Exception as e:
        print(e)
        

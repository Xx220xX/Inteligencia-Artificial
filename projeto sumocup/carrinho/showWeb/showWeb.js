var carrosa = [];
var carrosb = [];

function setup() {
  createCanvas(800,800);
  Stream.load(("../stream/init.car"),carrosa,carrosb);
}


function draw() {
  background(255);
  translate(0,SCL);
  circle(RAIO*SCL,-RAIO*SCL,2*RAIO*SCL);
  for (let i = 0; i<carrosa.length; i++) {
    carrosa[i].show();
    carrosb[i].show();
  }
  Stream.load(("../stream/update.car"),carrosa,carrosb);
}

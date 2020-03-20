var carrosa = [];
var carrosb = [];
let imgs = [null,null];

function setup() {
  imgs[0] = loadImage('assets/teste.png');
  imgs[1] = loadImage('assets/c2.jpg');
  console.log('SETUP');
  createCanvas(800,800);
  Stream.load(("../stream/init.car"),carrosa,carrosb);
}


function draw() {
  background(255);
  image(imgs[0],0,0,100,100);
  /*translate(0,SCL);
  circle(RAIO*SCL,-RAIO*SCL,2*RAIO*SCL);
  for (let i = 0; i<carrosa.length; i++) {
    carrosa[i].show();
    carrosb[i].show();
  }
  Stream.load(("../stream/update.car"),carrosa,carrosb);*/

}

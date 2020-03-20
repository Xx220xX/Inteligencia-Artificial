var im = 0;
class Carro {
  constructor(c, p) {      
    this.c = c;
    this.p = p;
    this.alive = true;
    this.img = imgs[im];
    im++;
    if(im==2)im=0;
  }
  toString() {
    return "c(%.2f,%.2f) p(%.2f,%.2f)%s".format(this.c.x, this.c.y, this.p.x, this.p.y, this.alive ? "vivo" : "morto");
  }
  update(c,p,alive){
    this.c = c;
    this.p = p;
    this.alive = alive;
  }
  show() {
    //if (!this.alive) { return null;}
    //console.log(this.c);
   let angle = atan2(-this.p.y + this.c.y,this.p.x - this.c.x)+ PI/2;
    push();
    if(this.alive){stroke(color(255,0,0));}
    translate(this.c.x*SCL, -this.c.y*SCL);
    rotate(angle);
    //rect(-largura/2*SCL, -comprimento/2*SCL, largura*SCL, comprimento*SCL);
    image(this.img,-largura/2*SCL, -comprimento/2*SCL, largura*SCL, comprimento*SCL);
    circle(0, -comprimento/2*SCL, 0.02*SCL);
    pop();

  }
}

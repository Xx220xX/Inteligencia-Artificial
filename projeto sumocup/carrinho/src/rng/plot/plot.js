
function setup() {
  createCanvas(800, 800);
  console.log(value);
}


function draw() {
  translate(width/2,height/2);
  for(let i = 0 ;i<value.length;i++){
    line(value[i].x0,value[i].y0,value[i].x1,value[i].y1);
  }
}

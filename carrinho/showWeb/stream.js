var s_loading = false;
function mload(ca,cb){
 return (result)=>{
   s_loading = false;
   for(let i=0;i<result.length;i++){
     //console.log(result[i]);
     eval(result[i]);
   }
   //eval('result');
   
 };
}

var Stream = {
  load :
(f, ca, cb)=> {
  console.log('try load');
  if (s_loading) {
    return null;
  }
  s_loading = true;
  loadStrings(f, mload(ca, cb));
}
};

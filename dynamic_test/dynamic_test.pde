
int dynamicMode = 0;
PImage monsterImg;
float posX, posY;
float speed;
float prevX, prevY;


void setup(){
  size(1280,720);
  frameRate(30);
  monsterImg = loadImage("littlemonster.png");
  posX = width+100;
  posY = (height/2)-40;
  textSize(16);

}

void draw(){
  
  
  background(0);
  
  
  switch(dynamicMode){
    
    
    // linear motion -------------------------------------------------------
    case 1: 
      text("linear motion - use mouse to adjust speed", 10, 25); 
      speed = mouseY/10.0; 
      posX -= speed;
      if(posX<-100){
        posX = width+100;  
      }
      println("linear");
      image(monsterImg,posX,posY,110,110);
    break;
    
    
    // lerp x -------------------------------------------------------
    case 2:
      text("lerp - use mouse to adjust speed", 10, 25);
      if(posX<-100){
        posX = width+100;  
      }
      speed = mouseY/5000.0; 
      posX = lerp(posX,-150,speed);
      image(monsterImg,posX,posY,110,110);
    break;
    
    
    // sin y -------------------------------------------------------
    case 3: 
      text("sin y - use mouse to adjust speed", 10, 25);
      speed = mouseY/10.0;
      if(posX<-100){
        posX = width+100;  
      }
      posY = (sin(millis()/100.0)*100) + ((height/2)-40);
      posX -= speed;
      image(monsterImg,posX,posY,110,110);
    break;
    
    
    //sin x and turnaround -------------------------------------------------------
    case 4: 
      text("sin x and turnaround", 10, 25);
      if(posX<-100){
        posX = width+100;  
      }
      posX = width+300 - abs((sin(millis()/1100.0)*(width-200)));
      if(prevX<posX){
        pushMatrix();
          scale(-1,1);
          image(monsterImg,-posX-110,posY,110,110);
        popMatrix(); 
      }else{
         image(monsterImg,posX,posY,110,110); 
      }
      prevX = posX;
    break;
    
    
    //lerp to mouse -------------------------------------------------------
    case 5: 
      text("follow your mouse with lerp", 10, 25); 
      posX = lerp(posX,mouseX,0.05);
      posY = lerp(posY,mouseY,0.05);
      image(monsterImg,posX,posY,110,110);
    break;
    
    
    // lerp and rotate -------------------------------------------------------
    case 6: 
      text("follow your mouse with lerp and rotate (would look better with a symmetrical character)", 10, 25); 
      posX = lerp(posX,mouseX,0.05);
      posY = lerp(posY,mouseY,0.05);
      float dx = posX-prevX;
      float dy = posY-prevY;
      float angle = atan2(dy,dx);
      pushMatrix();
        translate(posX,posY);
        rotate(angle);
        image(monsterImg,0,0,110,110);
      popMatrix();
      prevX = posX;
      prevY = posY;
    break;
    
    
    // boing boing -------------------------------------------------------   
    case 7: 
      text("boing boing - use mouse to adjust speed", 10, 25); 
      if(posX<-100){
        posX = width+100;  
      } 
      speed = mouseY/10.0;
      posY = (height-110) - (abs((sin(millis()/400.0))*200));
      posX -= speed;
      image(monsterImg,posX,posY,110,110);
    break;
    
    // circle -------------------------------------------------------   
    case 8: 
      posX = width/2 + cos(millis()/100.0)*mouseY;
      posY = height/2 + sin(millis()/100.0)*mouseY;
      image(monsterImg,posX,posY,110,110);
    break;
    
    
    // default -------------------------------------------------------
    default: 
      text("keys 1-7 for different dynamics", 10, 25); 
      println("default");
    break;
  }
  
  
}


void keyPressed(){
  
posX = width+100;
posY = (height/2)-40;
  
switch(key) {
  case '1':
    dynamicMode = 1; 
    break;
  case '2':
    dynamicMode = 2;  
    break;
  case '3':
    dynamicMode = 3;  
    break;
  case '4':
    dynamicMode = 4;  
    break;
  case '5':
    dynamicMode = 5;  
    break;
  case '6':
    dynamicMode = 6;  
    break;
  case '7':
    dynamicMode = 7;  
    break;
  case '8':
    dynamicMode = 8;  
    break;
  default:
    break;
}
 
  
}

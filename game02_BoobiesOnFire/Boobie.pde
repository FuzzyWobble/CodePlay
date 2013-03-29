class Boobie{
  
  PImage imgNormal, imgMad;
  float posX, posY;
  boolean mad;
  float catchUpSpeed = 0.01;
  Animation boobieMad;
  float boobCenterX, boobCenterY;
  float time = 0.0;
  
  Boobie(){
    imgNormal = loadImage("boobie_normal.png"); 
    imgMad = loadImage("boobie_mad.png"); 
    boobieMad = new Animation("boobie_mad_", 2);
    mad = false;
  }
  
  void xeno(float catchX, float catchY){
    posX = catchUpSpeed * catchX + (1-catchUpSpeed) * posX; 
    posY = catchUpSpeed * catchY + (1-catchUpSpeed) * posY; 
    boobCenterX = posX+17;
    boobCenterY = posY+17;
  }
  
  void draw(){
    //float posX_n = noise(time)*posX;
    //float posY_n = noise(time)*posY;
    //time += random(0.005,0.007);
    if(mad){
      boobieMad.display(posX, posY);
    }else{
      image(imgNormal, posX, posY); 
    }
  }
  
}

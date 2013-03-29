class Character{
  
  Animation characterL, characterR; //sprite facing left, sprite facing right
  float posX, posY; //position of character
  boolean dirRL; //right it true, left is false
  float catchUpSpeed = 0.50;
  float fireCenterX, fireCenterY;
  
  
  float playerBoxOffsetY = 1;
  float playerBoxW = 27;
  float playerBoxH = 53;
  float playerBoxOffsetX; //depends on direction
  
  float fireBoxOffsetY = 6;
  float fireBoxW = 15;
  float fireBoxH = 25;
  float fireBoxOffsetX; //depends on direction

  
  void draw(){
    //posX = mouseX;
    //posY = mouseY;
    if(dirRL){//right
      you.characterR.display(posX, posY);
    }else{//left
      you.characterL.display(posX, posY);
    }
  }
  
  void drawBnds(){
    noFill();
    strokeWeight(1);
    stroke(0,255,0);
    if(dirRL){ //right
      fireBoxOffsetX = 45;
      playerBoxOffsetX = 0;
    }else{ //left
      fireBoxOffsetX = 0;
      playerBoxOffsetX = 32;
    }
    //draw fire box
    rect(posX+fireBoxOffsetX,posY+fireBoxOffsetY,fireBoxW,fireBoxH);
    //draw player box
    rect(posX+playerBoxOffsetX,posY+playerBoxOffsetY,playerBoxW,playerBoxH);
    
    fireCenterX = posX+fireBoxOffsetX+7.5;
    fireCenterY = posY+fireBoxOffsetY+12.5;
    
  }
  
  void getDirection(float currentX){
    if(currentX<posX){ //left
      dirRL = false;
    }else if(currentX>posX){
      dirRL = true;
    }else{
      dirRL = dirRL; 
    }
  }
  
  void xeno(float catchX, float catchY){
    posX = catchUpSpeed * catchX + (1-catchUpSpeed) * posX; 
    posY = catchUpSpeed * catchY + (1-catchUpSpeed) * posY; 
  }

}

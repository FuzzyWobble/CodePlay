//boobies on fire
//fuzzywobble.com

Character you;
float lerpX, lerpY;
ArrayList boobies;
Boobie aBoobie;


void setup() {
  size(1280,720);
  background(255);
  frameRate(24);
  
  //boobies
  boobies = new ArrayList();
  for(int i=0;i<50;i++){
    aBoobie = new Boobie();
    aBoobie.posX = random(50,1230);
    aBoobie.posY = random(50,670);
    boobies.add(aBoobie);
  }
  
  //setup 'YOU'
  you = new Character();
  you.characterL = new Animation("character1_sm_l_", 2);
  you.characterR = new Animation("character1_sm_r_", 2);
  you.posX = 100;
  you.posY = 100;
  you.dirRL = true; //face right
}

void draw(){background(255);

  for(int i=0;i<boobies.size();i++){
    

    
    Boobie getBoob = (Boobie) boobies.get(i); //weird stuff? wtf java!
    getBoob.xeno(mouseX,mouseY);  
    
    //check distance
    if(getBoob.mad != true){
      if(abs(dist(getBoob.boobCenterX,getBoob.boobCenterY,you.fireCenterX,you.fireCenterY))<25){
        getBoob.mad = true;
        getBoob.posY -= 21;
      }
    }
    
    getBoob.draw();
  }
    
  you.getDirection(mouseX);
  you.xeno(mouseX,mouseY); 
  you.draw();
  you.drawBnds(); //shows green bounds 
  
  

}

void keyPressed(){

}







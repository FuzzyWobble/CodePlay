//long list of global variables
float gameTimer;
segment aSegment;
triangle aTriangle;
ArrayList segments;
ArrayList triangles;
PVector drawEnd, currentPos, dirVec, newEnd;
PVector adjustVec;
boolean newSegment;
int travelCount;
float travelSpeed;
float travelDist;
float accumulatedSpeed;
int segmentSize;
float characterX, characterY;
boolean you_are_dead;
float timerStart;
int segmentsMax;
int segmentsUsed;

void setup(){
  size(600,600);
  background(20,20,20);
  gameTimer = 0;
  newSegment = false;
  you_are_dead = false;
  drawEnd = new PVector(0,0,0); //first one starts at origin
  segments = new ArrayList();
  triangles = new ArrayList();
  travelCount = 0;
  travelSpeed = 0.06;
  accumulatedSpeed = 0;
  travelDist = 0;
  segmentSize = 40;
  characterX = 0;
  characterY = 0;
  frameRate(30);
  timerStart = 0;
  segmentsMax = 25;
  segmentsUsed = 0;
  
  for(int i=0;i<10;i++){
    aTriangle = new triangle();
    aTriangle.location = new PVector(random(50,550),random(50,550),0);
    aTriangle.visible = true;
    triangles.add(aTriangle);
  }
}


void draw(){
    
    
  
  
  if(you_are_dead==true){
    
    background(20,20,20);
    fill(255,0,0);
    textSize(22);
    text("YOU IS DEAD!", 230, 300); 
    
    if(timerStart==0){
      timerStart = millis();
    }else{
      if(millis()-timerStart>2000){  
        restartGame();
      }
    }
    
    
  }else{
    
    background(20,20,20);
    

  
    if(newSegment){
      
      //current pos
      currentPos = new PVector(mouseX,mouseY,0);
      
      //direction vector
      dirVec = PVector.sub(currentPos,drawEnd);
      dirVec.normalize();
      dirVec.setMag(segmentSize+1); 
      
      //adjusted direction vector
      adjustVec = PVector.sub(currentPos,drawEnd);
      adjustVec.normalize();
      adjustVec.setMag(segmentSize-2); 
      
      stroke(random(120,250),random(120,250),random(120,250));
      strokeWeight(5);
      line(drawEnd.x, drawEnd.y, drawEnd.x+dirVec.x, drawEnd.y+dirVec.y);
    }
    
    //draw segments 
    for(int i=0;i<segments.size();i++){
      segment getSeg = (segment) segments.get(i); //weird stuff? wtf java!
      getSeg.drawSegment();  
    }
    
    //draw triangles
    for(int i=0;i<triangles.size();i++){
      triangle getTri = (triangle) triangles.get(i); //weird stuff? wtf java!
      getTri.drawTriangle();  
    }
    
    
    //check intersect
    for(int i=0;i<segments.size();i++){
      segment segA = (segment) segments.get(i);
      for(int j=0;j<segments.size();j++){
        segment segB = (segment) segments.get(j);
        if(segB.visible==true && segA.visible==true){
          if( segIntersection(segA.startPt.x, segA.startPt.y, segA.endPt.x, segA.endPt.y, segB.startPt.x, segB.startPt.y, segB.endPt.x, segB.endPt.y) != null){
            println("INTERSECT, "+millis()); 
            you_are_dead = true;
          }
        }
      }
    }
    
  
    for(int i=0;i<segments.size();i++){
      segment seg = (segment) segments.get(i);
      if(seg.visible==true){
        if( (dist(mouseX,mouseY,0, seg.centerDot.x,seg.centerDot.y,0) < 20) && (i != segments.size()-1) ){
          fill(0,200,0);
          ellipse(seg.centerDot.x,seg.centerDot.y,10,10);
          break;
        }
      }
    }  
      
    
    //draw character on line
    if(segments.size()>2){
      segment onSegment = (segment) segments.get(travelCount);
      if(onSegment.visible == false){
        println("LINESEG, "+travelCount);
        you_are_dead = true;  
      }
      travelDist = segmentSize*accumulatedSpeed;
      accumulatedSpeed += travelSpeed;
      if(travelDist >= segmentSize){ //we have reached the end of this segment
        travelCount++;
        if(travelCount>segments.size()-1){
          println("LINEEND, "+travelCount);
          you_are_dead = true;          
        }
        accumulatedSpeed = 0;
        travelDist = 0;
      }else{
        characterX = (onSegment.normDirVec.x*travelDist) + onSegment.startPt.x;
        characterY = (onSegment.normDirVec.y*travelDist) + onSegment.startPt.y;
      }
      fill(255,0,0);
      ellipse(characterX,characterY,15,15);
      
      //check get triangle
      for(int i=0;i<triangles.size();i++){
        triangle getTri = (triangle) triangles.get(i); //weird stuff? wtf java!
        if(dist(getTri.location.x,getTri.location.y,characterX,characterY)<15){
          getTri.visible = false;
        }
      }
    }
    

    if(millis()-gameTimer<3500){
      fill(190);
      textSize(27);
      text("START DRAWING", 200, 300);   
      textSize(17);
      text("to start your anxiety attack", 200, 324);     
    }
    
    
    //used segments
    fill(100);
    textSize(23);
    text("SEGMENTS: "+segmentsUsed+"/"+segmentsMax, 390, 30); 
    

  
  }//end main draw  
}

void mousePressed(){
  if(mouseButton==LEFT){
    if(millis()-gameTimer>1500 && segmentsUsed!=segmentsMax){
      newSegment = true;
    } 
  }else if(mouseButton==RIGHT){
    for(int i=0;i<segments.size();i++){
      segment seg = (segment) segments.get(i);
      if( (dist(mouseX,mouseY,0, seg.centerDot.x,seg.centerDot.y,0) < 20) && (i != segments.size()-1) ){
        seg.visible = false;
        segmentsUsed--;
        break;
      }
    }
  }else{
    //do nothing
  }  
}

void mouseReleased(){
  if(mouseButton==LEFT){
    if(millis()-gameTimer>1500 && segmentsUsed!=segmentsMax){
      //determine the new end
      newEnd = new PVector(drawEnd.x+dirVec.x, drawEnd.y+dirVec.y, 0);
      //create segment
      aSegment = new segment();
      aSegment.startPt = new PVector(drawEnd.x,drawEnd.y,0);
      aSegment.endPt = new PVector(drawEnd.x+adjustVec.x, drawEnd.y+adjustVec.y, 0);
      aSegment.centerDot = new PVector( ((aSegment.startPt.x+aSegment.endPt.x)/2.0), ((aSegment.startPt.y+aSegment.endPt.y)/2.0) );
      aSegment.normDirVec = PVector.sub(aSegment.endPt,aSegment.startPt);
      aSegment.normDirVec.normalize();
      aSegment.col = color(random(120,250),random(120,250),random(120,250));
      aSegment.visible = true;
      segments.add(aSegment);
      drawEnd = new PVector(newEnd.x,newEnd.y,0);
      newSegment = false;
      segmentsUsed++;
    }
  }else if(mouseButton==RIGHT){
    //println("RIGHT pressed");
  }else{
    //do nothing
  }  
}


void mouseDragged(){
}
void mouseMoved(){
}



void restartGame(){
  newSegment = false;
  you_are_dead = false;
  drawEnd = new PVector(0,0,0); 
  segments = new ArrayList();
  triangles = new ArrayList();
  travelCount = 0;
  travelSpeed = 0.08;
  accumulatedSpeed = 0;
  travelDist = 0;
  segmentSize = 40;
  characterX = 0;
  characterY = 0;
  timerStart = 0;
  segmentsUsed = 0;
  gameTimer = millis();

  for(int i=0;i<10;i++){
    aTriangle = new triangle();
    aTriangle.location = new PVector(random(50,550),random(50,550),0);
    aTriangle.visible = true;
    triangles.add(aTriangle);
  }
}


//http://wiki.processing.org/w/Line-Line_intersection
PVector segIntersection(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4) 
{ 
  float bx = x2 - x1; 
  float by = y2 - y1; 
  float dx = x4 - x3; 
  float dy = y4 - y3;
  float b_dot_d_perp = bx * dy - by * dx;
  if(b_dot_d_perp == 0) {
    return null;
  }
  float cx = x3 - x1;
  float cy = y3 - y1;
  float t = (cx * dy - cy * dx) / b_dot_d_perp;
  if(t < 0 || t > 1) {
    return null;
  }
  float u = (cx * by - cy * bx) / b_dot_d_perp;
  if(u < 0 || u > 1) { 
    return null;
  }
  return new PVector(x1+t*bx, y1+t*by);
}

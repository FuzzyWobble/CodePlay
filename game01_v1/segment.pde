class segment {

  PVector startPt, endPt, centerDot, normDirVec;
  color col;
  boolean visible;
  
  void drawSegment(){
    if(visible==true){
      stroke(col);
      strokeWeight(5);
      line(startPt.x,startPt.y,endPt.x,endPt.y);
      noStroke();
      fill(255);
      ellipse(centerDot.x,centerDot.y,10,10);
    }
  }
}

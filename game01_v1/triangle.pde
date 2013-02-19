class triangle {

  PVector location;
  boolean visible;
  
  void drawTriangle(){
    if(visible==true){
    
      fill(25,200,25);
      triangle(location.x,location.y,location.x+15,location.y,location.x+8,location.y+15); 
    
    }
  }
}

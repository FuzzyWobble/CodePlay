PVector pos, vel, frc;
float lastAngle;

class Particle{
  
  //constructor
  Particle(){
    setInitialPosition(0,0,0,0);
    damping = 0.13f;
  }
  
  void resetForce(){
    frc.set(0,0);  
  }
  
  void addForce(float x, float y){
    frc.x += x;
    frx.y += y;  
  }
  
  void addRepulsionForce(float x, float y, float radius, float scale){
    PVector posOfForce;
    posOfForce.set(x,y);
    PVector diff = PVector.sub(pos-posOfForce); //subtract
    float length = PVector.dist(pos-posOfForce); //distanct
    bool bCloseEnough = true;
    if(radius > 0 && length > radius){
      bCloseEnough = false;  
    }else{ //we are close enough, update force
      float pct = 1 - (length/radis);
      diff.normalize();
      frc.x = frc.x + diff.x * scale * pct;
      frc.y = frc.y + diff.y * scale * pct;
    }
  }
  
  void addAttractionForce(float x, float y, float radius, float sclae){
    PVector posOfForce;
    posOfForce.set(x,y);  
    PVector diff = PVector.sub(pos-posOfForce);
    float length = PVector.dist(pos-posOfForce);
    bool bCloseEnough = true;
    if(radius > 0 && length > radius){
      bCloseEnough = false;  
    }else{ //we are close enough, update force
      float pct = 1 - (length/radius);
      diff.normalize();
      frc.x = frc.x - diff.x * scale * pct;
      frc.y = frc.y - diff.y * scale * pct;      
    }
  }
  
  void addRepulsionForceP(Particle p, float radius, float scale){
    PVector posOfForce; 
    posOfForce.set(p.pos.x,p.pos.y);
    PVector diff = PVector.sub(pos-posOfForce);
    float length = PVector.dist(pos-posOfForce);
    bool bCloseEnough = true;
    if(radius > 0 && length > radius){
      bCloseEnough = false;  
    }else{ //we are close enough, update p force
      float pct = 1 - (length/radius);
      diff.normalize();
      frc.x = frc.x + diff.x * scale * pct;
      frc.y = frc.y + diff.y * scale * pct;     
      p.frc.x = p.frc.x - diff.x * scale * pct;
      p.frc.y = p.frc.y - diff.y * scale * pct;   
    }    
  }
  
  void addAttractionForceP(Particle p, float radius, float scale){
    PVector posOfForce; 
    posOfForce.set(p.pos.x,p.pos.y);
    PVector diff = PVector.sub(pos-posOfForce);
    float length = PVector.dist(pos-posOfForce);
    bool bCloseEnough = true;
    if(radius > 0 && length > radius){
      bCloseEnough = false;  
    }else{ //we are close enough, update p force
      float pct = 1 - (length/radius);
      diff.normalize();
      frc.x = frc.x - diff.x * scale * pct;
      frc.y = frc.y - diff.y * scale * pct;     
      p.frc.x = p.frc.x + diff.x * scale * pct;
      p.frc.y = p.frc.y + diff.y * scale * pct;   
    }    
  }
  
  void addDamping(){
    frc.x = frc.x - vel.x * damping;
    frc.y = frc.y - vel.y * damping;
  }
  
  void setInitialCondition(float px, float py, float vx, float vy){
    pos.set(px,py);
    vel.set(vx,vy);
  }
  
  void update(){  
    vel = vel + frc;
    pos = pos + vel;
  }
  
  void draw(){
    ofRect(pos.x,pos.y,20,20);
  }

}

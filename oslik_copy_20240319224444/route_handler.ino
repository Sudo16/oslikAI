void route_handler(){
  if (route[0] != '0'){
    if (route_end) {Serial.println("[go]");stepper1.reset();stepper2.reset();}
    else movement();
  } 
  else Serial.println("[go]");
}

void movement(){
  stepper1.tick();
  stepper2.tick();
  if(!barrier()){
    if(((stepper1.getCurrent()+stepper2.getCurrent())/2)<(((float(int(route[1])/l_cir))*200)+count_barrier*800)) angle_retention();
    else route_end = true;
  }
}

bool barrier(){
  if (!digitalRead(6)){
    stepper1.setTarget(stepper1.getCurrent()-400);
    stepper2.setTarget(stepper2.getCurrent()-400);
    while(!stepper1.ready() && !stepper2.ready()) {stepper1.tick();stepper2.tick();}
    stepper1.setTarget(stepper1.getCurrent()+400);
    stepper2.setTarget(stepper2.getCurrent()-400);
    while(!stepper1.ready() && !stepper2.ready()) {stepper1.tick();stepper2.tick();}
    stepper1.setTarget(stepper1.getCurrent()+400);
    stepper2.setTarget(stepper2.getCurrent()+400);
    while(!stepper1.ready() && !stepper2.ready()) {stepper1.tick();stepper2.tick();}
    stepper1.setTarget(stepper1.getCurrent()-400);
    stepper2.setTarget(stepper2.getCurrent()+400);
    while(!stepper1.ready() && !stepper2.ready()) {stepper1.tick();stepper2.tick();}
    stepper1.setTarget(stepper1.getCurrent()+800);
    stepper2.setTarget(stepper2.getCurrent()+800);
    while(!stepper1.ready() && !stepper2.ready()) {stepper1.tick();stepper2.tick();}
    stepper1.setTarget(stepper1.getCurrent()-400);
    stepper2.setTarget(stepper2.getCurrent()+400);
    while(!stepper1.ready() && !stepper2.ready()) {stepper1.tick();stepper2.tick();}
    stepper1.setTarget(stepper1.getCurrent()+400);
    stepper2.setTarget(stepper2.getCurrent()+400);
    while(!stepper1.ready() && !stepper2.ready()) {stepper1.tick();stepper2.tick();}
    stepper1.setTarget(stepper1.getCurrent()+400);
    stepper2.setTarget(stepper2.getCurrent()-400);
    while(!stepper1.ready() && !stepper2.ready()) {stepper1.tick();stepper2.tick();}
    return true;
  }
  else return false;
}

void angle_retention(){
  if (current_angle>route[2]) {stepper1.setSpeed(-(route[2]/2));stepper2.setSpeed(route[2]/2);}
  else if (current_angle<route[2]) {stepper1.setSpeed((route[2]/2));stepper2.setSpeed(-(route[2]/2));}
  else {stepper1.setSpeed(route[2]);stepper2.setSpeed(route[2]);}
}
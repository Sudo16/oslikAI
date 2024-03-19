void parse_OPi(){
  if (Serial.available()){
    counter=0;
    count_subStr=0;
    num_subroute="";
    while  (Serial.available()){
      str_read[counter] = Serial.read();
      counter++;
    }
    for (int i = 0; i < counter; i++) {
      if (str_read == ',') {
        i++;
        count_subStr++;
        while(isDigit(str_read[i])){
          num_subroute+=str_read[i];
        }
        route[count_subStr] = num_subroute.c_str();
        count_subStr++;
      }
    }
  }

}
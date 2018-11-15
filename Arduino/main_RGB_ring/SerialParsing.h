    
#include <Servo.h> //servo motor controlling the autofocus
    
String serialParser(){    
    int index;
    String token;
    String term1;
    String term2;
    
    token = Serial.readStringUntil('>');
    //Serial.println(sizeof(token));
    //delay(5);
    index = token.indexOf('<');
    term1 = token.substring(0,index);
    //Serial.println(term1);
    term2 = token.substring(index+1);

    return term1, term2;
    //Serial.println(term2);

}// end serialParser

int a = 0;
int b = 0;
int c = 0;
int d = 0;

const int ct = 5;
double Arr[ct];
int id = 0;
int tot = 0;
int avg = 0;
double m = 0;
int high = 0;
int low = 0;
bool UP = true;

void setup() {
  Serial.begin(115200);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  digitalWrite(10,0);
  digitalWrite(11,0);
  for (int i=0; i<ct; i++)
  {
    Arr[i] = 0;
  }
}

void loop() {
  
  digitalWrite(10,1);
    for (int i = 0; i <= 2; i++) {
      Arr[0] = Arr[1];
      Arr[1] = Arr[2];
      Arr[2] = Arr[3];
      Arr[3] = Arr[4];
      Arr[4] = analogRead(A0);

      /*
      if(UP)
      {
        //look for down condition
        if((Arr[4]<Arr[3])&&(Arr[4]<Arr[2])&&(Arr[4]<Arr[1])&&(Arr[4]<Arr[0]))
        {
          UP = false;
        }
      }
      else
      {
        if((Arr[4]>Arr[3])&&(Arr[4]>Arr[2])&&(Arr[4]>Arr[1])&&(Arr[4]>Arr[0]))
        {
          UP = true;
        }
      }
      */
      if((Arr[4]==Arr[2])&&(Arr[2]==Arr[0]))
      {
        UP = true;
      }
      else
      {
        UP = false;
      }
      


      

      m = (2*Arr[4]+Arr[3]-Arr[1]-2*Arr[0])/40;


      //Serial.print(m);
      //Serial.print(",");
      Serial.println(Arr[4]);
      /*
      Serial.print(",");

      if(UP)
      {
        Serial.println(645);
      }
      else
      {
        Serial.println(575);
      }
      */
      /*
      if(m>0)
      {
        Serial.println(645);
      }
      else 
      {
        Serial.println(575);
      }
      */

      //m = ((double)0.05*Arr[4]+(double)0.025*Arr[3]-(double)0.025*Arr[1]-(double)0.058*Arr[0]);

    /*
      Serial.println(Arr[0]);
      Serial.println(Arr[1]);
      Serial.println(Arr[2]);
      Serial.println(Arr[3]);
      Serial.println(Arr[4]);
      Serial.println(m);
      Serial.println("");
      */
      
      /*
      tot = tot - Arr[id];
      Arr[id] = analogRead(A0);
      tot = tot + Arr[id];
      id = id+1;
      if (id>=ct)
      {
        id = 0;
      }
      avg = tot/ct;

      
      
      m = ((double)0.05*Arr[5]+(double)0.025*Arr[3]-(double)0.025*Arr[1]-(double)0.058*Arr[0]);

      Serial.println(Arr[0]);
      Serial.println(Arr[1]);
      Serial.println(Arr[2]);
      Serial.println(Arr[3]);
      Serial.println(Arr[4]);
      Serial.println(m);
      Serial.println("");



      
      if (Arr[id]>610)
      {
        Serial.print(645);
        Serial.print(",");
      }
      else
      {
        Serial.print(560);
        Serial.print(",");
      }

      Serial.print(avg);
      Serial.print(",");
      Serial.print(Arr[id]);
      Serial.print(",");
      Serial.println(610);

      

      //Serial.print(analogRead(A0));
      //Serial.print(",");
      //Serial.println(610);
      */
  }
  digitalWrite(10,0);
  delay(50);

}

//Define pins
#define PotA    A1 //Potentiometer A output
#define PotB    A2 //Potentiometer B output

//Global variables (Potentiometer Functions)
int ValSensorA;
int ValSensorB;

//Filter settings
int ArrayPotA[20];
int ArrayPotB[20];


void setup() {
  //Serial
  Serial.begin(9600);
}

void loop() {
  SensorSTD(20);
}

void SensorSTD(int Ct)
{
  //Aquire Ct points for both sensors
  for(int i=0; i<Ct; i++)
  {
    ArrayPotA[i] = analogRead(PotA);
    ArrayPotB[i] = analogRead(PotB);
  }

  //Sum of squares
  long SumSqA = 0;
  long SumSqB = 0;
  long TotA = 0;
  long TotB = 0;
  long tempA, tempB;
  for(int i=0; i<Ct; i++)
  {
    SumSqA += pow(ArrayPotA[i], 2);
    SumSqB += pow(ArrayPotB[i], 2);
    TotA += ArrayPotA[i];
    TotB += ArrayPotB[i];
    
    Serial.print(ArrayPotA[i]);
    Serial.print(",");
    Serial.println(ArrayPotB[i]);
  }
  TotA = pow(TotA, 2);
  TotB = pow(TotB, 2);
  TotA = TotA/Ct;
  TotB = TotB/Ct;

  int ResA = SumSqA-TotA;
  int ResB = SumSqB-TotB;

  Serial.println("");
  Serial.print(SumSqA);
  Serial.print(",");
  Serial.println(SumSqB);
  Serial.print(TotA);
  Serial.print(",");
  Serial.println(TotB);
  Serial.print(ResA);
  Serial.print(",");
  Serial.println(ResB);
  delay(5000);
}

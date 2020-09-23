int a = 0;
int b = 0;
int c = 0;
int d = 0;

const int ct = 3;
double Arr[ct];
int id = 0;
int tot = 0;
int avg = 0;
double m = 0;
int high = 0;
int low = 0;
bool UP = true;
int Drop = 570;
void setup() {
  Serial.begin(115200);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  digitalWrite(10, 0);
  digitalWrite(11, 0);

  //Fill array with zeros
  for (int i = 0; i < ct; i++)
  {
    Arr[i] = 0;
  }
}

void loop() {

  //Turn on motor
  digitalWrite(10, 1);
  //Stuff to do with motor on
  MovingAverage();

  digitalWrite(10, 0);
  delay(20);
}

void MovingAverage()
{
  for (int i = 0; i < 3; i++)
  {
    //Fill array
    for (int j = 0; j < ct - 1; j++)
    {
      Arr[j] = Arr[j + 1];
    }
    Arr[ct - 1] = analogRead(A0) - Drop;

    //Calculate the average value
    tot = 0;
    for (int j = 0; j < ct; j++)
    {
      tot = tot + Arr[j];
    }
    avg = tot / ct;
    Arr[ct - 1] = avg;

    //Plot the average value
    Serial.print(avg);
    Serial.print(",");
    Serial.print(65);
    Serial.print(",");
    Serial.println(15);
  }
}

void NoFilter()
{
  for (int i = 0; i < 3; i++)
  {
    //Plot the value
    Serial.print(analogRead(A0) - Drop);
    Serial.print(",");
    Serial.print(65);
    Serial.print(",");
    Serial.println(15);
  }
}

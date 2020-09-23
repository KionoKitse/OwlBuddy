int a = 0;
int b = 0;
int c = 0;
int d = 0;


int id = 0;

double m = 0;



//Moving average
//const int ct = 3;
//double Arr[ct];
int tot = 0;
int avg = 0;

//SearchMode
const byte Ct = 25; //About half a period
byte ArrByte[Ct];
byte Val = 0;
bool UP = true;
byte high = 0;
byte low = 255;
byte fail = 0;
//byte FailLim = 10;
byte LastLow = 0;
byte LastHigh = 0;

//AvgSearch
byte FailLim = 1;
const int ct = 10;
double Arr[ct];

//All
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
  //MovingAverage();
  //SearchMode();
  AvgSearch();

  digitalWrite(10, 0);
  delay(20);
}
void AvgSearch()
{
  for (int a = 0; a < 2; a++)
  {
    byte PrintVal = 0.5*(LastHigh-LastLow)+LastLow;
    
    //Fill array
    for (int i = 0; i < ct - 1; i++)
    {
      Arr[i] = Arr[i + 1];
    }
    Arr[ct - 1] = analogRead(A0) - Drop;

    //Calculate the average value
    tot = 0;
    for (int i = 0; i < ct; i++)
    {
      tot = tot + Arr[i];
    }
    avg = tot / ct;

    //Search top
    if (UP)
    {
      if(avg>high)
      {
        high = avg;
        fail = 0;
      }
      else
      {
        fail++;
        if(fail > FailLim)
        {
          PrintVal = high;
          LastHigh = high;
          //Top point found no longer going up
          UP = false;
          high = 0;
          fail = 0;
        }
      }
    }
    //Search bottom
    else
    {
      if(avg<low)
      {
        low = avg;
        fail = 0;
      }
      else
      {
        fail++;
        if(fail > FailLim)
        {
          PrintVal = low;
          LastLow = low;
          
          //bottom point found no longer going downp
          UP = true;
          low = 255;
          fail = 0;
        }
      }
    }
    //Zero point
    /*
    if(Val<24)
    {
      low = Val;
      PrintVal = low;
      LastLow = low;
      UP = true;
      low = 255;
      fail = 0; 
    }
    */

    //Plot the average value
    Serial.print(Arr[ct - 1]);
    Serial.print(",");
    Serial.print(avg);
    Serial.print(",");
    Serial.println(PrintVal);
    
  }
}
void SearchMode()
{
  for (int a = 0; a < 4; a++)
  {
    byte PrintVal = 0.5*(LastHigh-LastLow)+LastLow;
    //Get value
    Val = analogRead(A0) - Drop;

    //Print
    Serial.print(Val);
    Serial.print(",");
    
    //Search top
    if (UP)
    {
      if(Val>high)
      {
        high = Val;
        fail = 0;
      }
      else
      {
        fail++;
        if(fail > FailLim)
        {
          PrintVal = high;
          LastHigh = high;
          //Top point found no longer going up
          UP = false;
          high = 0;
          fail = 0;
        }
      }
    }
    //Search bottom
    else
    {
      if(Val<low)
      {
        low = Val;
        fail = 0;
      }
      else
      {
        fail++;
        if(fail > FailLim)
        {
          PrintVal = low;
          LastLow = low;
          
          //bottom point found no longer going downp
          UP = true;
          low = 255;
          fail = 0;
        }
      }
    }
    //Zero point
    if(Val<24)
    {
      low = Val;
      PrintVal = low;
      LastLow = low;
      UP = true;
      low = 255;
      fail = 0; 
    }
    Serial.println(PrintVal);
  }
}
void MovingAverage()
{
  for (int a = 0; a < 2; a++)
  {
    //Fill array
    for (int i = 0; i < ct - 1; i++)
    {
      Arr[i] = Arr[i + 1];
    }
    Arr[ct - 1] = analogRead(A0) - Drop;

    //Calculate the average value
    tot = 0;
    for (int i = 0; i < ct; i++)
    {
      tot = tot + Arr[i];
    }
    avg = tot / ct;

    //Plot the average value
    Serial.print(Arr[ct - 1]);
    Serial.print(",");
    Serial.println(avg);
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

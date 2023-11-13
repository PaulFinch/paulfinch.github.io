#include <Esplora.h>
#include <TFT.h>
#include <SPI.h>
#include <SD.h>
#include <TimerEvent.h>
#include <EEPROM.h>

#define WHEEL	1.95
#define SD_CS	8
#define ADDR	0

TimerEvent Timer01S;
TimerEvent Timer10S;

const unsigned int ScreenWidth = EsploraTFT.width();
const unsigned int ScreenHeight = EsploraTFT.height();
const unsigned int ScreenVBar1 = ScreenWidth * 1 / 3;
const unsigned int ScreenVBar2 = ScreenWidth * 2 / 3;
const unsigned int ScreenHBar3 = ScreenHeight - 6;
const unsigned int ScreenHBar1 = ScreenHBar3 * 1 / 3;
const unsigned int ScreenHBar2 = ScreenHBar3 * 2 / 3;

unsigned long lastInterrupt = 0;
unsigned long Step = 0;
unsigned long StepLast = 0;
unsigned long Distance = 0;
unsigned long Time = 0;
unsigned int Speed = 0;
unsigned int SpeedAvg = 0;
unsigned int SpeedStep = 0;
unsigned int SpeedStepAvg = 0;
unsigned int Difficulty = 0;
unsigned int TargetTime = 3600;
unsigned long RemainingTime = TargetTime;

unsigned int SpeedDisplay = 0;
unsigned int SpeedDisplayOld = 0;
unsigned int SpeedStepDisplay = 0;
unsigned int SpeedStepDisplayOld = 0;
unsigned int DifficultyOld = 0;
boolean ModeOld = false;

boolean Mode = true;
boolean Running = false;
boolean Refresh = true;
boolean SDCard = false;
boolean Remaining = false;

File DataFile;
char DataFileNameChar[13];

void setup()
{
  EsploraTFT.begin();
  Esplora.writeRGB(0, 0, 50);
  pinMode(12, INPUT_PULLUP);
  attachInterrupt(0, StepIncrement, RISING);

  Timer01S.set(1000, DoEvery1Second);
  Timer10S.set(10000, DoEvery10Seconds);

  //EEPROM.put(ADDR, 0);
  if (SD.begin(SD_CS))
  {
    SDCard = true;

    int DataSlot = 0;
    EEPROM.get(ADDR, DataSlot);
    GetFileName(DataSlot, DataFileNameChar);
    DataSlot++;
    EEPROM.update(ADDR, DataSlot);

    ClearScreen();
    DrawDataFile();
    delay(5000);
  }

  ClearScreen();
  DrawFrame();
  LogIt("New Session");
}

void loop()
{
  int slider = Esplora.readSlider();
  if (slider > 800 )
    Difficulty = 0;
  else
    if (slider > 300 )
      Difficulty = 1;
    else
      Difficulty = 2;

  if (Esplora.readButton(SWITCH_UP) == LOW)
  {
    Running = !Running;
    Refresh = true;
  }

  if (Esplora.readButton(SWITCH_LEFT) == LOW)
  {
    Mode = !Mode;
    Refresh = true;
  }

  if (Esplora.readButton(SWITCH_RIGHT) == LOW)
  {
    Remaining = !Remaining;
    Refresh = true;
  }

  if (Esplora.readButton(SWITCH_DOWN) == LOW)
  {
    Step = 0;
    Time = 0;
    Distance = 0;
    Speed = 0;
    SpeedAvg = 0;
    SpeedStep = 0;
    SpeedStepAvg = 0;
    RemainingTime = TargetTime;
    Running = false;
    Refresh = true;

    if (SDCard)
      LogIt("Reset");
  }

  Display();

  Timer01S.update();
  Timer10S.update();
 
  delay(1000);
}

void StepIncrement()
{
  if(millis() - lastInterrupt > 100) {
    lastInterrupt = millis();
    
    if (Running)
      Step++;
  }
}

void DoEvery1Second()
{
  if (Running)
  {
    Time++;
    Distance = round(Step * WHEEL);
    if (TargetTime >= Time)
      RemainingTime = TargetTime - Time;
    else
      RemainingTime = Time - TargetTime;
  }
}

void DoEvery10Seconds()
{
  if (Running)
  {
    Esplora.writeRGB(0, 0, 50);

    long StepPoint = Step;
    long StepDelta = StepPoint - StepLast;
    StepLast = StepPoint;

    Speed = round(StepDelta * 0.36 * WHEEL);    // * 3600s / 10s / 1000m
    SpeedStep = round(StepDelta * 2);           // * 60s / 10s / 3 steps

    if (Time > 0)
    {
      SpeedAvg = round(Distance * 3.6 / Time);  // * 3600s / time / 1000m
      SpeedStepAvg = round(Step * 20 / Time);   // * 60s / time / 3 steps 
    }
    else
    {
      SpeedAvg = 0;
      SpeedStepAvg = 0;
    }

    String DataString = "";
    DataString += Time;
    DataString += ";";
    DataString += Step;
    DataString += ";";
    DataString += Distance;
    DataString += ";";
    DataString += Speed;
    DataString += ";";
    DataString += SpeedAvg;
    DataString += ";";
    DataString += SpeedStep;
    DataString += ";";
    DataString += SpeedStepAvg;
    DataString += ";";
    DataString += Difficulty;
    LogIt(DataString);

    Mode = !Mode;
    Refresh = true;
  }
}

void LogIt(String v_input)
{
  if (SDCard)
  {
    DataFile = SD.open(DataFileNameChar, FILE_WRITE);
    if (DataFile) {
      DataFile.println(v_input);
      DataFile.close();
    }
  }
}

void Display()
{
  char SpeedDisplayChar[3];
  char SpeedStepDisplayChar[4];
  char DistanceChar[9];
  char RemainingTimeChar[9];
  char TimeChar[9];

  if (Running)
    Esplora.writeRGB(0, 50, 0);
  else
    Esplora.writeRGB(50, 0, 0);

  if (Mode)
    SpeedDisplay = Speed;
  else
    SpeedDisplay = SpeedAvg;

  if ((SpeedDisplay != SpeedDisplayOld) || Refresh)
  {
    SpeedDisplayOld = SpeedDisplay;
    GetSpeedDisplay(SpeedDisplay, SpeedDisplayChar);
    ClearSpeed();
    DrawSpeed(SpeedDisplayChar);
  }

  if (Mode)
    SpeedStepDisplay = SpeedStep;
  else
    SpeedStepDisplay = SpeedStepAvg;

  if ((SpeedStepDisplay != SpeedStepDisplayOld) || Refresh)
  {
    SpeedStepDisplayOld = SpeedStepDisplay;
    GetSpeedStepDisplay(SpeedStepDisplay, SpeedStepDisplayChar);
    ClearSpeedStep();
    DrawSpeedStep(SpeedStepDisplayChar);
  }

  if ((Mode != ModeOld) || Refresh)
  {
    ModeOld = Mode;
    ClearMode();
    DrawMode();
  }

  if ((Difficulty != DifficultyOld) || Refresh)
  {
    DifficultyOld = Difficulty;
    ClearDifficulty();
    DrawDifficulty();
  }

  if (Running || Refresh)
  {
    if (Mode)
    {
      GetDistanceDisplay(Distance, DistanceChar);
      ClearFooter();
      DrawFooter(DistanceChar);
    }
    else
    {
      if (Remaining)
      {
        GetTimeDisplay(RemainingTime, RemainingTimeChar);
        ClearFooter();
        DrawFooter(RemainingTimeChar);
      }
      else
      {
        GetTimeDisplay(Time, TimeChar);
        ClearFooter();
        DrawFooter(TimeChar);
      }
    }
  }

  Refresh = false;
}

void ClearScreen() {
  EsploraTFT.noStroke();
  EsploraTFT.fill(0, 0, 0);
  EsploraTFT.rect(1, 1, ScreenWidth - 2, ScreenHeight - 2);
}

void DrawDataFile() {
  EsploraTFT.stroke(255,255,0);
  EsploraTFT.noFill();
  EsploraTFT.rect(0, 0, ScreenWidth, ScreenHeight);

  EsploraTFT.stroke(255,255,0);
  EsploraTFT.setTextSize(1);
  EsploraTFT.text("Session logged in:", 8, 10);

  EsploraTFT.setTextSize(2);
  EsploraTFT.text(DataFileNameChar, 8, 25);
}

void DrawFrame() {
  EsploraTFT.stroke(255,255,0);
  EsploraTFT.noFill();
  EsploraTFT.rect(0, 0, ScreenWidth, ScreenHeight);

  EsploraTFT.stroke(255,255,0);
  EsploraTFT.noFill();
  EsploraTFT.line(ScreenVBar2, ScreenHBar1, ScreenWidth, ScreenHBar1);
  EsploraTFT.line(0, ScreenHBar2, ScreenWidth, ScreenHBar2);
  EsploraTFT.line(0, ScreenHBar3, ScreenWidth, ScreenHBar3);
  EsploraTFT.line(ScreenVBar2, 0, ScreenVBar2, ScreenHBar2);
  EsploraTFT.line(ScreenVBar1, ScreenHBar3, ScreenVBar1, ScreenHeight);
  EsploraTFT.line(ScreenVBar2, ScreenHBar3, ScreenVBar2, ScreenHeight);

  EsploraTFT.stroke(255,255,0);
  EsploraTFT.setTextSize(2);
  EsploraTFT.text("km/h", 52, 64);

  if (SDCard)
  {
    EsploraTFT.stroke(255,255,0);
    EsploraTFT.fill(255,0,0);
    EsploraTFT.circle(10, 73, 6);
  }
}

void DrawSpeed(char v_input[2])
{
  EsploraTFT.stroke(255,255,255);
  EsploraTFT.setTextSize(8); 
  EsploraTFT.text(v_input, 10, 5);
}

void ClearSpeed() {
  EsploraTFT.noStroke();
  EsploraTFT.fill(0, 0, 0);
  EsploraTFT.rect(10, 5, GetHPixels(8,2), GetVPixels(8,1));
}

void DrawSpeedStep(char v_input[3])
{
  EsploraTFT.stroke(255,255,255);
  EsploraTFT.setTextSize(2);   
  EsploraTFT.text(v_input,  116, 55);
}

void ClearSpeedStep() {
  EsploraTFT.noStroke();
  EsploraTFT.fill(0, 0, 0);
  EsploraTFT.rect(116, 55, GetHPixels(2,3), GetVPixels(2,1));
}

void DrawMode()
{
  EsploraTFT.stroke(255,255,255);
  EsploraTFT.setTextSize(2);
  if (Mode)
    EsploraTFT.text("NOW", 116, 13);
  else
    EsploraTFT.text("AVG", 116, 13);
}

void ClearMode() {
  EsploraTFT.noStroke();
  EsploraTFT.fill(0, 0, 0);
  EsploraTFT.rect(116, 13, GetHPixels(2,3), GetVPixels(2,1));
}

void DrawDifficulty()
{
  EsploraTFT.noStroke();
  if (Difficulty == 0)
  {
    EsploraTFT.fill(0, 255, 0);
    EsploraTFT.rect(1, ScreenHBar3 + 1, ScreenVBar1 - 1, ScreenHeight - ScreenHBar3 - 2);
  }

  if (Difficulty == 1)
  {
    EsploraTFT.fill(255, 69, 0);
    EsploraTFT.rect(ScreenVBar1 + 1, ScreenHBar3 + 1, ScreenVBar2 - ScreenVBar1 - 1, ScreenHeight - ScreenHBar3 - 2);
  }

  if (Difficulty == 2)
  {
    EsploraTFT.fill(255, 0, 0);
    EsploraTFT.rect(ScreenVBar2 + 1, ScreenHBar3 + 1, ScreenWidth - ScreenVBar2 - 2, ScreenHeight - ScreenHBar3 - 2);
  }
}

void ClearDifficulty() {
  EsploraTFT.noStroke();
  EsploraTFT.fill(0, 0, 0);
  EsploraTFT.rect(1, ScreenHBar3 + 1, ScreenVBar1 - 1, ScreenHeight - ScreenHBar3 - 2);
  EsploraTFT.rect(ScreenVBar1 + 1, ScreenHBar3 + 1, ScreenVBar2 - ScreenVBar1 - 1, ScreenHeight - ScreenHBar3 - 2);
  EsploraTFT.rect(ScreenVBar2 + 1, ScreenHBar3 + 1, ScreenWidth - ScreenVBar2 - 2, ScreenHeight - ScreenHBar3 - 2);
}

void DrawFooter(char v_input[8])
{
  EsploraTFT.stroke(255,255,255);
  EsploraTFT.setTextSize(3);
  EsploraTFT.text(v_input, 10, 92);

  if (Mode)
  {
    EsploraTFT.stroke(255,255,0);
    EsploraTFT.fill(255, 255, 0);
    EsploraTFT.rect(79, 110, 3, 3);
  } 
  else
  {
    EsploraTFT.stroke(0,0,0);
    EsploraTFT.fill(0, 0, 0);
    EsploraTFT.rect(79, 110, 3, 3);    
  }
}

void ClearFooter() {
  EsploraTFT.noStroke();
  EsploraTFT.fill(0, 0, 0);
  EsploraTFT.rect(10, 92, GetHPixels(3,8), GetVPixels(3,1));
}
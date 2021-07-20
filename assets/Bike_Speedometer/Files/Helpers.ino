void GetSpeedDisplay(unsigned int v_speed, char *v_char)
{
  String v_string = "";

  if ((v_speed > 99) || (v_speed < 0))
    v_string = "XX";
  else
  {
    if (v_speed < 10)
      v_string += "0";
    v_string += v_speed;
  }

  v_string.toCharArray(v_char, 3);
}

void GetSpeedStepDisplay(unsigned int v_speed, char *v_char)
{
  String v_string = "";

  if ((v_speed > 999) || (v_speed < 0))
    v_string = "XXX";
  else
  {
    if (v_speed < 100)
      v_string += "0";
    if (v_speed < 10)
      v_string += "0";

    v_string += v_speed;
  }

  v_string.toCharArray(v_char, 4);
}

void GetDistanceDisplay(unsigned long v_distance, char *v_char)
{
  String v_string = "";

  if ((v_distance > 9999999) || (v_distance < 0))
    v_string = "XXXXXXX";
  else 
  {
    if (v_distance < 1000000)
      v_string += "0";
    if (v_distance < 100000)
      v_string += "0";
    if (v_distance < 10000)
      v_string += "0";
    if (v_distance < 1000)
      v_string += "0";
    if (v_distance < 100)
      v_string += "0";
    if (v_distance < 10)
      v_string += "0";
    v_string += v_distance;
  }
  v_string += "m";

  v_string.toCharArray(v_char, 9);
}

void GetTimeDisplay(unsigned long v_time, char *v_char)
{
  String v_string = "";

  long v_hour = floor(v_time / 3600);
  v_time -= v_hour * 3600;

  long v_min = floor(v_time / 60);
  v_time -= v_min * 60;

  long v_sec = v_time;

  if (v_time > 215999)
    v_string = "XX:XX:XX";
  else
  {
    if (v_hour < 10)
      v_string += "0";
    v_string += v_hour;
    v_string += ":";
    if (v_min < 10)
      v_string += "0";
    v_string += v_min;
    v_string += ":";
    if (v_sec < 10)
      v_string += "0";
    v_string += v_sec;
  }

  v_string.toCharArray(v_char, 9);
}

void GetFileName(int v_num, char *v_char)
{
  String v_string = "C";

  if ((v_num > 9999999) || (v_num < 0))
    v_string += "XXXXXXX";
  else
  {
    if (v_num < 100000)
      v_string += "0";
    if (v_num < 100000)
      v_string += "0";
    if (v_num < 10000)
      v_string += "0";
    if (v_num < 1000)
      v_string += "0";
    if (v_num < 100)
      v_string += "0";
    if (v_num < 10)
      v_string += "0";
    v_string += v_num;
  }
  v_string += ".csv";

  v_string.toCharArray(v_char, 13);
}

int GetHPixels(int v_size, int v_bloc)
{
  int v_int = 0;
  v_int += v_bloc * 5;
  v_int += (v_bloc - 1);
  v_int *= v_size;

  return v_int;
}

int GetVPixels(int v_size, int v_bloc)
{
  int v_int = 0;
  v_int += v_bloc * 7;
  v_int += (v_bloc - 1);
  v_int *= v_size;

  return v_int;
}
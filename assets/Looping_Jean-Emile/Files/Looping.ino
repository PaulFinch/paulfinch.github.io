int pin_pot = A0;
int pin_empty = A1;
int pin_motor_enable = 9;
int pin_motor_in1 = 10;
int pin_motor_in2 = 11;
int pin_switch = 2;
int pin_mon = 6;
int pin_led_1 = 3;
int pin_led_2 = 4;

int value_out_min = 35;
int value_out_max = 75;
int value_pot = 0;
int value_switch = 0;

int value_current_speed = 0;
int tab_speed[] = { -10, 0, 0, 25, 25, 25, 50, 50, 50, 50, 75, 75, 75, 100, 100 };
int tab_speed_duration[] = { 1, 2, 2, 4, 4, 4, 5, 5, 5, 5, 4, 4, 4, 2, 2 };

void SetMotor(int speed)
{
    if (speed >= 0) {
        digitalWrite(pin_motor_in1, true);
        digitalWrite(pin_motor_in2, false);
    } else {
        digitalWrite(pin_motor_in1, false);
        digitalWrite(pin_motor_in2, true);
    }

    int value_out = map(abs(speed), 0, 100, value_out_min, value_out_max);
    analogWrite(pin_motor_enable, value_out);
}

void SetMon(int speed)
{
    int value_mon = map(abs(speed), 0, 100, 0, 255);
    analogWrite(pin_mon, value_mon);
}

void setup()
{
    pinMode(pin_motor_in1, OUTPUT);
    pinMode(pin_motor_in2, OUTPUT);
    pinMode(pin_motor_enable, OUTPUT);
    pinMode(pin_mon, OUTPUT);
    pinMode(pin_led_1, OUTPUT);
    pinMode(pin_led_2, OUTPUT);
    pinMode(pin_switch, INPUT_PULLUP);
    randomSeed(analogRead(pin_empty));

    SetMon(value_current_speed);
    SetMotor(value_current_speed);
    digitalWrite(pin_led_2, HIGH);
}

void loop()
{
    value_switch = digitalRead(pin_switch);

    if (value_switch == HIGH) {
        digitalWrite(pin_led_1, LOW);
        value_pot = analogRead(pin_pot);
        value_current_speed = map(value_pot, 0, 1023, 0, 100);

        SetMotor(value_current_speed);
        SetMon(value_current_speed);

        delay(500);
    } else {
        digitalWrite(pin_led_1, HIGH);
        int value_rand = random(0, 14);
        int value_target_speed = tab_speed[value_rand];
        int value_delay_speed = tab_speed_duration[value_rand] * 1000;
        int value_delay_accel;

        while (value_current_speed != value_target_speed) {
            int value_diff_speed = value_target_speed - value_current_speed;
            if (value_diff_speed > 50)
                value_delay_accel = 100;
            else if (value_diff_speed > 20)
                value_delay_accel = 150;
            else if (value_diff_speed > 10)
                value_delay_accel = 200;
            else
                value_delay_accel = 300;

            if (value_current_speed < value_target_speed)
                value_current_speed++;
            else
                value_current_speed--;

            SetMon(value_current_speed);
            SetMotor(value_current_speed);

            delay(150);
        }

        delay(value_delay_speed);
    }
}

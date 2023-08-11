
#define PIN_CLOCK 2
#define PIN_RESET 3   // Interrupt 1 for Reset
#define PIN_SEG_A 7
#define PIN_SEG_B 8
#define PIN_SEG_C 9
#define PIN_SEG_D 10
#define PIN_SEG_E 11
#define PIN_SEG_F 12
#define PIN_SEG_G 13
#define PIN_DIGIT_0 14
#define PIN_DIGIT_1 15
#define PIN_DIGIT_2 16
#define PIN_DIGIT_3 17

#define PIN_SEG_START   PIN_SEG_A
#define PIN_SEG_END     PIN_SEG_G
#define PIN_DIGIT_START PIN_DIGIT_0
#define PIN_DIGIT_END   PIN_DIGIT_3

#define SEG_A 1<<0    // 1
#define SEG_B 1<<1    // 2
#define SEG_C 1<<2    // 4
#define SEG_D 1<<3    // 8
#define SEG_E 1<<4    // 16
#define SEG_F 1<<5    // 32
#define SEG_G 1<<6    // 64

#define CFG_0 (SEG_A | SEG_B | SEG_C | SEG_D | SEG_E | SEG_F )
#define CFG_1 (SEG_B | SEG_C)
#define CFG_2 (SEG_A | SEG_B | SEG_G | SEG_E | SEG_D)
#define CFG_3 (SEG_A | SEG_B | SEG_G | SEG_C | SEG_D)
#define CFG_4 (SEG_F | SEG_G | SEG_B | SEG_C)
#define CFG_5 (SEG_A | SEG_F | SEG_G | SEG_C | SEG_D)
#define CFG_6 (SEG_A | SEG_C | SEG_D | SEG_E | SEG_F | SEG_G)
#define CFG_7 (SEG_A | SEG_B | SEG_C)
#define CFG_8 (255)
#define CFG_9 (SEG_A | SEG_C | SEG_D | SEG_B | SEG_F | SEG_G)
#define CFG_OVERFLOW (SEG_G)
#define CFG_BLANK (0)

#define NUMBER_OVERFLOW 10  // index into DIGITS array
#define NUMBER_BLANK    11  // index into DIGITS array

const int DIGITS[] = { CFG_0, CFG_1, CFG_2, CFG_3, CFG_4, CFG_5, CFG_6, CFG_7, CFG_8, CFG_9, CFG_OVERFLOW, CFG_BLANK };


int m_FrameCount = 0;
int m_ClockValue = 0;


// common cathode
int SEGMENT_LED_ON  = HIGH;
int SEGMENT_LED_OFF = LOW;
int COMMON_LED_ON   = LOW;
int COMMON_LED_OFF  = HIGH;


void setup() 
{
    for (int i = PIN_SEG_START; i <= PIN_SEG_END; ++i)
    {
        pinMode(i, OUTPUT);
        digitalWrite(i, SEGMENT_LED_OFF);
    }

    for (int i = PIN_DIGIT_START; i <= PIN_DIGIT_END; ++i)
    {
        pinMode(i, OUTPUT);
    }
    
    pinMode(PIN_CLOCK, INPUT);
    m_ClockValue = digitalRead(PIN_CLOCK);

    attachInterrupt(digitalPinToInterrupt(PIN_RESET), OnReset, RISING);

    Serial.begin(57600);
}


void OnClock()
{
    m_FrameCount++;

    char buffer[32];
    sprintf(buffer, "Frame %i", m_FrameCount);
    Serial.println(buffer);
}


void OnReset()
{
    m_FrameCount = 0;

    Serial.println("Reset");
}


void DisplayDigit(int number, int digit)
{
    int segmentMask = DIGITS[number];
    
    for (int i = PIN_DIGIT_START; i <= PIN_DIGIT_END; ++i)
    {
        digitalWrite(i, COMMON_LED_OFF);
    }

    for (int i = 0; i < 7; ++i)
    {
        if ((segmentMask & (1<<i)) != 0)
        {
            digitalWrite(PIN_SEG_START + i, SEGMENT_LED_ON);
        }
        else
        {
            digitalWrite(PIN_SEG_START + i, SEGMENT_LED_OFF);
        }    
    }

    digitalWrite(PIN_DIGIT_START + digit, COMMON_LED_ON);
}


void DisplayFrame(int frameCount)
{
    if (frameCount >= 10000)
    {
        DisplayOverflow();
        return;
    }

    int digits[] = 
    {
        (int)(frameCount) % 10,
        (int)((frameCount) / 10) % 10,
        (int)((frameCount) / 100) % 10,
        (int)((frameCount) / 1000) % 10
    };

    DisplayDigit(digits[0], 0);
    delay(1);

    if (frameCount >= 10)
    {
        DisplayDigit(digits[1], 1);
    }
    else
    {
        DisplayDigit(NUMBER_BLANK, 1);
    }
    delay(1);

    if (frameCount >= 100)
    {
        DisplayDigit(digits[2], 2);
    }
    else
    {
        DisplayDigit(NUMBER_BLANK, 2);
    }
    delay(1);

    if (frameCount >= 1000)
    {
        DisplayDigit(digits[3], 3);
    }
    else
    {
        DisplayDigit(NUMBER_BLANK, 3);
    }
    delay(1);
}


void DisplayOverflow()
{
    for (int i = 0; i < 4; ++i)
    {
        DisplayDigit(NUMBER_OVERFLOW, i);
        delay(1);
    }
}


void loop() 
{
    DisplayFrame(m_FrameCount);

    int clockValue = digitalRead(PIN_CLOCK);
    if (clockValue != m_ClockValue)
    {
        m_ClockValue = clockValue;

        if (clockValue == HIGH)
        {
            OnClock();
        }
    }
}

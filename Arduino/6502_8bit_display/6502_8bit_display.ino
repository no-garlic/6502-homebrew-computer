
#define PIN_DATA_0      0
#define PIN_DATA_1      1
#define PIN_DATA_2      2
#define PIN_DATA_3      3
#define PIN_DATA_4      4
#define PIN_DATA_5      5
#define PIN_DATA_6      6
#define PIN_DATA_7      7

#define PIN_SEG_A       8
#define PIN_SEG_B       9
#define PIN_SEG_C       10
#define PIN_SEG_D       11
#define PIN_SEG_E       12
#define PIN_SEG_F       13
#define PIN_SEG_G       14

#define PIN_DIGIT_0     15
#define PIN_DIGIT_1     16

#define PIN_IN_FIRST    PIN_DATA_0
#define PIN_IN_LAST     PIN_DATA_7
#define PIN_OUT_FIRST   PIN_SEG_A
#define PIN_OUT_LAST    PIN_DIGIT_1

#define PIN_SEG_START   PIN_SEG_A
#define PIN_SEG_END     PIN_SEG_G
#define PIN_DIGIT_START PIN_DIGIT_0
#define PIN_DIGIT_END   PIN_DIGIT_1

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
#define CFG_A (SEG_A | SEG_B | SEG_C | SEG_E | SEG_F | SEG_G)
#define CFG_B (SEG_C | SEG_D | SEG_E | SEG_F | SEG_G)
#define CFG_C (SEG_A | SEG_D | SEG_E | SEG_F | SEG_G)
#define CFG_D (SEG_B | SEG_C | SEG_D | SEG_E | SEG_G)
#define CFG_E (SEG_A | SEG_D | SEG_E | SEG_F | SEG_G)
#define CFG_F (SEG_A | SEG_E | SEG_F | SEG_G)

#define CFG_BLANK (0)

#define NUMBER_BLANK    16  // index into DIGITS array

const int DIGITS[] = { CFG_0, CFG_1, CFG_2, CFG_3, CFG_4, CFG_5, CFG_6, CFG_7, CFG_8, CFG_9, CFG_A, CFG_B, CFG_C, CFG_D, CFG_E, CFG_F, CFG_BLANK };

int SEGMENT_LED_ON  = HIGH;
int SEGMENT_LED_OFF = LOW;
int COMMON_LED_ON   = LOW;
int COMMON_LED_OFF  = HIGH;

int m_DisplayNumber = 0;


void setup() 
{
    for (int i = PIN_IN_FIRST; i <= PIN_IN_LAST; ++i)
    {
        pinMode(i, INPUT);
    }

    for (int i = PIN_OUT_FIRST; i <= PIN_OUT_LAST; ++i)
    {
        pinMode(i, OUTPUT);
        digitalWrite(i, SEGMENT_LED_OFF);
    }

    Serial.begin(57600);
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


void loop()
{
    int A0 = digitalRead(PIN_DATA_0);
    int A1 = digitalRead(PIN_DATA_1);
    int A2 = digitalRead(PIN_DATA_2);
    int A3 = digitalRead(PIN_DATA_3);
    int A4 = digitalRead(PIN_DATA_4);
    int A5 = digitalRead(PIN_DATA_5);
    int A6 = digitalRead(PIN_DATA_6);
    int A7 = digitalRead(PIN_DATA_7);

    //A1 = A4 = A5 = A7 = 1;
    //A2 = A3 = A6 = A0 = 0;

    int number = A0 + (A1 << 1) + (A2 << 2) + (A3 << 3) + (A4 << 4) + (A5 << 5) + (A6 << 6) + (A7 << 7);
    if (m_DisplayNumber != number)
    {
        m_DisplayNumber = number;
        char buffer[64];
        sprintf(buffer, "A0:%d A1:%d A2:%d A3:%d A4:%d A5:%d A6:%d A7:%d - 0x%02x", A0, A1, A2, A3, A4, A5, A6, A7, m_DisplayNumber);
        Serial.println(buffer);
    }

    int digit0 = number % 16;
    int digit1 = (int) (number / 16);

    DisplayDigit(digit0, 0);
    delay(1);

    DisplayDigit(digit1, 1);
    delay(1);
}





#define PIN_CLOCK       2
#define PIN_READ_WRITE  3

const char PIN_ADDR[] = { 22, 24, 26, 28, 30, 32, 34, 36, 38, 40, 42, 44, 46, 48, 50, 52 };
const char PIN_DATA[] = {39, 41, 43, 45, 47, 49, 51, 53 };

unsigned int g_FrameCount = 0;

void setup() 
{
  for (int i = 0; i < 16; ++i)
  {
    pinMode(PIN_ADDR[i], INPUT);
  }

  for (int i = 0; i < 8; ++i)
  {
      pinMode(PIN_DATA[i], INPUT);
  }

  pinMode(PIN_READ_WRITE, INPUT);

  attachInterrupt(digitalPinToInterrupt(PIN_CLOCK), OnClock, RISING);

  Serial.begin(57600);
}


void OnClock()
{
  g_FrameCount++;

  char buffer[64];
  unsigned int address_bus = 0;
  unsigned int data_bus = 0;

  for (int i = 0; i < 16; ++i)
  {
    int bit = digitalRead(PIN_ADDR[i]) ? 1 : 0;
    address_bus = (address_bus << 1) + bit;
  }

  for (int i = 0; i < 8; ++i)
  {
    int bit = digitalRead(PIN_DATA[i]) ? 1 : 0;
    data_bus = (data_bus << 1) + bit;
  }

  char read_write = digitalRead(PIN_READ_WRITE) ? 'r' : 'w';
  sprintf(buffer, "frame %i:\t 0x%04x  %c 0x%02x", g_FrameCount, address_bus, read_write, data_bus);
  Serial.println(buffer);
}

void loop() 
{
}


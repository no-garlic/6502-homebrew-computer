
#define PIN_MONITOR 7

int currentState = 0;
int currentFrame = 0;
char buffer[64];

void setup() 
{
    pinMode(PIN_MONITOR, INPUT);
    currentState = digitalRead(PIN_MONITOR);

    Serial.begin(57600);
}


void loop() 
{    
    int status = digitalRead(PIN_MONITOR);

    if (status != currentState)
    {
        if (status == 1) 
        {
            currentFrame++;
        }
        sprintf(buffer, "%d\t%d\t%lu", currentFrame, status, micros());
        Serial.println(buffer);        
        currentState = status;
    }

    /*
    if (status != currentState)
    {
        unsigned long now = micros();
        currentState = status;

        sprintf(buffer, "%ul\t %d", now, status);
        Serial.println(buffer);        
    }
    */

}

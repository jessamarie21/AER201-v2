#include <VirtualWire.h>

void setup()
{
    Serial.begin(9600);	  // Debugging only
    Serial.println("setup");

    pinMode(12,OUTPUT);
    pinMode(13,OUTPUT);    

    vw_set_tx_pin(12);  

    // Initialise the IO and ISR
    vw_set_ptt_inverted(true); // Required for DR3100
    vw_setup(2000);	 // Bits per sec
}

void loop()
{
    const char *msg = "HELLO TEAM N.A.D.C.";

    digitalWrite(13, HIGH); // Flash a light to show transmitting
    vw_send((uint8_t *)msg, strlen(msg));
    vw_wait_tx(); // Wait until the whole message is gone
    digitalWrite(13, LOW);
    Serial.println("Done Sending");
    delay(5000);
}

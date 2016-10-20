

void preCalibrate()
{
    uint8_t BaudCMD[28] = {0xB5,0x62,0x06,0x00,0x14,0x00,0x01,0x00,0x00,0x00,0xD0,0x08,0x00,0x00,0x00,0xC2,0x01,0x00,0x07,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0xC0,0x7E};
    uint8_t RateCMD[22] = {0xB5,0x62,0x06,0x08,0x06,0x00,0xC8,0x00,0x01,0x00,0x01,0x00,0xDE,0x6A,0xB5,0x62,0x06,0x08,0x00,0x00,0x0E,0x30};

    Serial.begin(9600);
    delay(100);
    Serial.write(RateCMD,sizeof(RateCMD));
    delay(100);
    Serial.write(BaudCMD,sizeof(BaudCMD));
}

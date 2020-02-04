#include "project.h"

#define EP_IN 1
#define EP_OUT 2

#define BUTTON_SIZE 2


static uint8 BUTTON_INPUT[BUTTON_SIZE];
static uint8 USB_INPUT[BUTTON_SIZE];
static uint8 USB_OUTPUT[BUTTON_SIZE];

void startup(void){
    for(uint8 i = 0; i < sizeof(BUTTON_INPUT); i++){
        BUTTON_INPUT[i] = 0;
    }
    for(uint8 j = 0; j < sizeof(BUTTON_INPUT); j++){
        USB_INPUT[j] = 0;
    }    
    for(uint8 k = 0; k < sizeof(BUTTON_INPUT); k++){
        USB_OUTPUT[k] = 0;
    }  
    USB_Start(0, USB_DWR_VDDD_OPERATION);
}

void read_buttons(void){
    BUTTON_INPUT[0] = Status_1_8_Read();
    BUTTON_INPUT[1] = Status_9_11_Read();
}


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */ 
    startup();
    
    for(;;)
    {
    led_Write(1);
    CyDelay(500);
    led_Write(0);
    CyDelay(500);
    
     while(!USB_GetEPAckState(EP_OUT));
     
    read_buttons();
    
     // if usb reading data is empty, write
    if (USB_GetEPState(EP_OUT) == USB_IN_BUFFER_EMPTY){
        USB_LoadInEP(EP_IN, (uint8 *)USB_OUTPUT, 11); // check last parameter
    }
     // if usb reading data is full, read 
    /*if (USB_GetEPState(EP_OUT) == USB_IN_BUFFER_FULL){
        USB_ReadOutEP(EP_OUT, (uint8 *)USB_INPUT, 11); 
    }*/
    }
}

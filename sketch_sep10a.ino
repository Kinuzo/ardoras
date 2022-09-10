#include <Mouse.h> 
#include <Wire.h> 
#include <SPI.h> 
#include <usbhub.h> 
USB     Usb; 
USBHub     Hub(&Usb); 
 
byte bf[2];
 
#include <hidboot.h> 
 
HIDBoot<USB_HID_PROTOCOL_MOUSE>    HidMouse(&Usb); 
 
String myString;  
int j = 0; 
int c = 0; 
int e = 0; 
int lmb = 0; 
int rmb = 0; 
int mmb = 0; 
int dx; 
int dy; 
int arr[2]; 
int arrv[8]; 
 
class MouseRptParser : public MouseReportParser 
 
{ 
 
  protected: 
 
    void OnMouseMove  (MOUSEINFO *mi); 
 
    void OnLeftButtonUp (MOUSEINFO *mi); 
 
    void OnLeftButtonDown (MOUSEINFO *mi); 
 
    void OnRightButtonUp  (MOUSEINFO *mi); 
 
    void OnRightButtonDown  (MOUSEINFO *mi); 
 
    void OnMiddleButtonUp (MOUSEINFO *mi); 
 
    void OnMiddleButtonDown (MOUSEINFO *mi); 
 
}; 
 
 
void MouseRptParser::OnMouseMove(MOUSEINFO *mi) 
 
{ 
 
  dx = mi->dX; 
 
  dy = mi->dY; 
 
}; 
 
  
 
  
 
void MouseRptParser::OnLeftButtonUp (MOUSEINFO *mi) 
 
{ 
 
  lmb = 0; 
 
}; 
 
  
 
  
 
void MouseRptParser::OnLeftButtonDown (MOUSEINFO *mi) 
 
{ 
 
  lmb = 1; 
 
}; 
 
  
 
  
 
void MouseRptParser::OnRightButtonUp  (MOUSEINFO *mi) 
 
{ 
 
  rmb = 0; 
 
}; 
 
  
 
  
 
void MouseRptParser::OnRightButtonDown  (MOUSEINFO *mi) 
 
{ 
 
  rmb = 1; 
 
}; 
 
  
 
  
 
void MouseRptParser::OnMiddleButtonUp (MOUSEINFO *mi) 
 
{ 
 
  mmb = 0; 
 
}; 
 
  
 
  
 
void MouseRptParser::OnMiddleButtonDown (MOUSEINFO *mi) 
 
{ 
 
  mmb = 1; 
 
}; 
  
MouseRptParser  Prs; 
 
void setup() {
 
  delay(5000); 
  Mouse.begin(); 
  Serial.begin(115200); 
  Serial.setTimeout(1);
   
  Usb.Init(); 
  HidMouse.SetReportParser(0, &Prs); 
  } 
 
void loop() {
  dx = 0; 
 
  dy = 0; 
 
   
 
  j = 0; 
 
  c = 0; 
 
  e = 0; 
 
     
 
  Usb.Task(); 
 
  
 
  //Clicking 
 
  if (lmb == 0){ 
 
    Mouse.release(MOUSE_LEFT); 
 
    } 
 
     
 
  else if (lmb == 1){ 
 
    Mouse.press(MOUSE_LEFT); 
 
    } 
 
  
 
  if (rmb == 0){ 
 
    Mouse.release(MOUSE_RIGHT); 
 
    } 
 
     
 
  else if (rmb == 1){ 
 
    Mouse.press(MOUSE_RIGHT); 
 
    } 
 
  
 
  if (mmb == 0){ 
 
    Mouse.release(MOUSE_MIDDLE); 
 
    } 
 
     
 
  else if (mmb == 1){ 
 
    Mouse.press(MOUSE_MIDDLE); 
 
    } 
    if (Serial.available() > 0) {
    Serial.readBytes(bf, 2);
   
    Mouse.move(bf[0], bf[1], 0);
 
  }
   else { 
 
    Mouse.move(dx, dy); 
 
    } 
}

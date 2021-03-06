#include "OLED.h"

// Class defines
/******************************************************************************/
Adafruit_SSD1306 display(OLED_RESET);

void OLED_Init(){
  // OLED Display setup
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
  // init done

  //Set the font
  //display.setFont(&FreeMono9pt7b);

  // text display tests
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,12);
  //display.println("Hello, world!");
  //display.display();

  // Show image buffer on the display hardware.
  // Since the buffer is intialized with an Adafruit splashscreen
  // internally, this will display the splashscreen.
  // Clear the buffer.
  display.clearDisplay();
  display.drawBitmap(0,0,logo,128,64,WHITE);
  display.display();
  delay(2000);

  // Clear the buffer.
  display.clearDisplay();

}

// Update OLED
void OLED_Update() {
  display.clearDisplay();
  display.setTextSize(2);

  //Line Origin vars
  int X;
  int Y;

  if(running){ // Running page
    // print first line:
    X = 0; Y = 0;
    // Time: H.M.S
    display.setCursor(X,Y);
    display.print("Running");

    // print second line:
    // H:M:S
    X = 0; Y = 20;
    display.setCursor(X,Y);
    display.print(hours);
    display.print(":");
    display.print(minutes);
    display.print(":");
    display.print(seconds);

    // print third line:
    // Stop
    X = 0; Y = 40;
    display.drawRect(X,Y,55,20,WHITE);
    display.setCursor(X+3,Y+3);
    display.print("STOP");

  }// end running page
  // Time Page:
  else if(item == HOUR_ITEM || item == MIN_ITEM || item == SEC_ITEM || item == STARTITEM){
    // print first line:
    X = 0; Y = 0;
    // Time: H.M.S
    display.setCursor(X,Y);
    display.print("Time:H.M.S");

    // print second line:
    // |x| |x| |x| |GO|
    // Hours:
    X = 0; Y = 20;
    if(itemSelect && item == HOUR_ITEM){    //Selected > Draw Filled Rect
      display.fillRect(X,Y,16,20,WHITE);
      display.setCursor(X+3,Y+3);
      display.setTextColor(BLACK);
      display.print(hours);
      display.setTextColor(WHITE);
    }else if(item == HOUR_ITEM){            //Hover    > Draw Rect
      display.drawRect(X,Y,16,20,WHITE);
      display.setCursor(X+3,Y+3);
      display.print(hours);
    }else{                                  // Just Print Value
      display.setCursor(X+3,Y+3);
      display.print(hours);
    }
    // Minutes:
    X = X + 20;
    if(itemSelect && item == MIN_ITEM){     //Selected > Draw Filled Rect
      display.fillRect(X,Y,28,20,WHITE);
      display.setCursor(X+3,Y+3);
      display.setTextColor(BLACK);
      display.print(minutes);
      display.setTextColor(WHITE);
    }else if(item == MIN_ITEM){             //Hover    > Draw Rect
      display.drawRect(X,Y,28,20,WHITE);
      display.setCursor(X+3,Y+3);
      display.print(minutes);
    }else{                                  // Just Print Value
      display.setCursor(X+3,Y+3);
      display.print(minutes);
    }
    // Seconds:
    X = X + 32;
    if(itemSelect && item == SEC_ITEM){     //Selected > Draw Filled Rect
      display.fillRect(X,Y,28,20,WHITE);
      display.setCursor(X+3,Y+3);
      display.setTextColor(BLACK);
      display.print(seconds);
      display.setTextColor(WHITE);
    }else if(item == SEC_ITEM){             //Hover    > Draw Rect
      display.drawRect(X,Y,28,20,WHITE);
      display.setCursor(X+3,Y+3);
      display.print(seconds);
    }else{                                  // Just Print Value
      display.setCursor(X+3,Y+3);
      display.print(seconds);
    }
    // Go!:
    X = X + 34;
    if(itemSelect && item == STARTITEM){    //Selected > Draw Filled Rect
      display.fillRect(X,Y,37,20,WHITE);
      display.setCursor(X+3,Y+3);
      display.setTextColor(BLACK);
      display.print("GO!");
      display.setTextColor(WHITE);
    }else if(item == STARTITEM){            //Hover    > Draw Rect
      display.drawRect(X,Y,37,20,WHITE);
      display.setCursor(X+3,Y+3);
      display.print("GO!");
    }else{                                  // Just Print Value
      display.setCursor(X+3,Y+3);
      display.print("GO!");
    }

    // print third line:
    // calibrate
    X = 0; Y = 44;
    display.setCursor(X, Y);
    display.setTextSize(1);
    display.print("Speed ");
    display.drawChar(X+60, Y, 0x19, WHITE, BLACK, 1);
  } // end first page
  // Second Page: Speed
  else if(item == SPEEDITEM || item == DIRITEM){
    // print first line:
    display.setTextSize(2);
    X = 0; Y = 0;
    // |Speed:|
    if(itemSelect && item == SPEEDITEM){    //Selected > Draw Filled Rect
      display.fillRect(X,Y,127,20,WHITE);
      display.setCursor(X+3,Y+3);
      display.setTextColor(BLACK);
      display.print("Speed: ");
      display.print(speed);
      display.print("%");
      display.setTextColor(WHITE);
    }else if(item == SPEEDITEM){            //Hover    > Draw Rect
      display.drawRect(X,Y,127,20,WHITE);
      display.setCursor(X+3,Y+3);
      display.print("Speed:");
      display.print(speed);
      display.print("%");
    }else{                                  // Just Print Value
      display.setCursor(X+3,Y+3);
      display.print("Speed:");
      display.print(speed);
      display.print("%");
    }

    // print second line:
    X = 0; Y = 22;
    // Dir:
    if(itemSelect && item == DIRITEM){    //Selected > Draw Filled Rect
      display.fillRect(X,Y,127,20,WHITE);
      display.setCursor(X+3,Y+3);
      display.setTextColor(BLACK);
      if(actual_direction == FORWARD) display.print("Dir: A-B");
      else if (actual_direction == BACKWARD) display.print("Dir: B-A");
      display.setTextColor(WHITE);
    }else if(item == DIRITEM){            //Hover    > Draw Rect
      display.drawRect(X,Y,127,20,WHITE);
      display.setCursor(X+3,Y+3);
      if(actual_direction == FORWARD) display.print("Dir: A-B");
      else if (actual_direction == BACKWARD) display.print("Dir: B-A");
    }else{                                  // Just Print Value
      display.setCursor(X+3,Y+3);
      if(actual_direction == FORWARD) display.print("Dir: A-B");
      else if (actual_direction == BACKWARD) display.print("Dir: B-A");
    }
    // print third line:
    // time
    X = 0; Y = 42;
    display.setCursor(X, Y);
    display.setTextSize(1);
    display.print("Calibrate ");
    display.drawChar(X+60, Y, 0x19, WHITE, BLACK, 1);
  } // end second page
  // Third Page: Calibrate
  else if(item == CAL_ITEM){
    // print first line:
    display.setTextSize(2);
    X = 0; Y = 0;
    // |Calibrate|
    if(itemSelect && item == CAL_ITEM){    //Selected > Draw Filled Rect
      display.fillRect(X,Y,127,20,WHITE);
      display.setCursor(X+3,Y+3);
      display.setTextColor(BLACK);
      display.print("Calibrate");
      display.setTextColor(WHITE);
    }else if(item == CAL_ITEM){            //Hover    > Draw Rect
      display.drawRect(X,Y,127,20,WHITE);
      display.setCursor(X+3,Y+3);
      display.print("Calibrate");
    }else{                                  // Just Print Value
      display.setCursor(X+3,Y+3);
      display.print("Calibrate");
    }

    // print second line:
    X = 0; Y = 22;
    // Direction:
    display.setCursor(X, Y);
    display.print("Stps:");
    display.print(calibration_steps);

    // print third line:
    // time
    X = 0; Y = 42;
    display.setCursor(X, Y);
    display.setTextSize(1);
    display.print("Time ");
    display.drawChar(X+60, Y, 0x19, WHITE, BLACK, 1);
  } // end Third page
  else if(item == FRUN_ITEM){
    // print first line:
    display.setTextSize(2);
    X = 0; Y = 0;
    // |Calibrate|
    if(itemSelect && item == CAL_ITEM){    //Selected > Draw Filled Rect
      display.fillRect(X,Y,127,20,WHITE);
      display.setCursor(X+3,Y+3);
      display.setTextColor(BLACK);
      display.print("Free Run");
      display.setTextColor(WHITE);
    }else if(item == CAL_ITEM){            //Hover    > Draw Rect
      display.drawRect(X,Y,127,20,WHITE);
      display.setCursor(X+3,Y+3);
      display.print("Free Run");
    }else{                                  // Just Print Value
      display.setCursor(X+3,Y+3);
      display.print("Free Run");
    }

    // // print second line:
    // X = 0; Y = 22;
    // // Steps:
    // display.setCursor(X, Y);
    // display.print("Stps:");
    // display.print(calibration_steps);
    //
    // // print third line:
    // // time
    // X = 0; Y = 42;
    // display.setCursor(X, Y);
    // display.setTextSize(1);
    // display.print("Time ");
    // display.drawChar(X+60, Y, 0x19, WHITE, BLACK, 1);
  } // end third page


  //DEBUG code
  #ifdef DEBUG_OLED
    //small little debug icon
    if(digitalRead(ENCS) == 0){
      display.fillCircle(119,2,2,WHITE);
    }
    if(running){
      display.fillCircle(122,2,2,WHITE);
    }
    // debug encoder pos
    display.setTextSize(1);
    display.setCursor(0,55);
    display.print(encoderPos);
    display.print(" ");
    display.print(status);
    display.print(" ");
    display.print(step_count);
    display.print(" ");
    //display.print(actual_direction);
    //display.print(" ");
    if (digitalRead(EMAX)) {
      display.print("1");
    }else{
      display.print("0");
    }
    display.print(MAX_FLAG);
    display.print(" ");
    if (digitalRead(EMIN)) {
      display.print("1");
    }else{
      display.print("0");
    }
    display.print(MIN_FLAG);
  #endif // debug oled

  // write out to the display
  display.display();
}

// clear the OLED
void OLED_Clear(bool d){
  display.clearDisplay();
  if(d) display.display();
}

// prints a string in size z at x and y .
void OLED_Print(String s, int x, int y, int z, bool d){
  display.setTextSize(z);
  display.setCursor(x,y);
  display.print(s);
  if(d) display.display();
}

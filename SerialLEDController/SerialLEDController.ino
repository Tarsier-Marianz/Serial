int LED_PIN = 12;

boolean stringComplete  = false;  // whether the string is complete
String cmd = "";                  // a string to hold incoming command
bool ledState = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  cmd.reserve(200);
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    cmd.trim();
    if (cmd == "ON" || cmd == "on") {
      ledState = HIGH;
      Serial.println("ON");
    } else  if (cmd == "OFF" || cmd == "off") {
      ledState = LOW;
      Serial.println("OFF");
    } else {
      Serial.print(cmd);
      Serial.println(" -->invalid command");
    }
    // clear the string command:
    cmd = "";
    stringComplete = false;
  }
  digitalWrite(LED_PIN, ledState);
}

void serialEvent() {
  while (Serial.available()) {
    char inChar = (char)Serial.read();      // get new byte

    if (inChar == '\010') { //if enter key is BACKSPACE (DEC =8, HEX= 8, OCT= 010)
      cmd = cmd.substring(0, cmd.length() - 1);   //remove last char if backspace
    } else {
      // add it to the inputString:
      cmd += inChar;
    }
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\015') {  //if enter key is CARRIAGE RETURN (DEC =13, HEX= D, OCT= 015)
      stringComplete = true;
    }
  }
}

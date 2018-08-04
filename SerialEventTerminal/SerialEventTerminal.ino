String inputString = "";         // a string to hold incoming data
boolean stringComplete  = false;  // whether the string is complete
boolean enableEcho       = false;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    inputString.trim();   //trim to remove unwanted chars
    if (inputString == "E1" || inputString == "e1") {
      enableEcho = true;
    } else  if (inputString == "E0" || inputString == "e0") {
      enableEcho = false;
    } else {
      if (enableEcho) {
        Serial.println();         // if echo enabled then add new line to avoid appending in the same line
      }
      //Serial.println(inputString);
      printPossibleAnswer(inputString);
    }
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

/*
  SerialEvent occurs whenever a new data comes in the
  hardware serial RX.  This routine is run between each
  time loop() runs, so using delay inside loop can delay
  response.  Multiple bytes of data may be available.
*/
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();

    if (inChar == '\010') { //if enter key is BACKSPACE (DEC =8, HEX= 8, OCT= 010)
      inputString = inputString.substring(0, inputString.length() - 1);   //remove last char if backspace
      if (enableEcho) {
        Serial.write(0x08);         // if echo enabled then send BACKSPACE to terminal
      }
    } else {
      // add it to the inputString:
      inputString += inChar;

      // if the incoming character is a newline, set a flag
      // so the main loop can do something about it:
      if (inChar == '\n' || inChar == '\r' || inChar == '\015') {  //if enter key is CARRIAGE RETURN (DEC =13, HEX= D, OCT= 015)
        stringComplete = true;
      } else {
        if (enableEcho) {
          Serial.write(inChar);         // if echo enabled then display entered characters
        }
      }
    }
  }
}

void printPossibleAnswer(String cmd) {
  if (cmd == "AT+CREG?") {
    Serial.println("CREG: 10, 0");
  } else if (cmd == "AT+CSQ?") {
    Serial.println("CSQ: 10, 19");
    Serial.println("     1 , 12");
  } else if (cmd == "HELP" || cmd == "Help" || cmd == "help" || cmd == "?") {
    printHelp();
  } else {
    Serial.println(cmd);
  }
}

void printHelp() {
  Serial.println("Copyright © Tarsier");
   Serial.println("-----Command usage-----");
  Serial.println("AT+<CMD>");
  Serial.println("\t list of commands <CMD>:");
  Serial.println("\tCREG?\t-to view registered network");
  Serial.println("\tCSQ?\t-to signal strength");
  Serial.println("\tHELP\t-to view commands");
  Serial.println("\tE1\t-to enable echo commands");
  Serial.println("\tE0\t-to disable echo commands");
}


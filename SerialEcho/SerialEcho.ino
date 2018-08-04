/* Use a variable called byteRead to temporarily store
   the data coming from the computer */
byte byteRead;

void setup() {
  // Turn the Serial Protocol ON
  Serial.begin(9600);
  Serial.println("Initializing...");
  delay(1000);
  Serial.println("Welcome Marianz");
  Serial.print(">");
}

void loop() {
  /*  check if data has been sent from the computer: */
  if (Serial.available()) {
    /* read the most recent byte */
    byteRead = Serial.read();

    /*Listen for a CARRIAGE RETURN which equals octal code 015 then create new line*/
    if (byteRead == '\015') {
      Serial.println();
      Serial.print(">");
    } else {
      /*ECHO the value that was read, back to the serial port. */
      Serial.write(byteRead);
    }
  }
}

void clearScreenAndHome() {
  Serial.write(27);
  Serial.print("[2J"); // clear screen
  Serial.write(27); // ESC
  Serial.print("[H"); // cursor to home
}

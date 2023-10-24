#define LED_RED 6
#define LED_GREEN 5
#define LED_BLUE 3

#define RED_BUTTON 2
#define GREEN_BUTTON 4

#define ENCODER1 A2
#define ENCODER2 A3

#define POTENTIOMETER A0

volatile bool redPressed = false;

void initRGB()
{

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
}



void initButtons()
{
  pinMode(RED_BUTTON, INPUT_PULLUP);
  pinMode(GREEN_BUTTON, INPUT_PULLUP);
}

void initEncoder()
{
  pinMode(ENCODER1, INPUT_PULLUP);
  pinMode(ENCODER2, INPUT_PULLUP);
}



void setup()
{
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  while (!Serial) {
    // wait for init
  }
  initRGB();
  initButtons();
}

int getNumber(String command, String prefix) {
  String numberStr = command.substring(prefix.length());
  numberStr.trim();
  int number = numberStr.toInt();
  number = max(number, 0);
  number = min(number, 255);
  return number;
}

void loop()
{
  if (Serial.available()) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    command.toLowerCase();
    
    String redCommandPrefix = "red";
    String greenCommandPrefix = "green";
    String blueCommandPrefix = "blue";
    if (command.startsWith(redCommandPrefix)) {
      int pwm = getNumber(command, redCommandPrefix);
      analogWrite(LED_RED, pwm);
    }
    else if (command.startsWith(greenCommandPrefix)) {
      int pwm = getNumber(command, greenCommandPrefix);
      analogWrite(LED_GREEN, pwm);
    }
    else if (command.startsWith(blueCommandPrefix)) {
      int pwm = getNumber(command, blueCommandPrefix);
      analogWrite(LED_BLUE, pwm);
    }
    else {
      Serial.println("Invalid command! Valid commands are");
      Serial.println("red NUM");
      Serial.println("blue NUM");
      Serial.println("green NUM");
    }
  }
}

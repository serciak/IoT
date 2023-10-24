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

void loop()
{
  int redButtonState = !digitalRead(RED_BUTTON);
  int greenButtonState = !digitalRead(GREEN_BUTTON);

  // Wysyłanie stanu przycisków przez łącze szeregowe
  Serial.print("Red Button: ");
  Serial.print(redButtonState);
  Serial.print(", Green Button: ");
  Serial.println(greenButtonState);

  delay(100); // Opcjonalne opóźnienie dla stabilności odczytu
}

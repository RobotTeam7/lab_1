#include <Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <String>

#define POLL_PIN PB12
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET 	-1 // This display does not have a reset pin accessible
Adafruit_SSD1306 display_handler(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void irq_handler();

// Variable to store the value of the counter
volatile uint16_t value = 0;
// Variable to show the program is running
uint16_t loop_count = 0;

void setup() {
  pinMode(POLL_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(POLL_PIN), irq_handler, RISING);

  display_handler.begin(SSD1306_SWITCHCAPVCC, 0x3C);
 
  // Displays Adafruit logo by default. call clearDisplay immediately if you
  // don't want this.
  display_handler.display();
  delay(2000);

  // Displays "Hello world!" on the screen
  display_handler.clearDisplay();
  display_handler.setTextSize(1);
  display_handler.setTextColor(SSD1306_WHITE);
  display_handler.setCursor(0,0);
  display_handler.println("Hello world!");
  display_handler.display();

}

auto win = std::string("YOU WIN!");

void loop() {
  display_handler.clearDisplay();
  display_handler.setCursor(0, 0);
  display_handler.println(loop_count++, DEC);
  display_handler.print(value, DEC);
  display_handler.display();

}

void irq_handler() {
  value++;
}

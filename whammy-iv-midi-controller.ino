#include <MIDI.h>

const int HARMONY_LED = D7;
const int HARMONY_BTN = D3;
int HARMONY_BTN_PREV;

const int OCT_1_LED = D6;
const int OCT_1_BTN = D2;
int OCT_1_BTN_PREV;

const int OCT_2_LED = D5;
const int OCT_2_BTN = D1;
int OCT_2_BTN_PREV;

const int BUTTONS[] = { HARMONY_BTN, OCT_1_BTN, OCT_2_BTN };
int BUTTONS_LEN = sizeof BUTTONS / sizeof BUTTONS[0];

const int LEDS[] = { HARMONY_LED, OCT_1_LED, OCT_2_LED };
int LEDS_LEN = sizeof LEDS / sizeof LEDS[0];

const int MIDI_CHANNEL = 14;

MIDI_CREATE_DEFAULT_INSTANCE();

void setup() {
  //Serial.begin(9600);
  MIDI.begin(MIDI_CHANNEL_OFF);
  
  //pinMode(LED_BUILTIN, OUTPUT);

  pinMode(HARMONY_LED, OUTPUT);
  pinMode(OCT_1_LED, OUTPUT);
  pinMode(OCT_2_LED, OUTPUT);
  
  pinMode(HARMONY_BTN, INPUT_PULLUP);
  pinMode(OCT_1_BTN, INPUT_PULLUP);
  pinMode(OCT_2_BTN, INPUT_PULLUP);

  HARMONY_BTN_PREV = digitalRead(HARMONY_BTN);
  OCT_1_BTN_PREV = digitalRead(OCT_1_BTN);
  OCT_2_BTN_PREV = digitalRead(OCT_2_BTN);
}

void loop() {   
  check(HARMONY_BTN, HARMONY_BTN_PREV, HARMONY_LED);
  HARMONY_BTN_PREV = digitalRead(HARMONY_BTN);
  
  check(OCT_1_BTN, OCT_1_BTN_PREV, OCT_1_LED);
  OCT_1_BTN_PREV = digitalRead(OCT_1_BTN);

  check(OCT_2_BTN, OCT_2_BTN_PREV, OCT_2_LED);
  OCT_2_BTN_PREV = digitalRead(OCT_2_BTN);
  
  delay(200);
}

void check(int btn, int btnPrevState, int led) {
  int btnState = digitalRead(btn);

  if ((btnState == LOW && btnPrevState == HIGH) || (btnState == HIGH && btnPrevState == LOW)) {
    //Serial.println("The button is pressed");
    
    digitalWrite(led, HIGH); 
    disableOtherLeds(led);

    if (btn == HARMONY_BTN) {
      MIDI.sendProgramChange(16, MIDI_CHANNEL);
    }

    if (btn == OCT_1_BTN) {
      MIDI.sendProgramChange(2, MIDI_CHANNEL);
    }

    if (btn == OCT_2_BTN) {
      MIDI.sendProgramChange(3, MIDI_CHANNEL);
    }

    delay(100);
  }
}

void disableOtherLeds(int led) {
  for (int i = 0; i < LEDS_LEN; i++) {
      if (LEDS[i] != led) {
        digitalWrite(LEDS[i], LOW); 
      }
  }
}

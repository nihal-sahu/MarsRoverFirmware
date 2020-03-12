#include "blockingneopixel.h"
#include "mbed.h"

// constexpr T0H
constexpr uint16_t H_0_NS = 200;
constexpr uint16_t H_1_NS = 550;
constexpr uint16_t L_NS = 450;

DigitalOut out(PA_2);

BlockingNeopixel::BlockingNeopixel(int numPixels) { pixelNum = numPixels; }

BlockingNeopixel::~BlockingNeopixel() {}

/*
    Writes 1 to the neopixels
    delay is based on the NRZ timing
*/
void BlockingNeopixel::pulse_1() {
  out.write(1);
  wait_ns(H_1_NS);
  out.write(0);
  wait_ns(L_NS);
}

/*
    Writes 0 to the neopixels
    delay is based on the NRZ timing
*/
void BlockingNeopixel::pulse_0() {
  out.write(1);
  wait_ns(H_0_NS);
  out.write(0);
  wait_ns(L_NS);
}

/*
Writes a byte of data to the pixels. Pixels require 3 bytes of data to be sent
Each byte written is the intensity of each led on each pixel
*/
void BlockingNeopixel::writeByte(const int buffer[8]) {
  for (int i = 7; i >= 0; i--) {
    if (buffer[i] == 1)
      // while bit value is 1
      pulse_1();
    else
      pulse_0();
  }
}

/*
    Writes byte data needed for the specified colour character.
    g = green
    b = blue
    r = red
    w = white
    n = no colour/off
*/
void BlockingNeopixel::showColour(colour selectedColour) {
  for (int i = 0; i < m_pixelNum; i++) {
    switch (colour) {
    case Green:
      writeByte(m_on_buffer);
      writeByte(m_off_buffer);
      writeByte(m_off_buffer);
      break;
    case Blue:
      writeByte(m_off_buffer);
      writeByte(m_off_buffer);
      writeByte(m_on_buffer);
      break;
    case Red:
      writeByte(m_off_buffer);
      writeByte(m_on_buffer);
      writeByte(m_off_buffer);
      break;
    case White:
      writeByte(m_on_buffer);
      writeByte(m_on_buffer);
      writeByte(m_on_buffer);
      break;
    case Off:
      writeByte(m_off_buffer);
      writeByte(m_off_buffer);
      writeByte(m_off_buffer);
      break;

    // can possibly add more colours but will need custom byte data so send
    default:
      break;
    }
  }
}

// tells pixels to turn on and off n times
void BlockingNeopixel::blinkPixels(int flashes, colour selectedColour) {
  for (int i = 0; i < flashes; i++) {
    for (int i = 0; i < m_pixelNum; i++) {
      showColour(colour);
    }
    wait(0.5);
    for (int i = 0; i < m_pixelNum; i++) {
      showColour('n');
    }
    wait(0.5);
  }
}

// Provided an array of integers of the RGB values (in GRB order), shows those
// colours on the pixels
void BlockingNeopixel::writeAnyRGB(const int colour[3]) {
  int colourBuffer[3] = {colour[0], colour[1], colour[2]};
  int buffer[][8] = {{}, {}, {}};
  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < 8; i++) {
      buffer[j][i] = colourBuffer[j] % 2;
      colourBuffer[j] /= 2;
    }
  }

  for (int k = 0; k < m_pixelNum; k++) {
    writeByte(buffer[0]);
    writeByte(buffer[1]);
    writeByte(buffer[2]);
  }
}

// Flashing Green
void BlockingNeopixel::flashGreen(int numFlashes, float delay_s) {
  for (int i = 0; i < numFlashes; i++) {
    showColour('g');
    wait(delay_s);
    showColour('n');
    wait(delay_s);
  }
}

// show solid red on all pixels
void BlockingNeopixel::displayRed() { showColour(Red); }

// show solid blue on all pixels
void BlockingNeopixel::displayBlue() { showColour(Blue); }

// turn off all pixels
void BlockingNeopixel::shutdown() { showColour(Off); }

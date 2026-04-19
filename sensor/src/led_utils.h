#pragma once

#define LED_R 14
#define LED_G 8
#define LED_B 17

/*
 * Shorthand for running pinMode for each channel.
 */
void setupRgbLed();

/*
 * Enable breathing effect on set pin.
 */
void ledBreathe(int pin, int delay_ms, int min = 0, int max = 255);

// https://gist.github.com/fairlight1337/4935ae72bcbcc1ba5c72
/*
 * Converts a given set of HSV values `h', `s', `v' into RGB
 * coordinates. The output RGB values are in the range [0, 1], and
 * the input HSV values are in the ranges h = [0, 360], and s, v =
 * [0, 1], respectively.
 */
void HSVtoRGB(float& fR, float& fG, float& fB, float& fH, float& fS, float& fV);

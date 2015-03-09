/*
 * File:   Human_Harp_Player_Test_App.pde
 * Author: Seb Madgwick
 *
 * Test application for Human Harp Player. Displays measurements as text and
 * time-series plots.
 *
 * Tested with Processing 2.2.1.
 */

//------------------------------------------------------------------------------
// Imported libraries

import processing.serial.*;

//------------------------------------------------------------------------------
// Variables

Serial port;
String receivedString = "";
float distance, velocity, azimuth, elevation, angularRate;
String[] rowTitles = { "Distance", "Velocity", "Azimuth", "Elevation", "Angular rate" };
float rowHeight;
float x = 0;
int previousWidth, previousHeigth;  // used to detect window resize

//------------------------------------------------------------------------------
// Main functions

void setup() {
  port = new Serial(this, Serial.list()[0], 115200); // open first serial port in available list
  size(1280, 720);
  if (frame != null) {
    frame.setResizable(true);
  }
  drawBackground(-1); // draw all rows
}

void draw() {
  drawDistance();
  drawVelocity();
  drawAzimuth();
  drawElevation();
  drawAngularRate();

  // Restart if graph full or window resized
  if (++x >= width || previousWidth != width || previousHeigth != height) {
    previousWidth = width;
    previousHeigth = height;
    rowHeight = height / rowTitles.length;
    x = 0;
    drawBackground(-1);
  }
}

//------------------------------------------------------------------------------
// Draw functions

void drawBackground(int selectedRow) {
  PFont f = createFont("Arial", 16, true); // Arial, 16 point, anti-aliasing on
  for (int i = 0; i < rowTitles.length; i++) {
    if(selectedRow == -1 || selectedRow == i) {

      // Draw rectangle for each row
      fill(0);
      strokeWeight(1); // rectangle border width
      stroke(64);
      rect(0, i * rowHeight, width, rowHeight);

      // Print row title
      fill(64);
      textAlign (LEFT);
      textFont(f, (int)rowHeight * 0.2);
      text(rowTitles[i], 10, (i * rowHeight) + (0.2 * rowHeight));
    }
  }
}

void drawDistance() {
  drawBackground(0);
  PFont f = createFont("Arial", 16, true); // Arial, 16 point, anti-aliasing on
  fill(192);
  textAlign(CENTER);
  textFont(f, (int)rowHeight);
  text(nf((int)distance, 1), width * 0.5, rowHeight * 0.9);
}

void drawVelocity() {
  strokeWeight(1);
  if(velocity < 0) {
    stroke(192, 64, 64);
  }
  else {
    stroke(64, 64, 192);
  }
  float y = mapAndClip(velocity, 50000, -50000, 1 * rowHeight, 2 * rowHeight);
  line(x, 1.5 * rowHeight, x, y);
}

void drawAzimuth() {
  drawBackground(2);
  PFont f = createFont("Arial", 16, true); // Arial, 16 point, anti-aliasing on
  fill(192);
  textAlign(CENTER);
  textFont(f, (int)rowHeight);
  text(nf(azimuth, 1, 2), width * 0.5, 2 * rowHeight + rowHeight * 0.9);
}

void drawElevation() {
  drawBackground(3);
  PFont f = createFont("Arial", 16, true); // Arial, 16 point, anti-aliasing on
  fill(192);
  textAlign(CENTER);
  textFont(f, (int)rowHeight);
  text(nf(elevation, 1, 2), width * 0.5, 3 * rowHeight + rowHeight * 0.9);
}

void drawAngularRate() {
  strokeWeight(1);
  stroke(64, 192, 64);
  float y = mapAndClip(angularRate, 2000, 0, 4 * rowHeight, 5 * rowHeight);
  line(x, 5 * rowHeight, x, y);
}

float mapAndClip(float value, float start1, float stop1, float start2, float stop2) {
  float result = map(value, start1, stop1, start2, stop2);
  if(result < start2) {
    result = start2;
  }
  else if(result > stop2) {
    result = stop2;
  }
  return result;
}

//------------------------------------------------------------------------------
// Send commands

void mousePressed() {
  if (mouseButton == LEFT) {
    port.write('Z'); // 'zero'
  } else if (mouseButton == RIGHT) {
    port.write('R'); // reset
  }
  port.write('\n');
}

//------------------------------------------------------------------------------
// OSC receive event

void serialEvent(Serial port) {
  
  // Add received byte to buffer
  char newChar = (char)port.read();
  receivedString += newChar;

  // Process complete string
  if (newChar == '\n') {

    // Process arguments
    //print(receivedString); // print string for debugging
    String values[] = split(receivedString, ',');
    if(values.length == 5) { // fetch values if measurement data
      distance = float(values[0]);
      velocity = float(values[1]);
      azimuth = float(values[2]) / 100;
      elevation = float(values[3]) / 100;
      angularRate = float(values[4]) / 100;
    }
    else { // else print received message, e.g. "Reset", "Zero", "Firmware: vX.X"
      print(receivedString);
    }
    
    // Flush buffer
    receivedString = "";
  }
}

//------------------------------------------------------------------------------
// End of file


// Algoithim based from
// https://www.geeksforgeeks.org/midpoint-ellipse-drawing-algorithm/
#include "BMP.h"
#include <cmath>
#include <iostream>

using namespace std;

void drawEllipse(BMP &img, int xc, int yc, int rx, int ry) {
  int x = 0, y = ry;
  int px = 0, py = 2 * rx * rx * y;

  // region 1
  int p = round(ry * ry - rx * rx * ry + rx * rx / 4.0);
  while (px < py) {
    img.set_pixel(xc + x, yc + y, 255, 255, 255, 0);
    img.set_pixel(xc - x, yc + y, 255, 255, 255, 0);

    x++;
    px = px + 2 * ry * ry;
    if (p < 0)
      p = p + ry * ry + px;
    else {
      y--;
      py = py - 2 * rx * rx;
      p = p + ry * ry + px - py;
    }
  }

  // region 2
  p = round(ry * ry * (x + 0.5) * (x + 0.5) + rx * rx * (y - 1) * (y - 1) -
            rx * rx * ry * ry);
  while (y >= 0) {
    img.set_pixel(xc + x, yc + y, 255, 255, 255, 0);
    img.set_pixel(xc - x, yc + y, 255, 255, 255, 0);

    y--;
    py = py - 2 * rx * rx;
    if (p > 0)
      p = p + rx * rx - py;
    else {
      x++;
      px = px + 2 * ry * ry;
      p = p + rx * rx - py + px;
    }
  }
}

int main() {
  int width = 1400;
  int height = 1800;

  BMP img(width, height, false);
  img.fill_region(0, 0, width, height, 0, 0, 0, 0);

  int xc = width / 2;
  int yc = height / 2;
  int rx = 384;
  int ry = 768;

  drawEllipse(img, xc, yc, rx, ry);

  img.write("output.bmp");

  return 0;
}

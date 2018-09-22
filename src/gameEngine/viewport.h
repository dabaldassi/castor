#ifndef VIEWPORT_H
#define VIEWPORT_H

/**
 * This cass contains information relative to the area visible in the windows
 */
struct Viewport {
  static constexpr float METER_TO_PIXEL = 1.;

	float x;
	float y;
	float width;
	float height;

  Viewport(int width, int height) 
  : x(0), y(0), width(width / METER_TO_PIXEL), height(height / METER_TO_PIXEL) {}
};

#endif /* VIEWPORT_H */

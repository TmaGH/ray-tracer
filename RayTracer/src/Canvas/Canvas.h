#pragma once
#include <array>
#include<memory>
#include<algorithm>
#include<sstream>
#include "Color/Color.h"

class Canvas
{
private:
	size_t w, h;
	std::shared_ptr <Color[]> canvas_ptr;
public:
	Canvas(size_t width, size_t height): w(width), h(height) {
		canvas_ptr = std::make_shared<Color[]>(w * h);
	}

	int width() {
		return w;
	}

	int height() {
		return h;
	}

	std::shared_ptr<Color[]> pixels() {
		return canvas_ptr;
	}

	void writePixel(int x, int y, Color c) {
		canvas_ptr[x + y * w] = c;
	}

	Color pixelAt(int x, int y) {
		return canvas_ptr[x + y * w];
	}

	static std::string canvasToPPM(Canvas c) {
		int charsWritten = 0;
		std::ostringstream oss;

		oss << "P3" << std::endl;
		oss << c.w << ' ' << c.h << std::endl;
		oss << 255 << std::endl;

		charsWritten = oss.tellp();

		for (int y = 0; y < c.h; y++) {
			int charsWrittenLine = 0;
			for (int x = 0; x < c.w; x++) {
				auto pixel = c.pixelAt(x, y);
				oss << std::clamp((int) std::round(255 * pixel.red()), 0, 255);

				charsWrittenLine = oss.tellp();
				if (charsWrittenLine - charsWritten > 65) {
					oss << std::endl;
					charsWritten = charsWrittenLine;
				}
				else {
					oss << ' ';
				}

				oss << std::clamp((int)std::round(255 * pixel.green()), 0, 255);

				charsWrittenLine = oss.tellp();
				if (charsWrittenLine - charsWritten > 65) {
					oss << std::endl;
					charsWritten = charsWrittenLine;
				}
				else {
					oss << ' ';
				}

				oss << std::clamp((int) std::round(255 * pixel.blue()), 0, 255);

				charsWrittenLine = oss.tellp();
				if (charsWrittenLine - charsWritten > 65) {
					oss << std::endl;
					charsWritten = charsWrittenLine;
				}
				else {
					if (x < c.w - 1) oss << ' ';
				}
			}
			oss << std::endl;
			charsWritten = charsWrittenLine;
		}
		oss << std::endl;

		return oss.str();
	}

};


#ifndef COLOREMITTER_H
#define COLOREMITTER_H

#include <iosfwd>

class ColorEmitter {
protected:
	enum Color {
		BLACK = 0,
		RED,
		GREEN,
		YELLOW,
		BLUE,
		MAGENTA,
		CYAN,
		WHITE,
		STANDARD
	};

	virtual void emitColor(std::ostream& os, Color c, bool background) = 0;
private:
	class ColorManipulator {
		ColorEmitter *emitter;
		Color color;
		bool background;
	public:
		ColorManipulator(ColorEmitter* emitter, Color color, bool background)
			: emitter(emitter), color(color), background(background) {}

		void emitColor(std::ostream& os) {
			emitter->emitColor(os, color, background);
		}
	};
public:
	virtual ~ColorEmitter() {}

	ColorManipulator standard() { return ColorManipulator(this, STANDARD,
		                                                  false); }
	ColorManipulator red() { return ColorManipulator(this, RED, false); }
	ColorManipulator green() { return ColorManipulator(this, GREEN, false); }
	ColorManipulator yellow() { return ColorManipulator(this, YELLOW, false); }
	ColorManipulator blue() { return ColorManipulator(this, BLUE, false); }
	ColorManipulator magenta() { return ColorManipulator(this, MAGENTA, false); }
	ColorManipulator cyan() { return ColorManipulator(this, CYAN, false); }
	ColorManipulator white() { return ColorManipulator(this, WHITE, false); }
	ColorManipulator black() { return ColorManipulator(this, BLACK, false); }

	ColorManipulator redbg() { return ColorManipulator(this, RED, true); }
	ColorManipulator greenbg() { return ColorManipulator(this, GREEN, true); }
	ColorManipulator yellowbg() { return ColorManipulator(this, YELLOW, true); }
	ColorManipulator bluebg() { return ColorManipulator(this, BLUE, false); }
	ColorManipulator magentabg() { return ColorManipulator(this, MAGENTA, true); }
	ColorManipulator cyanbg() { return ColorManipulator(this, CYAN, true); }
	ColorManipulator whitebg() { return ColorManipulator(this, WHITE, true); }
	ColorManipulator blackbg() { return ColorManipulator(this, BLACK, true); }

	friend std::ostream& operator<<(std::ostream& os, ColorManipulator& cm);
};

std::ostream& operator<<(std::ostream& os, ColorEmitter::ColorManipulator& cm);

#ifdef _WIN32
class WindowsColorEmitter : public ColorEmitter {
	int oldcolor;
public:
	WindowsColorEmitter();
	~WindowsColorEmitter();
protected:
	void emitColor(std::ostream& os, Color c, bool background);
};
#else
class PosixColorEmitter : public ColorEmitter {
protected:
	void emitColor(std::ostream& os, Color c, bool background);
};
#endif

#endif // COLOREMITTER_H

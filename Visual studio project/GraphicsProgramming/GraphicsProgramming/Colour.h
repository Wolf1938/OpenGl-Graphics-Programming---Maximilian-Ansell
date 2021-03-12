#pragma once
class Colour
{
public:
	Colour(float _red, float _green, float _blue, float _alpha = 1);
	~Colour();

	float getRed() { return red; }
	void setRed(float _red) { red = _red; }

	float getGreen() { return green; }
	void setGreen(float _green) { red = green; }

	float getBlue() { return blue; }
	void setBlue(float _blue) { red = _blue; }
	
	float getAlpha() { return alpha; }
	void setAlpha(float _alpha) { red = _alpha; }

private:
	float red;
	float green;
	float blue;
	float alpha;		
};
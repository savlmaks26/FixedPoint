#include <cmath>
#include <iostream>
using namespace std;
#pragma once

class FixedPoint {
private:
	int16_t  ipart;
	int8_t fpart;
public:
	FixedPoint(int ipart = 0, int fpart = 0) {
		this->ipart = ipart;
		this->fpart = fpart;
		if (ipart < 0.0 || fpart < 0) {
			if (ipart > 0.0)
				this->ipart = -ipart;
			if (fpart > 0.0)
				this->fpart = -fpart;
		}
	}
	FixedPoint(double fp) {
		ipart = static_cast<int>(fp);
		fpart = static_cast<int>(round(fp * 100.00)) % 100;
	}
	friend ostream& operator<<(ostream& out, FixedPoint& fp);
	operator double() const {
		return ipart + static_cast<double>(fpart) / 100;
	}
	FixedPoint& operator-() {
		ipart = -ipart;
		fpart = -fpart;
		return *this;
	}
	friend FixedPoint operator+ (FixedPoint& fp1, FixedPoint& fp2);
	bool operator==(const FixedPoint& fp) {
		return (fpart == fp.fpart && ipart == fp.ipart) ? true : false;
	}

	friend istream& operator>>(istream& in, FixedPoint& fp);

};

FixedPoint operator+ (FixedPoint& fp1, FixedPoint& fp2) {
	int fpart = fp1.fpart + fp2.fpart;
	int ipart = fp1.ipart + fp2.ipart;

	ipart += fpart / 100;
	fpart % 100;
	return FixedPoint(ipart, fpart);
}
istream& operator>>(istream& in, FixedPoint& fp) {
	double f;
	in >> f;
	fp = FixedPoint(f);
	return in;
}
ostream& operator<<(ostream& out, FixedPoint& fp) {
	out << static_cast<double>(fp);
	return out;
}
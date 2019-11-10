#pragma once
#include "pch.h"
#include <vector>
#include <iostream>
#include <string>

struct Vec3D {
	int x;
	int y;
	int z;
};

class VecArrayStat {
private: std::vector <Vec3D> v;
		 double m_mean, m_rms;
public:
	VecArrayStat(const std::string& fname);
	double get_max() const;
	double get_min() const;
	double mean() const;
	double rms() const;
	size_t count(int a) const;
	void print() const;
};
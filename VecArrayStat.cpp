#include "pch.h"
#include "VecArrayStat.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <numeric>
#include <cmath>

using namespace std;

std::istream& operator >> (std::istream& is, Vec3D& n) {
	is >> n.x >> n.y >> n.z;
	return is;
}
std::ostream& operator << (std::ostream& os, const Vec3D& n) {
	os << n.x << " " << n.y << " " << n.z << " " << endl;
	return os;
}

double norm(Vec3D vec) {
	return sqrt(vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

bool comparator(Vec3D vec1, Vec3D vec2) {
	double norm1 = norm(vec1);
	double norm2 = norm(vec2);
	return norm1 < norm2;
}

VecArrayStat::VecArrayStat(const string& fname)
{

	v.clear();
	ifstream file(fname, ifstream::in);
	if (!file.good()) {
		cout << "can not open file" << endl;
		exit(1);
	}
	while (!file.eof()){
		Vec3D n;
		file >> n;
		v.push_back(n);
	}

	sort(v.begin(), v.end(), comparator);
	vector<double> vec_n(v.size());
	transform(v.begin(), v.end(), vec_n.begin(), [](Vec3D v) { return norm(v); });
	m_mean = accumulate(vec_n.begin(), vec_n.end(), 0.)/vec_n.size();

	vector<double> squares(v.size());
	auto squarer = [](int a) { return a * a; };
	transform(vec_n.begin(), vec_n.end(), squares.begin(), squarer);
	double mean_sq = accumulate(squares.begin(), squares.end(), 0.) / squares.size();
	m_rms = sqrt(mean_sq - m_mean * m_mean);
}

double VecArrayStat::get_max() const { return norm(v.back()); }
double VecArrayStat::get_min() const { return norm(v.front()); }
double VecArrayStat::mean() const { return m_mean; }
double VecArrayStat::rms() const { return m_rms; }

size_t VecArrayStat::count(int a) const {
	int count;
	vector<double> vec_n(v.size());
	transform(v.begin(), v.end(), vec_n.begin(), [](Vec3D v) { return norm(v); });
	auto p = upper_bound(vec_n.begin(), vec_n.end(), a);
	count = distance(p, vec_n.end());
	return count;
}
void VecArrayStat::print() const
{
	cout << "the length of vectors is " << v.size() << endl;
	for (auto const &value : v)
	{
		cout << value << ' ';
	}
	int a;
	cout << "input your value" << endl;
	cin >> a;
	cout << "number of vector's norms which are more then your value: " << count(a) << endl;
}
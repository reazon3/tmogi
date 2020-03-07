#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;
struct  Point
{
	string benchmark_name;
	double height;
};

void ImportBenchmarks(vector<Point>& points) 
{
	ifstream heights_file("Var17_heights.txt");
	string benchmark_name;
	double height;
	vector <string> benchmark_names;
	vector<double> heights;
	while (heights_file >> benchmark_name >> height)
	{
		//cout << benchmark_name << "" << height << "\n";
		Point p;
		p.benchmark_name = benchmark_name;
		p.height = height;
		points.push_back(p);

	}

	for (auto pp : points)
	{
		cout << pp.benchmark_name << "" << pp.height << "\n";
	}
}
struct Meas
{
	string from_station;
	string to_station;
	double elevation;
	double distance;
	string leveling_class;
};
void ImportMeaseurement(vector<Meas>& sections)
{
	ifstream measurements_file("Var17_measurements.txt");
	string from_station;
	string to_station;
	double elevation;
	double distance;
	string leveling_class;

	
	while (measurements_file >> from_station >> to_station >> elevation
		>> distance >> leveling_class)
	{
		Meas m;
		m.from_station = from_station;
		m.to_station = to_station;
		m.elevation = elevation;
		m.distance = distance;
		m.leveling_class = leveling_class;
		sections.push_back(m);
	}
	for (auto section : sections) 
	{
		cout << section.from_station << "\t" << section.to_station << "\t" 
			<< section.elevation << "\t" << section.distance << "\t" 
			<< section.leveling_class << "\n";
	}
}
void GetResiduals(vector <Point>& points, vector <Meas>& sections)
{
double w1 = sections[1].elevation + sections[5].elevation + sections[4].elevation;
	double w2 = sections[2].elevation - sections[5].elevation - sections[6].elevation;
	double w3 = sections[3].elevation + sections[7].elevation + sections[6].elevation;
	double w4 = sections[0].elevation + sections[1].elevation + sections[2].elevation + sections[3].elevation - (points[1].height - points[0].height);

	cout << "w1= " << w1 << "\n";
	cout << "w2= " << w2 << "\n";
	cout << "w3= " << w3 << "\n";
	cout << "w4= " << w4 << "\n";
}

int main()
{
	vector <Point> points;
	ImportBenchmarks(points);

	vector <Meas> sections;
	ImportMeaseurement(sections);

	GetResiduals(points, sections);
	vector<double> weights;
	vector<double> inverse_weights;
	for (auto s : sections)
	{
		double rms = 20 * sqrt(s.distance); // миллиметры
		double weight = pow(1 / (rms / 1000.0), 2); // вес измерения
		weights.push_back(weight);
		inverse_weights.push_back(1 / weight);
	}
	
	vector<int> B1 = { 0, 1, 0, 0, 1, 1, 0, 0 };
	vector<int> B2 = { 0, 0, 1, 0, 0, -1, -1, 0 };
	vector<int> B3 = { 0, 0, 0, 1, 0, 0, 1, 1 };
	vector<int> B4 = { 1, 1, 1, 1, 0, 0, 0, 0 };

	vector<vector<int> > B = { B1, B2, B3, B4 };
	for (int i = 0; i < B.size(); ++i)
	{
		for (int j = 0; j < B1.size(); ++j)
		{
			cout << B[i][j] << "\t";
		}
		cout << "\n";
	}
	double qb1b1 = 0, qb1b2 = 0, qb1b3 = 0, qb1b4 = 0;
	double qb2b1 = 0, qb2b2 = 0, qb2b3 = 0, qb2b4 = 0;
	double qb3b1 = 0, qb3b2 = 0, qb3b3 = 0, qb3b4 = 0;
	double qb4b1 = 0, qb4b2 = 0, qb4b3 = 0, qb4b4 = 0;

	for (int i = 0; i < B1.size(); ++i)
	{
		qb1b1 +=  inverse_weights[i] * B[0][i] * B[0][i];
		qb1b2 +=  inverse_weights[i] * B[0][i] * B[1][i];
		qb1b3 +=  inverse_weights[i] * B[0][i] * B[2][i];
		qb1b4 +=  inverse_weights[i] * B[0][i] * B[3][i];

		qb2b1 += inverse_weights[i] * B[1][i] * B[0][i];
		qb2b2 += inverse_weights[i] * B[1][i] * B[1][i];
		qb2b3 += inverse_weights[i] * B[1][i] * B[2][i];
		qb2b4 += inverse_weights[i] * B[1][i] * B[3][i];

		qb3b1 += inverse_weights[i] * B[2][i] * B[0][i];
		qb3b2 += inverse_weights[i] * B[2][i] * B[1][i];
		qb3b3 += inverse_weights[i] * B[2][i] * B[2][i];
		qb3b4 += inverse_weights[i] * B[2][i] * B[3][i];

		qb4b1 += inverse_weights[i] * B[3][i] * B[0][i];
		qb4b2 += inverse_weights[i] * B[3][i] * B[1][i];
		qb4b3 += inverse_weights[i] * B[3][i] * B[2][i];
		qb4b4 += inverse_weights[i] * B[3][i] * B[3][i];


	 }
	cout << setw(10) << qb1b1 << setw(10) << qb1b2 << setw(10) << qb1b3 << setw(10) << qb1b4 << "\n";
	cout << setw(10) << qb2b1 << setw(10) << qb2b2 << setw(10) << qb2b3 << setw(10) << qb2b4 << "\n";
	cout << setw(10) << qb3b1 << setw(10) << qb3b2 << setw(10) << qb3b3 << setw(10) << qb3b4 << "\n";
	cout << setw(10) << qb4b1 << setw(10) << qb4b2 << setw(10) << qb4b3 << setw(10) << qb4b4 << "\n";
	system("pause");
}
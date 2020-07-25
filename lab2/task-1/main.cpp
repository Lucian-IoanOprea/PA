#include <fstream>
#include <iomanip>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

struct Object {
	int weight;
	int price;
	Object(int _weight, int _price) : weight(_weight), price(_price) {}
};
bool compareto( const Object& a, const Object& b){
	return (double) a.price/a.weight > (double) b.price/b.weight;
}

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	double n, w;
	vector<Object> objs;
	void read_input() {
		ifstream fin("in");
		fin >> n >> w;
		for (int i = 0, weight, price; i < n; i++) {
			fin >> weight >> price;
			objs.push_back(Object(weight, price));
		}
		fin.close();
	}

	double get_result() {
		double profit = 0;
		sort(objs.begin(),objs.end(),compareto);
		for( int i = 0; i < objs.size() && w > 0; i++){
			if( w - objs[i].weight >= 0){
				w -= objs[i].weight;
				profit += objs[i].price;
			}
			else
			{ 
				profit = profit + double(w/objs[i].weight)*objs[i].price;
				w = 0;
				break;
			}
		}
		return profit;
	}

	void print_output(double result) {
		ofstream fout("out");

		fout << setprecision(4) << fixed << result;
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}
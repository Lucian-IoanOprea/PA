#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Task {
public:
	void solve() {
		read_input();
		print_output(fast_pow(base, exponent, mod));
	}

private:
	long long base, exponent, mod;

	void read_input() {
		ifstream fin("in");
		fin >> base >> exponent >> mod;
		fin.close();
	}

	int fast_pow(long base, long exponent, long mod) {
	long long sol=1;
 	while( exponent!= 0){
 		if( exponent%2==1)
 			sol=(sol*base)%mod;
 			base = (base*base) % mod;
 			exponent/=2;
   	 	}
		return sol%mod ;
	}

	void print_output(int result) {
		ofstream fout("out");
		fout << result;
		fout.close();
	}
};

int main() {
	Task task;
	task.solve();
	return 0;
}

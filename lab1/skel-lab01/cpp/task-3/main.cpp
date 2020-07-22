#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Task {
public:
	void solve() {
		read_input();
		print_output(get_result(x, y, n));
	}

private:
	int n, x, y;

	void read_input() {
		ifstream fin("in");
		fin >> n >> x >> y;
		fin.close();
	}

	int get_result(int x, int y, int n) {
    if(n==0) return 1;
    long long p=(1<<(n-1));
    if( x<=p&&y<=p) return get_result(x, y, n-1);
    if(x<=p&&y>p) return get_result(x, y-p, n-1)+1LL*(p*p);
    if(x>p&&y<=p) return get_result(x-p, y, n-1)+1LL*(2*p*p);
    if(x>p&&y>p) return get_result(x-p, y-p, n-1)+1LL*(3*p*p);
    return 1;
		return 0;
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

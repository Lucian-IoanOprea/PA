#include <fstream>
#include <vector>
using namespace std;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n, m;
	vector<int> dist;

	void read_input() {
		ifstream fin("in");
		fin >> n >> m;
		for (int i = 0, d; i < n; i++) {
			fin >> d;
			dist.push_back(d);
		}
		fin.close();
	}

	int get_result() {
		int no_opriri = 0;
		int current_rezervor = m;
		for(int i = 0; i < dist.size() - 1; i++){
			if( current_rezervor > (dist[i + 1] -dist[i]) ){
				current_rezervor -= (dist[i + 1] -dist[i]);
			}
			else{
				no_opriri++;
				current_rezervor = m;
			}
		}

		return no_opriri;
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
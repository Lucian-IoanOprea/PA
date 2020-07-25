#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;

const int kNmax = 100005;

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	int m;
	int source;
	vector<int> adj[kNmax];

	void read_input() {
		ifstream fin("in");
		fin >> n >> m >> source;
		for (int i = 1, x, y; i <= m; i++) {
			fin >> x >> y;
			adj[x].push_back(y);
			adj[y].push_back(x);
		}
		fin.close();
	}

	vector<int> get_result() {
		vector<int> d(n + 1,-1);
		vector<int> viz(n+1,0);
		queue<int> mycoada;
		d[source]  = 0;
		viz[source] = 1;
		mycoada.push(source);
		while(!mycoada.empty()){
			int node = mycoada.front();
			for( int i = 0; i < adj[node].size(); i++){
				if(viz[adj[node][i]] == 0){
					viz[adj[node][i]] = 1;
					d[adj[node][i]] = d[node] + 1;
					mycoada.push(adj[node][i]);
				}
			}
			mycoada.pop();
		}
		return d;
	}
	void print_output(vector<int> result) {
		ofstream fout("out");
		for (int i = 1; i <= n; i++) {
			fout << result[i] << (i == n ? '\n' : ' ');
		}
		fout.close();
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}

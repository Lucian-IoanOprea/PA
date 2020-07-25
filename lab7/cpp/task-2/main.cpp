#include <fstream>
#include <vector>
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
	vector<int> adj[kNmax];

	void read_input() {
		ifstream fin("in");
		fin >> n >> m;
		for (int i = 1, x, y; i <= m; i++) {
			fin >> x >> y;
			adj[x].push_back(y);
		}
		fin.close();
	}
	void dfs(int node,vector<int> &topsort,vector<int> &viz){
		int i;
		for( int i = 0; i < adj[node].size(); i++){
			if( viz[adj[node][i]] == 0){
				viz[adj[node][i]] = 1;
				dfs(adj[node][i],topsort,viz);
			}
		}
		topsort.push_back(node);
	}

	vector<int> get_result() {
		vector<int> topsort;
		vector<int> viz(n + 1,0);
		for( int i = 1; i <= n; i++){
			if(  viz[i] == 0 ){
				viz[i] = 1;
				dfs(i,topsort,viz);
			}

		}
		reverse(topsort.begin(),topsort.end());
		return topsort;
	}

	void print_output(vector<int> result) {
		ofstream fout("out");
		for (int i = 0; i < int(result.size()); i++) {
			fout << result[i] << ' ';
		}
		fout << '\n';
		fout.close();
	}
};

int main() {
	Task *task = new Task();
	task->solve();
	delete task;
	return 0;
}

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
	vector<int> adjt[kNmax];
	vector<bool> viz;
	vector<int> postorder;
	void read_input() {
		ifstream fin("in");
		fin >> n >> m;
		for (int i = 1, x, y; i <= m; i++) {
			fin >> x >> y;
			adj[x].push_back(y);
			adjt[y].push_back(x);
		}
		viz.resize(n + 1,false);
		fin.close();
	}

	void dfs1(int node){
		for( auto it : adjt[node]){
			if( viz[it] == false){
				viz[it] = true;
				dfs1(it);
			}
		}
		postorder.push_back(node);
	}
	void dfs2(int node, vector<int> &components){
		components.push_back(node);
		for( auto it : adj[node]){
			if( viz[it] == true ){
				viz[it] = false;
				dfs2(it,components);
			}
		}
	}
	vector<vector<int>> get_result() {
		vector<vector<int>> sol;
		for( int i = 1; i <= n; ++i){
				if( viz[i] == false ){
					viz[i] = true;
					dfs1(i);
				}
		}
		vector<int> components;
		for( int i = n - 1; i >= 0; i--){
			if( viz[postorder[i]] == true ){
				viz[postorder[i]] = false;
				dfs2(postorder[i],components);
				components.push_back(-1);
			}
		}
		vector<int> aux;
		for( auto it : components ){
			if( it != -1 ){
				aux.push_back(it);
			}
			else{
				sol.push_back(aux);
				aux.resize(0);
			}
		}		

		return sol;
	}

	void print_output(vector<vector<int>> result) {
		ofstream fout("out");
		fout << result.size() << '\n';
		for (const auto& ctc : result) {
			for (int nod : ctc) {
				fout << nod << ' ';
			}
			fout << '\n';
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

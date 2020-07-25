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
	int time = 0;
	vector<int> adj[kNmax];
	vector<int> parent;
	struct Edge {
		int x;
		int y;
	};

	void read_input() {
		ifstream fin("in");
		fin >> n >> m;
		for (int i = 1, x, y; i <= m; i++) {
			fin >> x >> y;
			adj[x].push_back(y);
			adj[y].push_back(x);
		}
		parent.resize(n+1,0);
		fin.close();
	}
	void dfs( int node, vector<int> &idx,int nodd, vector<int> &low,vector<Edge> &sol){
		idx[node] = time;
		low[node] = time;
		time++;

		for( int i = 0; i < adj[node].size(); i++){
			if( !idx[adj[node][i]]){
				dfs(adj[node][i],idx,node,low,sol);
				low[node] = min(low[node],low[adj[node][i]]);
			
			if( low[adj[node][i]] > idx[node] ){
				Edge aux;
				aux.x = node;
				aux.y = adj[node][i];
				sol.push_back(aux);
			}
		} else if( adj[node][i] != nodd){
			low[node] = min(idx[adj[node][i]],low[node]);
		}
	  }
	}
	
	vector<Edge> get_result() {
		vector<Edge> sol;
		vector<int> low(n + 1);
		vector<int> idx(n + 1);
		vector<int> parent(n + 1,-1);
		for(int i = 1; i <= n; i++){
			if( !idx[i]){
				dfs(i,idx,0,low,sol);
			}
		}


		return sol;
	}

	void print_output(vector<Edge> result) {
		ofstream fout("out");
		fout << result.size() << '\n';
		for (int i = 0; i < int(result.size()); i++) {
			fout << result[i].x << ' ' << result[i].y << '\n';
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

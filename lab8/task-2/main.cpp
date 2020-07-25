#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#define inf 1004004
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
	int root;
	void read_input() {
		ifstream fin("in");
		fin >> n >> m;
		for (int i = 1, x, y; i <= m; i++) {
			fin >> x >> y;
			adj[x].push_back(y);
			adj[y].push_back(x);
		}
		parent.resize(n + 1,0);
		fin.close();
	}

	void dfs(int node, vector<int>& sol,vector<int> &idx, vector<int> &low){
		idx[node] = time;
		low[node] = time;
		time++;
		vector<int> children;
		for(int i = 0; i < adj[node].size();i++){
			//if(parent[node] != adj[node][i]){
				if( !idx[adj[node][i]] ){
					children.push_back(adj[node][i]);
					parent[adj[node][i]] = node;
					dfs(adj[node][i],sol,idx,low);
					low[node] = min(low[node],low[adj[node][i]]);					
				}
				else{
					low[node] = min(low[node],idx[adj[node][i]]);
				}
			//}
		}
		
		if( idx[node] == low[node] && children.size() >= 2){
			sol.push_back(node);
		}
		else if(idx[node] != low[node]){
			for( auto it : children){
				if( idx[node] <= low[it] ){
					sol.push_back(node);
					break;
				}
			}
		}

	}

	vector<int> get_result() {
	vector<int> sol;
	vector<int> idx(n + 1);
	vector<int> low(n + 1);

		for( int i = 1; i <= n; i++)
		  if( !idx[i]){
			  parent[i] = -1;
			  dfs(i,sol,idx,low);
		  }

		return sol;
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


#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>
#define nmax 10001

using namespace std;

struct Homework {
	int deadline;
	int score;

	Homework(int _deadline, int _score) : deadline(_deadline), score(_score) {}
};

bool compareto(Homework& h1, Homework& h2){
	 return h1.score > h2.score;
}

class Task {
 public:
	void solve() {
		read_input();
		print_output(get_result());
	}

 private:
	int n;
	vector<Homework> hws;
    bool teme[nmax] = {0};
	void read_input() {
		ifstream fin("in");
		fin >> n;
		for (int i = 0, deadline, score; i < n; i++) {
			fin >> deadline >> score;
			hws.emplace_back(deadline, score);
		}
		fin.close();
	}

	int get_result() {
	    int maxScore = 0, time = 0;
	    int maxi = 0;
		sort(hws.begin(), hws.end(), compareto);

		for (auto it : hws) {
		    if (!teme[it.deadline]) {
                maxScore += it.score;
                teme[it.deadline] = true;
		    } else {
		        for (int i = it.deadline - 1; i ; --i) {
		            if (!teme[i]) {
                        teme[i] = true;
                         maxScore += it.score;
                        break;
		            }
		        }
		    }
		}

		return maxScore;
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


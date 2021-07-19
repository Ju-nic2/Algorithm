#define MAX 987654320
#include <iostream>
#include <queue>
#include <algorithm>
#include <vector>
using namespace std;
struct info {
	int idx, val;
};
info tmp;
struct cmp {
	bool operator()(info &a, info &b) {
		return a.val > b.val;
	}
};
vector<info> v[2001];
int dist[2001];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
	int test, node, edge, candidate, start, a, b, s, e, val;
	cin >> test;
	for (int t = 0; t < test; t++) {
		cin >> node >> edge >> candidate;
		for (int i = 1; i <= node; i++) {
			v[i].clear();
			dist[i] = MAX;
		}
		cin >> start >> a >> b;
		for (int i = 0; i < edge; i++) {
			cin >> s >> e >> val;
			//무조건 지나간 길
			if ((s == a && e == b) || (s == b && e == a))
				tmp.val = 2 * val - 1;
			else
				tmp.val = 2 * val;
			tmp.idx = e;
			v[s].push_back(tmp);
			tmp.idx = s;
			v[e].push_back(tmp);
		}
		priority_queue<info, vector<info>, cmp> pq;
		dist[start] = 0;
		tmp.idx = start;
		tmp.val = 0;
		pq.push(tmp);
		while (!pq.empty()) {
			int cidx = pq.top().idx;
			int cv = pq.top().val;
			pq.pop();
			if (dist[cidx] < cv) continue;
			for (int i = 0; i < v[cidx].size(); i++) {
				int next = v[cidx][i].idx;
				int nv = v[cidx][i].val;
				if (dist[next] > cv + nv) {
                    cout << cidx << " ->" << next<<endl;
					dist[next] = cv + nv;
					tmp.val = cv + nv;
					tmp.idx = next;
					pq.push(tmp);
				}
			}
		}
		vector<int> answer;
		for (int i = 0; i < candidate; i++) {
			cin >> val;
			if (dist[val] % 2 == 1)
				answer.push_back(val);
		}
		sort(answer.begin(), answer.end());
		for (int i = 0; i < answer.size(); i++)
			cout << answer[i] << " ";
		cout << '\n';
	}
	system("pause");
	return 0;
}
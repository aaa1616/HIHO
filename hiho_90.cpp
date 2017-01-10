#include <stdio.h>
#include <algorithm>
#include <memory.h>

#define LEN 10001

using namespace std;

int T, L, R, N, Q, test;
int t, l, n, d, di[2];

typedef struct _EVENT{
	int t, n, x;
}EVENT;

int lane[2][LEN];
EVENT event[2][2 * LEN];

int cmp(const EVENT &e1, const EVENT &e2)
{
	if (e1.t < e2.t) {
		return 1;
	}else if (e1.t == e2.t) {
		if (e1.x < e2.x) {
			return 1;
		}else {
			return 0;
		}
	}else {
		return 0;
	}
}

int solve()
{
	int i, time, d, flag;
	d = 0;
	time = T;
	memset(di, 0, sizeof(di));
	while (R > 0) {
		flag = 0;
		while (di[d] < 2 * Q) {
			if (time > event[d][di[d]].t) {
				lane[d][event[d][di[d]].n] += event[d][di[d]].x;
				di[d]++;
			}else {
				for (i = 0 ; i < N ; i++) {
					if (lane[d][i] == 0) {
						flag = 1;
						break;
					}
				}
				if (flag == 1) {
					time += L;
					break;
				}else {
					time = event[d][di[d]].t;
					lane[d][event[d][di[d]].n] += event[d][di[d]].x;
					di[d]++;
				}
			}
		}
		if (flag == 0) {
			time += L;
		}
		d = 1 - d;
		R--;
	}

	return time;
}

int main()
{
	int i;
	freopen("input.txt", "r", stdin);
	scanf("%d", &test);
	while (test--) {
		memset(di, 0, sizeof(di));
		memset(event, 0, sizeof(event));
		memset(lane, 0, sizeof(lane));
		scanf("%d%d%d%d%d", &T, &L, &R, &N, &Q);
		for (i = 0 ; i < Q ; i++) {
			scanf("%d%d%d%d", &t, &l, &n, &d);
			if (l < L) {
				event[d][di[d]].t = t + l - L;
				event[d][di[d]].n = n;
				event[d][di[d]].x = 1;
				di[d]++;
				event[d][di[d]].t = t;
				event[d][di[d]].n = n;
				event[d][di[d]].x = -1;
				di[d]++;
			}else if (l == L) {
				event[d][di[d]].t = t - 1;
				event[d][di[d]].n = n;
				event[d][di[d]].x = 1;
				di[d]++;
				event[d][di[d]].t = t + 1;
				event[d][di[d]].n = n;
				event[d][di[d]].x = -1;
				di[d]++;
			}else {
				event[d][di[d]].t = t;
				event[d][di[d]].n = n;
				event[d][di[d]].x = 1;
				di[d]++;
				event[d][di[d]].t = t + l - L;
				event[d][di[d]].n = n;
				event[d][di[d]].x = -1;
				di[d]++;
			}
			event[1 - d][di[1 - d]].t = t - L;
			event[1 - d][di[1 - d]].n = n;
			event[1 - d][di[1 - d]].x = 1;
			di[1 - d]++;
			event[1 - d][di[1 - d]].t = t + l;
			event[1 - d][di[1 - d]].n = n;
			event[1 - d][di[1 - d]].x = -1;
			di[1 - d]++;
		}
		sort(&event[0][0], &event[0][2 * Q], cmp);
		sort(&event[1][0], &event[1][2 * Q], cmp);
		printf("%d\n", solve());
	}

	return 0;
}

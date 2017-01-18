#include <stdio.h>
#include <memory.h>
#include <algorithm>

#define SIZE 1001
#define TIME 5001

using namespace std;

typedef struct _NODE {
	int a, b, c;
}NODE;

int result[SIZE][TIME];
int t[TIME], h[TIME], q[TIME][TIME];
NODE node[SIZE];

int cmp(const NODE &n1, const NODE &n2)
{
	if (n1.b * n2.c > n2.b * n1.c) {
		return 1;
	}else {
		return 0;
	}
}

int cal(int b, int e, int i)
{
	int n, t;
	n = (e - b) / node[i].c;
	t = (node[i].a - node[i].b * b) * n - (n * (n - 1) / 2) * node[i].b * node[i].c;
	return t > 0 ? t : 0;
}

int main()
{
	freopen("input.txt", "r", stdin);
	int i, j, n, m, k, r, temp1, temp2, max;
	scanf("%d%d%d", &n, &m, &k);
	for (i = 1 ; i <= n ; i++) {
		scanf("%d%d%d", &node[i].a, &node[i].b, &node[i].c);
	}
	sort(node + 1, node + n + 1, cmp);
	memset(q, 0, sizeof(q));
	memset(result, 0, sizeof(result));

	for (i = 1 ; i <= n ; i++) {
		memset(t, 0xFF, sizeof(t));
		memset(h, 0, sizeof(h));
		for (j = 0 ; j < node[i].c ; j++) {
			t[j]++;
			q[j][t[j]] = j;
		}
		for (j = 1;  j < node[i].c ; j++) {
			result[i][j] = result[i - 1][j];
		}
		for (j = node[i].c ; j < m ; j++) {

			r = j % node[i].c;
			t[r]++;
			q[r][t[r]] = j;

			while (t[r] > h[r]) {
				temp1 = result[i - 1][q[r][t[r]]] + cal(q[r][t[r]], j, i);
				temp2 = result[i - 1][q[r][t[r] - 1]] + cal(q[r][t[r] - 1], j, i);
				if (temp1 >= temp2) {
					q[r][t[r] - 1] = q[r][t[r]];
					t[r]--;
				}else {
					break;
				}
			}

			while ((j - q[r][h[r]]) / node[i].c > k) {
				h[r]++;
			}

			result[i][j] = result[i - 1][q[r][h[r]]] + cal(q[r][h[r]], j, i);
		}
	}

	max = 0;
	for (i = 0 ; i < m ; i++) {
		max = result[n][i] > max ? result[n][i] : max;
	}

	printf("%d\n", max);
	return 0;
}

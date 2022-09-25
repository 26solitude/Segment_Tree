#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <math.h>
#include <malloc.h>

void Segtree_update(int* seg_tree, int start, int end, int i, int d_value, int current)
{
	if ((i < start) || (i > end)) return;
	seg_tree[current] = seg_tree[current] + d_value;
	int mid, child;
	if (start != end)
	{
		mid = start + (end - start) / 2;
		child = 2 * current;
		Segtree_update(seg_tree, start, mid, i, d_value, child + 1);
		Segtree_update(seg_tree, mid + 1, end, i, d_value, child + 2);
	}
}

int Query_sum(int* seg_tree, int start, int end, int q_s, int q_e, int current)
{
	if ((end < q_s) || (start > q_e)) return 0;						// ���� �ۿ� �ִ� ���
	if ((q_s <= start) && (q_e >= end)) return seg_tree[current];	// ���� �ȿ� �ִ� ���
	int mid = start + (end - start) / 2;							// ���ʸ� ��ģ ���
	int child = 2 * current;
	return Query_sum(seg_tree, start, mid, q_s, q_e, child + 1) + Query_sum(seg_tree, mid + 1, end, q_s, q_e, child + 2);

}

int Get_query(int* seg_tree, int n, int q_s, int q_e)
{
	if ((q_s < 0) || (q_e > n - 1) || (q_s > q_e))
	{
		printf("�ε����� ������ �ùٸ��� �ʽ��ϴ�.\n");
		return -1;
	}
	int sum = Query_sum(seg_tree, 0, n - 1, q_s, q_e, 0);	// current�� 0���� ����
	return sum;
}

int Construct_tree(int list[], int start, int end, int* seg_tree, int current)
{
	if (start == end)
	{
		seg_tree[current] = list[start];
		return list[start];
	}
	int mid = start + (end - start) / 2;
	int child = 2 * current;
	seg_tree[current] = Construct_tree(list, start, mid, seg_tree, child + 1) + Construct_tree(list, mid + 1, end, seg_tree, child + 2);
	return seg_tree[current];
}

int* Seg_tree_const(int list[], int n)
{
	int height = (int)log2(n);
	int t_size = 2 * (int)pow(2, height) - 1;
	int* seg_tree = (int*)malloc(sizeof(int) * t_size);
	Construct_tree(list, 0, n - 1, seg_tree, 0);
	return seg_tree;
}

void main()
{
	int list[] = { 21,7,8,19,2,9,6,10 };
	int n = sizeof(list) / sizeof(int);

	int* st = Seg_tree_const(list, n);
	printf("1�� 3 ������ ���� ���� %d�Դϴ�.\n", Get_query(st, n, 1, 3));

	printf("3�� ���� %d�Դϴ�.\n", Get_query(st, n, 3, 3));
	Segtree_update(st, 0, 7, 3, -9, 0);
	printf("3�� ���� %d�Դϴ�.\n", Get_query(st, n, 3, 3));
}
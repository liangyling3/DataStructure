#include <iostream>
using namespace std;

int arr[] = {2, 1, 4, 3, 6, 5, 8, 7};

void heapSort(int [] arr, int length) {
	if (length < 2) return;
	// 建立堆
	for (int i = length/2-1; i >= 0; i--) {
		adjustHeap(arr, i, length);
	}

	for (int i = length-1; i > 0; i--) {
		swap(arr, 0, j);
		adjustHeap(arr, 0, j);
	}
}

void adjustHeap(int [] arr, int i, int length) {
	int temp = arr[i];
	for (int k = 2*i+1; k < length; k = 2*k+1) {
		// k先指向子节点中最大的节点
		if (k+1 < length && arr[k] < arr[k+1]) {
			k++;
		}

		// 若子节点更大，则进行值的交换
		if (arr[k] > temp) {
			swap(arr, i, k);
			i = k;
		} 
		else {		// 若无需交换，则终止循环
			break;
		}
	}
}

void swap(int[] arr, int a, int b) {
	int temp = arr[a];
	arr[a] = arr[b];
	arr[b] = temp;
}
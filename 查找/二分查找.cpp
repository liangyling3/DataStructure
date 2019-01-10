// 二分查找，找到该值在数组中的下标，否则为-1
int binarySearch(int[] arr, int key) {
    int left = 0;
    int right = arr.length - 1;

    // 这里必须是 <=
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] == key) {
            return mid;
        }
        else if (arr[mid] < key) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1;
}
#include <iostream>
#include <vector>

void quickSort(std::vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivot = arr[high];  // 选择基准
        int i = (low - 1);      // 指针i

        for (int j = low; j <= high - 1; ++j) {
            // 当前元素小于或等于pivot
            if (arr[j] <= pivot) {
                i++;    // i指针右移
                std::swap(arr[i], arr[j]);  // 交换
            }
        }
        std::swap(arr[i + 1], arr[high]);  // 将pivot放到正确的位置
        int partitionIndex = i + 1;        // 分区索引

        quickSort(arr, low, partitionIndex - 1);  // 递归排序左子数组
        quickSort(arr, partitionIndex + 1, high); // 递归排序右子数组
    }
}

int main() {
    std::vector<int> arr = {10, 7, 8, 9, 1, 5};
    int n = arr.size();
    quickSort(arr, 0, n - 1);
    std::cout << "Sorted array: \n";
    for (int i = 0; i < n; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    system("pause");
    return 0;
}

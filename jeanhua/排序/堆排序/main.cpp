#include <iostream>
#include <vector>

void heapify(std::vector<int>& arr, int n, int i) {
    int largest = i;       // 初始化最大元素索引为根
    int left = 2 * i + 1;  // 左子节点
    int right = 2 * i + 2; // 右子节点

    // 如果左子节点大于根节点
    if (left < n && arr[left] > arr[largest])
        largest = left;

    // 如果右子节点比最大元素还大
    if (right < n && arr[right] > arr[largest])
        largest = right;

    // 如果最大元素不是根节点
    if (largest != i) {
        std::swap(arr[i], arr[largest]);

        // 递归地调整受影响的子树
        heapify(arr, n, largest);
    }
}

void heapSort(std::vector<int>& arr) {
    int n = arr.size();

    // 建立最大堆
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // 一个个从堆顶取出元素
    for (int i = n - 1; i >= 0; i--) {
        // 移动当前根节点到数组末尾
        std::swap(arr[0], arr[i]);

        // 调用heapify减小堆的大小并重新调整
        heapify(arr, i, 0);
    }
}

int main() {
    std::vector<int> arr = {12, 11, 13, 5, 6, 7};
    heapSort(arr);
    std::cout << "Sorted array: \n";
    for (int i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
    system("pause");
    return 0;
}

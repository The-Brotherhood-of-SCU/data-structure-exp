#include <iostream>
#include <stack>

class TreeNode {
public:
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// �ǵݹ��������
void preOrderTraversalNonRecursive(TreeNode* root) {
    if (root == nullptr) return;
    std::stack<TreeNode*> stack;
    stack.push(root);
    while (!stack.empty()) {
        TreeNode* node = stack.top();
        stack.pop();
        std::cout << node->val << " ";
        if (node->right) stack.push(node->right);
        if (node->left) stack.push(node->left);
    }
    std::cout << std::endl;
}

// �ǵݹ��������
void inOrderTraversalNonRecursive(TreeNode* root) {
    std::stack<TreeNode*> stack;
    TreeNode* current = root;
    while (current != nullptr || !stack.empty()) {
        while (current != nullptr) {
            stack.push(current);
            current = current->left;
        }
        current = stack.top();
        stack.pop();
        std::cout << current->val << " ";
        current = current->right;
    }
    std::cout << std::endl;
}

// �ǵݹ�������
void postOrderTraversalNonRecursive(TreeNode* root) {
    std::stack<TreeNode*> stack;
    TreeNode* lastVisited = nullptr;
    TreeNode* current = root;
    while (current != nullptr || !stack.empty()) {
        while (current != nullptr) {
            stack.push(current);
            current = current->left;
        }
        current = stack.top();
        // ��ǰ�ڵ��������Ϊ�ջ����������Ѿ������ʹ�
        if (current->right == nullptr || current->right == lastVisited) {
            std::cout << current->val << " ";
            lastVisited = current;
            stack.pop();
            current = nullptr; // ��������ջ��Ԫ��
        }
        else {
            current = current->right;
        }
    }
    std::cout << std::endl;
}


//�ݹ��������
void preOrderTraversalRecursive(TreeNode* root) {
    if (root == nullptr) return;
    std::cout << root->val << " ";
    preOrderTraversalRecursive(root->left);
    preOrderTraversalRecursive(root->right);
}

//�ݹ��������
void inOrderTraversalRecursive(TreeNode* root) {
    if (root == nullptr) return;
    inOrderTraversalRecursive(root->left);
    std::cout << root->val << " ";
    inOrderTraversalRecursive(root->right);
}

//�ݹ�������
void postOrderTraversalRecursive(TreeNode* root) {
    if (root == nullptr) return;
    postOrderTraversalRecursive(root->left);
    postOrderTraversalRecursive(root->right);
    std::cout << root->val << " ";
}

int main() {
    // ����
    //      1
    //     / \
    //    2   3
    //   / \
    //  4   5
    TreeNode* root = new TreeNode(1);
    root->left = new TreeNode(2);
    root->right = new TreeNode(3);
    root->left->left = new TreeNode(4);
    root->left->right = new TreeNode(5);

    //�ǵݹ����
    std::cout << "Pre-order Non-Recursive: ";
    preOrderTraversalNonRecursive(root);
    std::cout << "In-order Non-Recursive: ";
    inOrderTraversalNonRecursive(root);
    std::cout << "Post-order Non-Recursive: ";
    postOrderTraversalNonRecursive(root);

    //�ݹ����
    std::cout << "Pre-order Recursive: ";
    preOrderTraversalRecursive(root);
    std::cout << std::endl;
    std::cout << "In-order Recursive: ";
    inOrderTraversalRecursive(root);
    std::cout << std::endl;
    std::cout << "Post-order Recursive: ";
    postOrderTraversalRecursive(root);
    std::cout << std::endl;

    delete root->left->left;
    delete root->left->right;
    delete root->left;
    delete root->right;
    delete root;
    system("pause");
    return 0;
}

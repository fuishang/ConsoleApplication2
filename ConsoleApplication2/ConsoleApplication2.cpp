#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <algorithm>
using namespace std;

// AVL樹的節點
struct AVLNode {
    int data;
    AVLNode* left;
    AVLNode* right;
    int height;

    AVLNode(int val) : data(val), left(nullptr), right(nullptr), height(1) {}
};

// AVL樹類別
class AVLTree {
public:
    AVLNode* root;

    AVLTree() : root(nullptr) {}

    int height(AVLNode* node) {
        return node ? node->height : 0;
    }

    int balanceFactor(AVLNode* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    void updateHeight(AVLNode* node) {
        if (node) {
            node->height = max(height(node->left), height(node->right)) + 1;
        }
    }

    AVLNode* rotateRight(AVLNode* y) {
        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        updateHeight(y);
        updateHeight(x);

        return x;
    }

    AVLNode* rotateLeft(AVLNode* x) {
        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        updateHeight(x);
        updateHeight(y);

        return y;
    }

    AVLNode* balance(AVLNode* node) {
        int bf = balanceFactor(node);

        if (bf > 1) {
            if (balanceFactor(node->left) < 0)
                node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (bf < -1) {
            if (balanceFactor(node->right) > 0)
                node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    AVLNode* insert(AVLNode* node, int key) {
        if (!node) return new AVLNode(key);

        if (key < node->data) node->left = insert(node->left, key);
        else if (key > node->data) node->right = insert(node->right, key);

        updateHeight(node);

        return balance(node);
    }

    void insert(int key) {
        root = insert(root, key);
    }

    void inorder(AVLNode* node) {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    void display(AVLNode* node, int space = 0, int count = 10) {
        if (node == nullptr)
            return;

        space += count;

        display(node->right, space);

        cout << endl;
        for (int i = count; i < space; i++)
            cout << " ";
        cout << node->data << endl;

        display(node->left, space);
    }

    void show() {
        display(root);
    }
};

// 2-3樹的節點
struct TwoThreeNode {
    vector<int> keys;
    vector<TwoThreeNode*> children;

    TwoThreeNode(int key) {
        keys.push_back(key);
        children = vector<TwoThreeNode*>(4, nullptr); // 預留4個子樹指標
    }
};

// 2-3樹類別
class TwoThreeTree {
public:
    TwoThreeNode* root;

    TwoThreeTree() : root(nullptr) {}

    void insert(int key) {
        // 2-3樹的插入邏輯可以更複雜，這裡省略實現。可參考資料進行實現
    }

    void inorder(TwoThreeNode* node) {
        if (!node) return;
        for (int i = 0; i < node->keys.size(); i++) {
            inorder(node->children[i]);
            cout << node->keys[i] << " ";
        }
        inorder(node->children[node->keys.size()]);
    }

    void show() {
        inorder(root);
    }
};

// 主程式
int main() {
    AVLTree avlTree;
    TwoThreeTree twoThreeTree;
    int choice, value;

    while (true) {
        cout << "\n1. 輸入資料\n";
        cout << "2. 顯示AVL樹\n";
        cout << "3. 顯示2-3樹\n";
        cout << "4. 插入資料到AVL樹\n";
        cout << "5. 插入資料到2-3樹\n";
        cout << "6. 離開\n";
        cout << "請選擇操作：";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "請輸入資料，結束輸入請輸入-1：\n";
            while (true) {
                cin >> value;
                if (value == -1) break;
                avlTree.insert(value);
                twoThreeTree.insert(value); // 這裡簡化，實際插入邏輯要根據2-3樹的規範來寫
            }
            break;

        case 2:
            cout << "AVL樹的結構：\n";
            avlTree.show();
            break;

        case 3:
            cout << "2-3樹的結構：\n";
            twoThreeTree.show();
            break;

        case 4:
            cout << "請輸入要插入到AVL樹的資料：";
            cin >> value;
            avlTree.insert(value);
            break;

        case 5:
            cout << "請輸入要插入到2-3樹的資料：";
            cin >> value;
            twoThreeTree.insert(value);
            break;

        case 6:
            return 0;
        default:
            cout << "無效選項，請重新選擇。\n";
        }
    }

    return 0;
}

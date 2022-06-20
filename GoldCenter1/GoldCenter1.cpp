#include <iostream>
#include <vector>
#include <fstream>

bool compMax(int left, int right) {
    if (left < right) {
        return true;
    }

    return false;
}

bool compMin(int left, int right){
    if (left > right) {
        return true;
    }

    return false;
}

struct Heap {
    std::vector<int> tree;
    bool (*comporator)(int left, int right);

    Heap(bool (*comporator)(int left, int right)) {
        tree.push_back(0);
        this->comporator = comporator;
    }

    void push(int x) {
        tree.push_back(x);
        sift_up(tree.size() - 1);
    }

    int getTopElement() {
        if (tree.size() > 1) {
            return tree[1];
        }
        else {
            return -1;
        }
    }

    void pop() {
        if (tree.size() > 1) {
            tree[1] = tree.back();
            tree.pop_back();
            sift_down(1);
        }
        else {
            std::cout << "куча пуста";
            return;
        }
    }


    void sift_up(int v) {
        if (v == 1) {
            return;
        }

        if (comporator(tree[v/2], tree[v])) {//tree[v / 2] < tree[v]
            std::swap(tree[v], tree[v / 2]);
            sift_up(v / 2);
        }
    }


    void sift_down(int v) {
        if (v * 2 >= tree.size()) {
            return;
        }


        int max_idx;
        if (v * 2 + 1 == tree.size()) {
            max_idx = v * 2;
        }
        else if (!comporator(tree[v* 2], tree[v* 2 + 1])) {//tree[v * 2] >= tree[v * 2 + 1]
            max_idx = v * 2;
        }
        else {
            max_idx = v * 2 + 1;
        }

        if (comporator(tree[v], tree[max_idx])) {//tree[v] < tree[max_idx]
            std::swap(tree[v], tree[max_idx]);
            sift_down(max_idx);
        }
    }

    bool empty() {
        return tree.size() == 1;
    }
};

int main()
{
    std::ifstream inp("input.txt");
    std::ofstream out("output.txt");

    Heap* rightHeap = new Heap(compMin);
    Heap* leftHeap = new Heap(compMax);

    int n, center;
    int leftHeapSize = 0, rightHeapSize = 0;

    inp >> n;

    inp >> center;
    out << center << ' ';

    for (int i = 1; i < n; i++) {
        int next_number;
        inp >> next_number;

        if (next_number > center){
            rightHeap->push(next_number);
            rightHeapSize++;

            if (rightHeapSize - leftHeapSize >= 2) {
                leftHeap->push(center);
                leftHeapSize++;

                center = rightHeap->getTopElement();
                rightHeap->pop();
                rightHeapSize--;

            }
        }
        else {
            leftHeap->push(next_number);
            leftHeapSize++;

            if (leftHeapSize - rightHeapSize >= 2) {
                rightHeap->push(center);
                rightHeapSize++;

                center = leftHeap->getTopElement();
                leftHeap->pop();
                leftHeapSize--;
            }
            else if (leftHeapSize - rightHeapSize == 1) {
                rightHeap->push(center);
                rightHeapSize++;

                center = leftHeap->getTopElement();
                leftHeap->pop();
                leftHeapSize--;
            }
        }

        out << center << ' ';
    }

}


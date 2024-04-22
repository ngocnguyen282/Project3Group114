#ifndef HEAP_H
#define HEAP_H
#include <vector>

template<typename Key, typename Value>
class Heap {
private:
    std::vector<std::pair<Key,Value>> heap;
    bool (*compare)(Key, Key);

public:
    Heap(bool (*compare)(Key, Key)) {
        this->compare = compare;
    }
    void enqueue(Key key, Value val) {
        heap.push_back({key,val});
        int currInd = heap.size()-1;
        while (currInd > 0) {
            int parent = (currInd - 1)/2;
            if (compare(heap[currInd].first, heap[parent].first)) {
                break;
            }
            std::pair<Key,Value> temp = heap[currInd];
            heap[currInd] = heap[parent];
            heap[parent] = temp;
            currInd = parent;
        }
    }
    void heapify() {
        int currInd = 0;
        while (currInd < heap.size()/2) {
            int child = currInd*2+2;
            if (heap.size() <= child || compare(heap[child-1].first,heap[child].first)) {
                child = currInd*2+1;
            }
            if (compare(heap[child].first, heap[currInd].first)) {
                break;
            }
            std::pair<Key, Value> temp = heap[currInd];
            heap[currInd] = heap[child];
            heap[child] = temp;
            currInd = child;
        }
    }

    Value pop() {
        Value top = peek();
        dequeue();
        return top;
    }
    Value peek() {
        return heap[0].second;
    }
    Value dequeue() {
        heap[0] = heap[heap.size()-1];
        heap.pop_back();
        heapify();
    }
    int size() {
        return heap.size();
    }
    void print20() {
        for(int i = 0; i < 20; i++) {
            int n = 0;
            std::vector<std::string> strings = *(pop());
            //std::cout << strings[0];
            std::cout << "Transaction Amount: " << strings[2] << std::endl;
            std::cout << "Customer ID: " << strings[1] << std::endl;
            std::cout << "Transaction Date: " << strings[3] << std::endl;
            std::cout << "Payment Method: " << strings[4] << std::endl;
            std::cout << "Product Category: " << strings[5] << std::endl;
            std::cout << std::endl;
        }
    }
};

#endif

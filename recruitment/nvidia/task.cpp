#include <vector>
#include <iostream>
#include <functional>

struct Node {
    int data;
    Node* next;
};

int main() {
    Node* head = new Node;
    head->data = 1;

    std::vector<int> values = {1, 2, 3, 4, 5};
    auto node = head;
    for(auto &v : values) {
        node->next = new Node;
        node->next->data = v;
        node = node->next;
    }

    std::function<void(Node*)> print = [&print](Node* node) {
        if(node == nullptr) {
            std::cout << std::endl;
            return;
        }
        std::cout << node->data << " ";
        print(node->next);
    };
    node = head;
    print(node);

    return 0;
}
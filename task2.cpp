#include <iostream>
#include <string>
#include <vector>
using namespace std;

struct Node {
     //The node holds 64-bit part of the number
    uint64_t value;
    Node* next;

    Node(uint64_t val) : value(val), next(nullptr) {}
};

class LinkedList {
public:
    Node* head;

    LinkedList() : head(nullptr) {}

    void append(uint64_t val) {
        if (head == nullptr) {
            head = new Node(val);
        }
        else {
            Node* temp = head;
            while (temp->next) {
                temp = temp->next;
            }
            temp->next = new Node(val);
        }
    }

        string toString() const {
        string result;
        Node* current = head;
        while (current) {
            result += to_string(current->value);
            current = current->next;
        }
        return result;
    }

    ~LinkedList() {
        Node* current = head;
        while (current) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }
};

//Function to check if a number is prime
bool isPrime(const LinkedList& list) {
    string numStr = list.toString();

    // Check for trivial cases
    if (numStr == "0" || numStr == "1") return false;
    if (numStr == "2") return true; // 2 is prime
    if (numStr.back() % 2 == 0) return false; // Even number greater than 2

    // Convert to a large integer for testing
    uint64_t number = 0;
    const size_t maxDivisor = 100000; // Limit divisor range for trial division

    // Check divisibility by all odd numbers from 3 to sqrt(number)
    for (uint64_t d = 3; d <= maxDivisor; d += 2) {
        // Calculate the number mod d to avoid overflow
        number = 0;
        for (char c : numStr) {
            number = (number * 10 + (c - '0')) % d;
        }
        if (number == 0) {
            return false; // Divisible by d
        }
    }

    return true;
}

int main() {
    //  not a prime
    string number = "1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890";

    // prime
    LinkedList linkedList;

    //Populate the linked list with the number
    size_t index = 0;
    while (index < number.length()) {
        // Take the next 18 digits (since 10^18 is slightly less than 2^64)
        string chunk = number.substr(index, 18);
        uint64_t value = stoull(chunk); // Convert chunk to uint64_t
        linkedList.append(value);
        index += 18;
    }

    string fullNumberStr = linkedList.toString();
    cout << "The number is: " << fullNumberStr << std::endl;

    // Check if the number is prime
    bool isPrimeResult = isPrime(linkedList);
    cout << "Is the number prime? " << (isPrimeResult ? "True" : "False") <<endl;

    return 0;
}
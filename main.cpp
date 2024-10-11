#include <iostream>
#include <csignal>
#include <cstring>
#include <wait.h>

using namespace std;

int findMin(int arr[], int start, int end);

int main() {
    srand(time(nullptr));

    int arr[20] = {0};

    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i) {
        arr[i] = rand() % 100;
    }

    for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); ++i) {
        cout << "[" << arr[i] << "]";
        if (i == ((sizeof(arr) / sizeof(arr[0]))/2)-1){
            cout << " ";
            continue;
        }
    }
    cout << "\n";

    int parentMin = findMin(arr, 0, 10);
    cout << "Parent Process: " << getpid() << "\n\tMin Value:" << parentMin;

    cout << "\n";

    //pid_t is an int type to check against processes and errors
    pid_t pid = fork();

    if(pid < 0){
        cerr << "Fork Operation failed" << strerror(errno) << endl;
        return 1;
    }
    if(pid == 0){
        int childMin = findMin(arr, 10, 20);
        cout << "Child Process: " << getpid() << "\n\tMin Value:" << childMin;
        return 0;
    } else {
        wait(nullptr);
    }

    return 0;
}

int findMin(int arr[], int start, int end){
    int min = arr[start];
    for (int i = start; i < end; ++i) {
        if (arr[i] < min){
            min = arr[i];
        }
    }
    return min;
}
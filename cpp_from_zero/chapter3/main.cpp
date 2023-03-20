#include <iostream>
#include <cstddef>
#include <array> // std::array
#include <string> // std::string
#include <tuple> // std::tuple
#include <utility> // std::pair

// Function template: get the number of elements of an array
template <class T, std::size_t N>
constexpr std::size_t size(const T (&)[N]) noexcept { return N; }

void PrintArray1(const int x[5]) {
    // static_assert(sizeof(x) == sizeof(int*), "");
    for (int i = 0; i < 5; ++i) {
        std::cout << x[i] << std::endl;
    }
}

// Same with PrintArray1()
void PrintArray2(const int* x) {
    for (int i = 0; i < 5; ++i) {
        std::cout << x[i] << std::endl;
    }
}

// Better
void PrintArray(const int* x, std::size_t num) {
    for (int i = 0; i < num; ++i) {
        std::cout << x[i] << std::endl;
    }
}

int main() {
    {
        // Array
        int x[5] = { 0, 1, 2, 3, 4 };
        int y = x[2]; // 2

        int x1[3]; // Declear with its size
        x1[0] = 0;
        x1[1] = 1;
        x1[2] = 2;

        int x2[5] = { 0, 1, 2 }; // x[3] = x[4] = 0

        int x3[5] = { }; // All 0

        // Implicit type casting to pointer-type
        int* p = x;
        std::cout << *p << std::endl;
        std::cout << *(p + 1) << std::endl;
        std::cout << *(p + 2) << std::endl;
        std::cout << *(p + 3) << std::endl;
        std::cout << *(p + 4) << std::endl;

        // A pointer to the first element of the array is passed
        PrintArray1(x);
        PrintArray2(x);
        // Therefore the number of elements is required basically
        // std::size can be used from C++17
        PrintArray(x, size(x));

        // STL array by <array>
        std::array<int, 5> stdx = { 0, 1, 2, 3, 4 }; // From C++14
        // std::array<int, 5> stdx = {{ 0, 1, 2, 3, 4 }}; // Before

        auto stdx_size = stdx.size();
        // auto stdx_size = std::size(stdx); // From C++17

        int arr1_1[3] = {};
        // int arr1_2[3] = arr1_1; // Compilation error
        std::array<int, 3> arr2_1;
        std::array<int, 3> arr2_2 = arr2_1; // Copy
    }

    {
        // String
        std::string s = "Hello";
        for (auto i = 0; i < s.size(); i++) {
            std::cout << s[i];
        }
        std::cout << std::endl;
    }

    {
        // Tuple
        std::tuple<std::string, int> person { "Bob", 20 };

        // No limitation for the number of elements
        std::tuple<std::string, int, std::string> person2 { "Bob", 20, "USA" };

        // Refer an element
        std::get<0>(person); // "Bob"
        std::get<1>(person); // 20

        // Initialization
        std::tuple<std::string, int> person3 { "Bob", 20 };
        std::tuple<std::string, int> person4("Bob", 20);
        std::tuple<std::string, int> person5 = std::make_tuple("Bob", 20);

        // Assign elements to variables with std::tie()
        std::string name;
        int age;
        std::string country;
        std::tie(name, age, country) = person2; // name = "Bob", age = 20, country = "USA"
    }

    {
        // Pair
        std::pair<std::string, int> person { "Bob", 20 };

        // Refer an element
        std::get<0>(person); // "Bob"
        std::get<1>(person); // 20
        person.first;  // "Bob"
        person.second; // 20

        // Initialization
        std::pair<std::string, int> person2 { "Bob", 20 };
        std::pair<std::string, int> person3("Bob", 20);
        std::pair<std::string, int> person4 = std::make_pair("Bob", 20);

        // Assignment with std::tie()
        std::string name;
        int age;
        std::tie(name, age) = person; // name = "Bob", age = 20
    }

    return 0;
}

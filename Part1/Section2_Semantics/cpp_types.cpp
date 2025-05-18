#include <iostream>
#include <string>
#include <vector>
#include <functional>

// Move the template function outside of demonstrateTypeSystem
template <typename T>
T add(T a, T b)
{
    return a + b;
}

void demonstrateTypeSystem()
{
    // Static typing - explicit type declarations required
    int x = 5;
    std::cout << "x is " << x << ", type: int" << std::endl;

    // Cannot change variable type
    // x = "Hello"; // This would cause a compile error

    // Must create new variable with different type
    std::string y = "Hello";
    std::cout << "y is " << y << ", type: string" << std::endl;

    // Templates for generic programming - now calling the template function defined above
    std::cout << "add(5, 3): " << add<int>(5, 3) << std::endl;
    std::cout << "add(5.5, 3.2): " << add<double>(5.5, 3.2) << std::endl;

    // Explicit type casting required
    double pi = 3.14159;
    int roundedPi = static_cast<int>(pi);
    std::cout << "Rounded pi: " << roundedPi << std::endl;

    // Closures and scope
    int counter = 0;
    auto increment = [&counter]()
    {
        return ++counter;
    };

    std::cout << "Counter: " << increment() << std::endl; // 1
    std::cout << "Counter: " << increment() << std::endl; // 2
}

int main()
{
    demonstrateTypeSystem();
    return 0;
}
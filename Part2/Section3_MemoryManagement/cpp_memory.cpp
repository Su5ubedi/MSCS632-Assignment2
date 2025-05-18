#include <iostream>
#include <vector>
#include <memory>
#include <chrono>
#include <thread>
#include <string>

// A simple class to track allocation and deallocation
class Resource
{
private:
    std::string name;
    int *data;
    size_t size;

public:
    // Constructor
    Resource(const std::string &name, size_t size) : name(name), size(size)
    {
        std::cout << "Allocating " << name << " with " << size << " bytes" << std::endl;
        data = new int[size / sizeof(int)];
        // Initialize data to prevent optimization
        for (size_t i = 0; i < size / sizeof(int); ++i)
        {
            data[i] = static_cast<int>(i);
        }
    }

    // Destructor
    ~Resource()
    {
        std::cout << "Deallocating " << name << std::endl;
        delete[] data;
    }

    // Get data for demonstration
    int *getData() { return data; }
};

// Function demonstrating a memory leak
void createMemoryLeak()
{
    std::cout << "\n--- Demonstrating Memory Leak ---" << std::endl;
    Resource *leakedResource = new Resource("LeakedResource", 1024 * 1024); // 1MB
    std::cout << "Resource created but not deleted (leaked)" << std::endl;
    // No delete here - this causes a memory leak
}

// Function demonstrating proper memory management
void properMemoryManagement()
{
    std::cout << "\n--- Demonstrating Proper Manual Memory Management ---" << std::endl;
    Resource *resource = new Resource("ManagedResource", 1024 * 1024); // 1MB
    std::cout << "Resource created" << std::endl;
    // Use the resource...
    delete resource; // Proper cleanup
}

// Function demonstrating dangling pointer
void danglingPointerDemo()
{
    std::cout << "\n--- Demonstrating Dangling Pointer ---" << std::endl;
    int *ptr = new int(42);
    std::cout << "Allocated integer with value: " << *ptr << std::endl;

    delete ptr; // Memory is freed
    std::cout << "Memory freed, but pointer still exists" << std::endl;

    // Dangling pointer - accessing freed memory (undefined behavior)
    std::cout << "Attempting to access freed memory (dangerous!): ";
    // Uncommenting the next line would potentially crash or produce undefined behavior
    // std::cout << *ptr << std::endl;
    std::cout << "[access prevented to avoid crash]" << std::endl;

    // Fix: set pointer to nullptr after freeing
    ptr = nullptr;
    std::cout << "Set pointer to nullptr for safety" << std::endl;

    // Now we can safely check
    if (ptr == nullptr)
    {
        std::cout << "Pointer is null, safely avoided accessing freed memory" << std::endl;
    }
}

// Function demonstrating smart pointers
void smartPointerDemo()
{
    std::cout << "\n--- Demonstrating Smart Pointers ---" << std::endl;

    // Unique pointer - single ownership
    std::cout << "Creating unique_ptr (single ownership)" << std::endl;
    std::unique_ptr<Resource> uniqueResource =
        std::make_unique<Resource>("UniqueResource", 1024 * 1024);

    // Using the resource
    int *data = uniqueResource->getData();
    std::cout << "Used resource data at address: " << data << std::endl;

    // No need to manually delete - will be automatically cleaned up when goes out of scope

    // Shared pointer - shared ownership
    std::cout << "\nCreating shared_ptr (shared ownership)" << std::endl;
    std::shared_ptr<Resource> sharedResource1 =
        std::make_shared<Resource>("SharedResource", 1024 * 1024);

    {
        std::cout << "Reference count: " << sharedResource1.use_count() << std::endl;

        std::cout << "Creating another reference to the same resource" << std::endl;
        std::shared_ptr<Resource> sharedResource2 = sharedResource1;
        std::cout << "Reference count: " << sharedResource1.use_count() << std::endl;

        // sharedResource2 will go out of scope here
    }

    std::cout << "After inner scope, reference count: " << sharedResource1.use_count() << std::endl;

    // No need to manually delete - will be cleaned up when last reference is gone
}

int main()
{
    std::cout << "Memory Management in C++" << std::endl;

    // Demonstrate proper memory management
    properMemoryManagement();

    // Demonstrate dangling pointer
    danglingPointerDemo();

    // Demonstrate smart pointers (modern C++ approach)
    smartPointerDemo();

    // Demonstrate memory leak (commented out to prevent actual leaking)
    std::cout << "\nCAUTION: The following demonstration will cause a memory leak" << std::endl;
    createMemoryLeak();

    std::cout << "\nProgram completed. All properly managed resources should be freed." << std::endl;
    std::cout << "However, the deliberately leaked resource remains allocated." << std::endl;

    return 0;
}
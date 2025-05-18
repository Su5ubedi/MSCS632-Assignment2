def demonstrate_type_system():
    # Dynamic typing - no explicit type declarations
    x = 5                  # Integer
    print(f"x is {x}, type: {type(x)}")

    x = "Hello"            # Same variable can be reassigned to different type
    print(f"x is now {x}, type: {type(x)}")

    # Duck typing
    def process_sequence(items):
        return [item.upper() if hasattr(item, 'upper') else item for item in items]

    # Works with any iterable that contains items which might have upper() method
    print(process_sequence(["hello", 123, "world"]))

    # Type hints (optional)
    def greet(name: str) -> str:
        return f"Hello, {name}"

    # Still works with wrong type (type hints are not enforced at runtime)
    print(greet(123))  # Works despite type hint violation

    # Closures and scope
    def create_counter():
        count = 0
        def increment():
            nonlocal count  # Must declare nonlocal to modify outer scope
            count += 1
            return count
        return increment

    counter = create_counter()
    print(counter())  # 1
    print(counter())  # 2

demonstrate_type_system()
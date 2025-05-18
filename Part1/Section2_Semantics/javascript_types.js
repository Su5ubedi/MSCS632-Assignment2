function demonstrateTypeSystem() {
  // Dynamic typing - no explicit type declarations
  let x = 5; // Number
  console.log(`x is ${x}, type: ${typeof x}`);

  x = "Hello"; // Same variable can be reassigned to different type
  console.log(`x is now ${x}, type: ${typeof x}`);

  // Type coercion
  console.log("5" + 3); // "53" (string concatenation)
  console.log("5" - 3); // 2 (numeric subtraction)
  console.log("5" == 5); // true (loose equality)
  console.log("5" === 5); // false (strict equality)

  // Prototype-based inheritance
  function Person(name) {
    this.name = name;
  }

  Person.prototype.greet = function () {
    return `Hello, my name is ${this.name}`;
  };

  const person = new Person("Alice");
  console.log(person.greet());

  // Closures and scope
  function createCounter() {
    let count = 0;
    return function () {
      count += 1;
      return count;
    };
  }

  const counter = createCounter();
  console.log(counter()); // 1
  console.log(counter()); // 2
}

demonstrateTypeSystem();

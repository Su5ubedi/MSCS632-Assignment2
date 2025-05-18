fn main() {
    // Demonstrate ownership
    let s1 = String::from("hello");
    println!("Created string: {}", s1);

    // Transfer ownership (move)
    let s2 = s1;
    println!("Ownership transferred to s2: {}", s2);

    // This would cause a compile error - s1 no longer owns the data
    // println!("Try to use s1: {}", s1);

    // Demonstrate borrowing
    let s3 = String::from("world");
    print_string(&s3);  // Immutable borrow

    // We can still use s3 because we only borrowed it
    println!("After borrowing, s3 is still valid: {}", s3);

    // Mutable borrowing
    let mut s4 = String::from("hello");
    modify_string(&mut s4);
    println!("After mutable borrowing, s4 is: {}", s4);

    // Demonstrate automatic memory deallocation with scope
    {
        let s5 = String::from("temporary");
        println!("Inside scope: {}", s5);
        // s5 will be freed when this scope ends
    }
    // println!("s5 is no longer valid here: {}", s5); // Would not compile

    // Smart pointers for shared ownership
    use std::rc::Rc;

    let shared_data = Rc::new(String::from("shared"));
    println!("Created shared data, ref count: {}", Rc::strong_count(&shared_data));

    {
        let shared_ref1 = Rc::clone(&shared_data);
        let shared_ref2 = Rc::clone(&shared_data);
        println!("Added two references, ref count: {}", Rc::strong_count(&shared_data));
        println!("Shared data via ref1: {}", shared_ref1);
        println!("Shared data via ref2: {}", shared_ref2);
    } // shared_ref1 and shared_ref2 go out of scope here, decreasing the ref count

    println!("After inner scope, ref count: {}", Rc::strong_count(&shared_data));
}

// Function that borrows a string immutably
fn print_string(s: &String) {
    println!("Borrowed: {}", s);
    // s is an immutable reference, cannot modify it
    // s.push_str(" more"); // Would cause compile error
}

// Function that borrows a string mutably
fn modify_string(s: &mut String) {
    s.push_str(" world");
    println!("Modified borrowed string: {}", s);
}
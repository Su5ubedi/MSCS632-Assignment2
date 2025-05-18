import java.util.ArrayList;
import java.util.List;
import java.lang.management.ManagementFactory;
import java.lang.management.MemoryMXBean;
import java.lang.management.MemoryUsage;

public class MemoryManagementDemo {
    public static void main(String[] args) {
        printMemoryUsage("Initial memory usage");

        // Create and manage objects through reference
        List<byte[]> allocatedMemory = new ArrayList<>();

        // Allocate some memory
        System.out.println("Allocating memory...");
        for (int i = 0; i < 5; i++) {
            allocatedMemory.add(new byte[1024 * 1024]); // Allocate 1MB
            System.out.println("Allocated 1MB, total: " + (i + 1) + "MB");
            printMemoryUsage("After allocation " + (i + 1));
        }

        // Demonstrate object lifecycle and garbage collection
        System.out.println("\nRemoving references to trigger garbage collection...");
        allocatedMemory.clear(); // Remove references

        // Suggest garbage collection (no guarantee it will run immediately)
        System.gc();
        try {
            Thread.sleep(100); // Give GC a chance to run
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        printMemoryUsage("After clearing references and requesting GC");

        // Demonstrate memory leak pattern
        System.out.println("\nDemonstrating potential memory leak pattern...");
        List<Object> leakyList = new ArrayList<>();

        class DataHolder {
            private byte[] data = new byte[1024 * 1024]; // 1MB
            private String name;

            public DataHolder(String name) {
                this.name = name;
            }

            @Override
            public String toString() {
                return name + " (" + (data.length / 1024 / 1024) + "MB)";
            }
        }

        // Create objects that will remain referenced
        for (int i = 0; i < 5; i++) {
            leakyList.add(new DataHolder("Object " + i));
            System.out.println("Added " + leakyList.get(i) + " to leaky list");
            printMemoryUsage("After adding to leaky list");
        }

        // Objects remain in memory as long as leakyList exists
        System.out.println("\nObjects in leakyList will persist until leakyList is garbage collected");

        // In a real memory leak, references would be held indefinitely
        // Here we'll clean up to avoid actual leaks
        leakyList = null; // Now these objects can be collected

        System.gc();
        try {
            Thread.sleep(100);
        } catch (InterruptedException e) {
            e.printStackTrace();
        }

        printMemoryUsage("Final memory usage");
    }

    private static void printMemoryUsage(String label) {
        MemoryMXBean memoryBean = ManagementFactory.getMemoryMXBean();
        MemoryUsage heapUsage = memoryBean.getHeapMemoryUsage();

        long usedMemory = heapUsage.getUsed() / 1024 / 1024;
        long maxMemory = heapUsage.getMax() / 1024 / 1024;

        System.out.println(label + ": " + usedMemory + "MB used of " + maxMemory + "MB max");
    }
}
import java.util.HashMap;
import java.util.Scanner;

public class PhoneBook {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        // Read the number of entries in the phone book
        int n = scanner.nextInt();
        scanner.nextLine(); // Read the newline character after the integer

        // Create a HashMap to store the phone book entries
        HashMap<String, String> phoneBook = new HashMap<>();

        // Read the phone book entries
        for (int i = 0; i < n; i++) {
            String name = scanner.nextLine().trim();
            String phoneNumber = scanner.nextLine().trim();
            phoneBook.put(name, phoneNumber);
        }

        // Read the queries until end-of-file
        while (scanner.hasNextLine()) {
            String query = scanner.nextLine().trim();
            String phoneNumber = phoneBook.getOrDefault(query, "Not found");
            System.out.println(phoneNumber);
        }

        scanner.close();
    }
}

import java.net.Socket;
import java.net.ServerSocket;
import java.io.File;
import java.util.Scanner;
import java.io.PrintStream;

public class Server {
    public static void main(String[] args) {
        ServerSocket ssocket = null;
        Socket csocket = null;
        Scanner scanner = null;
        String sampletxt = null;
        PrintStream print;
        try {
            ssocket = new ServerSocket(25200);
            scanner = new Scanner(new File("sample.txt"));
            /**
             * .hasNextLine is of type boolean and checks if there is a next line.
             * scanner.nextLine grabs the next line but does not grab the new line
             * character, making it one big bunch. Once it sees the new line character it
             * stops and goes to the next line, hence adding the \n.
             */
            while (scanner.hasNextLine()) {
                sampletxt = sampletxt + scanner.nextLine() + "\n";
            }
            System.out.println("Listening for connection on port 25200");
            scanner.close();
            while (true) {
                csocket = ssocket.accept();
                print = new PrintStream(csocket.getOutputStream());
                print.println(sampletxt);
                csocket.getOutputStream().close();
                System.out.println("File Sent");
            }

        } catch (Exception e) {
            System.out.println("Error: 500");
            // TODO: handle exception
        }
    }
}
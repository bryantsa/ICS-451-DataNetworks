import java.net.Socket;
import java.nio.Buffer;
import java.io.BufferedReader;
import java.io.InputStreamReader;

public class Client {
    public static void main(String[] args) {
        String IP = "127.0.0.1";
        int port = Integer.parseInt(args[0]);

        Socket socket = null;
        InputStreamReader in = null;
        BufferedReader br = null;
        String text = null;
        try {
            socket = new Socket(IP, port);
            in = new InputStreamReader(socket.getInputStream());
            br = new BufferedReader(in);

            System.out.println("Connected to server:\n\n\n");
            /**
             * This while loop reads all of the file until it is null however, Once it hits
             * null the client will still be alive rather than terminate. The client needs
             * to know when the EOF is or somehow it ends the file, this means the server
             * needs a way to notify that the EOF has been reach which was close the stream.
             */
            while ((text = br.readLine()) != null) {
                System.out.println(text);
            }
            socket.close();
            in.close();
            br.close();
        } catch (Exception e) {
            System.out.println("Server is not up.");
            // TODO: handle exception
        }
    }
}
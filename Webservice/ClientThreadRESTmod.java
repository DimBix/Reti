import java.io.*;
import java.net.*;
import java.util.ArrayList;
import java.util.List;
import java.lang.Integer;

class ClientThreadRESTmod {
    public static void main(String args[]) {
        if (args.length < 3) {
            System.out.println("USAGE: java ClientREST tipofunzione op1 op2");
        } else {
            int op1 = Integer.parseInt(args[1]);
            int op2 = Integer.parseInt(args[2]);

            RESTAPI service1 = new RESTAPI("127.0.0.1", args[0], args[1], String.valueOf(((op2 - op1) / 3) + op1));
            RESTAPI service2 = new RESTAPI("127.0.0.1", args[0], String.valueOf(((op2 - op1) / 3) + op1),
                    String.valueOf(((op2 - op1) / 3) * 2 + op1));
            RESTAPI service3 = new RESTAPI("127.0.0.1", args[0], String.valueOf(((op2 - op1) / 3) * 2 + op1), args[2]);
            service1.start();
            service2.start();
            service3.start();
        }
    }
}

class RESTAPI extends Thread {
    String server, service, param1, param2;

    public void run() {
        if (service.equals("calcola-num-primi")) {
            System.out.println("Risultato: " + calcolaPrimi(Integer.parseInt(param1), Integer.parseInt(param2)));
        } else {
            System.out.println("Servizio non disponibile!");
        }

    }

    RESTAPI(String remoteServer, String srvc, String p1, String p2) {
        server = new String(remoteServer);
        service = new String(srvc);
        param1 = new String(p1);
        param2 = new String(p2);
    }

    synchronized List<Integer> calcolaPrimi(int val1, int val2) {
        URL u = null;
        List<Integer> risultato = new ArrayList<>();
        int i;

        try {
            u = new URL("http://" + server + ":8000/calcola-num-primi?param1=" + val1 + "&param2=" + val2);
            System.out.println("URL aperto: " + u);
        } catch (MalformedURLException e) {
            System.out.println("URL errato: " + u);
            return risultato; // Return empty list on error
        }

        try {
            URLConnection c = u.openConnection();
            c.connect();
            BufferedReader b = new BufferedReader(new InputStreamReader(c.getInputStream()));
            System.out.println("Lettura dei dati...");
            String s;
            while ((s = b.readLine()) != null) {
                System.out.println(s);
                // Check for the "primi" keyword
                if ((i = s.indexOf("primi")) != -1) {
                    String numberString = s.substring(i + 7).trim(); // Extract the number
                    try {
                        risultato.add(Integer.parseInt(numberString.replaceAll("[^0-9]", ""))); // Clean and parse
                    } catch (NumberFormatException e) {
                        System.err.println("Error parsing number from string: " + numberString);
                    }
                }
                // Attempt to parse the entire line as an integer
                try {
                    String cleanedString = s.trim().replaceAll("[^0-9]", ""); // Clean the string
                    if (!cleanedString.isEmpty()) {
                        risultato.add(Integer.parseInt(cleanedString));
                    }
                } catch (NumberFormatException e) {
                    System.err.println("Error parsing number from line: " + s);
                }
            }
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }

        return risultato;
    }

}

import java.io.*;
import java.net.*;
import java.util.ArrayList;
import java.util.List;

class ClientREST {
    public static void main(String args[]) {
        RESTAPI service1 = new RESTAPI("127.0.0.1");

        if (args.length < 3) {
            System.out.println("USAGE: java ClientREST tipofunzione op1 op2");
        } else if (args[0].equals("calcola-somma")) {
            System.out.println(
                    "Risultato: " + service1.calcolaSomma(Float.parseFloat(args[1]), Float.parseFloat(args[2])));
        } else if (args[0].equals("calcola-num-primi")) {
            System.out.println(
                    "Risultato: " + service1.calcolaPrimi(Integer.parseInt(args[1]), Integer.parseInt(args[2])));
        }
    }
}

class RESTAPI {
    String server;

    RESTAPI(String remoteServer) {
        server = new String(remoteServer);
    }

    float calcolaSomma(float val1, float val2) {
        URL u = null;
        float risultato = 0;
        int i;

        try {
            u = new URL("http://" + server + ":8000/calcola-somma?param1=" + val1 + "&param2=" + val2);
            System.out.println("URL aperto: " + u);
        } catch (MalformedURLException e) {
            System.out.println("URL errato: " + u);
        }

        try {
            URLConnection c = u.openConnection();
            c.connect();
            BufferedReader b = new BufferedReader(new InputStreamReader(c.getInputStream()));
            System.out.println("Lettura dei dati...");
            String s;
            while ((s = b.readLine()) != null) {
                System.out.println(s);
                if ((i = s.indexOf("somma")) != -1) {
                    risultato = Float.parseFloat(s.substring(i + 7));
                }
            }
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }

        return (float) risultato;
    }

    List<Integer> calcolaPrimi(int val1, int val2) {
        URL u = null;
        List<Integer> risultato = new ArrayList<>();
        int i;

        try {
            u = new URL("http://" + server + ":8000/calcola-num-primi?param1=" + val1 + "&param2=" + val2);
            System.out.println("URL aperto: " + u);
        } catch (MalformedURLException e) {
            System.out.println("URL errato: " + u);
        }

        try {
            URLConnection c = u.openConnection();
            c.connect();
            BufferedReader b = new BufferedReader(new InputStreamReader(c.getInputStream()));
            System.out.println("Lettura dei dati...");
            String s;
            while ((s = b.readLine()) != null) {
                System.out.println(s);
                if ((i = s.indexOf("primi")) != -1) {
                    risultato.add(Integer.parseInt(s.substring(i + 7)));
                }
                try {
                    risultato.add(Integer.parseInt(s));
                } catch (Exception e) {
                }
            }
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }

        return risultato;
    }
}

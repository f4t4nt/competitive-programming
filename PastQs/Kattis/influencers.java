import java.util.*;
import java.io.*;

public class G {
    public static void main(String[] args) throws IOException {
        FastScanner in = new FastScanner(System.in);
        PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

        int n = in.nextInt();
        int m = in.nextInt();
        int[] delta = new int[n];
        int idx = 0;
        for (char c : in.nextLine().toCharArray()) {
            if (c == '+') {
                delta[idx] = 1;
            }
            else if (c == '-') {
                delta[idx] = -1;
            }
            idx++;
        }

        int[] s = new int[n];
        ArrayList<Integer>[] adj = new ArrayList[n];
        for (int i = 0; i < n; i++) {
            adj[i] = new ArrayList<>();
        }

        for (int i = 0; i < m; i++) {
            int a = in.nextInt() - 1;
            int b = in.nextInt() - 1;
            adj[a].add(b);
            adj[b].add(a);
        }

        boolean changed = true;

        for (int i = 0; i < Math.pow(10, 2); i++) {
            boolean curChange = false;
            for (int j = 0; j < n; j++) {
                if (delta[j] == 0) continue;

                int cur = 0;
                for (int to : adj[j]) {
                    cur += s[to];
                }

                for (int to : adj[j]) {
                    if (cur <= 0 && delta[j] > 0) {
                        s[to] += 1;
                        curChange = true;
                    }
                    if (cur >= 0 && delta[j] < 0) {
                        s[to] -= 1;
                        curChange = true;
                    }
                }
            }
            if (!curChange) changed = false;
        }

        if (changed) {
            out.println("Impossible");
        }
        else {
            for (int x : s) {
                out.println(x);
            }
        }

        out.close();

    }


    static class FastScanner {
        BufferedReader br;
        StringTokenizer st;
        public FastScanner(InputStream i) {
            br = new BufferedReader(new InputStreamReader(i));
            st = new StringTokenizer("");
        }
        public String next() throws IOException {
            if (st.hasMoreTokens()) {
                return st.nextToken();
            }
            else
                st = new StringTokenizer(br.readLine());
            return next();
        }
        public int nextInt() throws IOException {
            return Integer.parseInt(next());
        }
        public double nextDouble() throws IOException {
            return Double.parseDouble(next());
        }
        public long nextLong() throws IOException {
            return Long.parseLong(next());
        }
        public String nextLine() throws IOException {
            if (!st.hasMoreTokens()) {
                st = new StringTokenizer(br.readLine());
                return nextLine();
            }

            String ret = "";
            while (st.hasMoreTokens()) {
                ret += " " + st.nextToken();
            }
            return ret.substring(1);
        }
        public int[] nextIntArr(int size) throws IOException {
            int[] arr = new int[size];
            for (int i = 0; i < arr.length; i++) {
                arr[i] = nextInt();
            }
            return arr;
        }
        public long[] nextLongArr(int size) throws IOException {
            long[] arr = new long[size];
            for (int i = 0; i < arr.length; i++) {
                arr[i] = nextLong();
            }
            return arr;
        }
        public double[] nextDoubleArr(int size) throws IOException {
            double[] arr = new double[size];
            for (int i = 0; i < arr.length; i++) {
                arr[i] = nextDouble();
            }
            return arr;
        }
    }
}
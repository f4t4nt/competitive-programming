
import java.util.*;

public class bricks {

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int tc = in.nextInt();

        while (tc-- > 0) {
            int n = in.nextInt();
            long[] amts = new long[n];
            char[] bw = new char[n];
            long[] r = new long[2];

            in.nextLine();
            for (int i = 0; i < n; i++) {
                String[] line = in.nextLine().split(" ");
                long amt = Long.parseLong(line[0]);
                char cur = line[1].charAt(0);
                amts[i] = amt;
                bw[i] = cur;
                if (cur == 'B') {
                    r[0] += amt;
                }
                else {
                    r[1] += amt;
                }
            }

            if (r[0] == 0 || r[1] == 0) {
                System.out.println(r[0] + r[1]);
                continue;
            }

            long factor = gcd(r[0], r[1]);
            r[0] /= factor;
            r[1] /= factor;

            long blocks = 0;
            long[] cur = new long[2];
            long[] prev = new long[2];


            for (int i = 0; i < n; i++) {
                if (i != 0 && bw[i] != bw[i - 1]) {
                    prev[0] = cur[0];
                    prev[1] = cur[1];
                }

                if (bw[i] == 'B') {
                    cur[0] += amts[i];
                }
                else {
                    cur[1] += amts[i];
                }

                if (cur[0] != 0 && cur[1] != 0) {
                    if (bw[i] == 'B' && cur[0] * r[1] >= cur[1] * r[0] && cur[1] % r[1] == 0 && prev[0] * r[1] < prev[1] * r[0]) {
                        cur[0] -= cur[1] * r[0] / r[1];
                        cur[1] = 0;
                        blocks++;
                    }
                    else if (bw[i] == 'W' && cur[1] * r[0] >= cur[0] * r[1] && cur[0] % r[0] == 0 && prev[1] * r[0] < prev[0] * r[1]) {
                        cur[1] -= cur[0] * r[1] / r[0];
                        cur[0] = 0;
                        blocks++;
                    }
                }
            }

            System.out.println(blocks);
        }
    }

    static long gcd(long a, long b) {
        if (a == 0) return b;
        return gcd(b % a, a);
    }
}
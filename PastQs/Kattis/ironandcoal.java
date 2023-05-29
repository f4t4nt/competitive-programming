import java.util.*;

public class ironandcoal {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        int n = in.nextInt();
        int m = in.nextInt();
        int k = in.nextInt();

        ArrayDeque<Integer> q = new ArrayDeque<>();
        ArrayDeque<Integer> mq = new ArrayDeque<>();
        ArrayDeque<Integer> kq = new ArrayDeque<>();

        int[] dist = new int[n + 1];
        int[] dist_iron = new int[n + 1];
        int[] dist_coal = new int[n + 1];

        q.add(1);
        for (int i = 0; i < n; i++) {
            dist[i + 1] = (int) 1e8;
            dist_iron[i + 1] = (int) 1e8;
            dist_coal[i + 1] = (int) 1e8;
        }
        dist[1] = 0;

        for (int i = 0; i < m; i++) {
            int cur = in.nextInt();
            mq.add(cur);
            dist_iron[cur] = 0;
        }
        for (int i = 0; i < k; i++) {
            int cur = in.nextInt();
            kq.add(cur);
            dist_coal[cur] = 0;
        }

        ArrayList<Integer>[] adj = new ArrayList[n + 1];
        ArrayList<Integer>[] adj_rev = new ArrayList[n + 1];

        for (int i = 1; i <= n; i++) {
            adj[i] = new ArrayList<>();
            adj_rev[i] = new ArrayList<>();
        }

        for (int i = 1; i <= n; i++) {
            int tmp = in.nextInt();
            for (int j = 0; j < tmp; j++) {
                int to = in.nextInt();
                adj[i].add(to);
                adj_rev[to].add(i);
            }
        }

        bfs(q, dist, adj);
//        System.out.println(Arrays.toString(dist));
        bfs(mq, dist_iron, adj_rev);
//        System.out.println(Arrays.toString(dist_iron));
        bfs(kq, dist_coal, adj_rev);
//        System.out.println(Arrays.toString(dist_coal));

        int ans = Integer.MAX_VALUE;
        for (int i = 1; i <= n; i++) {
            ans = Math.min(ans, dist[i] + dist_iron[i] + dist_coal[i]);
//            System.out.println(dist[i] + " " + dist_iron[i] + " " + dist_coal[i]);
        }

        System.out.println((ans >= 1e8) ? "impossible" : ans);

    }

    static void bfs(ArrayDeque<Integer> q, int[] dist, ArrayList<Integer>[] adj) {
        boolean[] vis = new boolean[dist.length];
        while (q.size() > 0) {
            int cur = q.poll();
            if (vis[cur]) continue;
            vis[cur] = true;

            for (int to : adj[cur]) {
                if (dist[cur] + 1 < dist[to]) {
                    dist[to] = dist[cur] + 1;
                    q.add(to);
                }
            }
        }
    }
}


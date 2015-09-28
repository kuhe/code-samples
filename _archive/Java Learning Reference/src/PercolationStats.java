/**
 * hey
 */
public class PercolationStats {

    private double[] percolatedAtStep;
    private static final boolean VISUAL = true;
    private int dimension;

    public PercolationStats(int N, int T) {
        if (N <= 0 || T <= 0) {
            throw new IllegalArgumentException("humbug");
        }
        int times = T;
        this.times = T;
        dimension = N;
        percolatedAtStep = new double[T];

        while (times-- > 0) {
            Percolation graph = new Percolation(N);

            int[][] sitePositions = new int[(N)*(N)][2];
            int index = 0;
            for (int i = 1; i <= N; i++) {
                for (int j = 1; j <= N; j++) {
                    sitePositions[index][0] = i;
                    sitePositions[index][1] = j;
                    index++;
                }
            }
            StdRandom.shuffle(sitePositions);

            int n = 0;
            while (!graph.percolates()) {
                int row = sitePositions[n][0];
                int col = sitePositions[n][1];
                graph.open(row, col);

//                if (VISUAL) {
//                    StdDraw.show(0);
//                    PercolationVisualizer.draw(graph, N);
//                    StdDraw.show(0);
//                }
                n++;
            }
            percolatedAtStep[times] = (double) n;
        }
    }
    public double mean() {
        int sum = 0;
        for (int i = 0; i < percolatedAtStep.length; i++) {
            sum += percolatedAtStep[i];
        }
        return ((double) sum) / percolatedAtStep.length / (dimension * dimension);
    }
    public double stddev() {
        return StdStats.stddev(percolatedAtStep) / (dimension * dimension);
    }
    private double interval() {
        return 1.96 * stddev() / Math.sqrt(times);
    }
    private int times;
    public double confidenceLo() {
        return mean() - interval();
    }
    public double confidenceHi() {
        return mean() + interval();
    }
    public static void main(String[] args) {
        int N, T;
        if (args.length == 2) {
            N = Integer.parseInt(args[0]);
            T = Integer.parseInt(args[1]);
            if (N <= 0 || T <= 0) {
                throw new IllegalArgumentException("bah");
            }
        } else {
            N = 500; T = 2;
        }
        PercolationStats stats = new PercolationStats(N, T);
        StdOut.println("mean                    = " + stats.mean());
        StdOut.println("stddev                  = " + stats.stddev());
        StdOut.println("95% confidence interval = " + stats.confidenceLo() + ", " + stats.confidenceHi());
    }
}

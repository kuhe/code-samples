/**
 * hey
 */
public class PercolationStats {

    private int[] percolatedAtStep;
    private static final boolean visual = true;
    private int dimension;

    public PercolationStats(int N, int T) {
        int times = T;
        dimension = N;
        percolatedAtStep = new int[T];

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

                if (visual) {
                    StdDraw.show(0);
                    PercolationVisualizer.draw(graph, N);
                    StdDraw.show(0);
                }
                n++;
            }
            percolatedAtStep[times] = n;
        }
    }
    // sample mean of percolation threshold
    public double mean() {
        int sum = 0;
        for (int i = 0; i < percolatedAtStep.length; i++) {
            sum += percolatedAtStep[i];
        }
        return ((double) sum) / percolatedAtStep.length / (dimension * dimension);
    }
    // sample standard deviation of percolation threshold
    public double stddev() {
        return 0;
    }
    // low  endpoint of 95% confidence interval
    public double confidenceLo() {
        return 0;
    }
    // high endpoint of 95% confidence interval
    public double confidenceHi() {
        return 0;
    }
    // test client (described below)
    public static void main(String[] args) {
        //todo use args for N, T
        PercolationStats stats = new PercolationStats(200, 1);
        StdOut.println(stats.mean());
    }

    private void index(int i, int j) {

    }
}

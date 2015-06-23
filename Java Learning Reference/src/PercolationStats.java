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
            int n = 0;
            while (!graph.percolates()) {
                n++;
                int row = (int) Math.ceil(StdRandom.uniform() * N);
                int col = (int) Math.ceil(StdRandom.uniform() * N);
                graph.open(row, col);

                if (visual) {
                    StdDraw.show(0);
                    PercolationVisualizer.draw(graph, N);
                    StdDraw.show(0);
                }
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
        PercolationStats stats = new PercolationStats(20, 3);
        StdOut.println(stats.mean());
    }

    private void index(int i, int j) {

    }
}

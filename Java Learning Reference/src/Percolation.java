/**
 * womp womp
 */
public class Percolation {
    private static final int BLOCKED = 0;
    private static final int OPEN = 1;
    private static final int FULL = 2;
    private int[][] sites;
    private int dimension = 0;

    private WeightedQuickUnionUF unionFind;
    private int secondDimensionScalar = 10;

    private int leak = -1;

    private boolean percolates = false;

    public Percolation(int N) {
        if (N <= 0) {
            throw new IllegalArgumentException("hah");
        }
        dimension = N;
        sites = new int[dimension + 1][dimension + 1];
        double indexDimension = (double) dimension;
        while (indexDimension > 1) {
            indexDimension /= 10;
            secondDimensionScalar *= 10;
        }
        unionFind = new WeightedQuickUnionUF(secondDimensionScalar * secondDimensionScalar);

        for (int n = 0; n <= dimension; n++) {
            for (int j = 0; j <= dimension; j++) {
                sites[n][j] = BLOCKED;
            }
        }
    }
    public void open(int i, int j) {
        validateIndex(i, j);
        sites[i][j] = OPEN;
        if (leak == -1 && i == 1) {
            leak = index(1, j);
            sites[i][j] = FULL;
        } else if (i == 1) {
            unionFind.union(index(1, j), leak);
        }
        int base = index(i, j);

        int[][] indexes = {{0,1}, {0,-1}, {1,0}, {-1,0}};
        for (int n = 0; n < 4; n++) {
            int[] pair = indexes[n];
            int rowOffset = pair[0], colOffset = pair[1];
            int target = index(i + rowOffset, j + colOffset);
            if (validIndex(i + rowOffset, j + colOffset) && isOpen(i + rowOffset, j + colOffset)) {
                unionFind.union(base, target);
            }
        }
    }
    public boolean isOpen(int i, int j) {
        validateIndex(i, j);
        return sites[i][j] == OPEN || sites[i][j] == FULL;
    }
    public boolean isFull(int i, int j) {
        validateIndex(i, j);
        boolean full = false;
        if (sites[i][j] == FULL) {
            full = true;
        }
        if (!full && leak != -1 ) {
            full = unionFind.connected(index(i, j), leak);
        }
        if (full) {
            sites[i][j] = FULL;
            if (i == dimension) {
                percolates = true;
            }
        }
        return full;
    }
    public boolean percolates() {
        return percolates;
    }
    public static void main(String[] args) {
        Percolation p = new Percolation(5);
        System.out.println(p.isOpen(1, 1));
        System.out.println(p.isOpen(5, 5));
    }

    private int index(int i, int j) {
        return secondDimensionScalar * i + j;
    }
    private void validateIndex(int i, int j) {
        if (!validIndex(i, j)) {
            throw new IndexOutOfBoundsException("uh oh");
        }
    }
    private boolean validIndex(int i, int j) {
        return !(i < 1 || i > dimension || j < 1 || j > dimension);
    }
}

/**
 * womp womp
 */
public class Percolation {
    private static final char BLOCKED = '0';
    private static final char OPEN = '1';
    private static final char FULL = '2';
    private static final char DRAINS = '3';
    private static final char PERCOLATES = '4';

    private char[] sites;
    private int dimension = 0;

    private WeightedQuickUnionUF unionFind;
    private int secondDimensionScalar = 1;

    private boolean percolates = false;

    public Percolation(int N) {
        if (N <= 0) {
            throw new IllegalArgumentException("hah");
        }
        dimension = N;
        int indexDimension = Integer.parseInt(dimension + "" + dimension);

        double indexSize = (double) indexDimension;
        while (indexSize >= 1) {
            indexSize /= 10;
            secondDimensionScalar *= 10;
        }
        secondDimensionScalar = (int) Math.sqrt(secondDimensionScalar);

        unionFind = new WeightedQuickUnionUF(indexDimension + 1);
        sites = new char[indexDimension + 1];
    }
    private void setToState(int index, char state) {
        sites[unionFind.find(index)] = state;
    }
    private char getState(int index) {
        return sites[unionFind.find(index)];
    }
    public void open(int i, int j) {
        validateIndex(i, j);

        int base = index(i, j);
        setToState(base, deriveStatus(getState(base), OPEN));

        if (i == 1) {
            setToState(base, deriveStatus(getState(base), FULL));
        }
        if (i == dimension) {
            setToState(base, deriveStatus(getState(base), DRAINS));
        }

        int[][] indexes = {{0,1}, {0,-1}, {1,0}, {-1,0}};
        for (int n = 0; n < 4; n++) {
            int[] pair = indexes[n];
            int rowOffset = pair[0], colOffset = pair[1];
            int target = index(i + rowOffset, j + colOffset);
            if (validIndex(i + rowOffset, j + colOffset) && isOpen(i + rowOffset, j + colOffset)) {
                char baseStatus = getState(base);
                char targetStatus = getState(target);
                unionFind.union(base, target);
                char newStatus = deriveStatus(targetStatus, baseStatus);
                setToState(base, newStatus);
                setToState(target, newStatus);
            }
        }
    }
    private char deriveStatus(char target, char base) {
        char result = base;
        if (base == DRAINS || target == DRAINS) {
            result = DRAINS;
        }
        if (base == FULL || target == FULL) {
            result = FULL;
        }
        if (base == DRAINS && target == FULL) {
            result = PERCOLATES;
        }
        if (base == FULL && target == DRAINS) {
            result = PERCOLATES;
        }
        if (base == PERCOLATES || target == PERCOLATES) {
            result = PERCOLATES;
        }
        if (result == PERCOLATES) {
            percolates = true;
        }
        return result;
    }
    public boolean isOpen(int i, int j) {
        validateIndex(i, j);
        int site = getState(index(i, j));
        return site == OPEN || site == FULL || site == DRAINS || site == PERCOLATES;
    }
    public boolean isFull(int i, int j) {
        validateIndex(i, j);
        int site = getState(index(i, j));
        return site == FULL || site == PERCOLATES;
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
            throw new IndexOutOfBoundsException("uh oh " + i + " " + j);
        }
    }
    private boolean validIndex(int i, int j) {
        return !(i < 1 || i > dimension || j < 1 || j > dimension);
    }
}

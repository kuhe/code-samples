import java.util.Iterator;
import java.util.NoSuchElementException;

public class RandomizedQueue<Item> implements Iterable<Item> {

    private Item[] arr = (Item[]) new Object[0];
    private int N = 0;

    public RandomizedQueue() {
    }

    public boolean isEmpty() {
        return N == 0;
    }

    public int size() {
        return N;
    }

    public void enqueue(Item item) {
        if (null == item) {
            throw new java.lang.NullPointerException();
        }
        if (arr.length <= N) {
            Item[] newArr = (Item[]) new Object[Math.max(2, 2 * N)];
            for (int i = 0; i < N; i++) {
                newArr[i] = arr[i];
            }
            arr = newArr;
        }
        arr[N] = item;

        Item m = arr[N];
        int n = StdRandom.uniform(N + 1);
        arr[N] = arr[n];
        arr[n] = m;

        N++;
    }
    public Item dequeue() {
        if (isEmpty()) {
            throw new NoSuchElementException();
        }
        if (arr.length > 4*N) {
            Item[] newArr = (Item[]) new Object[arr.length/2];
            for (int i = 0; i < N; i++) {
                newArr[i] = arr[i];
            }
            arr = newArr;
        }
        Item selection = arr[N-1];
        arr[N-1] = null;
        N--;
        return selection;
    }
    public Item sample() {
        if (isEmpty()) {
            throw new NoSuchElementException();
        }
        int index = StdRandom.uniform(N);
        return arr[index];
    }

    private RandomizedQueue(RandomizedQueue<Item> copy) {
        Item[] items = (Item[]) new Object[copy.size()];
        int n = 0;
        while (!copy.isEmpty()) {
            Item item = copy.dequeue();
            enqueue(item);
            items[n++] = item;
        }
        for (Item item : items) {
            copy.enqueue(item);
        }
    }

    public Iterator<Item> iterator()  { return new RandomizedQueueIterator();  }

    private class RandomizedQueueIterator implements Iterator<Item> {
        private RandomizedQueue<Item> copy;
        public RandomizedQueueIterator() {
            copy = new RandomizedQueue<Item>(RandomizedQueue.this);
        }
        public boolean hasNext()  { return !copy.isEmpty(); }
        public void remove()      { throw new UnsupportedOperationException(); }
        public Item next() {
            if (copy.isEmpty()) throw new NoSuchElementException();
            return copy.dequeue();
        }
    }

    public static void main(String[] args) {
        RandomizedQueue<Integer> wreck = new RandomizedQueue<Integer>();
        wreck.enqueue(1);
        wreck.enqueue(2);
        wreck.enqueue(3);
        wreck.enqueue(4);
        wreck.enqueue(5);
        wreck.enqueue(6);
        wreck.enqueue(7);
        wreck.enqueue(8);
        wreck.enqueue(9);

        Iterator it1 = wreck.iterator();
        Iterator it2 = wreck.iterator();

        while (it1.hasNext()) {
            System.out.print(it1.next());
        }

        System.out.println("");
        System.out.println("---");

        while (it2.hasNext()) {
            System.out.print(it2.next());
        }

    }
}
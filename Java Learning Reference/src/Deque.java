import java.util.Iterator;
import java.util.NoSuchElementException;

public class Deque<Item> implements Iterable<Item> {

    private class Node {
        private Item item;
        private Node next;
        private Node prev;
    }

    private Node head;
    private Node tail;
    private int N = 0;

    public Deque() {

    }

    public boolean isEmpty() {
        return N == 0;
    }
    public int size() {
        return N;
    }
    public void addFirst(Item item){
        if (null == item) {
            throw new java.lang.NullPointerException();
        }
        Node node = new Node();
        node.item = item;
        node.next = head;
        if (head != null) {
            head.prev = node;
        }
        head = node;
        N++;
        if (N == 1) {
            tail = head;
        }
    }
    public void addLast(Item item) {
        if (null == item) {
            throw new java.lang.NullPointerException();
        }
        Node node = new Node();
        node.item = item;
        node.prev = tail;
        if (tail != null) {
            tail.next = node;
        }
        tail = node;
        N++;
        if (N == 1) {
            head = tail;
        }
    }
    public Item removeFirst() {
        if (N <= 0) {
            throw new java.util.NoSuchElementException();
        }
        Node first = head;
        head = head.next;
        if (null != head) {
            head.prev = null;
        } else {
            tail = null;
        }
        N--;
        return first.item;
    }
    public Item removeLast() {
        if (N <= 0) {
            throw new java.util.NoSuchElementException();
        }
        Node last = tail;
        tail = tail.prev;
        if (tail != null) {
            tail.next = null;
        } else {
            head = null;
        }
        N--;
        return last.item;
    }

    public Iterator<Item> iterator()  { return new ListIterator();  }
    private class ListIterator implements Iterator<Item> {
        private Node current = head;
        public boolean hasNext()  { return current != null;                     }
        public void remove()      { throw new UnsupportedOperationException();  }

        public Item next() {
            if (!hasNext()) throw new NoSuchElementException();
            Item item = current.item;
            current = current.next;
            return item;
        }
    }

    private static void test(int a, int b) {
        if (a == b) {
            System.out.print(".");
        } else {
            System.out.print("x");
        }
    }
    private static void test(boolean a) {
        if (a) {
            System.out.print(".");
        } else {
            System.out.print("x");
        }
    }

    public static void main(String[] args) {
        Deque deck = new Deque<Integer>();
        deck.addFirst(1);
        deck.addLast(2);
        test((int) deck.removeFirst(), 1);
        test((int) deck.removeLast(), 2);
        test(deck.size(), 0);
        test(deck.head == null);
        test(deck.tail == null);
        deck.addLast(5);
        deck.addLast(6);
        test((int) deck.removeFirst(), 5);
        test((int) deck.removeFirst(), 6);
        test(deck.size(), 0);
        test(deck.head == null);
        test(deck.tail == null);
        deck.addLast(3);
        deck.addLast(4);
        deck.addLast(5);
        deck.addLast(6);
        deck.addFirst(2);
        deck.addFirst(1);
        Iterator<Integer> it = deck.iterator();
        int n = 1;
        while (it.hasNext()) {
            int c = it.next();
            test(c, n++);
        }
        while (!deck.isEmpty()) {
            deck.removeFirst();
        }
        test(deck.size(), 0);
        test(deck.head == null);
        test(deck.tail == null);
        deck.addFirst(2);
        deck.addFirst(1);
        test((int) deck.removeLast(), 2);
        test((int) deck.removeLast(), 1);
        test(deck.size(), 0);
        test(deck.head == null);
        test(deck.tail == null);
    }
}

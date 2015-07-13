

public class Subset {
    public static void main(String[] args) {
        String input = StdIn.readLine();
        int k;
        RandomizedQueue<String> rq = new RandomizedQueue<String>();
        String[] inputs = input.split("\\s+");
        for (String word : inputs) {
            rq.enqueue(word);
        }
        if (args.length >= 1) {
            k = Integer.parseInt(args[0]);
        } else {
            k = inputs.length;
        }
        while (k-- > 0) {
            StdOut.println(rq.dequeue());
        }
    }
}

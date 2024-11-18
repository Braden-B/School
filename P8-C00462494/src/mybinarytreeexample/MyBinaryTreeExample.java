package mybinarytreeexample;

public class MyBinaryTreeExample {

    public static void main(String[] args) {
        MyBinaryTree<Integer> mbt = new MyBinaryTree();
        
        mbt.insert(4);
        mbt.insert(20);
        mbt.insert(1);
        mbt.insert(9);
        mbt.insert(3);
        mbt.insert(3);
        mbt.insert(7);
        mbt.insert(2);
        mbt.insert(-1);
        mbt.insert(19);
        mbt.insert(-5);
        mbt.insert(-2);
        mbt.insert(22);
        mbt.insert(15);
        mbt.insert(11);
        mbt.insert(0);
        
        mbt.inorder();
        mbt.preorder();
        mbt.postorder();
        
        System.out.println("\nIterator Example:");
        java.util.Iterator it = mbt.iterator();
        while(it.hasNext()) {
            System.out.printf("%3s", it.next());
        }
        System.out.println();

        System.out.println("\nSearching Examples:\n");
        System.out.println("Searching for -1.");
        System.out.println(mbt.findElement(-1));
        System.out.println("Testing lazy delete");
        mbt.lazyDelete(-1);
        System.out.println("Searching for -1.");
        System.out.println(mbt.findElement(-1));
        System.out.println("Searching for 98.");
        System.out.println(mbt.findElement(98));

        System.out.println("Removing Lazy Deleted Nodes:");
        mbt.trimTree();
        System.out.println("\nAfter Lazy Deletion of -1:");
        java.util.Iterator it2 = mbt.iterator();
        while(it2.hasNext()) {
            System.out.printf("%3s", it2.next());
        }
        System.out.println();

        System.out.println("Show leaves example:");
        mbt.showLeaves();
        System.out.println();
        System.out.println("Breadth Traversal");
        mbt.breadthTraversal();
        System.out.println();
        System.out.println("\nDeleting Examples:\n");
        mbt.delete(4);        
        mbt.preorder();
        mbt.delete(-5);        
        mbt.preorder();
        mbt.delete(11);        
        mbt.preorder();
        mbt.delete(3);        
        mbt.preorder();
        mbt.delete(19);        
        mbt.preorder();
        mbt.delete(20);        
        mbt.preorder();
        mbt.delete(15);        
        mbt.preorder();
        mbt.delete(1);        
        mbt.preorder();
        mbt.delete(0);        
        mbt.preorder();
        mbt.delete(-1);        
        mbt.preorder();
        mbt.delete(1);        
        mbt.preorder();
        mbt.delete(-2);        
        mbt.preorder();
        mbt.delete(9);        
        mbt.preorder();
        mbt.delete(7);        
        mbt.preorder();
        mbt.delete(22);        
        mbt.preorder();
        mbt.delete(2);        
        mbt.preorder();
    }
    
}

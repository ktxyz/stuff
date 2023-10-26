import java.util.Arrays;
import java.util.List;

public class Main {
    final static private int[][][] example_tests = {
            {
                    {4,2,5,4},
                    {4,15,11,1},
                    {-1,9,6,8},
                    {12,7,7,-2}
            },
            {
                    {6,3,10,4,11},
                    {8,10,4,8,5},
                    {-1,14,11,3,-2},
                    {15,3,4,14,15},
                    {14,7,15,5,5}
            },
            {
                    {9,1,9,0,13,0},
                    {14,1,11,2,11,4},
                    {-1,2,11,0,0,15},
                    {4,3,9,6,3,-2}
            },
            {
                    {-1,6,12,15,11},
                    {8,7,15,7,10},
                    {13,7,13,15,-2},
                    {11,10,8,1,3},
                    {12,6,9,14,7}
            },
            {
                    {6,3,0,9,14,13,14},
                    {-1,14,9,11,15,14,15},
                    {2,15,0,12,6,15,-2},
                    {4,10,7,6,15,5,3},
                    {7,3,13,13,14,7,0}
            }
    };

    final static private  List<List<String>> example_sols = Arrays.asList(
            Arrays.asList("NNE", "EE", "S", "SS"),
            Arrays.asList("", "", "E", "", "E", "NESE"),
            Arrays.asList("E", "SE", "", "E", "E", "E"),
            null,
            null
    );

    public static void main(String[] args) {
        for(int i = 0; i < example_tests.length; ++i) {
            MazeSolver solver = new MazeSolver(example_tests[i]);
            solver.PrintMazes();
            var solution = solver.solve();
            if (solution != example_sols.get(i)) {
                // Print bad test
                System.out.println("Test " + i + " failed!");
                System.out.println("Expected: " + example_sols.get(i));
                System.out.println("Got: " + solution);
            } else {
                // Print good test
                System.out.println("Test " + i + " passed!");
            }
        }
    }
}

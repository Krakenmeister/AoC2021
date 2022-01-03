import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;
import java.util.stream.Collectors;

public class Part1 {
	public static void main(String[] args) {
		try {
			File input = new File("input.txt");
			Scanner reader = new Scanner(input);

			ArrayList<Integer> numbers = new ArrayList<>();
			ArrayList<ArrayList<ArrayList<Integer>>> boards = new ArrayList<>();

			boolean firstLine = true;
			while (reader.hasNextLine()) {
				String line = reader.nextLine();
				if (firstLine) {
					numbers = Arrays.stream(line.split(",")).map(Integer::valueOf).collect(Collectors.toCollection(ArrayList::new));
					line = reader.nextLine();
					firstLine = false;
				} else {
					ArrayList<ArrayList<Integer>> currentBoard = new ArrayList<>();
					for (int i=0; i<5; i++) {
						currentBoard.add(Arrays.stream(line.trim().split("\\s+")).map(Integer::valueOf).collect(Collectors.toCollection(ArrayList::new)));
						if (reader.hasNextLine()) {
							line = reader.nextLine();
						}
					}
					boards.add(currentBoard);
				}
			}

			int score = 0;
			for (int i=0; i<numbers.size(); i++) {
				for (int j=0; j<boards.size(); j++) {
					int[] bingoCounts = new int[10];
					for (int k=0; k<5; k++) {
						for (int l=0; l<5; l++) {
							if (boards.get(j).get(k).get(l) == numbers.get(i)) {
								boards.get(j).get(k).set(l, (-1 * boards.get(j).get(k).get(l)) - 1);
							}
							if (boards.get(j).get(k).get(l) < 0) {
								bingoCounts[k]++;
								bingoCounts[l+5]++;
							}
						}
					}
					for (int k=0; k<10; k++) {
						if (bingoCounts[k] == 5) {
							for (int l=0; l<5; l++) {
								for (int m=0; m<5; m++) {
									if (boards.get(j).get(l).get(m) >= 0) {
										score += boards.get(j).get(l).get(m);
									}
								}
							}
							score *= numbers.get(i);
							System.out.println("Bingo has been won! Final score = " + score);
/*							for (int a=0; a<boards.size(); a++) {
								for (int b=0; b<5; b++) {
									for (int c=0; c<5; c++) {
										System.out.print(boards.get(a).get(b).get(c) + " ");
									}
									System.out.println();
								}
								System.out.println();
							}*/
							return;
						}
					}
				}
			}

			System.out.println("No one got a bingo");
			for (int i=0; i<boards.size(); i++) {
				for (int j=0; j<5; j++) {
					for (int k=0; k<5; k++) {
						System.out.print(boards.get(i).get(j).get(k) + " ");
					}
					System.out.println();
				}
				System.out.println();
			}
		} catch (FileNotFoundException e) {
			System.out.println("Couldn't locate input.txt");
		}
	}
}

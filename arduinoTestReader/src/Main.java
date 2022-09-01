import java.io.*;
import java.util.Arrays;

public class Main {

    public static void main(String[] args) throws IOException {
        File file = new File("dashOutput.txt");
        BufferedReader br = new BufferedReader(new FileReader(file));

        int rpm = 0, ect = 0, lambda = 0, map = 0;
        int [] arr = new int [4];
        String st;
        String[] splitArray;

        while ((st = br.readLine()) != null) {
          try { if (st.startsWith("ECT") == true){
              splitArray = st.replaceAll("ECT: |    Lambda:|    MAP:|    RPM:", "").split(" ");
              for (int i = 0; i < splitArray.length; i++) {
                  arr[i] = Integer.valueOf(splitArray[i]);
              }
              ect = arr[0];
              lambda = arr[1];
              map = arr[2];
              rpm = arr[3];
              System.out.println(ect + " " + lambda + " " + map + " " + rpm);
          }
                Thread.sleep(20);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
    }


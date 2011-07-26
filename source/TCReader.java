import java.util.*;
import java.io.*;

public class TCReader {
	static Scanner in;

	static {
	    in = new Scanner(System.in);
	};
	
	public static String readline(){
        return in.nextLine();
	}
	
	public static int[] readintArray(){
	    String s = readline().trim();
	    s = s.substring(1,s.length()-1);
	    String [] sr = s.split(",");
	    int [] result = new int[sr.length];
	    for (int i = 0; i < sr.length; i++){
	        result[i] = Integer.parseInt(sr[i].trim());
	    }
	    return result;
	}

	public static double[] readdoubleArray(){
	    String s = readline().trim();
	    s = s.substring(1,s.length()-1);
	    String [] sr = s.split(",");
	    double [] result = new double[sr.length];
	    for (int i = 0; i < sr.length; i++){
	        result[i] = Double.parseDouble(sr[i]);
	    }
	    return result;
	}
	
	public static int readint(){
	    String s = readline().trim();
        return Integer.parseInt(s);
	}

	public static double readdouble(){
	    String s = readline().trim();
        return Double.parseDouble(s);
	}

	public static String fetchString(String s){
	    int l = s.indexOf("\"");
	    int r = s.lastIndexOf("\"");
        return s.substring(l,r);
	}
	
	public static String readString(){
	    String s = readline();
        return fetchString(s);
	}

	public static String[] readStringArray(){
        String s = readline().trim();
	    s = s.substring(1,s.length()-1);
	    String [] sr = s.split(",");
	    String [] result = new String[sr.length];
	    for (int i = 0; i < sr.length; i++){
	        result[i] = fetchString(sr[i]);
	    }
	    return result;
	}
	
}

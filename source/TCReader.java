import java.util.*;
import java.io.*;

public class TCReader {
	static Scanner in;
	static BufferedReader bin;
	static boolean eof = false;

	static {
	    in = new Scanner(System.in);
	};
	
	public static String readline(){
        return in.nextLine();
	}
	
	public static char readChar(){
	    int r = 0;
	    try{
		r = bin.read();
		if (r == -1){
		    eof = true;
		    r = 0;
		}
	    }catch(Exception e){
	    }
	    return (char)r;
	}
	
	public static String readString(){
	    char c = readChar();
	    while (!eof && c != '\"'){
		c = readChar();
	    }
	    c = readChar();
	    String r = "";
	    while(!eof && c != '\"'){
		r = r + c;
		c = readChar();
	    }
	    return r;
	}
	
	public static String readArray(){
	    char c = readChar();
	    while (!eof && c != '{'){
		c = readChar();
	    }
	    c = readChar();
	    String r = "";
	    while (!eof && c != '}'){
		r = r + c;
		c = readChar();
	    }
	    return r;
	}
	
	public static int[] readintArray(){
	    String s = readArray();
	    String [] sr = s.split(",");
	    int [] result = new int[sr.length];
	    for (int i = 0; i < sr.length; i++){
	        result[i] = Integer.parseInt(sr[i].trim());
	    }
	    return result;
	}

	public static double[] readdoubleArray(){
	    String s = readArray();
	    String [] sr = s.split(",");
	    double [] result = new double[sr.length];
	    for (int i = 0; i < sr.length; i++){
	        result[i] = Double.parseDouble(sr[i].trim());
	    }
	    return result;
	}
	
	public static int readint(){
	    return in.nextInt();
	}

	public static double readdouble(){
	    return in.nextDouble();
	}

	public static String fetchString(String s){
	    int l = s.indexOf("\"");
	    int r = s.lastIndexOf("\"");
        return s.substring(l,r);
	}
	

	public static String[] readStringArray(){
	    String s = readArray();
	    String [] sr = s.split(",");
	    String [] result = new String[sr.length];
	    for (int i = 0; i < sr.length; i++){
	        result[i] = fetchString(sr[i].trim());
	    }
	    return result;
	}
	
}

import java.util.*;
import java.io.*;

public class TCReader {
	static Scanner in;
	static BufferedReader bin;
	static boolean eof = false;

	static {
	    try{
		in = new Scanner(System.in);
		bin = new BufferedReader(new InputStreamReader(System.in));
	    }catch(Exception e){
		e.printStackTrace();
	    }
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
		e.printStackTrace();
		eof = true;
	    }
	    //System.out.println((char)r);
	    return (char)r;
	}
	
	public static String readStringBetween(char a, char b){
	    char c = readChar();
	    while (!eof && c != a){
		c = readChar();
	    }
	    c = readChar();
	    StringBuffer r = new StringBuffer();
	    while(!eof && c != b){
		r.append(c);
		c = readChar();
	    }
	    //System.out.println(r.toString());
	    return r.toString();
	}
	
	public static String readString(){
	    return readStringBetween('"','"');
	}
	
	public static String readArray(){
	    return readStringBetween('{','}');
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

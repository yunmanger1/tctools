import java.util.*;
import java.io.*;

public class TCReader {
	static BufferedReader bin;
	static boolean eof = false;
	static char c = '\n';
	
	static {
	    try{
		bin = new BufferedReader(new InputStreamReader(System.in));
	    }catch(Exception e){
		e.printStackTrace();
	    }
	};
	
	public static String readline(){
	    try{
		return bin.readLine();
	    }catch(IOException e){
		eof = true;
	    }
	    return "";
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
	    c = (char)r;
	    return c;
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
	
	public static boolean isIn(char c, String allowed){
	    return allowed.indexOf(c) != -1;
	}
	
	public static String readIn(String allowed){
	    while (!eof && !isIn(c, allowed)){
		readChar();
	    }
	    StringBuffer sb = new StringBuffer();
	    while(!eof && isIn(c, allowed)){
		sb.append(c);
		readChar();
	    }
	    return sb.toString();
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
	    return Integer.parseInt(readIn("1234567890"));
	}
	
	public static long readlong(){
	    return Long.parseLong(readIn("1234567890"));
	}

	public static double readdouble(){
	    return Double.parseDouble(readIn("1234567890."));
	}

	public static String fetchString(String s){
	    int l = s.indexOf("\"");
	    int r = s.lastIndexOf("\"");
	    if (l == -1){
		return s;
	    }
	    if (l == r){
		int n = s.length();
		if (l > n/2){
		    l = -1;
		}else{
		    r = n;
		}
	    }
	    return s.substring(l+1,r);
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

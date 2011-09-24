
import java.io.StringReader;

import junit.framework.Assert;

import org.junit.BeforeClass;
import org.junit.Test;


public class SimpleTestCase {

	@BeforeClass
	public static void setUpBeforeClass() throws Exception {
	}
	
	public static void _(String s){
	    System.out.println(s);
	}
	public static void _f(String fmt, Object ... args){
	    System.out.printf(fmt, (Object[])args);
	}
	
	@Test
	public void test0001(){
		StringReader in = new StringReader("asdfasdf { \"\",\"asd\\}asd\"}");
		TCReader tcr = new TCReader(in);
		String [] r = TCReader.readStringArray();
		for (String s : r){
			_(s);
		}
		Assert.assertTrue(r[0].equals(""));
		Assert.assertTrue(r[1].equals("asd}asd"));
	}

	
	@Test
	public void test0002(){
		StringReader in = new StringReader("asdfasdf { 165,1 ,548}");
		TCReader tcr = new TCReader(in);
		int [] r = TCReader.readintArray();
		for (int s : r){
			_f("%d\n",s);
		}
		Assert.assertTrue(r[0] == 165);
		Assert.assertTrue(r[1] == 1);
		Assert.assertTrue(r[2] == 548);
	}

	@Test
	public void test0003(){
		StringReader in = new StringReader("asdfasdf { 165,1 ,548.5}");
		TCReader tcr = new TCReader(in);
		double [] r = TCReader.readdoubleArray();
		for (double s : r){
			_f("%.2f\n",s);
		}
		Assert.assertTrue(r[0] == 165);
		Assert.assertTrue(r[1] == 1);
		Assert.assertTrue(r[2] == 548.5);
	}
	
	@Test
	public void test0004(){
		StringReader in = new StringReader("asdfasdf \" 165,1 ,\\\"548.5}\"asdas");
		TCReader tcr = new TCReader(in);
		String r = TCReader.readString();
		_(r);
		Assert.assertTrue(r.equals(" 165,1 ,\"548.5}"));
	}

}

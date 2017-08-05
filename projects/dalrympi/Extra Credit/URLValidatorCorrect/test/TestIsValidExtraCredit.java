// Extra credit random tester of isValid method 
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Random;
import java.util.concurrent.ThreadLocalRandom;
import java.util.regex.Pattern;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

import junit.framework.TestCase;

public class TestIsValidExtraCredit extends TestCase
{
		
	   public TestIsValidExtraCredit(String testName) 
	   {
		      super(testName);
	   }
	   
	   // Check if the scheme is valid or not 
	   private boolean isSchemeValid(String scheme)
	   {
		   // Check for no scheme 
		   if(scheme.length() == 0) return false;
		   
		   // List of acceptable schemes 
		   List<String> acceptable = new ArrayList<String>(); 
		   acceptable.add("http://");
		   acceptable.add("https://");
		   acceptable.add("ftp://");
		   
		   // Now check if the scheme is in the list 
		   for(String str : acceptable)
			   if(str.equals(scheme))
				   return true;

		   return false;
	   }
	   
	   // Randomly set up the scheme
	   // https://stackoverflow.com/questions/2482078/how-to-get-a-random-letter-from-a-list-of-specific-letters
	   private ResultPair randScheme() 
	   {
		   // Seed a random 
		   Random r = new Random(); 
		   
		   // Set up a list of chars to be chosen from 
		   List<Character> l = Arrays.asList('h', 't', 'p', ':', '/', 'f', 's');
		   
		   // Get a length 
		   int length = ThreadLocalRandom.current().nextInt(0, 8 + 1);
		   
		   // Return string and resultPair
		   String retString = "";
		   	   
		   // Loop and create schemes 
		   for(int i = 0; i < length; i++)
		   {
			   char c = l.get(r.nextInt(l.size()));
			   retString += c;
		   }
		  
		   // Bounce 
		   return new ResultPair(retString, isSchemeValid(retString));
	   }
	   
	   // Check if the ip is valid 
	   private boolean isIpValid(String ip)
	   {
		   // Parse on period then check all the pieces 
		   String pieces[] = ip.split(Pattern.quote("."));
		   for(String octet : pieces)
		   {
			   if(Integer.parseInt(octet) >= 256)
				   return false;
		   }
		   
		   return true;	   
	   }
	      	   
	   // Check if the computer name auth is valid 
	   private boolean isCompNameValid(String compName)
	   {
		   // Check for no length 
		   if(compName.length() == 0) return false; 
		   
		   // Check to make sure it does not begin or end with a period 
		   if(compName.charAt(0) == '.' || compName.charAt(compName.length() - 1) == '.')
			   return false;
		
		   // Create list of acceptable domains and check if ends in one of them
		   List<String> doms = new ArrayList<String>(); 
		   doms.add(".edu");
		   doms.add(".com");
		   doms.add(".org");
		   doms.add(".gov");
		   doms.add(".au");
		   for(String d : doms)
			   if(compName.endsWith(d))
				   return true;

		   return false;
	   }
	   
	   // Randomly set up the authority 
	   // https://stackoverflow.com/questions/2482078/how-to-get-a-random-letter-from-a-list-of-specific-letters
	   private ResultPair randAuth() 
	   {
		   // Seed a random 
		   Random r = new Random(); 
		   
		   // Authority portion
		   String authRet = "";
		   
		   // Get random number to decide if IP or computer name 
		   int ipOrComp = ThreadLocalRandom.current().nextInt(0, 1 + 1); 
		   
		   // Spin up an IP address 
		   if(ipOrComp == 0)
		   {
				authRet = r.nextInt(500) + "." + r.nextInt(500) + "." + r.nextInt(500) + "." + r.nextInt(500);
				return new ResultPair(authRet, isIpValid(authRet));
		   }
		   
		   // Create a computer name type of auth
		   int length = ThreadLocalRandom.current().nextInt(0, 1 + 20); 
		   for(int i = 0; i < length; i++)
		   {
			   int capSmallNumber = ThreadLocalRandom.current().nextInt(0, 1 + 3); 
			   switch(capSmallNumber)
			   {
				   case 0:
					    authRet += (char)(r.nextInt(26) + 'a'); break;
				   case 1:
					   authRet += (char)(r.nextInt(26) + 'A'); break;
				   case 2: 
					   authRet += (char)(r.nextInt(10) + '0'); break;
				   case 3: 
					   authRet += "."; break;
				   default:
					   authRet += "."; break;
			   }
		   }
		   return new ResultPair(authRet, isCompNameValid(authRet));			   	 
	   }
	   
	   // Check if the port is valid or not 
	   private boolean isPortValid(int port)
	   {		   
		   // Check if in correct range 
		   if(port > 0 && port < 65536)
			   return true;

		   // Otherwise you fail
		   return false;
	   }
	   
	   // Randomly set up the port
	   // https://stackoverflow.com/questions/2482078/how-to-get-a-random-letter-from-a-list-of-specific-letters
	   private ResultPair randPort() 
	   {
		   // Seed a random 
		   Random r = new Random(); 
		   
		   // Authority portion
		   int portRet = ThreadLocalRandom.current().nextInt(-100, 1 + 100000); 
		   	  	   
		   // Send the result back to the caller
		   return new ResultPair(":" + Integer.toString(portRet), isPortValid(portRet));			   	 
	   }
	
	   // Check if the scheme is valid or not 
	   private boolean isPathValid(String path)
	   {
		   // Check length 
		   if(path.length() == 0) return true;
		   
		   // Check random fail cases 
		   if(path.charAt(0) != '/') return false;
		   if(path.endsWith(".")) return false;
		   if(path.contains("..")) return false;
		   if(path.contains("//")) return false;
 
		   return true;
	   }
	   
	   // Randomly set up the path
	   // https://stackoverflow.com/questions/2482078/how-to-get-a-random-letter-from-a-list-of-specific-letters
	   private ResultPair randPath() 
	   {
		   // Seed a random 
		   Random r = new Random(); 
		   
		   // Declare the resturn path 
		   String retPath = "";
		   
		   // Decide if / at first or not 
		   if(r.nextBoolean() == true) 
			   retPath = "/";
		   	   
		   // Get a length 
		   int length = ThreadLocalRandom.current().nextInt(0, 25 + 1);
		   
		   for(int i = 0; i < length; i++)
		   {
			   int capSmallNumber = ThreadLocalRandom.current().nextInt(0, 1 + 5); 
			   switch(capSmallNumber)
			   {
				   case 0:
					    retPath += (char)(r.nextInt(26) + 'a'); break;
				   case 1:
					   retPath += (char)(r.nextInt(26) + 'A'); break;
				   case 2: 
					   retPath += (char)(r.nextInt(10) + '0'); break;
				   case 3: 
					   retPath += "."; break;
				   case 4: 
					   retPath += "/"; break;
				   default:
					   retPath += ""; break;
			   }
		   }
		  
		   // Bounce 
		   return new ResultPair(retPath, isPathValid(retPath));
	   }
	   
	   // Check if the scheme is valid or not 
	   private boolean isQueryValid(String query)
	   {
		   // Check length 
		   if(query.length() == 0) return true;
		   
		   // Check random fail cases 
		   if(query.charAt(0) != '?') return false;
		   if(query.endsWith("=")) return false;
		   if(query.endsWith("?")) return false;
		   if(query.endsWith("&")) return false;
		   if(query.charAt(1) == '=') return false;
		   if(query.charAt(1) == '&') return false;
		   
		   // Check for more than one ? and make sure the number of = is 1 more than &
		   int qCounter = 0;
		   int eCounter = 0;
		   int aCounter = 0;
		   for(int i =0; i < query.length(); i++)
		   {
			   if(query.charAt(i) == '?') qCounter++;
			   if(query.charAt(i) == '=') eCounter++;
			   if(query.charAt(i) == '&') aCounter++;
		   }
		   if(qCounter > 0) return false;
		   if(eCounter != aCounter + 1) return false;
		    
		   
		   // Make sure =& are never one after the other 
		   for(int i =0; i < query.length(); i++)
		   {
			    if(query.charAt(i) == '=' || query.charAt(i) == '&')
			    {
			    	if(query.charAt(i - 1) == '=' || query.charAt(i + 1) == '=') return false;
			    	if(query.charAt(i - 1) == '&' || query.charAt(i + 1) == '&') return false;
			    }
		   }
		   	   
		   return true;
	   }
	   
	   // Randomly set up the path
	   // https://stackoverflow.com/questions/2482078/how-to-get-a-random-letter-from-a-list-of-specific-letters
	   private ResultPair randQuery() 
	   {
		   // Seed a random 
		   Random r = new Random(); 
		   
		   // Declare the return query
		   String retQuery = "";
		   
		   // Decide if / at first or not 
		   if(r.nextBoolean() == true) 
			   retQuery = "?";
		   	   
		   // Get a length 
		   int length = ThreadLocalRandom.current().nextInt(0, 25 + 1);
		   
		   for(int i = 0; i < length; i++)
		   {
			   int capSmallNumber = ThreadLocalRandom.current().nextInt(0, 1 + 6); 
			   switch(capSmallNumber)
			   {
				   case 0:
					    retQuery += (char)(r.nextInt(26) + 'a'); break;
				   case 1:
					   retQuery += (char)(r.nextInt(26) + 'A'); break;
				   case 2: 
					   retQuery += (char)(r.nextInt(10) + '0'); break;
				   case 3: 
					   retQuery += "="; break;
				   case 4: 
					   retQuery += "?"; break;
				   case 5: 
					   retQuery += "&"; break;
				   default:
					   retQuery += ""; break;
			   }
		   }
		  
		   // Bounce 
		   return new ResultPair(retQuery, isQueryValid(retQuery));
	   }
	      
	   // https://stackoverflow.com/questions/1625234/how-to-append-text-to-an-existing-file-in-java
	   public void writeToFile(String dataToWrite, String filePath)
	   {
		   try
		   (FileWriter fw = new FileWriter(filePath, true);
				    BufferedWriter bw = new BufferedWriter(fw);
				    PrintWriter out = new PrintWriter(bw))
				{
				    out.println(dataToWrite);
				} 
		   catch (IOException e) 
				{
				    //exception handling left as an exercise for the reader
				}	   
	   }
	   
	   // Entrance point 
	   public static void main(String[] argv) 
	   {
		   // Locals 
		   TestIsValidExtraCredit oVal = new TestIsValidExtraCredit("ExtraCreditObject");
		   UrlValidator urlVal = new UrlValidator();
		   int iterIdx = 0;
		   int iterations = 100000;
					   
		   // Run a large number of tests 
		   String url = "";
		   boolean expected = false;
		   boolean result = false;
		   int failCount = 0;
		   for(iterIdx = 0; iterIdx < iterations; iterIdx++)
		   {
			   // Set up the parts 
			   ResultPair scheme = oVal.randScheme();
			   ResultPair authority = oVal.randAuth();   
			   ResultPair port = oVal.randPort();
			   ResultPair path = oVal.randPath();
			   ResultPair query = oVal.randQuery();
			   
			   // Construct the URL 
			   url = scheme.item + authority.item + port.item + path.item + query.item;
			   
			   // Find the truth values 
			   expected = scheme.valid && authority.valid && port.valid && path.valid && query.valid;
			   result = urlVal.isValid(url);
			   
			   // Print result if fail
			   if(expected != result)
			   {
				   failCount++;
				   // System.out.println(url + " FAILED and current fail count is " + Integer.toString(failCount));
				   if(argv[0].length() > 0)
					   oVal.writeToFile(url + " FAILED and current fail count is " + Integer.toString(failCount), argv[0]);
				   else 
					   oVal.writeToFile(url + " FAILED and current fail count is " + Integer.toString(failCount), "C:\\");
			   }
			   else 
			   {
				   if(argv[0].length() > 0)
					   oVal.writeToFile(url + " PASSED", argv[0]);
				   else 
					   oVal.writeToFile(url + " PASSED", "C:\\"); 
			   }

			   // DEBUG ONLY
			   // System.out.println(scheme.item + authority.item + port.item + path.item + query.item + scheme.valid + authority.valid + port.valid + path.valid + query.valid);
		   }
		   
		   // Present the final results 
		   // System.out.println("Final results: failed = " + Integer.toString(failCount) + " of total " + Integer.toString(iterations));
		   if(argv[0].length() > 0)
			   oVal.writeToFile("Final results: failed = " + Integer.toString(failCount) + " of total " + Integer.toString(iterations), argv[0]);
		   else 
			   oVal.writeToFile("Final results: failed = " + Integer.toString(failCount) + " of total " + Integer.toString(iterations), "C:\\");
	   }
}

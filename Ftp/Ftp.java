
import java.io.*;
import java.net.*;
import java.util.Vector;

public class Ftp {
	Socket ctrlSocket;
	public PrintWriter ctrlOutput;
	public BufferedReader ctrlInput;
	private final Object lock = new Object();
	public Vector<String> message = new Vector<String>(); 
	
	final int CTRLPORT =21;
	
	public void openConnection(String host,int port)
		throws IOException,UnknownHostException,ConnectException
	{
		ctrlSocket= new Socket(host,port);
		ctrlOutput = new PrintWriter(ctrlSocket.getOutputStream());
		ctrlInput = new BufferedReader(new InputStreamReader(ctrlSocket.getInputStream()));
	}
	public void closeConnection()
		throws IOException
	{
			ctrlSocket.close();
			
	}
	public String getCommand()
	{
		String buf = "";
		BufferedReader lineread = new BufferedReader(new InputStreamReader(System.in));
//		while(buf.length()!=2)
//		{
			try {
				buf = lineread.readLine();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
//		}
		return (buf);
	}
	public void showMenu()
	{
			safePrintln(">Command?");
			safePrint("1 login");
			safePrint(" 2 ls");
			safePrint(" 3 cd");
			safePrint(" 4 get");
			safePrint(" 5 put");
			safePrint(" 6 ascii");
			safePrint(" 7 binary");
			safePrint(" 8 delete file");
			safePrint(" 9 delete dir");
			safePrint(" 10 make dir");
			safePrint(" 11 print working dir");
			safePrint(" 12 NLST");
			safePrintln(" 13 quit");
	}
	
	public void doLogin(String user,String password)
	{
		String loginName = user;
		String loginPassword = password;

		
		ctrlOutput.println("USER "+ loginName);
		ctrlOutput.flush();	
		ctrlOutput.println("PASS "+password);
		ctrlOutput.flush();
		
	}
	
	public void doCd(String dirName)
	{
		ctrlOutput.println("CWD "+ dirName );
		ctrlOutput.flush();
		
	}
	
	public Vector<String> doLs()
	{
		int n;
		byte[] buff = new byte[1024];
		Socket dataSocket = dataConnection("LIST");
		Vector<String> lines= new Vector<String>();
		try {
			BufferedReader dataInput
				= new BufferedReader(new InputStreamReader(dataSocket.getInputStream()));
			
			String line = "";
			while((line = dataInput.readLine()) != null)
			{
				lines.add(line);
			}
			dataSocket.close();
			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			System.exit(1);
		}
		return lines;
	}
	
	public Vector<String> doLs(String dirName)
	{
		int n;
		byte[] buff = new byte[1024];
		Socket dataSocket = dataConnection("LIST "+dirName);
		Vector<String> lines= new Vector<String>();
		try {
			BufferedReader dataInput
				= new BufferedReader(new InputStreamReader(dataSocket.getInputStream()));
			
			String line = "";
			while((line = dataInput.readLine()) != null)
			{
				lines.add(line);
			}
			dataSocket.close();
			
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			System.exit(1);
		}
		return lines;
	}
	
	public void doGet(String fileName,String OutputFileName)
	{

		
		int n;
		byte[] buff = new byte[1024];
		try {
			FileOutputStream outfile = new FileOutputStream(OutputFileName);
			Socket dataSocket = dataConnection("RETR "+fileName);
			BufferedInputStream dataInput
				= new BufferedInputStream(dataSocket.getInputStream());
			while((n = dataInput.read(buff))>0)
			{
				outfile.write(buff,0,n);
			}
			dataSocket.close();
			outfile.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	public void doAscii()
	{
		ctrlOutput.println("TYPE A");
		ctrlOutput.flush();
	}
	
	public void doBinary()
	{
		ctrlOutput.println("TYPE I");
		ctrlOutput.flush();
	}
	
	public void doPut(String OutputFileName,String fileName)
	{
		int n;
		byte[] buff = new byte[1024];
		try {
			FileInputStream sendfile = new FileInputStream(OutputFileName);
			Socket dataSocket = dataConnection("STOR "+fileName);
			OutputStream outstr = dataSocket.getOutputStream();
			while((n=sendfile.read(buff))> 0 )
			{
				outstr.write(buff,0,n);
			}
			dataSocket.close();
			sendfile.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		
	}
	
	public void doDeleteFile(String fileName)
	{
		ctrlOutput.println("DELE "+ fileName );
		ctrlOutput.flush();
	}
	
	public void doDeleteDir(String dirName)
	{
			ctrlOutput.println("RMD "+ dirName );
			ctrlOutput.flush();
	}
	
	public void doMkDir(String dirName)
	{	
		ctrlOutput.println("MKD "+ dirName );
		ctrlOutput.flush();
	}
	
	public String doPWD()
	{
		ctrlOutput.println("PWD");
		ctrlOutput.flush();
		
		while(true)
		{
			String lastmessage = this.message.lastElement();
			String messagePrefix = lastmessage.substring(0,3);
			if(messagePrefix.equals("257"))
			{
				return lastmessage.substring(lastmessage.indexOf("\"")+1,lastmessage.lastIndexOf(("\"")));
			}
		}
		
	}
	
	public Vector<String> doNLST(String dirName)
	{		
		int n;
		byte[] buff = new byte[1024];
		Vector<String> lines = new Vector<String>();
		Socket dataSocket = dataConnection("NLST " + dirName);
		try {
			BufferedReader dataInput
				= new BufferedReader(new InputStreamReader(dataSocket.getInputStream()));
			String line = "";
			while((line = dataInput.readLine()) != null)
			{
				lines.add(line);
			}
			dataSocket.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			System.exit(1);
		}
		return lines;
	}
	
	
	public void doQuit()
	{
		ctrlOutput.println("QUIT");
		ctrlOutput.flush();
	}
	
	
	public Socket dataConnection(String ctrlcmd)
	{
		String cmd = "PORT ";
		int i;
		Socket dataSocket = null;
		try {
			//byte[] address = InetAddress.getLocalHost().getAddress();
			
			byte[] address = InetAddress.getByName("localhost").getAddress();;
			try {

				ServerSocket serverDataSocket = new ServerSocket(0,1);

				for(i = 0;i<4;++i)
					cmd = cmd + (address[i]&0xff) + ",";
			cmd = cmd +(((serverDataSocket.getLocalPort())/256) & 0xff)+","+(serverDataSocket.getLocalPort()&0xff);
			ctrlOutput.println(cmd);
			ctrlOutput.flush();
			ctrlOutput.println(ctrlcmd);
			ctrlOutput.flush();

			dataSocket = serverDataSocket.accept();

			serverDataSocket.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				System.exit(1);
			}
		} catch (UnknownHostException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			System.exit(1);
		}
		return dataSocket;
	}
	

	
	public void getMsgs()
	{
		CtrlListen listener = new CtrlListen(ctrlInput);
		Thread listenerThread = new Thread(listener);
		listenerThread.start();
	}
	
	public void safePrintln(String s) {
		  synchronized (System.out) {
		    System.out.println(s);
		  }
		}
	public void safePrint(String s) {
		  synchronized (System.out) {
		    System.out.print(s);
		  }
		}
	class CtrlListen implements Runnable
	{
		BufferedReader ctrlInput = null;
		public CtrlListen(BufferedReader in)
		{
			ctrlInput = in;
		}
		
		public void run()
		{
			while(true)
			{
				try {
					String input = ctrlInput.readLine();
					//System.out.println(input);
					if(input == null)
					{
						return;
					}

					synchronized(message)
					{
					message.add(input);		
					
						if(message.size()>=10)
						{
							for(int i=0;i<7;i++)
							{
								message.remove(0);
							}
						}
					}
				}catch (SocketException e)
				{
					return ;
				}catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} 
			}
		}
	}
}

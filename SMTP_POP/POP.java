import java.io.*;
import java.net.Socket;
import java.util.Vector;

import javax.net.ssl.SSLSocket;
import javax.net.ssl.SSLSocketFactory;

public class POP {
	int POP_PORT = 995;
	String pop_server = null;
	BufferedReader pop_in = null;
	PrintWriter pop_out = null;
	//SSLSocket pop = null;
	Socket pop = null;
	String username = null;
	String password = null;
	public Vector<String> getLines(String command)
		throws  IOException
	{
		boolean cont = true;
		String buf = null;
		Vector<String> lines = new Vector<String>();
		pop_out.print(command + "\r\n");
		pop_out.flush();
		String res = pop_in.readLine();
		System.out.println(res);
		if (res == null) {
			this.update();
			pop_out.print(command + "\r\n");
			pop_out.flush();
			res = pop_in.readLine();
			System.out.println(res);
		}

		if (!("+OK".equals(res.substring(0, 3)))) {
			if(pop !=null)
				pop.close();
			throw new RuntimeException(res);
		}

		while (cont) {
			buf = pop_in.readLine();
			//System.out.println(buf);
			if (".".equals(buf)) {
				cont = false;
				continue;
			}

			lines.add(buf);
		}
		return lines;
	}

	public void getSingleLine(String command) throws IOException {
		pop_out.print(command + "\r\n");
		pop_out.flush();
		System.out.println(command);
		String res = pop_in.readLine();
		System.out.println(res);

		if (res!=null && !("+OK".equals(res.substring(0, 3)))) {
			if(pop !=null)
				pop.close();
			throw new RuntimeException(res);
		}
	}


	public void authorization(String username,String password) throws IOException {
		/*SSLSocketFactory sslsocketfactory = (SSLSocketFactory) SSLSocketFactory
				.getDefault();

		pop = (SSLSocket) sslsocketfactory.createSocket(
				pop_server,POP_PORT);*/

		pop = new Socket(pop_server,POP_PORT);
		pop_in = new BufferedReader(new InputStreamReader(pop.getInputStream()));
		pop_out = new PrintWriter((pop.getOutputStream()));

		String res = pop_in.readLine();
		System.out.println(res);
		if (!("+OK".equals(res.substring(0, 3)))) {
			pop.close();
			throw new RuntimeException(res);
		}

		getSingleLine("User " + username);
		getSingleLine("PASS " + password);
		this.username = username;
		this.password = password;
	}

	public void update() throws IOException {

		try {
			if (pop != null) {
				getSingleLine("QUIT");
				pop.close();
			}
		} catch (Exception e) {

		}finally {
			this.authorization(this.username,this.password);
		}

	}

	public void quit() throws IOException {
		getSingleLine("QUIT");
		if (pop != null) {
			pop.close();
		}
	}

	public Vector<String> list() throws IOException {
		return getLines("LIST");
	}

	public Vector<String> retrieve(int number) throws IOException {
		Vector<String> lines = getLines("RETR " + Integer.toString(number));
		//getSingleLine("RSET ");
		return lines;
	}

	public void delete(int number) throws IOException {
		getSingleLine("DELE " + Integer.toString(number));
	}

	public void transaction()
		throws IOException
	{
		String buf = "";
		BufferedReader lineread
			= new BufferedReader(new InputStreamReader(System.in));
		boolean cont = true;
		
		while(cont)
		{
			System.out.println("Command: L)ist R)etrieve D)elete Q)uit");
			buf = lineread.readLine();
			
			if(buf.equalsIgnoreCase("Q")) cont = false;
			else if(buf.equalsIgnoreCase("L")){ getLines("LIST");}
			else if (buf.equalsIgnoreCase("R")) {
				System.out.println("Number? : ");
				buf = lineread.readLine();
				getLines("RETR " + buf);
			} else if ("D".equals(buf) || "d".equals(buf)) {
				System.out.println("Number? : ");
				buf = lineread.readLine();
				getSingleLine("DELE " + buf);
			}
		}
	}

	public static void main(String[] args) throws IOException {
		POP p = new POP();
		//p.mainproc(args);
	}
}

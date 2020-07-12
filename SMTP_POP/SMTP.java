import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.InetAddress;
import java.net.Socket;
import java.util.Scanner;
import java.util.Vector;

import javax.net.ssl.SSLSocket;
import javax.net.ssl.SSLSocketFactory;

public class SMTP {
    int SMTP_PORT ;
    String smtp_server = "";
    String my_email_addr = "";
    String pass ="";
    BufferedReader smtp_in = null;
    PrintWriter smtp_out = null;
    //SSLSocket smtp = null;
    Socket smtp = null;
    public void sendCommandAndResultCheck(Socket smtp,
                                          BufferedReader smtp_in,
                                          PrintWriter smtp_out,
                                          String command,
                                          int success_code)
            throws Exception {
        smtp_out.print(command + "\r\n");
        smtp_out.flush();
        System.out.println("send> " + command);
        resultCheck(smtp, smtp_in, smtp_out, success_code);
    }

    public void resultCheck(Socket smtp,
                            BufferedReader smtp_in,
                            PrintWriter smtp_out,
                            int success_code)
            throws Exception {
        String res = smtp_in.readLine();
        System.out.println("recv> " + res);

        if (Integer.parseInt(res.substring(0, 3)) != success_code) {
            smtp.close();
            throw new RuntimeException();
        }
    }
    public void reply(String subject, Vector<String> to, Vector<String> msgs,String mesgId) throws Exception {
    	sendCommandAndResultCheck(smtp, smtp_in, smtp_out,
                "MAIL FROM:<" + my_email_addr + ">", 250);
    	for (String s : to) {
            try {
                sendCommandAndResultCheck(smtp, smtp_in, smtp_out,
                        "RCPT TO:<" + s + ">", 250);
            } catch (Exception ignore) {
                // TODO: 閮����蔭��
            }
        }
    	sendCommandAndResultCheck(smtp, smtp_in, smtp_out,
                "DATA", 354);
    	
        smtp_out.print("References:" +mesgId+ "\r\n");
        smtp_out.flush();
        smtp_out.print("In-Reply-To:" +mesgId + "\r\n");
        smtp_out.flush();
    	smtp_out.print("Subject:" +subject + "\r\n");
        smtp_out.flush();


        smtp_out.print("From:<" + my_email_addr + ">\r\n");
        smtp_out.flush();
        smtp_out.print("To:");
        for (String s : to) {

            smtp_out.print("<" + s + ">");
        }
        smtp_out.print("\r\n");
        smtp_out.flush();

        smtp_out.print("Content-Type: text/html; charset=\"UTF-8\"\r\n");
        smtp_out.flush();
        
        System.out.println("send> Subject: " + subject);
        smtp_out.println();
        smtp_out.flush();

        // ���
        for (String msg : msgs) {
            smtp_out.println(msg);
            smtp_out.flush();
            System.out.println("send> " + msg);
        }
        sendCommandAndResultCheck(smtp, smtp_in, smtp_out,
                "\r\n.", 250);
        
    }

    public void send(String subject, Vector<String> to, Vector<String> msgs)
            throws Exception {

        // ��AIL FROM
        sendCommandAndResultCheck(smtp, smtp_in, smtp_out,
                "MAIL FROM:<" + my_email_addr + ">", 250);

        // ��CPT TO
        for (String s : to) {
            try {
                sendCommandAndResultCheck(smtp, smtp_in, smtp_out,
                        "RCPT TO:<" + s + ">", 250);
            } catch (Exception ignore) {
                // TODO: 閮����蔭��
            }
        }


        // ��ATA
        sendCommandAndResultCheck(smtp, smtp_in, smtp_out,
                "DATA", 354);

        // ��ubject璅
        smtp_out.print("Subject:" +subject + "\r\n");
        smtp_out.flush();

        /*smtp_out.print("In-Reply-To:<" + "5ef6ec94.1c69fb81.21f32.8bbf@mx.google.com" + ">\r\n");
        smtp_out.flush();
        smtp_out.print("References:<" + "5ef6ec94.1c69fb81.21f32.8bbf@mx.google.com" + ">\r\n");
        smtp_out.flush();*/
        smtp_out.print("From:<" + my_email_addr + ">\r\n");
        smtp_out.flush();
        smtp_out.print("To:");
        for (String s : to) {

            smtp_out.print("<" + s + ">");
        }
        smtp_out.print("\r\n");
        smtp_out.flush();

        smtp_out.print("Content-Type: text/html; charset=\"UTF-8\"\r\n");
        smtp_out.flush();
        /*smtp_out.print("Reply-To:<" + my_email_addr + ">\r\n");
        smtp_out.flush();*/

        System.out.println("send> Subject: " + subject);
        smtp_out.println();
        smtp_out.flush();

        // ���
        for (String msg : msgs) {
            smtp_out.println(msg);
            smtp_out.flush();
            System.out.println("send> " + msg);
        }
        sendCommandAndResultCheck(smtp, smtp_in, smtp_out,
                "\r\n.", 250);

        // ��UIT
        /*sendCommandAndResultCheck(smtp, smtp_in, smtp_out,
                "QUIT", 221);

        // �����蝺�
        smtp.close();*/
    }

  /*  public void setAddress() {
        Scanner scanner = new Scanner(System.in);

        System.out.print("隢撓��隞嗡撩��雿蔭 >> ");
        smtp_server = "smtp.gmail.com";
        System.out.println("隢撓�雿�隞嗡�蔭 >> ");
        my_email_addr = "s10659013@gm2.nutn.edu.tw";
    }*/
    public void update() throws Exception {

		try {
			if (smtp != null) {
				
				smtp.close();
			}
		} catch (Exception e) {

		}finally {
			this.sendAuth(my_email_addr, pass);
		}
    }
    
    public Vector<String> getMsgs() {
        Scanner scanner = new Scanner(System.in);
        Vector<String> msgs = new Vector<>();


        System.out.println("隢撓�閬���(���暺��.����):");
        String msg = scanner.nextLine();
        while(!msg.equals(".")) {
            msgs.add(msg);
            msg = scanner.nextLine();
        }
        System.out.println("頛詨摰");
        return msgs;
    }


    void auth(BufferedReader smtp_in,
              PrintWriter smtp_out, String s) throws Exception {
        smtp_out.write(s);
        smtp_out.write("\r\n");
        smtp_out.flush();
        System.out.println("send> "+s);
        String response = smtp_in.readLine();
        System.out.println("recv> " + response);
        int res = Integer.parseInt(response.substring(0, 3));
        if (res == 501 || res == 535) {
            System.out.print("�銵����隤歹��");
            throw new Exception("�銵����隤歹��");
        }
    }

    void sendAuth(String account,String password) throws Exception {
        /*SSLSocketFactory sslsocketfactory = (SSLSocketFactory) SSLSocketFactory
                .getDefault();
        smtp = (SSLSocket) sslsocketfactory.createSocket(
                smtp_server,SMTP_PORT);*/

        smtp = new Socket(smtp_server,SMTP_PORT);
        smtp_in = new BufferedReader(
                new InputStreamReader(smtp.getInputStream()));
        smtp_out = new PrintWriter(
                smtp.getOutputStream());

        resultCheck(smtp, smtp_in, smtp_out, 220);

        // ��ELO
        String myname = InetAddress.getLocalHost().getHostName();
        sendCommandAndResultCheck(smtp, smtp_in, smtp_out,
                "HELO " + myname, 250);

        // 撽��
        sendCommandAndResultCheck(smtp, smtp_in, smtp_out,
                "AUTH LOGIN", 334);
        Base64 b = new Base64();
        String id = b.encode(account.getBytes());
        String p = b.encode(password.getBytes());
        auth(smtp_in, smtp_out, id);
        auth(smtp_in, smtp_out, p);
        my_email_addr = account;
        pass = password;
        System.out.println("撽��");
    }

    public void close() throws Exception {
        if(smtp !=null){
            sendCommandAndResultCheck(smtp, smtp_in, smtp_out,
                    "QUIT", 221);
            smtp.close();
        }
        if(smtp_in!=null)
        {
            smtp_in.close();
        }
        if(smtp_out!=null){
            smtp_out.close();
        }
    }
   /* public void mainProcess() {

        String subject = "TEST";
        Vector<String> to_list = new Vector<String>();

        to_list.add("s10659013@gm2.nutn.edu.tw");
        if (to_list.size() > 0) {
            try {

                setAddress();
                Vector<String> msgs = getMsgs();
                send(subject, to_list, msgs);
            } catch (Exception e) {
                System.out.print("��蝺隤歹��");
                e.printStackTrace();
            }
        }
    }*/

    public static void main(String[] args) {
        SMTP ms = new SMTP();
       // ms.mainProcess();
    }
}

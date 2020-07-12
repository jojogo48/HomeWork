
import java.awt.BorderLayout;
import java.awt.FlowLayout;
import java.awt.Font;

import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JPanel;
import javax.swing.border.EmptyBorder;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.ConnectException;
import java.net.Socket;
import java.net.UnknownHostException;
import java.awt.GridLayout;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JTextField;

import java.awt.event.ActionListener;
import java.awt.event.ActionEvent;
import javax.swing.SwingConstants;

public class Login extends JDialog {
	
	/**
	 * 
	 */
	private static final Font size12 = new Font("Arial", Font.PLAIN, 20);
	private static final long serialVersionUID = 1L;
	private final JPanel contentPanel = new JPanel();
	private JTextField hostNameEntry;
	private JTextField userNameEntry;
	private JTextField passwordEntry;
	private JTextField portEntry;
	private final int CTRLPORT =21;
	private static JLabel Error;
	public static Login dialog;
	/**
	 * Launch the application.
	 */
	public static void main(String[] args) {
		try {
			dialog = new Login();
			dialog.setDefaultCloseOperation(JDialog.DISPOSE_ON_CLOSE);
			dialog.setVisible(true);
		} catch (Exception e) {
			e.printStackTrace();
		}
	}

	/**
	 * Create the dialog.
	 */
	

	public Login() {
		setBounds(100, 100,410, 230);
		setResizable(false);
		setTitle("Login");
		getContentPane().setLayout(new BorderLayout());
		contentPanel.setBorder(new EmptyBorder(0, 0, 0, 0));
		getContentPane().add(contentPanel, BorderLayout.CENTER);
		contentPanel.setLayout(new GridLayout(2, 2, 0, 0));
		{
			JPanel panel = new JPanel();
			contentPanel.add(panel);
			panel.setLayout(new FlowLayout(FlowLayout.CENTER, 5, 5));
			{
				JLabel hostNameLabel = new JLabel("Host Name");
				hostNameLabel.setFont(size12);
				panel.add(hostNameLabel);
			}
			{
				hostNameEntry = new JTextField();
				hostNameEntry.setFont(size12);
				panel.add(hostNameEntry);
				hostNameEntry.setColumns(10);
			}
		}
		{
			JPanel panel = new JPanel();
			contentPanel.add(panel);
			{
				JLabel portLabel = new JLabel("Port Number");
				portLabel.setFont(size12);
				panel.add( portLabel);
			}
			{
				portEntry = new JTextField();
				portEntry.setFont(size12);
				panel.add(portEntry);
				portEntry.setColumns(10);
			}
		}
		{
			JPanel panel = new JPanel();
			contentPanel.add(panel);
			{
				JLabel lblNewLabel_1 = new JLabel("User Name");
				lblNewLabel_1.setFont(size12);
				panel.add(lblNewLabel_1);
			}
			{
				userNameEntry = new JTextField();
				userNameEntry.setFont(size12);
				panel.add(userNameEntry);
				userNameEntry.setColumns(10);
			}
		}
		{
			JPanel panel = new JPanel();
			contentPanel.add(panel);
			{
				JLabel passwordLabel = new JLabel("Password ");
				 passwordLabel.setFont(size12);
				panel.add( passwordLabel);
			}
			{
				passwordEntry = new JTextField();
				passwordEntry.setFont(size12);
				panel.add(passwordEntry);
				passwordEntry.setColumns(10);
			}
		}
		
		{
			JPanel buttonPane = new JPanel();
			buttonPane.setLayout(new FlowLayout(FlowLayout.RIGHT));
			getContentPane().add(buttonPane, BorderLayout.SOUTH);
			{
				JButton okButton = new JButton("OK");
				okButton.setFont(size12);
				okButton.addMouseListener(new MouseAdapter() {
					@Override
					public void mousePressed(MouseEvent arg0) {
						Error.setText("Logining");
					}
					@Override
					public void mouseClicked(MouseEvent arg0) {
						String[] arg = {hostNameEntry.getText(),userNameEntry.getText(),passwordEntry.getText()};

						if(arg[1].contains("[") || arg[1].contains("]"))
						{
							Error.setText("Invalid character");
							return;
						}
						
						Ftp ftp = null ;
						try {
							 ftp =new Ftp();
							 int port = Integer.parseInt(portEntry.getText());
					
							 ftp.openConnection(arg[0],port);
							 ftp.getMsgs();
							 ftp.doLogin(arg[1], arg[2]);
							 
							 while(true)
							 {
								 if(ftp.message.size() ==0)
									 continue;
								 
								 if(ftp.message.lastElement().substring(0,3).equals("230") )
								 {
									 
									 FtpGUI.main(ftp);						 
									 dispose(); 	
									 return;
								 }else if(ftp.message.lastElement().substring(0,3).startsWith("5")||ftp.message.lastElement().substring(0,3).startsWith("4"))
								 {
									 Error.setText("Login or password incorrect!");
									 break;
								 }
							 }
							ftp.doQuit();
							ftp.closeConnection();
						}catch(UnknownHostException e)
						{
							Error.setText("Host Error");
						}catch(ConnectException e)
						{
							Error.setText("Connect Refuse");
						}
						catch (NumberFormatException e) 
						{
							Error.setText("Port Error");
						}
						catch(Exception e)
						{
							e.printStackTrace();
						}

					}
				});
				{
					Error = new JLabel("");
					Error.setHorizontalAlignment(SwingConstants.CENTER);
					buttonPane.add(Error);
				}
				okButton.setActionCommand("OK");
				buttonPane.add(okButton);
				getRootPane().setDefaultButton(okButton);
			}
			{
				JButton cancelButton = new JButton("Cancel");
				cancelButton.setFont(size12);
				cancelButton.addActionListener(new ActionListener() {
					public void actionPerformed(ActionEvent arg0) {
						System.exit(0);
					}
				});
				cancelButton.setActionCommand("Cancel");
				buttonPane.add(cancelButton);
			}
		}
	}

}

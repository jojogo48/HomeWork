
import java.awt.Dimension;
import java.awt.EventQueue;
import java.awt.Font;

import javax.swing.*;
import javax.swing.filechooser.FileSystemView;
import javax.swing.text.DefaultCaret;

import java.awt.GridLayout;
import java.awt.Rectangle;
import java.awt.TextArea;
import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.Transferable;
import java.awt.datatransfer.UnsupportedFlavorException;
import java.awt.dnd.InvalidDnDOperationException;

import javax.swing.tree.DefaultMutableTreeNode;
import javax.swing.tree.DefaultTreeModel;
import javax.swing.tree.TreeNode;
import javax.swing.tree.TreePath;
import javax.swing.tree.TreeSelectionModel;

import java.awt.event.MouseMotionAdapter;
import java.io.File;
import java.io.IOException;
import java.util.*;
import java.awt.event.MouseEvent;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import javax.swing.event.TreeWillExpandListener;
import javax.swing.event.TreeExpansionEvent;
import javax.swing.event.TreeExpansionListener;
import java.awt.FlowLayout;
import javax.swing.event.TreeSelectionListener;
import javax.swing.event.TreeSelectionEvent;

public class FtpGUI {
	private JFrame frame;
	public Ftp ftp;
	private JTree tree;
	private JFileChooser fileChooser = new JFileChooser(FileSystemView.getFileSystemView().getHomeDirectory());
	private static final Font size12 = new Font(Font.SERIF, Font.PLAIN, 20);
	
	/**
	 * Launch the application.
	 */
	public static void main(Ftp ftp) {
		 
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					FtpGUI window = new FtpGUI(ftp);
					window.frame.setVisible(true);
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});
	}

	/**
	 * Create the application.
	 */
	public FtpGUI(Ftp ftp) {
		this.ftp = ftp;
		TimeoutListenor timer = new TimeoutListenor();
		timer.ftp = ftp;
		timer.gui = this;
		timer.start();
		initialize();
	}
	
	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {
		frame = new JFrame();
		
		
		
		frame.setBounds(100, 100, 750, 600);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().setLayout(new GridLayout(1, 0, 0, 0));
		
		JSplitPane splitPane = new JSplitPane();
		splitPane.setResizeWeight(0.8);
		splitPane.setOrientation(JSplitPane.VERTICAL_SPLIT);
		frame.getContentPane().add(splitPane);
		
		JSplitPane splitPane_1 = new JSplitPane();
		splitPane_1.setResizeWeight(0.5);
		splitPane.setLeftComponent(splitPane_1);
		

		JScrollPane scrollPane3 = new JScrollPane();
		splitPane.setRightComponent(scrollPane3);
		JTextArea messageArea = new JTextArea();
		messageArea.setEditable(false);
		messageArea.setFont(size12);
		scrollPane3.setViewportView(messageArea);
		MessageListenor messagelis =new MessageListenor();
		messagelis.ftp = ftp;
		messagelis.area = messageArea;
		messagelis.start();
		
		JSplitPane splitPane_2 = new JSplitPane();
		splitPane_2.setOrientation(JSplitPane.VERTICAL_SPLIT);
		splitPane_1.setLeftComponent(splitPane_2);
		
		
		JButton ChooseDir = new JButton("ChooseDir");
		ChooseDir.setFont(size12);
		fileChooser.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
		fileChooser.setAcceptAllFileFilterUsed(false);
		ChooseDir.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				if (fileChooser.showOpenDialog(null) == JFileChooser.APPROVE_OPTION) {

//					System.out.println("getCurrentDirectory(): " + fileChooser.getCurrentDirectory());
					File selectedFile = fileChooser.getSelectedFile();
					System.out.println("Selected file: " + selectedFile.getName());
				
					File[] files = selectedFile.listFiles();
									
				 	DefaultMutableTreeNode root = new DefaultMutableTreeNode(selectedFile.getName());

				 	search(files,root);
				 	
					DefaultTreeModel model = new DefaultTreeModel(root);		
					
					tree.setModel(model);
					
					tree.setTransferHandler(new MyTransferHandlerClient((DefaultTreeModel)tree.getModel()
							, fileChooser.getCurrentDirectory()+"\\",tree));
				}
			}
		});
		JPanel panel_1 = new JPanel();
		panel_1.setLayout(new FlowLayout(FlowLayout.CENTER, 5, 5));
		panel_1.add(ChooseDir);
		
		splitPane_2.setLeftComponent(panel_1);
		
		JScrollPane scrollPane = new JScrollPane();
		splitPane_2.setRightComponent(scrollPane);
		
		tree = new JTree();
		tree.setFont(size12);
		tree.setDragEnabled(true);
		tree.setDropMode(DropMode.ON_OR_INSERT);
		tree.setModel(null);
		
		scrollPane.setViewportView(tree);
		
		JSplitPane splitPane_3 = new JSplitPane();
		splitPane_3.setOrientation(JSplitPane.VERTICAL_SPLIT);
		splitPane_1.setRightComponent(splitPane_3);
		
		 MouseAdapter ma = new MouseAdapter() {
		        private void myPopupEvent(MouseEvent e) {
		            int x = e.getX();
		            int y = e.getY();
		            JTree tree = (JTree)e.getSource();
		            TreePath path = tree.getPathForLocation(x, y);
		            if (path == null)
		                return; 

		            tree.setSelectionPath(path);
		          
		            DefaultMutableTreeNode obj = (DefaultMutableTreeNode)path.getLastPathComponent();
		            JPopupMenu popup = new JPopupMenu();
		            if(obj.isLeaf())
		            {
		            	JMenuItem item1 = new JMenuItem("DeleteFile");
		            	popup.add(item1);
		            	item1.addActionListener((ActionListener) new ActionListener() {
		                    @Override
		                    public void actionPerformed(ActionEvent arg0) {
		                    	
		                    	DefaultTreeModel model = (DefaultTreeModel)tree.getModel();
		                    	
		                    	
		                    	String absPath ="/";
		                    	Object[] paths = path.getPath();
		                    	for(int i=1;i<paths.length;i++)
		                    	{
		                    		absPath += paths[i].toString()+"/";
		                    	}   	
		                    	ftp.doDeleteFile(absPath);
		                    	model.removeNodeFromParent(obj);
		                    }
		            	});
		            
		            }else
		            {
		            	JMenuItem item1 = new JMenuItem("CreateDir");
		            	JMenuItem item2 = new JMenuItem("DeleteDir");
				        popup.add(item1);
				        popup.add(item2);
				        
				        item1.addActionListener((ActionListener) new ActionListener() {
		                    @Override
		                    public void actionPerformed(ActionEvent arg0) {
		                    	DefaultTreeModel model = (DefaultTreeModel)tree.getModel();
		                    	
		                    	String absPath ="/";
		                    	Object[] paths = path.getPath();
		                    	for(int i=1;i<paths.length;i++)
		                    	{
		                    		absPath += paths[i].toString()+"/";
		                    	}
		                    	
		                    	String dirName = JOptionPane.showInputDialog("Please Input Dir Name ");
		                    	if(dirName == null)
		                    		return;
		                    	while(dirName.contains("\\") || dirName.contains("/"))
		                    	{
		                    		dirName = JOptionPane.showInputDialog("Invalid Name(can't contain '\' or '/'),enter again");
		                           	if(dirName == null)
			                    		return;
		                    	}
		                    	ftp.doMkDir(absPath+dirName);
		                    	
		                        DefaultMutableTreeNode newNode = new DefaultMutableTreeNode(dirName)
		                        		{
		                        			public boolean isLeaf()
		                        			{
		                        				return false;
		                        			}
		                        		};
		                 
		                        boolean is_insert = true;
		                        for(int i=0;i<obj.getChildCount();i++)
		                        {
		                       	 DefaultMutableTreeNode child =(DefaultMutableTreeNode)obj.getChildAt(i);
		                       	 Object[] obj = child.getPath();
		                       	 if((!child.isLeaf())&& paths[paths.length-1].toString().equals(dirName))
		                       	 {
		                       		 is_insert=false;
		                       	 }
		                        }
		                        if(is_insert)
		                        {
		                       	  model.insertNodeInto(newNode, obj,  model.getChildCount(obj));
		                        }
		                    }
		            	});
			
		            	item2.addActionListener((ActionListener) new ActionListener() {
		                    @Override
		                    public void actionPerformed(ActionEvent arg0) {
		                    	
		                    	DefaultTreeModel model = (DefaultTreeModel)tree.getModel();
		                    	
		                    	
		                    	
		                    	String absPath ="/";
		                    	Object[] paths = path.getPath();
		                    	for(int i=1;i<paths.length;i++)
		                    	{
		                    		absPath += paths[i].toString()+"/";
		                    	}   	
		                    	ftp.doDeleteDir(absPath);
		                    	if(obj.getChildCount() ==0)
		                    	{
		                    		model.removeNodeFromParent(obj);
		                    	}
			                    
		                    }
		            	});
		            }
		           
		           
		           
		            popup.show(tree, x, y);
		        }
		        public void mousePressed(MouseEvent e) {
		            if (e.isPopupTrigger()) myPopupEvent(e);
		        }
		        public void mouseReleased(MouseEvent e) {
		            if (e.isPopupTrigger()) myPopupEvent(e);
		        }
		    };

		
		JScrollPane scrollPane4 = new JScrollPane();
		JTree tree_1 = new JTree();
		tree_1.addTreeSelectionListener(new TreeSelectionListener() {
			public void valueChanged(TreeSelectionEvent e) {
				
				JTree tree = (JTree)e.getSource();
				
				TreePath treepath = e.getPath();
				DefaultMutableTreeNode node =(DefaultMutableTreeNode)treepath.getLastPathComponent();
				

				String abspath= "/";
				Object[] paths = treepath.getPath();
				

				
				if(node.isLeaf()||tree.getSelectionPath()==null)
				{
					for(int i =1;i<paths.length-1;i++)
					{
						abspath += paths[i].toString()+"/";
					}
				}else
				{
					for(int i =1;i<paths.length;i++)
					{
						abspath += paths[i].toString()+"/";
					}
				}
				
				ftp.doCd(abspath);
				if(tree.getSelectionPath()==null)
				{
					DefaultTreeModel model = (DefaultTreeModel)tree_1.getModel();
	            	DefaultMutableTreeNode rootnode = (DefaultMutableTreeNode)model.getRoot();
	            	
	            	String dirName= abspath.trim();
	            	String[] splitDir = dirName.split("/");
	                boolean found = false;
	            	for(String temps:splitDir)
	            	{
	            		if(temps.equals(""))
	            		{
	            			continue;
	            		}
	            		found = false;
	            		for(int i =0;i<rootnode.getChildCount();i++)
	            		{
	            			DefaultMutableTreeNode node1 =(DefaultMutableTreeNode)rootnode.getChildAt(i);
	            			Object[] temppaths = node1.getPath();
	            			if(temppaths[temppaths.length-1].toString().equals(temps))
	            			{
	            				found = true;
	            				rootnode = node1;
	            				continue;
	            			}
	            		}
	            	}       
	            	tree_1.setSelectionPath(new TreePath(rootnode.getPath()));
				}
				
  
            
			}
		});
		
		tree_1.setFont(size12);
		tree_1.addMouseListener(ma);
		tree_1.addTreeExpansionListener(new TreeExpansionListener() {
			public void treeCollapsed(TreeExpansionEvent event) {
			}
			public void treeExpanded(TreeExpansionEvent event) {
				TreePath treePaths= event.getPath();
			
				DefaultMutableTreeNode parent= (DefaultMutableTreeNode)treePaths.getLastPathComponent();
				
				if(!parent.isLeaf() && parent.getChildCount() ==0)
				{
					String absPath = "/";
					
					Object[] paths = treePaths.getPath();
					for(int i=1;i<paths.length;i++)
					{
						absPath+= paths[i].toString()+"/";
					}
					Vector<String> dirFiles = ftp.doLs(absPath);
					
					for(String line : dirFiles)
					{
		
						String[] splitFile = line.split("\\s+");
						String fileName = line.substring(line.indexOf(splitFile[8]),line.length());
						if(line.startsWith("d"))
						{
							DefaultMutableTreeNode node = new DefaultMutableTreeNode(fileName) {
								
								public boolean isLeaf()
								{
									return false;
								}
							};
							DefaultTreeModel model = (DefaultTreeModel)tree_1.getModel();
							model.insertNodeInto(node, parent, 0);
						}else
						{
							DefaultMutableTreeNode node = new DefaultMutableTreeNode(fileName);
							DefaultTreeModel model = (DefaultTreeModel)tree_1.getModel();
							model.insertNodeInto(node, parent, 0);
						}		
					}		
				}
			}
		});
		scrollPane4.setViewportView(tree_1);
		tree_1.setDragEnabled(true);
		tree_1.setDropMode(DropMode.ON_OR_INSERT);
		
		Vector<String> ftpFiles = ftp.doLs();
	 	DefaultMutableTreeNode root = new DefaultMutableTreeNode(ftp.doPWD());
	 	
			
		for(String file:ftpFiles)
		{
			String[] splitFile = file.split("\\s+");
			String fileName = file.substring(file.indexOf(splitFile[8]),file.length());
			
			if(file.charAt(0)=='d')
			{
				DefaultMutableTreeNode node = new DefaultMutableTreeNode(fileName) {
				
					public boolean isLeaf()
					{
						return false;
					}
				};
				root.add(node);
			}else
			{
				DefaultMutableTreeNode node = new DefaultMutableTreeNode(fileName);
				root.add(node);
			}
		}
		DefaultTreeModel model = new DefaultTreeModel(root);	
		tree_1.setModel(model);
		tree_1.setTransferHandler(new MyTransferHandlerServer((DefaultTreeModel)tree_1.getModel(),tree_1));
		tree_1.setExpandsSelectedPaths(true);
		tree_1.setScrollsOnExpand(true);
		
		splitPane_3.setRightComponent(scrollPane4);
		
		JPanel panel = new JPanel();
		splitPane_3.setLeftComponent(panel);
		panel.setLayout(new FlowLayout(FlowLayout.CENTER, 5, 5));
		
		JButton btnNewButton = new JButton("QUIT");
		btnNewButton.setFont(size12);
		JButton btnNewButton_1 = new JButton("CD");
		btnNewButton_1.setFont(size12);
		JButton btnNewButton_2 = new JButton("PWD");
		btnNewButton_2.setFont(size12);
		JButton btnNewButton_3 = new JButton("ASCII");
		btnNewButton_3.setFont(size12);
		JButton btnNewButton_4 = new JButton("BINARY");
		btnNewButton_4.setFont(size12);
		JButton btnNewButton_5 = new JButton("LS");
		btnNewButton_5.setFont(size12);
		JButton btnNewButton_6 = new JButton("NLST");
		btnNewButton_6.setFont(size12);
		btnNewButton.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				ftp.doQuit();
				frame.dispose();
			}
		});
		
		btnNewButton_1.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				
				String dirName = JOptionPane.showInputDialog("Please enter Cd Dir Name ");
            	if(dirName == null)
            		return;
            	while(dirName.contains("\\"))
            	{
            		dirName = JOptionPane.showInputDialog("Please enter Cd Dir Name again(not allowed '\')");
            	}
       
            	DefaultTreeModel model = (DefaultTreeModel)tree_1.getModel();
            	DefaultMutableTreeNode rootnode = (DefaultMutableTreeNode)model.getRoot();
            	
            	dirName= dirName.trim();
            	String[] splitDir = dirName.split("/");
                boolean found = false;
            	for(String temps:splitDir)
            	{
            		if(temps.equals(""))
            		{
            			continue;
            		}
            		found = false;
            		for(int i =0;i<rootnode.getChildCount();i++)
            		{
            			DefaultMutableTreeNode node1 =(DefaultMutableTreeNode)rootnode.getChildAt(i);
            			Object[] paths = node1.getPath();
            			if(paths[paths.length-1].toString().equals(temps))
            			{
            				found = true;
            				rootnode = node1;
            				continue;
            			}
            		}
            	}

            	if(dirName.equals(".."))
            	{
            		DefaultMutableTreeNode selectedNode =  (DefaultMutableTreeNode)tree_1.getLastSelectedPathComponent(); 
            		if(selectedNode != null)
            		{
            			rootnode = (DefaultMutableTreeNode)model.getRoot();
            			if(selectedNode.isLeaf())
            			{
            				selectedNode =  (DefaultMutableTreeNode)selectedNode.getParent();
            			}
            			
            			selectedNode =  (DefaultMutableTreeNode)selectedNode.getParent();
            		}
            		
            		rootnode = selectedNode;
            		if(rootnode==null)
            		{
            			rootnode = (DefaultMutableTreeNode)model.getRoot();
            		}
            		found = true;
            	}	
            	
            	if(!found)
            	{
            		JOptionPane.showMessageDialog(frame, "Path Not found");
            		return ;
            	}
            	
            	tree_1.setSelectionPath(new TreePath(rootnode.getPath()));
            	TreePath path = tree_1.getSelectionPath();
            	if (path == null) return;
            	Rectangle bounds = tree_1.getPathBounds(path);

            	bounds.height = tree_1.getVisibleRect().height;
            	tree_1.scrollRectToVisible(bounds);
             	ftp.doCd(dirName);
			}
		});
		btnNewButton_2.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {

				JTextField mesg = new JTextField();
				mesg.setFont(size12);
				mesg.setEditable(false);
				mesg.setText(ftp.doPWD());
				JScrollPane temp = new JScrollPane(mesg);
				temp.setPreferredSize( new Dimension( 400, 70 ) );
				JOptionPane.showMessageDialog(frame, temp);
			}
		});
		btnNewButton_3.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				ftp.doAscii();
			}
		});
		btnNewButton_4.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				ftp.doBinary();
			}
		});
		btnNewButton_5.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				Vector<String> files = ftp.doLs();

				JTextArea mesg = new JTextArea();

				for(String file : files)
				{
					mesg.setText(mesg.getText()+file+"\n");
				}
				mesg.setEditable(false);
				mesg.setFont(size12);
				
				JScrollPane temp = new JScrollPane(mesg);
				temp.setPreferredSize( new Dimension( 500, 300 ) );

				JOptionPane.showMessageDialog(frame,temp);
			}
		});
		btnNewButton_6.addMouseListener(new MouseAdapter() {
			@Override
			public void mouseClicked(MouseEvent e) {
				String dirName = JOptionPane.showInputDialog("Please enter Dir Name ");
            	if(dirName == null)
            		return;
            	while(dirName.contains("\\"))
            	{
            		dirName = JOptionPane.showInputDialog("Please enter Dir Name again(not allowed '\')");
            	}
            	DefaultTreeModel model = (DefaultTreeModel)tree_1.getModel();
            	DefaultMutableTreeNode rootnode = (DefaultMutableTreeNode)model.getRoot();
            	
            	dirName= dirName.trim();
            	String[] splitDir = dirName.split("/");
                boolean found = false;
            	for(String temps:splitDir)
            	{
            		if(temps.equals(""))
            		{
//            			System.out.println("continue");
            			continue;
            		}
            		found = false;
            		for(int i =0;i<rootnode.getChildCount();i++)
            		{
            			DefaultMutableTreeNode node1 =(DefaultMutableTreeNode)rootnode.getChildAt(i);
            			Object[] paths = node1.getPath();
            			if(paths[paths.length-1].toString().equals(temps))
            			{
            				found = true;
            				rootnode = node1;
            				continue;
            			}
            		}
            	}
     
            	if(!dirName.equals("/")&&!dirName.equals("")&&(!found || (!dirName.startsWith("/"))))
            	{
            		JOptionPane.showMessageDialog(frame, "Path Not found");
            		return ;
            	}
            	
				Vector<String> files = ftp.doNLST(dirName);
				
				JTextArea mesg = new JTextArea();

				for(String file : files)
				{
					mesg.setText(mesg.getText()+file+"\n");
				}
				mesg.setEditable(false);
				mesg.setFont(size12);
				
				JScrollPane temp = new JScrollPane(mesg);
				temp.setPreferredSize( new Dimension( 500, 300 ) );

				JOptionPane.showMessageDialog(frame,temp);
			}
		});
		panel.add(btnNewButton_6);
		panel.add(btnNewButton_5);
		panel.add(btnNewButton_4);
		panel.add(btnNewButton_3);
		panel.add(btnNewButton_2);
		panel.add(btnNewButton_1);
		panel.add(btnNewButton);

	}
	public void stop()
	{
		JOptionPane.showMessageDialog(frame, "Time out,please relogin");
		frame.dispose();
	}
	class TimeoutListenor extends Thread
	{
		public Ftp ftp;
		public FtpGUI gui;
		public void run()
		{
			while(true)
			{	synchronized(ftp.message)
				{	

					if(ftp.message.lastElement().substring(0,3).equals("421"))
					{
						gui.stop();
						break;
					}
					if(ftp.message.lastElement().substring(0,3).equals("221"))
					{
						break;
					}
			
				}
			}
		}
	}
	
	class MessageListenor extends Thread
	{
		public Ftp ftp;
		public JTextArea area;
		public void run()
		{
			String lastMeg = "";
			while(true)
			{
				synchronized(ftp.message)
				{
					if(lastMeg.length()>=3 && (lastMeg.substring(0,3).equals("421")||lastMeg.substring(0,3).equals("221")))
						return;
					
					if(!lastMeg.equals(ftp.message.lastElement()))
					{
						lastMeg = ftp.message.lastElement();
						area.setText(area.getText()+lastMeg+"\n");
						DefaultCaret caret = (DefaultCaret) area.getCaret();
						caret.setUpdatePolicy(DefaultCaret.ALWAYS_UPDATE);
					}
				}
				
			}
		}
	}
	
	public void search(File[] files,DefaultMutableTreeNode root)
	{
		if(files==null)
			return;
		for(File file:files)
		{
			if(file.isDirectory())
			{
				DefaultMutableTreeNode dir = new DefaultMutableTreeNode(file.getName()){
				
					public boolean isLeaf()
					{
						return false;
					}
				};
				File[] tempfiles = file.listFiles();
				search(tempfiles,dir);
				root.add(dir);
			}else
			{
				root.add(new DefaultMutableTreeNode(file.getName()));
			}
			
		}
	}
	
	
	class MyTransferHandlerClient extends TransferHandler
	{
		public DefaultTreeModel model;
		public JTree tree;
		public String currentDir;
		public MyTransferHandlerClient(DefaultTreeModel model,String currentDir,JTree tree)
		{
			this.model = model;
			this.currentDir = currentDir;
			this.tree = tree;
		}
		 protected Transferable createTransferable(JComponent c) {
			    JTree tree = (JTree)c;
			    TreePath[] paths = tree.getSelectionPaths();
			    Transferable t = null;
			      DataFlavor DF = DataFlavor.stringFlavor; 
			      t = new Transferable() {

			        @Override
			        public DataFlavor[] getTransferDataFlavors() {
			          return new DataFlavor[]{DF};
			        }

			        @Override
			        public boolean isDataFlavorSupported(DataFlavor flavor) {
			          return flavor.equals(DF);
			        }

			        @Override
			        public Object getTransferData(DataFlavor flavor) throws UnsupportedFlavorException, IOException {
			          if (!flavor.equals(DF)) {
			            return null;
			          }
			          DefaultMutableTreeNode node = (DefaultMutableTreeNode)tree.getLastSelectedPathComponent();
			          if(!node.isLeaf())
			          {
			        	  return null;
			          }
			          
			          String selectedPath = "";
			          for (TreePath path : paths) {
			        	  
			        	  Object[] totalPaths =path.getPath();
			        	  for(int i =0;i<totalPaths.length-1;i++)
			        	  {
			        		 selectedPath += totalPaths[i].toString()+"\\";
			        	  }
			        	  selectedPath += totalPaths[totalPaths.length-1].toString();
			          }
			          if(selectedPath.contains(":\\"))
			          {
			        	  return selectedPath;
			          }
			          return currentDir+selectedPath;
			        }          
			      };
			    return t;        
			  }  

		
		
		public boolean canImport(TransferHandler.TransferSupport support) {
            if (!support.isDataFlavorSupported(DataFlavor.stringFlavor) ||
                !support.isDrop()) {
            return false;
            }
            JTree.DropLocation dropLocation = (JTree.DropLocation)support.getDropLocation();
    
            Object[] paths = dropLocation.getPath().getPath();
            
            String transferString = null;
			try {
				transferString = (String)(support.getTransferable().getTransferData(DataFlavor.stringFlavor));
				if(transferString == null)
					return false;
			}catch(InvalidDnDOperationException e)
			{
				return false;
			}catch (UnsupportedFlavorException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				return false;
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				return false;
			}
            return dropLocation.getPath() != null && !transferString.startsWith(this.currentDir);
		}
		public int getSourceActions(JComponent c) {
		     return TransferHandler.COPY;
		}
		
        public boolean importData(TransferHandler.TransferSupport support) {
             if (!canImport(support)) {
                return false;
             }

             JTree.DropLocation dropLocation = (JTree.DropLocation)support.getDropLocation();
             TreePath path = dropLocation.getPath();

             Transferable transferable = support.getTransferable();
         
             String transferData;
             try {
             transferData = (String)transferable.getTransferData(
                 DataFlavor.stringFlavor);
             } catch (IOException e) {
             return false;
             } catch (UnsupportedFlavorException e) {
             return false;
             }

             int childIndex = dropLocation.getChildIndex();
             if (childIndex == -1) {
             childIndex = model.getChildCount(path.getLastPathComponent());
             }
             String[] tempSplit = transferData.split("/");
             DefaultMutableTreeNode newNode = new DefaultMutableTreeNode(tempSplit[tempSplit.length-1]);
             DefaultMutableTreeNode parentNode = (DefaultMutableTreeNode)path.getLastPathComponent();
             if(parentNode.isLeaf())
             {
              	parentNode = (DefaultMutableTreeNode)path.getParentPath().getLastPathComponent();
             }
             
             boolean is_insert = true;
             for(int i=0;i<parentNode.getChildCount();i++)
             {
            	 DefaultMutableTreeNode child =(DefaultMutableTreeNode)parentNode.getChildAt(i);
            	 Object[] paths = child.getPath();
            	 if(child.isLeaf()&& paths[paths.length-1].toString().equals(tempSplit[tempSplit.length-1]) )
            	 {
            		 
            		 is_insert=false;
            	 }
             }

             String selectedPath = "";
             Object[] paths = parentNode.getPath();
             for(int i =0;i<paths.length;i++)
             {
            	 selectedPath +=paths[i].toString()+"\\";
             }

             if(selectedPath.contains(":\\"))
             {
            	 ftp.doGet(transferData,selectedPath+tempSplit[tempSplit.length-1]);
             }else
             {
            	 ftp.doGet(transferData,this.currentDir+selectedPath+tempSplit[tempSplit.length-1]);
             }
             if(is_insert)
             {
            	  model.insertNodeInto(newNode, parentNode, childIndex);
             }

           
             return true;
             }  
	}

	class MyTransferHandlerServer extends TransferHandler
	{
		public DefaultTreeModel model;
		public JTree tree;
		public MyTransferHandlerServer(DefaultTreeModel model,JTree tree)
		{
			this.model = model;
			this.tree = tree;
		}
		 protected Transferable createTransferable(JComponent c) {
			    JTree tree = (JTree)c;
			    TreePath[] paths = tree.getSelectionPaths();
			    Transferable t = null;
			      DataFlavor DF = DataFlavor.stringFlavor; 
			      t = new Transferable() {

			        @Override
			        public DataFlavor[] getTransferDataFlavors() {
			          return new DataFlavor[]{DF};
			        }

			        @Override
			        public boolean isDataFlavorSupported(DataFlavor flavor) {
			          return flavor.equals(DF);
			        }

			        @Override
			        public Object getTransferData(DataFlavor flavor) throws UnsupportedFlavorException, IOException {
			          if (!flavor.equals(DF)) {
			            return null;
			          }
			          DefaultMutableTreeNode node = (DefaultMutableTreeNode)tree.getLastSelectedPathComponent();
			          if(!node.isLeaf())
			          {
			        	  return null;
			          }
			          
			          String absPath = "";
			          for (TreePath path : paths) {
			        	  Object[] totalPaths =path.getPath();
			        	  for(int i =1;i<totalPaths.length;i++)
			        	  {
			        		absPath +="/"+totalPaths[i].toString();
			        	  }
			          }
			          return absPath;
			        }          
			      };
			    return t;        
			  }  

		
		
		public boolean canImport(TransferHandler.TransferSupport support) {
            if (!support.isDataFlavorSupported(DataFlavor.stringFlavor) ||
                !support.isDrop()){
            return false;
            }
            JTree.DropLocation dropLocation = (JTree.DropLocation)support.getDropLocation();
            Object[] paths = dropLocation.getPath().getPath();
            String transferString = null;
			try {
				transferString = (String)(support.getTransferable().getTransferData(DataFlavor.stringFlavor));
				if(transferString == null)
					return false;
			}catch(InvalidDnDOperationException e)
			{
				return false;
			}catch (UnsupportedFlavorException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				return false;
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
				return false;
			}
			
            return dropLocation.getPath() != null && !transferString.startsWith(this.tree.getModel().getRoot().toString());
		}
		public int getSourceActions(JComponent c) {
		     return TransferHandler.COPY;
		}
		
        public boolean importData(TransferHandler.TransferSupport support) {
             if (!canImport(support)) {
                return false;
             }

             JTree.DropLocation dropLocation = (JTree.DropLocation)support.getDropLocation();
             TreePath path = dropLocation.getPath();

             Transferable transferable = support.getTransferable();
         
             String transferData;
             try {
             transferData = (String)transferable.getTransferData(
                 DataFlavor.stringFlavor);
             } catch (IOException e) {
             return false;
             } catch (UnsupportedFlavorException e) {
             return false;
             }

             int childIndex = dropLocation.getChildIndex();
             if (childIndex == -1) {
             childIndex = model.getChildCount(path.getLastPathComponent());
             }
             transferData.replace("\\", "\\\\");
             String[] tempSplit = transferData.split("\\\\");
             
             DefaultMutableTreeNode newNode = new DefaultMutableTreeNode(tempSplit[tempSplit.length-1]);
             DefaultMutableTreeNode parentNode = (DefaultMutableTreeNode)path.getLastPathComponent();
             if(parentNode.isLeaf())
             {
              	parentNode = (DefaultMutableTreeNode)path.getParentPath().getLastPathComponent();
             }

             boolean is_insert = true;
             
   
             for(int i=0;i<parentNode.getChildCount();i++)
             {
            	 DefaultMutableTreeNode child =(DefaultMutableTreeNode)parentNode.getChildAt(i);
            	 Object[] paths = child.getPath();
            	 if(child.isLeaf()&& paths[paths.length-1].toString().equals(tempSplit[tempSplit.length-1]) )
            	 {
            		 is_insert=false;
            	 }
             }

             
             String selectedPath = "/";
             Object[] paths = parentNode.getPath();
             for(int i =1;i<paths.length;i++)
             {
            	 selectedPath +=paths[i].toString()+"/";
             }

             ftp.doPut(transferData,selectedPath+tempSplit[tempSplit.length-1]);
  
             if(is_insert)
             {
            	  model.insertNodeInto(newNode, parentNode, childIndex);
             }

             return true;
             }  
	}
}



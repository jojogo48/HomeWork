import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.layout.*;
import javafx.scene.web.HTMLEditor;
import javafx.scene.web.WebEngine;
import javafx.scene.web.WebView;


import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.*;
import java.util.Base64;

public class MailController {

    @FXML
    private SplitPane first_splitpane;

    @FXML
    private SplitPane second_splitpane;

    @FXML
    private ListView<Label> mailBox;

    @FXML
    private TextField searchField;
    @FXML
    private Button search;
    
    @FXML
    private GridPane main_gridpane;

    @FXML
    private Button Read_Item;

    @FXML
    private Button Delete_Item;

    @FXML
    private ToolBar tool_bar;
    @FXML
    private WebView mail_content;

    @FXML
    private Tab smtp_tab;

    @FXML
    private TabPane tab_pane;

    @FXML
    private Tab pop_tab;

    @FXML
    private Button refresh;

    @FXML
    private HTMLEditor editor;

    @FXML
    private Label label_recipient;

    @FXML
    private TextField recipient;

    @FXML
    private Label label_subject;

    @FXML
    private TextField subject;

    @FXML
    private Button Send;
    @FXML
    private Button forward;

    @FXML
    private GridPane reci_sub_gridpane;

    @FXML
    private Button clear;
    @FXML
    private Button reply;

    private  SMTP smtp = null;
    private  POP pop = null;
    private Presenter pres = null;
    private GmailParser forward_mail = null;
    public void setSmtp(SMTP smtp) {
        this.smtp = smtp;
    }

    public void setPop(POP pop) {
        this.pop = pop;
    }
    public void setPresenter(Presenter pres) {
        this.pres = pres;
    }

    private String relpace_tag(String str) {
        return str.replace("<","&lt;").replace(">","&gt;");
    }
    private boolean isReply = false;
    private String mesgId = null;
    public void reply() throws IOException {
        int number = Integer.parseInt((mailBox.getSelectionModel().getSelectedItem().getText().split("[\\s]+")[0]));
        Vector<String> lines = pop.retrieve(number);
        GmailParser par = new GmailParser(lines);
        par.parse();

        recipient.setText(par.attributes.get("Return-Path").replace("<", "").replace(">", ""));
        subject.setText("Re: "+par.attributes.get("Subject"));

        mesgId = par.attributes.get("Message-ID");
        isReply = true;
        tab_pane.getSelectionModel().select(1);
    }

    private Vector<String> split_const_str(String str, int num) {
        Vector<String> split = new Vector<>();

        for (int i = 0; i < str.length(); i += num) {
            if (i+num > str.length()) {
                split.add(str.substring(i,str.length()));
            } else {
                split.add(str.substring(i,i+num));
            }
        }

        return split;
    }
    public void send() throws Exception {
        String[] mails = recipient.getText().split(",");
        Vector<String> vectormails = new Vector<String>(Arrays.asList(mails));
        Vector<String> vectorContent = new Vector<String>(Arrays.asList(editor.getHtmlText().split("(?=<br>)")));
        
        if(!isReply)
        {
        	smtp.send(subject.getText(),vectormails,vectorContent);
        }else {
        	smtp.reply(subject.getText(),vectormails, vectorContent, mesgId);
        }
        isReply = false;
        mesgId = null;

        
        
        subject.setText("");
        recipient.setText("");
        editor.setHtmlText("");
    }

    public void clear() {
        editor.setHtmlText("");
        editor.setDisable(false);
        subject.setText("");
        recipient.setText("");
    }

    public void readmail() throws IOException {

        int number = Integer.parseInt((mailBox.getSelectionModel().getSelectedItem().getText().split("[\\s]+")[0]));
        Vector<String> lines = pop.retrieve(number);

        for(String line:lines)
            System.out.println(line);

        String html = "<br>";

        GmailParser par = new GmailParser(lines);
        par.parse();
        html += "<div class=\"page-wrapper\">";
        html += "<div class=\"top-area\">";
        html +="<table><tbody>";

        html += "<tr><th>郵件ID：</th><td>" + relpace_tag(par.attributes.get("Message-ID") )+ "</td></tr>";
        html += "<tr><th>寄件者：</th><td>" + relpace_tag(par.attributes.get("From")) + "</td></tr>";
        if(par.attributes.get("To") != null){
            html += "<tr><th>收件者：</th><td>" + relpace_tag(par.attributes.get("To")) + "</td></tr>";
        }
        if(par.attributes.get("Reply-To")!=null){
            html += "<tr><th>Reply-To：</th><td>" + relpace_tag(par.attributes.get("Reply-To")) + "</td></tr>";
        }
        if(par.attributes.get("In-Reply-To")!=null){
            html += "<tr><th>In-Reply-To：</th><td>" + relpace_tag(par.attributes.get("In-Reply-To")) + "</td></tr>";
        }
        if(par.attributes.get("References")!=null){
            html += "<tr><th>References：</th><td>" + relpace_tag(par.attributes.get("References")) + "</td></tr>";
        }
        html += "<tr><th>主旨：</th><td>" + relpace_tag(par.attributes.get("Subject")) + "</td></tr>";
        html += "</tbody></table><br>";
        html += "<style type=\"text/css\" nonce>";
        html += "body{font-family:'Arial','Helvetica',sans-serif!important;font-size:14px;margin:0}.page-wrapper{display:table;height:auto;width:100%}.page_title{font-size:20px;font-weight:normal;padding:20px 11% 0px 11%}.message_id{color:#2e7d32}.top-area{background-color:#fff;display:table-row}table{border-collapse:collapse;margin:0px auto;width:80%}td,th{border-bottom:solid thin #e0e0e0;border-top:solid thin #e0e0e0;font-weight:normal}td{border-right:solid thin #e0e0e0;padding:8px}th{border-left:solid thin #e0e0e0;padding:12px 20px;text-align:left}.download-buttons,.learn-more-link{color:#15c;cursor:pointer;padding-left:5px;text-decoration:none}.authresult{text-transform:uppercase}.download-buttons{display:inline-block;font-size:14px;padding:20px}.more-actions{display:table;padding-bottom:25px;width:100%}.download-links{display:table-cell;width:39%}.header-body-button{display:table-cell;text-align:right;width:39%}#butterbar-wrap{display:inline-block}#butterbar-container{left:auto;position:absolute;text-align:center;top:18px;width:100%}.clipboard-icon{background-image:url(//ssl.gstatic.com/images/icons/material/system/1x/content_paste_black_24dp.png);background-position:center;background-repeat:no-repeat;background-size:15px;padding:8px 20px 8px 8px}.copy-header-body-button.jfk-button.jfk-button-action{display:inline-block;padding:4px 6px;text-decoration:none}#copy-header-body-button{margin:10px}.spacing{display:table-cell;width:11%}.bottom-area{background-color:#eeeeee;display:table-row;height:100%}.raw_message{border-top:solid thin #bdbdbd;display:table-cell;height:100%}.raw_message_text{background-color:#fff;border:solid thin #e0e0e0;border-radius:5px;color:#616161;height:100%;margin:25px 10%;padding:40px 30px;white-space:pre-wrap;word-break:break-word;word-wrap:break-word}.truncate_message{color:#d32f2f;padding:10px;text-align:center}.goog-inline-block{position:relative;display:-moz-inline-box;display:inline-block}* html .goog-inline-block{display:inline}*:first-child+html .goog-inline-block{display:inline}.jfk-button{-webkit-border-radius:2px;-moz-border-radius:2px;border-radius:2px;cursor:default;font-size:11px;font-weight:bold;text-align:center;white-space:nowrap;margin-right:16px;height:27px;line-height:27px;min-width:54px;outline:0px;padding:0 8px}.jfk-button-hover{-webkit-box-shadow:0 1px 1px rgba(0,0,0,.1);-moz-box-shadow:0 1px 1px rgba(0,0,0,.1);box-shadow:0 1px 1px rgba(0,0,0,.1)}.jfk-button-selected{-webkit-box-shadow:inset 0px 1px 2px rgba(0,0,0,0.1);-moz-box-shadow:inset 0px 1px 2px rgba(0,0,0,0.1);box-shadow:inset 0px 1px 2px rgba(0,0,0,0.1)}.jfk-button .jfk-button-img{margin-top:-3px;vertical-align:middle}.jfk-button-label{margin-left:5px}.jfk-button-narrow{min-width:34px;padding:0}.jfk-button-collapse-left,.jfk-button-collapse-right{z-index:1}.jfk-button-collapse-left.jfk-button-disabled{z-index:0}.jfk-button-checked.jfk-button-collapse-left,.jfk-button-checked.jfk-button-collapse-right{z-index:2}.jfk-button-collapse-left:focus,.jfk-button-collapse-right:focus,.jfk-button-hover.jfk-button-collapse-left,.jfk-button-hover.jfk-button-collapse-right{z-index:3}.jfk-button-collapse-left{margin-left:-1px;-moz-border-radius-bottomleft:0;-moz-border-radius-topleft:0;-webkit-border-bottom-left-radius:0;-webkit-border-top-left-radius:0;border-bottom-left-radius:0;border-top-left-radius:0}.jfk-button-collapse-right{margin-right:0px;-moz-border-radius-topright:0;-moz-border-radius-bottomright:0;-webkit-border-top-right-radius:0;-webkit-border-bottom-right-radius:0;border-top-right-radius:0;border-bottom-right-radius:0}.jfk-button.jfk-button-disabled:active{-webkit-box-shadow:none;-moz-box-shadow:none;box-shadow:none}.jfk-button-action{-webkit-box-shadow:none;-moz-box-shadow:none;box-shadow:none;background-color:#4d90fe;background-image:-webkit-linear-gradient(top,#4d90fe,#4787ed);background-image:-moz-linear-gradient(top,#4d90fe,#4787ed);background-image:-ms-linear-gradient(top,#4d90fe,#4787ed);background-image:-o-linear-gradient(top,#4d90fe,#4787ed);background-image:linear-gradient(top,#4d90fe,#4787ed);border:1px solid #3079ed;color:#fff}.jfk-button-action.jfk-button-hover{-webkit-box-shadow:none;-moz-box-shadow:none;box-shadow:none;background-color:#357ae8;background-image:-webkit-linear-gradient(top,#4d90fe,#357ae8);background-image:-moz-linear-gradient(top,#4d90fe,#357ae8);background-image:-ms-linear-gradient(top,#4d90fe,#357ae8);background-image:-o-linear-gradient(top,#4d90fe,#357ae8);background-image:linear-gradient(top,#4d90fe,#357ae8);border:1px solid #2f5bb7;border-bottom-color:#2f5bb7}.jfk-button-action:focus{-webkit-box-shadow:inset 0 0 0 1px #fff;-moz-box-shadow:inset 0 0 0 1px #fff;box-shadow:inset 0 0 0 1px #fff;border:1px solid #fff;border:rgba(0,0,0,0) solid 1px;outline:1px solid #4d90fe;outline:rgba(0,0,0,0) 0}.jfk-button-action.jfk-button-clear-outline{-webkit-box-shadow:none;-moz-box-shadow:none;box-shadow:none;outline:none}.jfk-button-action:active{-webkit-box-shadow:inset 0 1px 2px rgba(0,0,0,0.3);-moz-box-shadow:inset 0 1px 2px rgba(0,0,0,0.3);box-shadow:inset 0 1px 2px rgba(0,0,0,0.3);background:#357ae8;border:1px solid #2f5bb7;border-top:1px solid #2f5bb7}.jfk-button-action.jfk-button-disabled{background:#4d90fe;filter:alpha(opacity=50);opacity:0.5}.jfk-butterBar{-webkit-border-radius:2px;-moz-border-radius:2px;border-radius:2px;-webkit-box-shadow:0px 2px 4px rgba(0,0,0,0.2);-moz-box-shadow:0px 2px 4px rgba(0,0,0,0.2);box-shadow:0px 2px 4px rgba(0,0,0,0.2);-webkit-transition:all 0s linear 1s,opacity 1s;-moz-transition:all 0s linear 1s,opacity 1s;-o-transition:all 0s linear 1s,opacity 1s;transition:all 0s linear 1s,opacity 1s;border-style:solid;border-width:0;font-size:11px;height:0;opacity:0;visibility:hidden;overflow:hidden;padding:0;text-align:center}.jfk-butterBar-info{background-color:#f9edbe;border-color:#f0c36d;color:#333}.jfk-butterBar-error{background-color:#484848;border-color:#202020;color:#fff}.jfk-butterBar-promo{background-color:#d6e9f8;border-color:#4d90f0;color:#333}.jfk-butterBar-warning{background-color:#dd4b39;border-color:#602019;color:#fff}.jfk-butterBar-shown{-webkit-transition:opacity 0.218s;-moz-transition:opacity 0.218s;-o-transition:opacity 0.218s;transition:opacity 0.218s;border-width:1px;min-height:14px;height:auto;opacity:1;visibility:visible;padding:6px 16px}.jfk-butterBar-mini.jfk-butterBar-shown{padding:2px 16px}";
        html += "</style>";
        html += "</div>";



        html += "<div class = \"bottom-area\">";
        html += "<div class = \"raw_message\">";
        html += "<pre class=\"raw_message_text\" style=\"font-size:18px\">";
        for (Content c : par.contents) {

            for (Map.Entry<String,String> entry : c.attributes.entrySet())
                html +=entry.getKey() + ": " + entry.getValue()+"<br>";
            for (int i = 0; i < c.cont.size(); i++) {
                html +=relpace_tag( c.cont.get(i));
            }


        }
        html += "</pre>";
        html += "</div>";
        html += "</div>";
        html += "</div>";

        System.out.println(html);


        WebEngine webEngine = mail_content.getEngine();
        webEngine.loadContent(html);
    }

    public void delete() throws IOException {
        int number =  Integer.parseInt((mailBox.getSelectionModel().getSelectedItem().getText().split("[\\s]+")[0]));
        pop.delete(number);
    }

    public void refresh() throws Exception {
        pop.update();
        smtp.update();
        mailBox.getItems().clear();
        Vector<String> lists = null;
        try {
            lists = pop.list();
        } catch (IOException e) {
            e.printStackTrace();
        }
        for(String list:lists)
        {
            Label label = new Label(list+"bytes");
            label.setStyle("-fx-font: 18 arial;");
            mailBox.getItems().add(label);
        }
    }
    
    public void Search()
    {
    	try {
    		int number = Integer.parseInt((searchField.getText()));
    		Vector<String> lists = null;
            try {
                lists = pop.list();
            } catch (Exception e) {
                e.printStackTrace();
            }
            int index = -1;
            for(int i =0;i<lists.size();i++)
            {
            	if(lists.get(i).startsWith(Integer.toString(number)))
            	{
            		index = i;
            		break;
            	}
            }
            if(index == -1)
            {
        		Alert alert = new Alert(AlertType.INFORMATION);
        		alert.setContentText("此郵件不存在");
        		alert.showAndWait();
        		return;
            }
            
            mailBox.getSelectionModel().select(index);
            mailBox.getFocusModel().focus(index);
            mailBox.scrollTo(index);
            this.readmail();
    	}catch(Exception e) {
    		
    	}
    	
    }
    

    public void forward() throws IOException {
        int number = Integer.parseInt((mailBox.getSelectionModel().getSelectedItem().getText().split("[\\s]+")[0]));
        Vector<String> lines = pop.retrieve(number);

        GmailParser par = new GmailParser(lines);

        par.parse();
        editor.setHtmlText("---------- Forwarded message ---------" + "<br>");
        editor.setHtmlText(editor.getHtmlText() + "From:" + relpace_tag(par.attributes.get("From")) + "<br>");
        if(par.attributes.get("Date") != null)
            editor.setHtmlText(editor.getHtmlText() + "Date:" + par.attributes.get("Date") + "<br>");
        editor.setHtmlText(editor.getHtmlText() + "Subject:" + relpace_tag(par.attributes.get("Subject")) + "<br>");
        if(par.attributes.get("To") != null){
            editor.setHtmlText(editor.getHtmlText() + "<tr><th>To：</th><td>" + relpace_tag(par.attributes.get("To")) + "</td></tr>");
        }
        if(par.attributes.get("Reply-To")!=null){
            editor.setHtmlText(editor.getHtmlText() + "<tr><th>Reply-To：</th><td>" + relpace_tag(par.attributes.get("Reply-To")) + "</td></tr>");
        }
        if(par.attributes.get("In-Reply-To")!=null){
            editor.setHtmlText(editor.getHtmlText() + "<tr><th>In-Reply-To：</th><td>" + relpace_tag(par.attributes.get("In-Reply-To")) + "</td></tr>");
        }
        if(par.attributes.get("References")!=null){
            editor.setHtmlText(editor.getHtmlText() + "<tr><th>References：</th><td>" + relpace_tag(par.attributes.get("References")) + "</td></tr>");
        }
        editor.setHtmlText(editor.getHtmlText()+"<br>");
        for (Content c : par.contents) {
            for (Map.Entry<String, String> entry : c.attributes.entrySet()) {
                System.out.println("Key = " + entry.getKey() +
                        ", Value = " + entry.getValue());
                editor.setHtmlText(editor.getHtmlText()+entry.getKey()+": "+relpace_tag(entry.getValue())+"<br>");
            }
            for (int i = 0; i < c.cont.size(); i++) {
                System.out.println( c.cont.get(i));
                editor.setHtmlText(editor.getHtmlText()+relpace_tag(c.cont.get(i))+"<br>");
            }
        }
        editor.setHtmlText(editor.getHtmlText()+"<br>");
        System.out.println("Content:");

        subject.setText("Fwd: "+par.attributes.get("Subject"));



        tab_pane.getSelectionModel().select(1);
    }


    @FXML
    private void initialize() {
        first_splitpane.setDividerPositions(0.2);
        Delete_Item.setStyle("-fx-font: 18 arial;");
        Read_Item.setStyle("-fx-font: 18 arial;");
        mail_content.setStyle("-fx-font: 18 arial;");
        tab_pane.setStyle("-fx-font: 18 arial;");
        subject.setStyle("-fx-font: 18 arial;");
        label_subject.setStyle("-fx-font: 18 arial;");
        label_recipient.setStyle("-fx-font: 18 arial;");
        recipient.setStyle("-fx-font: 18 arial;");
        Send.setStyle("-fx-font: 18 arial;");
        editor.setStyle("-fx-font: 12 arial;");


       /* ColumnConstraints col1 = new ColumnConstraints();
        col1.setPrefWidth(label_recipient.getPrefWidth());
        reci_sub_gridpane.getColumnConstraints().clear();
        reci_sub_gridpane.getColumnConstraints().add(col1);*/

        Platform.runLater(() -> {
            Vector<String> lists = null;
            try {
                lists = pop.list();
            } catch (IOException e) {
                e.printStackTrace();
            }
            for(String list:lists)
            {
                Label label = new Label(list+"bytes");
                label.setStyle("-fx-font: 18 arial;");
                mailBox.getItems().add(label);
            }

            pres.primaryStage.widthProperty().addListener((obs, oldVal, newVal) -> {

                mailBox.setPrefWidth(newVal.doubleValue());
                tool_bar.setPrefWidth(newVal.doubleValue());
                first_splitpane.setDividerPositions(0.2);
                second_splitpane.setDividerPositions(0.2);
                recipient.setPrefWidth(newVal.doubleValue());
                /*reci_sub_gridpane.setPrefWidth(newVal.doubleValue());

                reci_sub_gridpane.getColumnConstraints().clear();
                reci_sub_gridpane.getColumnConstraints().addAll(col1,col2);*/


                recipient.setPrefWidth(newVal.doubleValue());
                subject.setPrefWidth(newVal.doubleValue());
            });

            pres.primaryStage.heightProperty().addListener((obs, oldVal, newVal) -> {
                mailBox.setPrefHeight(newVal.doubleValue());
                tool_bar.setPrefHeight(newVal.doubleValue());
                first_splitpane.setDividerPositions(0.2);
                second_splitpane.setDividerPositions(0.2);
            });
        });
    }


}

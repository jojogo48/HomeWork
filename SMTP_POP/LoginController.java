import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.GridPane;
import javafx.stage.Stage;

import java.net.ConnectException;
import java.net.UnknownHostException;


public class LoginController {

    @FXML
    private Label label_port;

    @FXML
    private GridPane gridPane_1_3;

    @FXML
    private GridPane gridPane_1_2;

    @FXML
    private Label label_server;

    @FXML
    private TextField pop_port;

    @FXML
    private Button btn_login;

    @FXML
    private Label label_smtp;

    @FXML
    private Label label_pass;

    @FXML
    private PasswordField password;

    @FXML
    private TextField pop_server;

    @FXML
    private TextField smtp_port;

    @FXML
    private TextField smtp_server;

    @FXML
    private Label label_account;

    @FXML
    private Label label_welcome;

    @FXML
    private GridPane gridPane_1;

    @FXML
    private TextField account;

    private SMTP smtp;
    private POP pop;

    public void login()
    {
        smtp_server.setStyle("-fx-border-color: black");
        smtp_port.setStyle("-fx-border-color: black");
        pop_server.setStyle("-fx-border-color: black");
        pop_port.setStyle("-fx-border-color: black");
        account.setStyle("-fx-border-color: black");

        boolean is_return = false;
        if(smtp_server.getText().equals(""))
        {
            smtp_server.setStyle("-fx-border-color: red");
            is_return = true;
        }
        if(smtp_port.getText().equals(""))
        {
            smtp_port.setStyle("-fx-border-color: red");
            is_return = true;
        }
        if(pop_server.getText().equals(""))
        {
            pop_server.setStyle("-fx-border-color: red");
            is_return = true;
        }
        if(pop_port.getText().equals(""))
        {
            pop_port.setStyle("-fx-border-color: red");
            is_return = true;
        }
        if(account.getText().equals(""))
        {
            account.setStyle("-fx-border-color: red");
            is_return = true;
        }
        if(password.getText() == null)
        {
            password.setText("");
        }

        if(is_return)
        {
            return;
        }

        smtp = new SMTP();
        smtp.SMTP_PORT = Integer.parseInt(smtp_port.getText());
        smtp.smtp_server = smtp_server.getText();

        pop = new POP();
        pop.pop_server = pop_server.getText();
        pop.POP_PORT = Integer.parseInt(pop_port.getText());


        try {
            smtp.sendAuth(account.getText(), password.getText());
        } catch (UnknownHostException e) {
            smtp_server.setStyle("-fx-border-color: red");
            return;
        } catch (ConnectException e) {
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setTitle("Error");
            alert.setContentText("Connection Exception");
            alert.show();
            e.printStackTrace();
            return;
        } catch (Exception e) {
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setTitle("Error");
            alert.setContentText(e.getMessage());
            alert.show();
            e.printStackTrace();
            return;
        }


        try {
            pop.authorization(account.getText(), password.getText());
        }catch (UnknownHostException e) {
            pop_server.setStyle("-fx-border-color: red");
            return;
        } catch (ConnectException e) {
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setTitle("Error");
            alert.setContentText("Connection Exception");
            alert.show();
            e.printStackTrace();
            return;
        } catch (Exception e) {
            Alert alert = new Alert(Alert.AlertType.INFORMATION);
            alert.setTitle("Error");
            alert.setContentText(e.getMessage());
            alert.show();
            e.printStackTrace();
            return;
        }



        try {
            LoginGUI.primaryStage.close();

            Presenter presenter = new Presenter();
            presenter.primaryStage = LoginGUI.primaryStage;
            presenter.smtp = smtp;
            presenter.pop = pop;
            presenter.self = presenter;
            presenter.showMain();
        } catch (Exception e) {
            return;
        }

    }
}

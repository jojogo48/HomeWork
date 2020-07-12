import javafx.fxml.FXMLLoader;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.SplitPane;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;

import java.io.IOException;

public class Presenter {
    public SMTP smtp = null;
    public POP pop = null;
    public Stage primaryStage = null;
    public Presenter self = null;
    public void showMain() throws IOException {
        FXMLLoader fxmlLoader = new FXMLLoader(getClass().getResource("mail.fxml"));
        Parent root = (Parent) fxmlLoader.load();
        MailController controller = fxmlLoader.<MailController>getController();
        controller.setSmtp(smtp);
        controller.setPop(pop);
        controller.setPresenter(self);

        Scene scene = new Scene(root);
        primaryStage.setScene(scene);
        primaryStage.show();
    }

}

package li3;

import engine.TCDCommunity;

public class MVC {

    public static  void main(String[] args){
        View view = new View();
        TCDCommunity model = new TCDCommunity();
        Controller controller = new Controller(model, view);

        view.setVisible(true);
        view.setLocationRelativeTo(null);


    }


}

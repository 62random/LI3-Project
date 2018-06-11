package engine

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.HashMap;

public class MyUserHandler extends DefaultHandler {

    private List<MyUser> users = null;
    private Map<Long, Integer> users_rep = null;
    private MyUser u = null;

    public List<MyUser> getUsers() {
        return users;
    }

    public Map<Long, Integer> getUsers_rep() {
        return users_rep;
    }

    @Override
    public void startElement(String uri, String localName, String qName, Attributes attributes) throws SAXException {

        if (users == null)
            users = new LinkedList<MyUser>();

        if (users_rep == null)
            users_rep = new HashMap<Long, Integer>();

        int n;

        if (qName.equalsIgnoreCase("row")) {
            u = new MyUser();

            String str = attributes.getValue("Id");
            if(str != null)
                u.setId(Long.parseLong(str));

            str = attributes.getValue("DisplayName");
            if(str != null)
                u.setUsername(str);

            str = attributes.getValue("Reputation");
            if(str != null) {
                n = Integer.parseInt(str);
                u.setRep(n);
                users_rep.put(u.getId(), n);
            }

            str = attributes.getValue("AboutMe");
            if(str != null)
                u.setBio(str);

        }

    }

    @Override
    public void endElement(String uri, String localName, String qName) throws SAXException {
        if (qName.equalsIgnoreCase("row")) {
            users.add(u);
        }
    }



    @Override
    public void characters(char ch[], int start, int length) throws SAXException {
    }



}

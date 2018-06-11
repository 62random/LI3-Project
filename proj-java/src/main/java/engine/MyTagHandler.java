package engine

import org.xml.sax.Attributes;
import org.xml.sax.SAXException;
import org.xml.sax.helpers.DefaultHandler;

import java.util.HashMap;




public class MyTagHandler extends DefaultHandler {

    private HashMap<String, Long> tags = null;

    public HashMap<String, Long> getTags() {
        return tags;
    }

    @Override
    public void startElement(String uri, String localName, String qName, Attributes attributes) throws SAXException {

        if (qName.equalsIgnoreCase("row")) {

            String str1 = attributes.getValue("TagName");
            String str2 = attributes.getValue("Id");

            if (tags == null)
                tags = new HashMap<String, Long>();

            if(str1 != null && str2 != null)
                tags.put(str1, Long.parseLong(str2));
        }

    }

    @Override
    public void endElement(String uri, String localName, String qName) throws SAXException {
    }

    @Override
    public void characters(char ch[], int start, int length) throws SAXException {
    }
}

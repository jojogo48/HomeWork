import java.util.HashMap;
import java.util.Map;
import java.util.Vector;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class GmailParser {


    private Vector<String> lines ;
    public Map<String, String> attributes = new HashMap<String, String>();
    public Vector<Content> contents = new Vector<>();
    public GmailParser(final Vector<String> lines) {
        this.lines = lines;
    }
    private int l = 0;
    public void parse() {
        this.parseHeader();
    }

    private void parseHeader() {
        String last_token = null;
        for (l = 0; l < lines.size(); l++) {
            if (lines.get(l).matches("^(\\s+).+")) {
                String temps = attributes.get(last_token);
                attributes.put(last_token,temps+ lines.get(l));
                continue;
            }
            String [] tokens = lines.get(l).split(":",2);
            if (!tokens[0].isEmpty()) {
                if (tokens[0].trim().equals("Content-Type")) {
                    parseCotent();
                    return;
                } else {
                    attributes.put(tokens[0].trim(), tokens[1].isEmpty()? null : tokens[1].trim());
                    last_token = tokens[0].trim();
                }
            }
        }
    }

    private void parseCotent() {
        Content tempt = new Content();
        String last_token = null;
        String [] tokens = lines.get(l).split(":",2);
        if (!tokens[0].isEmpty()) {
            tempt.attributes.put(tokens[0].trim(), tokens[1].trim());
            last_token = tokens[0].trim();
        }
        l++;
        while(lines.get(l).matches("^(\\s+).+")) {
            String temps = tempt.attributes.get(last_token);
            tempt.attributes.put(last_token, temps + lines.get(l++));
        }
        contents.add(tempt);
        if (tempt.attributes.get(last_token).contains("text/plain")||tempt.attributes.get(last_token).contains("text/html")) {
            parseTextPlain(false,null);
            return ;
        } else if (tempt.attributes.get(last_token).contains("multipart/alternative")) {
            parseMultipartAlter();
            return;
        } else {
            while(l<lines.size()) {
                tempt.cont.add(lines.get(l++));
            }
        }
    }


    private void parseMultipartAlter() {
        Content tempt = this.contents.lastElement();
        String bounary = getBounary(tempt);

        while(!lines.get(l).contains(bounary)) {
            l++;
        }

        do {
            l++;
            Content t = new Content();
            this.contents.add(t);
            parseContentType();
            parseTextPlain(true,bounary);
        }while(!lines.get(l).contains(bounary+"--"));
    }

    private void parseContentType() {
        String last_token = null;
        Content tempt = this.contents.lastElement();
        String [] tokens = lines.get(l).split(":",2);
        if (!tokens[0].isEmpty()) {
            tempt.attributes.put(tokens[0].trim(), tokens[1].trim());
            last_token = tokens[0].trim();
        }
        l++;
        while(lines.get(l).matches("^(\\s+).+")) {
            String temps = tempt.attributes.get(last_token);
            tempt.attributes.put(last_token, temps + lines.get(l++));
        }

    }
    private String getBounary(Content t) {
        String ct= t.attributes.get("Content-Type");

        Pattern pattern = Pattern.compile("boundary=\"[^\"]+\"");
        Matcher matcher = pattern.matcher(ct);

        if(matcher.find()) {
            Pattern pattern2 = Pattern.compile("\"[^\"]+\"");
            Matcher matcher2 = pattern2.matcher(matcher.group(0));
            if(matcher2.find())
                return matcher2.group(0).replace("\"", "");
        }
        return null;
    }

    private void parseTextPlain(boolean hasBounary,String bounary) {
        String last_token = null;
        Content tempt = this.contents.lastElement();
        if (!lines.get(l).trim().equals("")) {
            // trnansfer encodeing
            String[] tokens = lines.get(l).split(":", 2);
            if (!tokens[0].isEmpty()) {
                tempt.attributes.put(tokens[0].trim(), tokens[1].trim());
                last_token = tokens[0].trim();
            }
            l++;
            while (lines.get(l).matches("^(\\s+).+")) {
                String temps = tempt.attributes.get(last_token);
                tempt.attributes.put(last_token, temps + lines.get(l++));
            }
        }
        // content
        l++; //blank line
        while (l < lines.size()) {
            if(hasBounary)
            {
                if(lines.get(l).contains(bounary)) {
                    return;
                }else {
                    tempt.cont.add(lines.get(l++));
                }
            }else {
                tempt.cont.add(lines.get(l++));
            }
        }
    }

}

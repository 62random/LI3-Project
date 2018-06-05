package engine;

import common.Pair;
import li3.TADCommunity;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import javax.xml.parsers.SAXParser;
import javax.xml.parsers.SAXParserFactory;
import java.io.File;
import java.io.IOException;
import java.time.LocalDate;
import java.util.*;


public class TCDCommunity implements TADCommunity {

    private Map<Long, MyUser>                   users;
    private Map<Long, MyPost>                   posts_id;
    private Map<LocalDate, ArrayList<Long>>     posts_date;
    private Map<String, Long>                   tags;
    private LinkedList<Long>                    pre_posts;
    private LinkedList<Long>                    pre_rep;


    public TCDCommunity() {
        this.users      = new LinkedHashMap<Long, MyUser>();
        this.posts_id   = new LinkedHashMap<Long, MyPost>();
        this.posts_date = new LinkedHashMap<LocalDate, ArrayList<Long>>();
        this.tags       = new LinkedHashMap<String, Long>();
        this.pre_posts  = new LinkedList<Long>();
        this.pre_rep    = new LinkedList<Long>();
    }

    public TCDCommunity(Map<Long, MyUser> users, Map<Long, MyPost> posts_id, Map<LocalDate, ArrayList<Long>> posts_date, Map<String, Long> tags, List<Long> pre_posts, List<Long> pre_rep) {
        this.setUsers(users);
        this.setPosts_id(posts_id);
        this.setPosts_date(posts_date);
        this.setTags(tags);
        this.setPre_posts(pre_posts);
        this.setPre_rep(pre_rep);
    }

    public TCDCommunity(TCDCommunity c){
        this.users      = c.getUsers();
        this.posts_id   = c.getPosts_id();
        this.posts_date = c.getPosts_date();
        this.tags       = c.getTags();
        this.pre_posts  = c.getPre_posts();
        this.pre_rep    = c.getPre_rep();
    }

    public LinkedHashMap<Long, MyUser> getUsers() {
        LinkedHashMap<Long, MyUser> ret = new LinkedHashMap<Long, MyUser>();
        ret.putAll(this.users);
        return ret;
    }

    public void setUsers(Map<Long, MyUser> users) {
        this.users.putAll(users);
    }

    public LinkedHashMap<Long, MyPost> getPosts_id() {
        LinkedHashMap<Long, MyPost> ret = new LinkedHashMap<Long, MyPost>();
        ret.putAll(this.posts_id);
        return ret;
    }

    public void setPosts_id(Map<Long, MyPost> posts_id) {
        this.posts_id.putAll(posts_id);
    }

    public LinkedHashMap<LocalDate, ArrayList<Long>> getPosts_date() {
        LinkedHashMap<LocalDate, ArrayList<Long>> ret = new LinkedHashMap<LocalDate, ArrayList<Long>>();
        ret.putAll(this.posts_date);
        return ret;
    }

    public void setPosts_date(Map<LocalDate, ArrayList<Long>> posts_date) {
        this.posts_date.putAll(posts_date);
    }

    public LinkedHashMap<String, Long> getTags() {
        LinkedHashMap<String, Long> ret = new LinkedHashMap<String, Long>();
        ret.putAll(this.tags);
        return ret;
    }

    public void setTags(Map<String, Long> tags) {
        this.tags.putAll(tags);
    }

    public LinkedList<Long> getPre_posts() {
        LinkedList<Long> ret = new LinkedList<Long>();
        ret.addAll(this.pre_posts);
        return ret;
    }

    public void setPre_posts(List<Long> pre_posts) {
        this.pre_posts.addAll(pre_posts);
    }

    public LinkedList<Long> getPre_rep() {
        LinkedList<Long> ret = new LinkedList<Long>();
        ret.addAll(this.pre_rep);
        return ret;
    }

    public void setPre_rep(List<Long> pre_rep) {
        this.pre_rep.addAll(pre_rep);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        TCDCommunity that = (TCDCommunity) o;
        return  this.users.equals(that.getUsers())              &&
                this.posts_id.equals(that.getPosts_id())        &&
                this.posts_date.equals(that.getPosts_date())    &&
                this.tags.equals(that.getTags())                &&
                this.pre_posts.equals(that.getPre_posts())      &&
                this.pre_rep.equals(that.getPre_rep())          ;
    }

    public TCDCommunity clone(){
        return new TCDCommunity(this);
    }

    public String toString(){
        StringBuilder sb = new StringBuilder();

        sb.append("Users: ");
        sb.append(this.users.toString());
        sb.append("\n");
        sb.append("Posts: ");
        sb.append(this.posts_id.toString());
        sb.append("\n");
        sb.append("Tags: ");
        sb.append(this.tags.toString());
        sb.append("\n");

        return sb.toString();
    }

    public void load(String path){

        SAXParserFactory saxParserFactory = SAXParserFactory.newInstance();
        try {
            SAXParser saxParser = saxParserFactory.newSAXParser();
            MyUserHandler user_handler = new MyUserHandler();
            saxParser.parse(new File(path + "Users.xml"), user_handler);

            MyPostHandler post_handler = new MyPostHandler();
            saxParser.parse(new File(path + "Posts.xml"), post_handler);

            MyTagHandler tag_handler = new MyTagHandler();
            saxParser.parse(new File(path + "Tags.xml"), tag_handler);

            for(MyUser u : user_handler.getUsers())                                         //adiciona users à sua hash
                this.users.put(u.getId(), u);

            ArrayList<Long> longs = new ArrayList<Long>();
            for(MyPost p : post_handler.getPosts()) {

                try {
                    p.setOwner_name(this.users.get(p.getId()).getUsername());
                } catch(NullPointerException o){}

                this.posts_id.put(p.getId(), p);                                            //adiciona post na hash por Id

                if(this.posts_date.containsKey(p.getCdate()))
                    longs = this.posts_date.get(p.getCdate());
                else
                    longs = new ArrayList<Long>();
                longs.add(p.getId());
                this.posts_date.put(p.getCdate(), longs);                                   //adiciona post na hash por datas (LocalDate -> ArrayList<Long>) datas para conjuntos de Id's
            }

            this.tags = tag_handler.getTags();


            TreeMap<Integer, ArrayList<Long>> temp = new TreeMap<Integer, ArrayList<Long>>();

            for(Map.Entry<Long, Integer> e : user_handler.getUsers_rep().entrySet()) {      //insere na árvore o par <reputação, utilizador> !!!!mudar para heap!!!

                longs = temp.containsKey(e.getValue()) ? temp.get(e.getValue()) : new ArrayList<Long>();
                longs.add(e.getKey());
                temp.put(e.getValue(), longs);
            }


            while(!temp.isEmpty())
                this.pre_rep.addAll(temp.remove(temp.lastKey()));




            for(Map.Entry<Long, List<Long>> e : post_handler.getUser_posts().entrySet())  //atribui os post aos users na hash deles
                if(users.containsKey(e.getKey()) && e.getValue() != null)
                    for(long l : e.getValue())
                        setPostToUser(l);



            for(Map.Entry<Long, Integer> e : post_handler.getNum_posts().entrySet()) {       //insere na árvore o par <numero de posts, utilizador> !!!!mudar para heap!!!

                longs = temp.containsKey(e.getValue()) ? temp.get(e.getValue()) : new ArrayList<Long>();
                longs.add(e.getKey());
                temp.put(e.getValue(), longs);
            }


            while(!temp.isEmpty()) {

                this.pre_posts.addAll(temp.remove(temp.lastKey()));
            }


            for(MyPost p : this.posts_id.values())                                          //atribui aos posts a lista dos seus filhos
                if(this.posts_id.containsKey(p.getParent_id()))
                    setChildToPost(p.getParent_id(), p.getId());






        } catch (ParserConfigurationException | SAXException | IOException e) {
            e.printStackTrace();
        }

    }

    private void setChildToPost(long parent, long child){

        MyPost post = posts_id.get(parent);
        post.addFilho(child);

        this.posts_id.put(parent, post);

    }


    //++++++++++++++++++++++++++++++++++++++++++++++QUERIES+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

    private void setPostToUser(long post){
        this.users.get(this.posts_id.get(post).getOwner_id()).addPost(post);
    }

    // Query 1 
    public Pair<String,String> infoFromPost(long id){
        MyPost p = this.posts_id.get(id);

        if(p.getType_id() == 2)
            p = this.posts_id.get(p.getParent_id());

        return new Pair<String, String>(p.getTitle(), p.getOwner_name());
    }

    // Query 2
    public List<Long> topMostActive(int N){
        if(N > this.pre_posts.size())
                N = this.pre_posts.size();
        return this.pre_posts.subList(0, N);
    }

    // Query 3
    public Pair<Long,Long> totalPosts(LocalDate begin, LocalDate end){
        Pair<Long, Long> res = new Pair<Long,Long>(0L, 0L);

        for(Map.Entry<Long, MyPost> e : this.posts_id.entrySet())
            if(e.getValue().getCdate().isAfter(begin) && e.getValue().getCdate().isBefore(end))
                if(e.getValue().getType_id() == 1)
                    res.setFst(res.getFst() + 1);
                else if(e.getValue().getType_id() == 2)
                    res.setSecond(res.getSnd() + 1);

        return res;
    }

    // Query 4
    public List<Long> questionsWithTag(String tag, LocalDate begin, LocalDate end){
        TreeSet<MyPost> posts = new TreeSet<MyPost>(new Comparator<MyPost>() {

            public int compare (MyPost p1, MyPost p2){
                if (p1.getCdate().equals(p2.getCdate())) {
                    return p1.getId() < p2.getId() ? 1 : -1;
                }

                return p1.getCdate().isBefore(p2.getCdate()) ? 1 : -1;
            }
        });

        for(Map.Entry<LocalDate, ArrayList<Long>> e : this.posts_date.entrySet())
            if(e.getKey().isAfter(begin) && e.getKey().isBefore(end))
                for(Long l : e.getValue())
                    if(this.posts_id.get(l).getTags().contains(tag))
                        posts.add(this.posts_id.get(l));

        ArrayList<Long> res = new ArrayList<Long>();

        for(MyPost p : posts)
                res.add(p.getId());

        return res;
    }

    // Query 5
    public Pair<String, List<Long>> getUserInfo(long id){
        TreeSet<MyPost> posts = new TreeSet<MyPost>(new Comparator<MyPost>() {

            public int compare (MyPost p1, MyPost p2){
                if (p1.getCdate().equals(p2.getCdate())) {
                    return p1.getId() < p2.getId() ? 1 : -1;
                }

                return p1.getCdate().isBefore(p2.getCdate()) ? 1 : -1;
            }
        });

        for(Long l : this.users.get(id).getPosts())
            posts.add(this.posts_id.get(l));

        int n = 0;
        ArrayList<Long> res = new ArrayList<Long>();
        Iterator i = posts.iterator();

        while(i.hasNext() && n++ < 10)
              res.add(((MyPost) i.next()).getId());



        return new Pair<String, List<Long>>(this.users.get(id).getBio(), res);
    }

    // Query 6
    public List<Long> mostVotedAnswers(int N, LocalDate begin, LocalDate end){
        TreeSet<MyPost> posts = new TreeSet<MyPost>(new Comparator<MyPost>() {

            public int compare (MyPost p1, MyPost p2){
                if (p1.getScore()== p2.getScore()) {
                    return p1.getId() < p2.getId() ? 1 : -1;
                }

                return p1.getScore() < p2.getScore() ? 1 : -1;
            }
        });

        for(Map.Entry<LocalDate, ArrayList<Long>> e : this.posts_date.entrySet())
            if(e.getKey().isAfter(begin) && e.getKey().isBefore(end))
                for(Long l : e.getValue())
                    if(this.posts_id.get(l).getType_id() == 2)
                        posts.add(this.posts_id.get(l));

        ArrayList<Long> res = new ArrayList<Long>();
        int n = 0;
        Iterator i = posts.iterator();

        while (i.hasNext() && n++ < N)
            res.add(((MyPost) i.next()).getId());

        return res;
    }

    // Query 7
    public List<Long> mostAnsweredQuestions(int N, LocalDate begin, LocalDate end){
        TreeSet<MyPost> posts = new TreeSet<MyPost>(new Comparator<MyPost>() {

            public int compare (MyPost p1, MyPost p2){
                if (p1.getScore()== p2.getScore()) {
                    return p1.getId() < p2.getId() ? 1 : -1;
                }

                return p1.getAns_count() < p2.getAns_count() ? 1 : -1;
            }
        });

        for(Map.Entry<LocalDate, ArrayList<Long>> e : this.posts_date.entrySet())
            if(e.getKey().isAfter(begin) && e.getKey().isBefore(end))
                for(Long l : e.getValue())
                    if(this.posts_id.get(l).getType_id() == 1)
                        posts.add(this.posts_id.get(l));

        ArrayList<Long> res = new ArrayList<Long>();
        int n = 0;
        Iterator i = posts.iterator();

        while (i.hasNext() && n++ < N)
            res.add(((MyPost) i.next()).getId());

        return res;
    }

    // Query 8
    public List<Long> containsWord(int N, String word){
        TreeSet<MyPost> posts = new TreeSet<MyPost>(new Comparator<MyPost>() {

            public int compare (MyPost p1, MyPost p2){
                if (p1.getCdate().equals(p2.getCdate())) {
                    return p1.getId() < p2.getId() ? 1 : -1;
                }

                return p1.getCdate().isBefore(p2.getCdate()) ? 1 : -1;
            }
        });

        for(MyPost p : this.posts_id.values())
            if(p.getTitle()!= null && p.getTitle().contains(word))
                posts.add(p);



        ArrayList<Long> res = new ArrayList<Long>();
        int n = 0;
        Iterator i = posts.iterator();

        while (i.hasNext() && n++ < N)
            res.add(((MyPost) i.next()).getId());

        return res;
    }

    // Query 9
    public List<Long> bothParticipated(int N, long id1, long id2){

        TreeSet<MyPost> posts = new TreeSet<MyPost>(new Comparator<MyPost>() {

            public int compare (MyPost p1, MyPost p2){
                if (p1.getCdate().equals(p2.getCdate())) {
                    return p1.getId() < p2.getId() ? 1 : -1;
                }

                return p1.getCdate().isBefore(p2.getCdate()) ? 1 : -1;
            }
        });
        MyPost p = null;

        for (Long l : this.users.get(id1).getPosts()){
            if (this.posts_id.get(l).getType_id() == 1)
                p = this.posts_id.get(l);
            else if (this.posts_id.get(l).getType_id() == 2)
                p = this.posts_id.get(this.posts_id.get(l).getParent_id());

            if(p != null)
                for (Long m : p.getFilhos())
                    if (this.posts_id.get(m).getOwner_id() == id2)
                        posts.add(p);
        }

        ArrayList<Long> res = new ArrayList<Long>();
        int n = 0;
        Iterator i = posts.iterator();

        while (i.hasNext() && n++ < N)
            res.add(((MyPost) i.next()).getId());

        return res;
    }

    // Query 10
    public long betterAnswer(long id){
        long res = -2;
        double max = 0, atual;
        MyPost p;

        for(Long l : this.posts_id.get(id).getFilhos()){
            p = this.posts_id.get(l);
            atual = 0.65*p.getScore() + 0.25*this.users.get(p.getOwner_id()).getRep() + 0.1*p.getComm_count();

            if(atual > max){
                max = atual;
                res = l;
            }
        }

        return res;
    }

    // Query 11
    public List<Long> mostUsedBestRep(int N, LocalDate begin, LocalDate end){
        HashMap<Long, Integer> ocorrencias = new HashMap<Long, Integer>();


        for (Long l : this.pre_rep.subList(0,  this.pre_rep.size() > N ? N : this.pre_rep.size())){
            for(Long postid : this.users.get(l).getPosts()){
                MyPost p = this.posts_id.get(postid);
                if(p.getCdate().isAfter(begin) && p.getCdate().isBefore(end))
                    for(String tag : p.getTags())
                        ocorrencias.put(this.tags.get(tag), ocorrencias.containsKey(this.tags.get(tag)) ? ocorrencias.get(this.tags.get(tag)) + 1 : 1);
            }
        }

        TreeMap<Integer, TreeSet<Long>> ordenados = new TreeMap<Integer, TreeSet<Long>>();
        TreeSet<Long> longs;

        for(Map.Entry<Long, Integer> e : ocorrencias.entrySet()) {

            longs = ordenados.containsKey(e.getValue())? ordenados.get(e.getValue()) : new TreeSet<Long>();
            longs.add(e.getKey());
            ordenados.put(e.getValue(), longs);
        }

        ArrayList<Long> res = new ArrayList<Long>();

        for (int i = 0; i < N && !ordenados.isEmpty(); i++) {
            longs = ordenados.get(ordenados.lastKey());
            res.add(longs.pollFirst());

            if (longs.isEmpty())
                ordenados.remove(ordenados.lastKey());
            else
                ordenados.put(ordenados.lastKey(), longs);
        }

        return res;
    }

    //          NAO SEI SE ESTA MERDA É ASSIM QUE SE FAZ
    public void clear(){
        this.pre_rep.clear();;
        this.users.clear();
        this.posts_id.clear();
        this.posts_date.clear();
        this.pre_posts.clear();
        this.tags.clear();
    }


}

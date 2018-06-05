package engine;

import java.util.*;
import java.time.LocalDate;

public class MyPost {

    private long            id;
    private int             type_id;
    private int             ans_count;
    private int             comm_count;
    private int             fav_count;
    private int             score;
    private long            parent_id;
    private long            owner_id;
    private String          owner_name;
    private String          title;
    private LocalDate       cdate;
    private ArrayList<Long> filhos;
    private Set<String>     tags;

    public MyPost(int id, int type_id, int ans_count, int comm_count, int fav_count, int score, long parent_id, long owner_id, String owner_name, String title, LocalDate cdate, ArrayList<Long> filhos, Set<String> tags) {
        this.id         = id;
        this.type_id    = type_id;
        this.ans_count  = ans_count;
        this.comm_count = comm_count;
        this.fav_count  = fav_count;
        this.score      = score;
        this.parent_id  = parent_id;
        this.owner_id   = owner_id;
        this.owner_name = owner_name;
        this.title      = title;
        this.cdate      = cdate;
        this.filhos     = filhos;
        this.tags       = tags;
    }

    public MyPost() {
        this.id         = -2;
        this.type_id    = 0;
        this.ans_count  = 0;
        this.comm_count = 0;
        this.fav_count  = 0;
        this.score      = 0;
        this.parent_id  = -2;
        this.owner_id   = -2;
        this.owner_name = null;
        this.title      = null;
        this.cdate      = null;
        this.filhos     = new ArrayList<Long>();
        this.tags       = new HashSet<String>();
    }

    public MyPost(MyPost m) {
        this.id         = m.getId();
        this.type_id    = m.getType_id();
        this.ans_count  = m.getAns_count();
        this.comm_count = m.getComm_count();
        this.fav_count  = m.getFav_count();
        this.score      = m.getScore();
        this.parent_id  = m.getParent_id();
        this.owner_id   = m.getOwner_id();
        this.owner_name = m.getOwner_name();
        this.title      = m.getTitle();
        this.cdate      = m.getCdate();
        this.filhos     = m.getFilhos();
        this.tags       = m.getTags();
    }

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public int getType_id() {
        return type_id;
    }

    public void setType_id(int type_id) {
        this.type_id = type_id;
    }

    public int getAns_count() {
        return ans_count;
    }

    public void setAns_count(int ans_count) {
        this.ans_count = ans_count;
    }

    public int getComm_count() {
        return comm_count;
    }

    public void setComm_count(int comm_count) {
        this.comm_count = comm_count;
    }

    public int getFav_count() {
        return fav_count;
    }

    public void setFav_count(int fav_count) {
        this.fav_count = fav_count;
    }

    public int getScore() {
        return score;
    }

    public void setScore(int score) {
        this.score = score;
    }

    public long getParent_id() {
        return parent_id;
    }

    public void setParent_id(long parent_id) {
        this.parent_id = parent_id;
    }

    public long getOwner_id() {
        return owner_id;
    }

    public void setOwner_id(long owner_id) {
        this.owner_id = owner_id;
    }

    public String getOwner_name() {
        return owner_name;
    }

    public void setOwner_name(String owner_name) {
        this.owner_name = owner_name;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public LocalDate getCdate() {
        return LocalDate.from(cdate);
    }

    public void setCdate(LocalDate cdate) {
        this.cdate = cdate;
    }

    public ArrayList<Long> getFilhos() {
        ArrayList<Long> list = new ArrayList<Long>();
        list.addAll(filhos);                        //podemos usar adAll porque são longs
        return list;
    }

    public void setFilhos(ArrayList<Long> filhos) {
        this.filhos.addAll(filhos);
    }

    public void addFilho(long id) {
        this.filhos.add(id);
    }

    public Set<String> getTags() {
        Set<String> set = new HashSet<String>();
        set.addAll(tags);                   //podemos usar addAll porque são strings
        return set;
    }

    public void setTags(Set<String> tags) {
        if(tags != null)
            this.tags.addAll(tags);
    }

    public MyPost clone(){
        return new MyPost(this);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        MyPost myPost = (MyPost) o;
        return  getId()         == myPost.getId()               &&
                getType_id()    == myPost.getType_id()          &&
                getAns_count()  == myPost.getAns_count()        &&
                getComm_count() == myPost.getComm_count()       &&
                getFav_count()  == myPost.getFav_count()        &&
                getScore()      == myPost.getScore()            &&
                getParent_id()  == myPost.getParent_id()        &&
                getOwner_id()   == myPost.getOwner_id()         &&
                getOwner_name().equals(myPost.getOwner_name())  &&
                getTitle().equals(myPost.getTitle())            &&
                getCdate().equals(myPost.getCdate())            &&
                getFilhos().equals(myPost.getFilhos())          &&
                getTags().equals(myPost.getTags());
    }

    @Override
    public String toString(){
        StringBuilder sb = new StringBuilder();

        sb.append("Id: ");
        sb.append(this.id);
        sb.append("\n");
        sb.append("Type Id: ");
        sb.append(this.type_id);
        sb.append("\n");
        sb.append("Answer Count: ");
        sb.append(this.ans_count);
        sb.append("\n");
        sb.append("Comment Count: ");
        sb.append(this.comm_count);
        sb.append("\n");
        sb.append("Favorite Count: ");
        sb.append(this.fav_count);
        sb.append("\n");
        sb.append("Score: ");
        sb.append(this.score);
        sb.append("\n");
        sb.append("Parent Id: ");
        sb.append(this.parent_id);
        sb.append("\n");
        sb.append("Owner Id: ");
        sb.append(this.owner_id);
        sb.append("\n");
        sb.append("Owner Name: ");
        sb.append(this.owner_name);
        sb.append("\n");
        sb.append("Title: ");
        sb.append(this.title);
        sb.append("\n");
        sb.append("Creation Date: ");
        sb.append(this.cdate);
        sb.append("\n");
        sb.append("Tags: ");
        sb.append(this.tags);
        sb.append("\n");
        sb.append("Filhos ");
        sb.append("(" + this.filhos.size() + "): ");
        sb.append(Arrays.toString(this.filhos.toArray()));
        sb.append("\n");


        return sb.toString();
    }

}

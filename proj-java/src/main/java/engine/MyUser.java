package engine;

import java.util.List;
import java.util.ArrayList;

public class MyUser {

    private long    id;
    private int     rep;
    private String  username;
    private String  bio;
    List<Long>      posts;

    public MyUser() {
        this.id         = -2;
        this.rep        = 0;
        this.username   = null;
        this.bio        = null;
        this.posts      = new ArrayList<Long>();
    }

    public MyUser(int id, int rep, String username, String bio, List<Long> posts) {
        this.id         = id;
        this.rep        = rep;
        this.username   = username;
        this.bio        = bio;
        this.posts      = new ArrayList<Long>();
        this.posts.addAll(posts);
    }

    public MyUser(MyUser m){
        this.id         = m.getId();
        this.rep        = m.getRep();
        this.username   = m.getUsername();
        this.bio        = m.getBio();
        this.posts      = m.getPosts();
    }

    public long getId() {
        return id;
    }

    public void setId(long id) {
        this.id = id;
    }

    public int getRep() {
        return rep;
    }

    public void setRep(int rep) {
        this.rep = rep;
    }

    public String getUsername() {
        return username;
    }

    public void setUsername(String username) {
        this.username = username;
    }

    public String getBio() {
        return bio;
    }

    public void setBio(String bio) {
        this.bio = bio;
    }

    public List<Long> getPosts() {
        ArrayList<Long> list = new ArrayList<Long>();
        list.addAll(this.posts);
        return list;
    }

    public void setPosts(List<Long> list) {
        this.posts.addAll(list);
    }

    public void addPost(long id){
        this.posts.add(id);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        MyUser myUser = (MyUser) o;
        return  getId()     == myUser.getId()               &&
                getRep()    == myUser.getRep()              &&
                getUsername().equals(myUser.getUsername())  &&
                getBio().equals(myUser.getBio())            &&
                getPosts().equals(myUser.getPosts())        ;
    }

    public MyUser clone(){
        return new MyUser(this);
    }

    public String toString(){
        StringBuilder sb = new StringBuilder();

        sb.append("Id: ");
        sb.append(this.id);
        sb.append("\n");
        sb.append("Username: ");
        sb.append(this.username);
        sb.append("\n");
        sb.append("Reputacao: ");
        sb.append(this.rep);
        sb.append("\n");
        sb.append("Biografia: ");
        sb.append(this.bio);
        sb.append("\n");
        sb.append("Posts criados ");
        sb.append("(" + this.posts.size() + "): ");
        sb.append(this.posts);
        sb.append("\n");

        return sb.toString();
    }

}

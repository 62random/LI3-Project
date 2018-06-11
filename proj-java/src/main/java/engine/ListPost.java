package engine;

import java.util.Comparator;
import java.util.List;
import java.util.stream.Collectors;
import java.util.ArrayList;

public class ListPost {

    private int perguntas;
    private int respostas;
    private List<MyPost> posts;

    public ListPost(){
        this.posts = new ArrayList<>();
        this.perguntas = 0;
        this.respostas = 0;
    }

    public ListPost(List<MyPost> a){
        this.posts = a.stream().map(MyPost::clone).collect(Collectors.toCollection(ArrayList::new));
        for(MyPost i : this.posts){
            if (i.getType_id() == 1)
                perguntas++;
            else if (i.getType_id() == 2)
                respostas++;
        }
    }

    public ListPost (ListPost a){
        this.posts = a.getPosts().stream().map(MyPost::clone).collect(Collectors.toCollection(ArrayList::new));
        this.perguntas = a.getPerguntas();
        this.respostas = a.getRespostas();
    }

    public List<MyPost> getPosts(){
        return posts;
    }

    public ListPost clone(){
        return  new ListPost(this);
    }

    public int getPerguntas(){
        return this.perguntas;
    }

    public int getRespostas(){
        return this.respostas;
    }

    public void add(MyPost p){
        this.posts.add(p);
        if (p.getType_id() == 1)
            perguntas++;
        else if (p.getType_id() == 2)
            respostas++;
    }

    private int compaux(MyPost a1, MyPost a2){
        if (a1.getId() > a2.getId())
            return -1;
        else if (a1.getId() < a2.getId())
            return 1;
        return 0;
    }

    public void sort(){
        Comparator<MyPost> comp = (a1,a2) -> compaux(a1,a2);
        this.posts.sort(comp);
    }




}

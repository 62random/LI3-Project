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

    /**
     * Contrutor sem argumentos.
     */
    public TCDCommunity() {
        this.users      = new LinkedHashMap<Long, MyUser>();
        this.posts_id   = new LinkedHashMap<Long, MyPost>();
        this.posts_date = new LinkedHashMap<LocalDate, ArrayList<Long>>();
        this.tags       = new LinkedHashMap<String, Long>();
        this.pre_posts  = new LinkedList<Long>();
        this.pre_rep    = new LinkedList<Long>();
    }

    /**
     * Construtor com argumentos.
     * @param users             Map de <ID,User> a introduzir.
     * @param posts_id          Map de <ID,Post> a introduzir.
     * @param posts_date        Map de <Data,Posts> a introduzir.
     * @param tags              Map de <TAG,Contagem> a introduzir..
     * @param pre_posts         Conjunto de posts pre calculados a introduzir.
     * @param pre_rep           Conjunto de reputacao pre calculada a introduzir.
     */
    public TCDCommunity(Map<Long, MyUser> users, Map<Long, MyPost> posts_id, Map<LocalDate, ArrayList<Long>> posts_date, Map<String, Long> tags, List<Long> pre_posts, List<Long> pre_rep) {
        this.setUsers(users);
        this.setPosts_id(posts_id);
        this.setPosts_date(posts_date);
        this.setTags(tags);
        this.setPre_posts(pre_posts);
        this.setPre_rep(pre_rep);
    }
    /**
     * Construtor por copias.
     * @param c     Classe a copiar.
     */
    public TCDCommunity(TCDCommunity c){
        this.users      = c.getUsers();
        this.posts_id   = c.getPosts_id();
        this.posts_date = c.getPosts_date();
        this.tags       = c.getTags();
        this.pre_posts  = c.getPre_posts();
        this.pre_rep    = c.getPre_rep();
    }

    /**
     * Get para a variável users objeto.
     * @return  Users do objeto.
     */
    public LinkedHashMap<Long, MyUser> getUsers() {
        LinkedHashMap<Long, MyUser> ret = new LinkedHashMap<Long, MyUser>();
        ret.putAll(this.users);
        return ret;
    }

    public void setUsers(Map<Long, MyUser> users) {
        this.users.putAll(users);
    }

    /**
     * Get para a variável post_id do objeto.
     * @return  Post_Id do objeto.
     */
    public LinkedHashMap<Long, MyPost> getPosts_id() {
        LinkedHashMap<Long, MyPost> ret = new LinkedHashMap<Long, MyPost>();
        ret.putAll(this.posts_id);
        return ret;
    }

    public void setPosts_id(Map<Long, MyPost> posts_id) {
        this.posts_id.putAll(posts_id);
    }

    /**
     * Get para a variável post_date do objeto.
     * @return  Post_date do objeto.
     */
    public LinkedHashMap<LocalDate, ArrayList<Long>> getPosts_date() {
        LinkedHashMap<LocalDate, ArrayList<Long>> ret = new LinkedHashMap<LocalDate, ArrayList<Long>>();
        ret.putAll(this.posts_date);
        return ret;
    }

    public void setPosts_date(Map<LocalDate, ArrayList<Long>> posts_date) {
        this.posts_date.putAll(posts_date);
    }

    /**
     * Get para a variável tags do objeto.
     * @return  Tags do objeto.
     */
    public LinkedHashMap<String, Long> getTags() {
        LinkedHashMap<String, Long> ret = new LinkedHashMap<String, Long>();
        ret.putAll(this.tags);
        return ret;
    }

    public void setTags(Map<String, Long> tags) {
        this.tags.putAll(tags);
    }

    /**
     * Get para a variável pre_posts do objeto.
     * @return  Pre_posts do objeto.
     */
    public LinkedList<Long> getPre_posts() {
        LinkedList<Long> ret = new LinkedList<Long>();
        ret.addAll(this.pre_posts);
        return ret;
    }

    public void setPre_posts(List<Long> pre_posts) {
        this.pre_posts.addAll(pre_posts);
    }

    /**
     * Get para a variável pre_red do objeto.
     * @return  Pre_rep do objeto.
     */
    public LinkedList<Long> getPre_rep() {
        LinkedList<Long> ret = new LinkedList<Long>();
        ret.addAll(this.pre_rep);
        return ret;
    }

    public void setPre_rep(List<Long> pre_rep) {
        this.pre_rep.addAll(pre_rep);
    }

    /**
     * Método equal do objeto.
     * @param  o     Objeto a comparar
     * @return       Booelan que verifica se o objeto e igual
     */
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

    /**
     * Método que clona este objeto.
     * @return clone do objeto
     */
    public TCDCommunity clone(){
        return new TCDCommunity(this);
    }

    /**
     * Método toString do objeto.
     * @return Objeto em modo string.
     */
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

    /**
     * Função dá load aos ficheiros xml.
     * @param	path	    String com a diretoria onde se encontram os ficheiros.
     */
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
    /**
     * Método que adicionar uma respota a um post.
     * @param parent        Pai a adiconar.
     * @param child         Filho que vai ser adicionado.
     */
    private void setChildToPost(long parent, long child){

        MyPost post = posts_id.get(parent);
        post.addFilho(child);

        this.posts_id.put(parent, post);

    }


    //++++++++++++++++++++++++++++++++++++++++++++++QUERIES+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    /**
     * Função mete um post no correspondete user.
     * @param post			Identificador do post.
     */
    private void setPostToUser(long post){
        this.users.get(this.posts_id.get(post).getOwner_id()).addPost(post);
    }

    // Query 1
    /**
     * Função retorna a informacao de um post.
     * @param	id		Id do post
     * @return 			STR_pair com o title e name do user, retorna NULL em caso de nao ser encontrado.
     */
    public Pair<String,String> infoFromPost(long id){
        MyPost p = this.posts_id.get(id);

        if(p.getType_id() == 2)
            p = this.posts_id.get(p.getParent_id());

        return new Pair<String, String>(p.getTitle(), p.getOwner_name());
    }

    // Query 2
    /**
     * Função que calcula os N utilizadores com mais posts.
     * @param	N		Número de jogadores.
     * @return 			LONG_list com os N users mais ativos, retorna -2 nos restantes indices da lista caso exceda o numero de users.
     */
    public List<Long> topMostActive(int N){
        if(N > this.pre_posts.size())
                N = this.pre_posts.size();
        return this.pre_posts.subList(0, N);
    }

    // Query 3
    /**
     * Função que dado um intervalo de tempo obtem o numero total de perguntas e respostas.
     * @param	begin	Data inicial da procura
     * @param	end		Data final da procura
     * @return 			LONG_pair com o numero total de perguntas e resposta no dado intervalo.
     */
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
    /**
     * Função que dado um intervalo de tempo retornar todas as perguntas contendo uma determinada tag.
     * @param	tag		Tag.
     * @param	begin	Data inicial da procura.
     * @param	end		Data final da procura.
     * @return 			LONG_list com o id de todas as tags que ocorreram no dado intervalo de tempo.
     */
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
    /**
     * Função que dado um id de um user devolve informacao sobre este mesmo.
     * @param	id		Id do post.
     * @return 			Estrutura USER com a biografia e os 10 posts mais recentes desse mesmo user, retorna -2 nos indices dos posts apartir do momento que nao seja encontrado mais posts desse user.
     */
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
    /**
     * Função que dado um intervalo de tempo calcula os N posts com melhor score.
     * @param	N		Número de respostas.
     * @param	begin	Data do começo do intervalo.
     * @param	end		Data do fim do intervalo.
     * @return 			LONG_list com os N utilizadores que mais votaram no dado intervalo de tempo, caso nao encontre N utilizadores retornara -2 nos restantes indices do array.
     */
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
    /**
     * Função que dado um intervalo de tempo calcula as N perguntas com mais respostas.
     * @param	N		Número de posts a calcular.
     * @param	begin	Data do começo do intervalo.
     * @param	end		Data do fim do intervalo.
     * @return 			LONG_list com os N utilizadores que mais votaram no intervalo dado, caso nao encontre N utilizadores retornara -2 nos restantes indices do array.
     */
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
    /**
     * Função que obtém os id's das N perguntas mais recentes cujo título contém uma dada palavra.
     * @param	word	Palavra a ser procurada nos títulos.
     * @param	N		Número máximo de resultados N.
     * @return 			LONG_list com as N perguntas mais recentes que contêm a palavra dada.
     */
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
    /**
     * Função que dado 2 users retorna as N perguntas em que ambos participaram.
     * @param id1		ID do user 1.
     * @param id2		ID do user 2.
     * @param N			Número máximo de N
     * @return 			LONG_list com as N perguntas mais recentes em que ambos os users participaram, caso a lista seja menor que N os restantes indices ficam com o valor de -2.
     */
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
    /**
     * Função que dado um id de um post devolve a resposta melhor cotada desse post.
     * @param	id		Id do post
     * @return 			ID da respota com melhor pontuacao,retorna -2 caso nao haja nenhuma respota, -3 caso a pergunta nao seja encontrado o post e -4 caso o id do post dado nao corresponda a uma pergunta.
     */
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
    /**
     * Função que obtém o número de ocorrencias das N tags mais usadas num dado período de tempo pelos N users com maior reputação.
     * @param	N		Número máximo de tags.
     * @param	begin	Início do período de tempo.
     * @param	end		Final do período de tempo.
     * @return 			LONG_list com as N tags mais usados num dado intervalo de tempo pelos users com mais reputacao.
     */
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
    // 0 fucks given vou documentar á mesma :D

    /**
     * Função que liberta a memória do objeto.
     */
    public void clear(){
        this.pre_rep.clear();;
        this.users.clear();
        this.posts_id.clear();
        this.posts_date.clear();
        this.pre_posts.clear();
        this.tags.clear();
    }


}

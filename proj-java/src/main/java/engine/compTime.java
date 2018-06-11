package engine

import java.util.Comparator;

public class compTime implements Comparator<MyPost> {
    @Override
    public int compare(MyPost p1,MyPost p2){
        if (p1.getCdate().equals(p2.getCdate())) {
            return p1.getId() < p2.getId() ? 1 : -1;
        }

        return p1.getCdate().isBefore(p2.getCdate()) ? 1 : -1;
    }
}

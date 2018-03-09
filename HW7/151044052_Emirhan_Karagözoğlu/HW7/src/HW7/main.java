package HW7;

import javafx.util.Pair;
import java.security.InvalidParameterException;

/**
 * Test Class
 * @author Emirhan Karagözoğlu
 */
public class main{

    /**
     *
     * @param args the command line arguments
     */
    @SuppressWarnings("unchecked")
    public static void main(String args[]){
        
        //Integer Set Tests
        System.out.println("------------------------------");

        
        GTUSet<Integer> integerSet = new GTUSet<>(Integer[].class);
        GTUSet<Integer>.GTUIterator integerIt = integerSet.new GTUIterator();

        System.out.printf("Size of integer set is %d\n",integerSet.size());

        try{
            integerSet.insert(5);
            integerSet.insert(2);
            integerSet.insert(4);
            integerSet.insert(1);
            integerSet.insert(3);
            integerSet.insert(2);
        }
        catch(InvalidParameterException ia){
            System.out.println(ia.getMessage());
        }

        for(int i=0; i<integerSet.size(); ++i)
            System.out.printf("%d ",integerIt.next());
        System.out.println();

        System.out.println("Insert process completed!");

        integerSet.erase(1);
        integerSet.erase(1);
        integerSet.erase(5);

        integerIt.setPosition(0);
        for(int i=0; i<integerSet.size(); ++i)
                System.out.printf("%d ",integerIt.next());
        System.out.println();

        System.out.println("Erase process completed!");

        System.out.printf("Size of integer set is %d\n",integerSet.size());

        integerIt.setPosition(integerSet.find(4).getPosition());
        System.out.printf("Set contains %d\n", integerIt.next());

        System.out.printf("Number of 12 is %d\n",integerSet.count(12));
        System.out.printf("Number of 2 is %d\n",integerSet.count(2));

        integerSet.clear();

        if(integerSet.empty())
            System.out.println("Set is empty!");

        //String Set Tests
        System.out.println("------------------------------");

        
        GTUSet<String> stringSet = new GTUSet<>(String[].class);
        GTUSet<String>.GTUIterator stringIt = stringSet.new GTUIterator();

        System.out.printf("Size of string set is %d\n",stringSet.size());

        try{
            stringSet.insert("Gebze");
            stringSet.insert("Teknik");
            stringSet.insert("Universitesi");
            stringSet.insert("Bilgisayar");
            stringSet.insert("Muhendisligi");
        }
        
        catch(InvalidParameterException ia){
            System.out.println(ia.getMessage());
        }

        for(int i=0; i<stringSet.size(); ++i)
                System.out.printf("%s ",stringIt.next());
        System.out.println();

        System.out.println("Insert process completed!");

        stringSet.erase("Muhendisligi");
        stringSet.erase("Bilgisayar");

        stringIt.setPosition(0);
        for(int i=0; i<stringSet.size(); ++i)
                System.out.printf("%s ",stringIt.next());
        System.out.println();

        System.out.println("Erase process completed!");

        System.out.printf("Size of string set is %d\n",stringSet.size());

        stringIt.setPosition(stringSet.find("Gebze").getPosition());
        System.out.printf("Set contains %s\n", stringIt.next());

        System.out.printf("Number of Gebzel is %d\n",stringSet.count("Gebzel"));
        System.out.printf("Number of Teknik is %d\n",stringSet.count("Teknik"));

        stringSet.clear();

        if(stringSet.empty())
            System.out.println("Set is empty!");
        
        //String Integer Map Tests
        System.out.println("------------------------------");
        
        GTUMap<String,Integer> strIntMap = new GTUMap(Pair[].class);
        GTUMap<String,Integer>.GTUIterator strIntMapIt = strIntMap.new GTUIterator();
        
        System.out.printf("Size of string-integer map is %d\n",strIntMap.size());
        
        try{
            strIntMap.insert(new Pair<>("Yusuf",12));
            strIntMap.insert(new Pair<>("Sinan",13));
            strIntMap.insert(new Pair<>("Akgül",14));
            strIntMap.insert(new Pair<>("Akgül",14));
        }
        
        catch(InvalidParameterException ia){
            System.out.println(ia.getMessage());
        }
        System.out.printf("Yusuf=%d ",strIntMap.at("Yusuf"));
        System.out.printf("Sinan=%d ",strIntMap.at("Sinan"));
        System.out.printf("Akgül=%d\n",strIntMap.at("Akgül"));
        
        System.out.println("Insert process completed!");
        
        strIntMap.erase(new Pair<>("Akgül",14));
        
        strIntMapIt.setPosition(0);
        for(int i=0; i<strIntMap.size(); ++i)
               System.out.printf("%s ",strIntMapIt.next());
        System.out.println();
        
        System.out.println("Erase process completed!");
        
        System.out.printf("Size of string-integer map is %d\n",strIntMap.size());
        
        strIntMapIt.setPosition(strIntMap.find(new Pair<>("Yusuf",12)).getPosition());
        System.out.printf("Set contains %s\n", strIntMapIt.next());
        
        System.out.printf("Number of Yusuf is %d\n",strIntMap.count(new Pair<>("Yusuf",12)));
        
        System.out.printf("Number of Ali is %d\n",strIntMap.count(new Pair<>("Ali",55)));

        strIntMap.clear();

        if(strIntMap.empty())
            System.out.println("Set is empty!");
        
        //Integer Sets Intersection Tests
        System.out.println("------------------------------");

        
        GTUSet<Integer> firstSet = new GTUSet<>(Integer[].class);
        
        
        GTUSet<Integer> secondSet = new GTUSet<>(Integer[].class);
        
        GTUSet<Integer>.GTUIterator firstIt = firstSet.new GTUIterator();
        GTUSet<Integer>.GTUIterator secondIt = secondSet.new GTUIterator();
        
        try{
            firstSet.insert(55);
            firstSet.insert(44);
            firstSet.insert(33);
            firstSet.insert(77);
            
            secondSet.insert(55);
            secondSet.insert(45);
            secondSet.insert(33);
        }
        catch(InvalidParameterException ia){
            System.out.println(ia.getMessage());
        }
        
        System.out.printf("First set is = ");
        for(int i=0; i<firstSet.size(); ++i)
            System.out.printf("%d ",firstIt.next());
        System.out.println();
        
        System.out.printf("Second set is = ");
        for(int i=0; i<secondSet.size(); ++i)
            System.out.printf("%d ",secondIt.next());
        System.out.println();
        
       
        GTUSet<Integer> intersectionSet = new GTUSet<>(Integer[].class);
        
        
        intersectionSet = (GTUSet<Integer>)firstSet.intersection(secondSet);
        
        GTUSet<Integer>.GTUIterator intersectionIt = intersectionSet.new GTUIterator();
        
        System.out.printf("Intersection of two map is = ");
        for(int i=0; i<intersectionSet.size(); ++i)
            System.out.printf("%d ",intersectionIt.next());
        System.out.println();
        
        //String-String Maps Intersection Tests
        System.out.println("------------------------------");

        
        GTUMap<String,String> firstMap = new GTUMap(Pair[].class);
        
        
        GTUMap<String,String> secondMap = new GTUMap(Pair[].class);
        
        GTUMap<String,String>.GTUIterator firstMapIt = firstMap.new GTUIterator();
        GTUMap<String,String>.GTUIterator secondMapIt = secondMap.new GTUIterator();
        
        try{
            firstMap.insert(new Pair<>("London","England"));
            firstMap.insert(new Pair<>("Washington","USA"));
            firstMap.insert(new Pair<>("Paris","France"));
            firstMap.insert(new Pair<>("Rome","Italy"));
            firstMap.insert(new Pair<>("Madrid","Spain"));
            
            secondMap.insert(new Pair<>("Havana","Cuba"));
            secondMap.insert(new Pair<>("Buenos Aires","Argentina"));
            secondMap.insert(new Pair<>("Washington","USA"));
            secondMap.insert(new Pair<>("Paris","Champs-Élysées"));
        }
        catch(InvalidParameterException ia){
            System.out.println(ia.getMessage());
        }
        
        System.out.println("First map is ");
        for(int i=0; i<firstMap.size(); ++i)
            System.out.printf("%s \n",firstMapIt.next());
        System.out.println();
        
        System.out.println("Second map is ");
        for(int i=0; i<secondMap.size(); ++i)
            System.out.printf("%s \n",secondMapIt.next());
        System.out.println();
        
       
        GTUMap<String,String> intersectionMap = new GTUMap(Pair[].class);
        
        intersectionMap = (GTUMap<String,String>)secondMap.intersection(firstMap);
        
        GTUMap<String,String>.GTUIterator intersectionMapIt = intersectionMap.new GTUIterator();
        
        System.out.println("Intersection of two map is ");
        for(int i=0; i<intersectionMap.size(); ++i)
            System.out.printf("%s \n",intersectionMapIt.next());
    }
}
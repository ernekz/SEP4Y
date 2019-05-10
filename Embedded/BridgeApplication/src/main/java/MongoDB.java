import com.mongodb.MongoClient;
import com.mongodb.MongoClientURI;

public class MongoDB {
    MongoClientURI uri;
    MongoClient mongoClient;

    public MongoDB(){
        uri= new MongoClientURI("");
        mongoClient = new MongoClient(uri);
    }
}

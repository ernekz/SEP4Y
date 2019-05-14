import com.mongodb.MongoClient;
import com.mongodb.MongoClientURI;
import com.mongodb.client.MongoDatabase;
import org.bson.Document;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.time.LocalDate;

import java.util.Calendar;


import static java.time.format.DateTimeFormatter.ISO_LOCAL_DATE;

public class MongoDB {
    MongoClientURI uri;
    MongoClient mongoClient;
    MongoDatabase mongoDatabase;

    DateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
    String currentDateAndTime= dateFormat.format(Calendar.getInstance().getTime());


    public MongoDB(){
        uri= new MongoClientURI("mongodb+srv://admin:admin@sep4y-8ayle.gcp.mongodb.net/test?retryWrites=true");
        mongoClient = new MongoClient(uri);
        mongoDatabase=mongoClient.getDatabase("sep4database");
    }

    public void insertNewDocument(String collectionName, int co2, int temperature){
        Document document = new Document("date", currentDateAndTime)
                .append("co2", co2)
                .append("temperature", temperature)
                .append("room_id", 1)
                .append("date_created", LocalDate.now().format(ISO_LOCAL_DATE))
                .append("name", "example1");
                mongoDatabase.getCollection(collectionName).insertOne(document);
    }
}

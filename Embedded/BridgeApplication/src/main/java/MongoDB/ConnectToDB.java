package MongoDB;

import com.mongodb.client.MongoClient;
import com.mongodb.client.MongoClients;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;
import org.bson.Document;

public class ConnectToDB {

        //Connect to mongoDB instance
        MongoClient mongoClient = MongoClients.create();
        //Access the database
        MongoDatabase database= mongoClient.getDatabase("databaseName");
        //Access collection
        MongoCollection<Document> coll = database.getCollection("collectionName");




}

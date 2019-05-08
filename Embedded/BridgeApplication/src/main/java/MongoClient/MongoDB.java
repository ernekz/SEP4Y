package MongoClient;

import com.mongodb.client.MongoClient;
import com.mongodb.client.MongoClients;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;
import com.mongodb.client.model.Indexes;
import static com.mongodb.client.model.Filters.eq;
import static com.mongodb.client.model.Updates.*;

import org.bson.Document;
import org.bson.types.ObjectId;

import static com.mongodb.client.model.Updates.combine;
import static com.mongodb.client.model.Updates.currentDate;

public class MongoDB {
    MongoDatabase database;
    MongoClient mongoClient;
    MongoCollection<Document> collection;


    public MongoDB() {
        //Connect to MongoDB instance
        mongoClient = MongoClients.create(new MongoClientURI("mongodb+srv://admin:<password>@sep4y-8ayle.gcp.mongodb.net/test?retryWrites=true"));
    }

    //Access the database
    public void accessDatabase(String databaseName){
        mongoClient.getDatabase(databaseName);
    }
    //Access collection
    public void accessCollection(String collectionName){
         collection = database.getCollection(collectionName);
    }
    //Create an ascending index
    public void createAscendingIndex(String fieldName){
        collection.createIndex(Indexes.ascending(fieldName));
    }
    //Create an ascending compound index
    public void createAscendingCompoundIndex(String fieldName1, String fieldName2){
        collection.createIndex(Indexes.ascending(fieldName1, fieldName2));
    }
    //Create a descending index
    public void createDescendingIndex(String fieldName){
        collection.createIndex(Indexes.descending(fieldName));
    }
    //Create a descending compound index
    public void createDescendingCompoundIndex(String fieldName1, String fieldName2){
        collection.createIndex(Indexes.descending(fieldName1, fieldName2));
    }
    //Insert new single document into the collection
    public void insertSingleDocument(String key, String value){
        Document document = new Document(key, value);
        collection.insertOne(document);
    }
    //Update a single document
    public void updateSingleDocument(String id, String objectId, String key, String value){
        collection.updateOne(
             eq(id, new ObjectId(objectId)),
        combine(set(key, value), currentDate("lastModified")));
    }
}

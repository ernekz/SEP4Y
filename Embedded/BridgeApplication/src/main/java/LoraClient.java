import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.WebSocket;
import java.nio.ByteBuffer;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.CompletionStage;

public class LoraClient implements WebSocket.Listener {
    String hexTemperature, hexCo2, stringMessage;
    public static final String keyword="data";
    int decTemperature, decCo2;
    MongoDB mongoDB;

    public LoraClient(){
        HttpClient client = HttpClient.newHttpClient();
        stringMessage ="";
        hexTemperature="";
        decTemperature=0;
        hexCo2="";
        decCo2=0;
        CompletableFuture<WebSocket> webSocket = client.newWebSocketBuilder().buildAsync(URI.create("wss://iotnet.teracom.dk/app?token=vnoRoQAAABFpb3RuZXQudGVyYWNvbS5kazdq6klI6RmA9s7aH5ya0Eo="), this);
        System.out.println("LoraClient created.");
    }
    public void onOpen(WebSocket webSocket) {
        webSocket.request(1);
        System.out.println("WebSocket Listener has been opened for requests. ");
    }
    public void onError(WebSocket webSocket, Throwable error) {
        System.out.println("A "+error.getCause() + " exception was thrown.");
        System.out.println("Message: " + error.getLocalizedMessage());
        webSocket.abort();
    }
    public CompletionStage<?> onClose(WebSocket webSocket, int statusCode, String reason) {
        System.out.println("WebSocket closed!");
        System.out.println("Status: " + statusCode + " Reason: "+ reason);
        return new CompletableFuture().completedFuture("onClose() completed.").thenAccept(System.out::println);
    }
    public CompletionStage<?> onPing(WebSocket webSocket, ByteBuffer message) {
        webSocket.request(1);
        System.out.println("Ping: Client ---> Server");
        System.out.println(message.asCharBuffer().toString());
        return new CompletableFuture().completedFuture("Ping completed.").thenAccept(System.out::println);
    }

    public CompletionStage<?> onPong(WebSocket webSocket, ByteBuffer message) {
        webSocket.request(1);
        System.out.println("Pong: Client---> Server");
        System.out.println(message.asCharBuffer().toString());
        return new CompletableFuture().completedFuture("Pong completed.").thenAccept(System.out::println);
    }
    public CompletionStage<?> onText(WebSocket webSocket, CharSequence data, boolean least) {
        if(data.toString().contains(keyword)){
        System.out.println("JSON MESAGE: "+data);
//            mongoDB= new MongoDB();
//            List<String> message = new ArrayList<String>(Arrays.asList(data.toString().split(",")));
//            for(int i=0; i<message.size(); i++){
//                if(message.get(i).contains(keyword)){
//                    sendData(message, i);
//                }
//            }
//            stringMessage="";
        }
        webSocket.request(1);
        return new CompletableFuture().completedFuture("onText() completed.").thenAccept(System.out::println);
    }
    public void sendData(List<String> message, int dataIndex){
                System.out.println(message.get(dataIndex));
                if (message.get(dataIndex).substring(12)=="1"){
                    hexCo2=message.get(dataIndex).substring(13, 16);
                    decCo2=Integer.parseInt(hexCo2, 16)/10;
                    System.out.println("CO2 value: "+decCo2);
                }else{
                    hexTemperature=message.get(dataIndex).substring(13,16);
                    decTemperature = Integer.parseInt(hexTemperature, 16)/10;
                    System.out.println("Temperature value: "+decTemperature);
                }

                if(hexTemperature!="0000"&&hexCo2!="0000"){
                    mongoDB.insertNewDocument("sep4collection", decCo2, decTemperature);
                    hexCo2="0000";
                    hexTemperature="0000";
                }


    }
}

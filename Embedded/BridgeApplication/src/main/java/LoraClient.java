import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.WebSocket;
import java.nio.ByteBuffer;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.CompletionStage;

public class LoraClient implements WebSocket.Listener {
    static int temperature;
    static int co2;
    String jsonMessage;

    MongoDB mongoDB= new MongoDB();


    public LoraClient(){
        HttpClient client = HttpClient.newHttpClient();
        temperature=0;
        co2=0;
        jsonMessage="";
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
        jsonMessage=data.toString();
        System.out.println(data);
        getTemperature(jsonMessage);
        getCo2(jsonMessage);
        mongoDB.insertNewDocument("BridgeAppSampleData", temperature, co2);
        webSocket.request(1);

        return new CompletableFuture().completedFuture("onText() completed.").thenAccept(System.out::println);
    }

    public void getTemperature(CharSequence jsonMessage){
        temperature=Integer.parseInt(jsonMessage.toString().substring(116, 120));
    }
    public void getCo2(CharSequence jsonMessage){
        co2=Integer.parseInt(jsonMessage.toString().substring(120, 124));
    }

}

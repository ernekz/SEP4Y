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
    String hexTemperature, hexCo2;
    public static final String keyword="data";
    double decTemperature;
    int decCo2;
    MongoDB mongoDB;

    public LoraClient(){
        HttpClient client = HttpClient.newHttpClient();
        hexTemperature="";
        decTemperature=0.0;
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
        System.out.println("\nJSON MESAGE: "+data+"\n");

            List<String> message = new ArrayList<String>(Arrays.asList(data.toString().split(",")));
            for(int i=0; i<message.size(); i++){
                if(message.get(i).contains(keyword)){
                    sendData(message, i);
                }
            }
        }
        webSocket.request(1);
        return null;
    }
    public void sendData(List<String> message, int dataIndex){
                if (message.get(dataIndex).charAt(11)=='1'){
                    hexCo2=message.get(dataIndex).substring(12, 16);
                    decCo2=Integer.parseInt(hexCo2, 16);
                    System.out.println("CO2 value: "+decCo2);
                    System.out.println("Temperature value: "+decTemperature);
                }else{
                    hexTemperature=message.get(dataIndex).substring(12,16);
                    long parseHex = parseTemperature(hexTemperature);
                    decTemperature= parseHex/10.0;
                    System.out.println("Temperature value: "+decTemperature);
                    System.out.println("CO2 value: "+decCo2);
                }
                if(decTemperature!=0.0&&decCo2!=0){
                    mongoDB= new MongoDB();
                    mongoDB.insertNewDocument("sep4collection", decCo2, decTemperature);
                    decCo2=0;
                    decTemperature=0.0;
                }
    }
    public static long parseTemperature(String data) {
        if (data.length() == 16) {
            return (parseTemperature(data.substring(0, 1)) << 60)
                    | parseTemperature(data.substring(1));
        }
        return Long.parseLong(data, 16);
    }
}

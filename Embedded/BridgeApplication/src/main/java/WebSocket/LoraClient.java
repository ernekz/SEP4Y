package WebSocket;


import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.WebSocket;
import java.nio.ByteBuffer;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.CompletionStage;

public class LoraClient implements Listener {

    public LoraClient(){
        HttpClient client = HttpClient.newHttpClient();
        CompletableFuture<WebSocket> ws= client.newWebSocketBuilder()
                .buildAsync(URI.create("wss://iotnet.teracom.dk/app?token=vnoRlAAAABFpb3RuZXQudGVyYWNvbS5kay68arsawh5bptw7waIoimg="), (WebSocket.Listener) this);
    }
    @Override
    public void onOpen(WebSocket webSocket) {
        webSocket.request(1);
        System.out.println("WebSocket Listener has been opened for requests. ");
    }

    @Override
    public void onError(WebSocket webSocket, Throwable error) {
        System.out.println("A "+error.getCause() + " exception was thrown.");
        System.out.println("Message: " + error.getLocalizedMessage());
        webSocket.abort();
    }

    @Override
    public CompletionStage<?> onClose(WebSocket webSocket, int statusCode, String reason) {
        System.out.println("WebSocket closed!");
        System.out.println("Status: " + statusCode + " Reason: "+ reason);
        return null;
    }

    @Override
    public CompletionStage<?> onPing(WebSocket webSocket, ByteBuffer message) {
        webSocket.request(1);
        System.out.println("Ping: Client ---> Server");
        System.out.println(message.asCharBuffer().toString());
        return null;
    }

    @Override
    public CompletionStage<?> onPong(WebSocket webSocket, ByteBuffer message) {
        webSocket.request(1);
        System.out.println("Pong: Client---> Server");
        System.out.println(message.asCharBuffer().toString());
        return null;
    }

    @Override
    public CompletionStage<?> onText(WebSocket webSocket, CharSequence data, boolean least) {
        System.out.println(data);
        webSocket.request(1);
        return null;
    }
}

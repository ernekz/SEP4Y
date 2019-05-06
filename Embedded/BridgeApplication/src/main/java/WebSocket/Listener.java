import java.net.http.WebSocket;
package WebSocket;



public interface Listener {
    public void onOpen(WebSocket webSocket);
}

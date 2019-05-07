package WebSocket;

import java.net.http.WebSocket;
import java.nio.ByteBuffer;
import java.util.concurrent.CompletionStage;

public interface Listener {
    public void onOpen(WebSocket webSocket);
    public void onError(WebSocket webSocket, Throwable error);
    public CompletionStage<?> onClose(WebSocket webSocket, int statusCode, String reason);
    public CompletionStage<?> onPing(WebSocket webSocket, ByteBuffer message);
    public CompletionStage<?> onPong(WebSocket webSocket, ByteBuffer message);
    public CompletionStage<?> onText(WebSocket webSocket, CharSequence data, boolean least);
}

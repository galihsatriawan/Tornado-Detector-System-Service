package anton.tornado.detector.system;

import android.app.Application;

import com.google.firebase.FirebaseApp;

/**
 * Created by root on 7/29/18.
 */

public class App extends Application {
    @Override
    public void onCreate() {
        super.onCreate();
        FirebaseApp.initializeApp(getApplicationContext());
    }
}

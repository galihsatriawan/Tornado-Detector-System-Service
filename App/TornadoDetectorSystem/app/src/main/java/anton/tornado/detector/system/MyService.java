package anton.tornado.detector.system;

import android.app.Service;
import android.content.Intent;
import android.os.IBinder;

import com.google.firebase.iid.FirebaseInstanceIdService;
import com.google.firebase.messaging.FirebaseMessagingService;

public class MyService extends Service {
    public MyService() {
    }
    @Override
    public IBinder onBind(Intent intent) {
        // TODO: Return the communication channel to the service.
        return null;
    }
    @Override
    public void onCreate(){
        super.onCreate();
        startService(new Intent(this, FirebaseMessagingService.class));
        startService(new Intent(this, FirebaseInstanceIdService.class));
    }
    @Override
    public  int onStartCommand(Intent intent,int flags, int startId){
        try{

        }catch (Exception e){
            e.printStackTrace();
        }
        return  START_STICKY;
    }


    public  void onDestroy(){
        try{
            // mTimer.cancel();;
            // timerTask.cancel();
        }catch (Exception e){
            e.printStackTrace();
        }
        Intent intent= new Intent("anton.tornado.detector.system");
        sendBroadcast(intent);
    }
    @Override
    public  void onTaskRemoved(Intent rootIntent){
        Intent restartService= new Intent(getApplicationContext(),this.getClass());
        restartService.setPackage(getPackageName());
        startService(restartService);
        super.onTaskRemoved(rootIntent);
    }
}

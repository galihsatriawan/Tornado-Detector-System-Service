package anton.tornado.detector.system;

import android.app.Service;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;

import com.google.firebase.iid.FirebaseInstanceIdService;
import com.google.firebase.messaging.FirebaseMessagingService;

public class BootUpReceiver extends BroadcastReceiver {

    @Override
    public void onReceive(Context context, Intent intent) {
        // TODO: This method is called when the BroadcastReceiver is receiving
        // an Intent broadcast.
        if (intent.getAction().equals(Intent.ACTION_BOOT_COMPLETED)) {
            //Do your coding here...
            Intent instanceIdService= new Intent(context,FirebaseInstanceIdService.class);
            Intent message = new Intent(context,FirebaseMessagingService.class);
            context.startService(instanceIdService);
            context.startService(message);

        }
    }
}

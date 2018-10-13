package anton.tornado.detector.system;

import android.app.AlarmManager;
import android.app.PendingIntent;
import android.app.ProgressDialog;
import android.content.Context;
import android.content.Intent;
import android.os.Handler;
import android.os.SystemClock;
import android.support.annotation.NonNull;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.Toast;

import com.google.firebase.iid.FirebaseInstanceId;

import anton.tornado.detector.system.Retrofit.ApiClient;
import anton.tornado.detector.system.Retrofit.InterfaceApi;
import anton.tornado.detector.system.Retrofit.Model.Data;
import anton.tornado.detector.system.Retrofit.Model.Note;
import retrofit2.Call;
import retrofit2.Callback;
import retrofit2.Response;

import java.util.Calendar;


public class MainActivity extends AppCompatActivity {
    TextView txtWindSpeed;
    TextView txtDirection;
    TextView txtRaining;
    TextView txtMoisture;
    TextView txtLocation;
    TextView txtIndication;
    Button btnRefresh;
    String tokenku ;
    public static final int REQUEST_CODE = 0;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        txtWindSpeed = findViewById(R.id.wind_speed);
        txtDirection= findViewById(R.id.direction);
        txtRaining= findViewById(R.id.raining);
        txtMoisture= findViewById(R.id.moisture);

        btnRefresh = findViewById(R.id.btn_refresh);
        txtLocation = findViewById(R.id.location);
        txtIndication= findViewById(R.id.indication);
        // Get token
        final String token = FirebaseInstanceId.getInstance().getToken();
        tokenku = token;
        btnRefresh.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                get_data(token);
            }
        });

        /*
            Repeating Alarm

         */

        // BEGIN_INCLUDE (intent_fired_by_alarm)
        // First create an intent for the alarm to activate.
        // This code simply starts an Activity, or brings it to the front if it has already
        // been created.
        Intent intent = new Intent(this, BootUpReceiver.class);

        // END_INCLUDE (intent_fired_by_alarm)

        // BEGIN_INCLUDE (pending_intent_for_alarm)
        // Because the intent must be fired by a system service from outside the application,
        // it's necessary to wrap it in a PendingIntent.  Providing a different process with
        // a PendingIntent gives that other process permission to fire the intent that this
        // application has created.
        // Also, this code creates a PendingIntent to start an Activity.  To create a
        // BroadcastIntent instead, simply call getBroadcast instead of getIntent.
        PendingIntent pendingIntent = PendingIntent.getActivity(this, REQUEST_CODE,
                intent, 0);

        // END_INCLUDE (pending_intent_for_alarm)

        // BEGIN_INCLUDE (configure_alarm_manager)
        // There are two clock types for alarms, ELAPSED_REALTIME and RTC.
        // ELAPSED_REALTIME uses time since system boot as a reference, and RTC uses UTC (wall
        // clock) time.  This means ELAPSED_REALTIME is suited to setting an alarm according to
        // passage of time (every 15 seconds, 15 minutes, etc), since it isn't affected by
        // timezone/locale.  RTC is better suited for alarms that should be dependant on current
        // locale.

        // Both types have a WAKEUP version, which says to wake up the device if the screen is
        // off.  This is useful for situations such as alarm clocks.  Abuse of this flag is an
        // efficient way to skyrocket the uninstall rate of an application, so use with care.
        // For most situations, ELAPSED_REALTIME will suffice.
        int alarmType = AlarmManager.ELAPSED_REALTIME;
        final int FIFTEEN_SEC_MILLIS = 15000;

        // The AlarmManager, like most system services, isn't created by application code, but
        // requested from the system.
        AlarmManager alarmManager = (AlarmManager)
                getApplication().getSystemService(this.ALARM_SERVICE);

        // setRepeating takes a start delay and period between alarms as arguments.
        // The below code fires after 15 seconds, and repeats every 15 seconds.  This is very
        // useful for demonstration purposes, but horrendous for production.  Don't be that dev.
        alarmManager.setRepeating(alarmType, SystemClock.elapsedRealtime() + FIFTEEN_SEC_MILLIS,
                FIFTEEN_SEC_MILLIS, pendingIntent);
        // END_INCLUDE (configure_alarm_manager);
        get_data(token);
        insert_token(token);
    }
    final Handler handler = new Handler();
    boolean test = new Handler().postDelayed(new Runnable() {

        @Override
        public void run() {
            Log.d("Anton", "run: Again");
            try{
                get_data(tokenku);
            }catch(Exception e){
                Log.d("Anton", "run: "+e.getMessage());
            }

            handler.postDelayed(this, 10000);
        }
    }, 10000);
    private ProgressDialog mProgressDialog;

    public void showProgressDialog(Context ctx) {
        if (mProgressDialog == null) {
            mProgressDialog = new ProgressDialog(ctx);
            mProgressDialog.setCancelable(false);
            mProgressDialog.setMessage("Loading...");
        }
        mProgressDialog.show();
    }

    public void hideProgressDialog() {
        if (mProgressDialog != null && mProgressDialog.isShowing()) {
            mProgressDialog.dismiss();
        }
    }


    public void get_data(String token){
        InterfaceApi api = ApiClient.getRetrofitInstance().create(InterfaceApi.class);
        showProgressDialog(this);
        Call<Data> call = api.get_data(token);
        call.enqueue(new Callback<Data>() {
            @Override
            public void onResponse(Call<Data> call, Response<Data> response) {
                //After get data show in text view
                Data data = response.body();
                hideProgressDialog();
                Log.d("Anton", "onResponse: "+data.getLokasi()+"--"+data.getVar_1());
                txtWindSpeed.setText(data.getVar_1()+" km/hour");
                txtDirection.setText(data.getVar_2());
                txtRaining.setText(data.getVar_3());
                txtMoisture.setText(data.getVar_4()+"");
                txtLocation.setText(data.getLokasi()+"");
                txtIndication.setText(data.getIndication());

            }

            @Override
            public void onFailure(Call<Data> call, Throwable t) {
                Log.d("Anton", "onFailure: "+t.getMessage());
                String failed = "Connection Failed";
                txtWindSpeed.setText(failed);
                txtDirection.setText(failed);
                txtRaining.setText(failed);
                txtMoisture.setText(failed);
                txtLocation.setText(failed);
                txtIndication.setText(failed);
                hideProgressDialog();
            }
        });
    }
    public void insert_token(String token){
        InterfaceApi api = ApiClient.getRetrofitInstance().create(InterfaceApi.class);
        Call<Note> call = api.insert_token(token);
        showProgressDialog(this);
        call.enqueue(new Callback<Note>() {
            @Override
            public void onResponse(Call<Note> call, Response<Note> response) {
                hideProgressDialog();
            }

            @Override
            public void onFailure(Call<Note> call, Throwable t) {
                Log.d("Anton", "onFailure: "+t.getMessage());
                hideProgressDialog();
            }
        });
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();

    }
}

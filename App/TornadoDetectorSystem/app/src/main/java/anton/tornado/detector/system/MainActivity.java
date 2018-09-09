package anton.tornado.detector.system;

import android.app.ProgressDialog;
import android.content.Context;
import android.os.Handler;
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
    TextView txtLocation;
    TextView txtIndication;
    Button btnRefresh;
    String tokenku ;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        txtWindSpeed = findViewById(R.id.wind_speed);
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
                txtLocation.setText(data.getLokasi()+"");
                txtIndication.setText(data.getIndication());

            }

            @Override
            public void onFailure(Call<Data> call, Throwable t) {
                Log.d("Anton", "onFailure: "+t.getMessage());
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
}

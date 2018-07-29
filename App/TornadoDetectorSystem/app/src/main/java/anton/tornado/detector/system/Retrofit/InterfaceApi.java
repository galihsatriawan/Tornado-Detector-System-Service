package anton.tornado.detector.system.Retrofit;

import anton.tornado.detector.system.Retrofit.Model.Data;
import anton.tornado.detector.system.Retrofit.Model.Note;
import retrofit2.Call;
import retrofit2.http.Field;
import retrofit2.http.FormUrlEncoded;
import retrofit2.http.GET;
import retrofit2.http.POST;

/**
 * Created by root on 7/29/18.
 */

public interface InterfaceApi {
    @FormUrlEncoded
    @POST("get_data.php")
    Call<Data> get_data(@Field("token") String token);

    @FormUrlEncoded
    @POST("insert_token.php")
    Call<Note> insert_token(@Field("token") String token);
}

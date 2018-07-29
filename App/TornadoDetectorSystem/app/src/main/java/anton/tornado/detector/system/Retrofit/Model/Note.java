package anton.tornado.detector.system.Retrofit.Model;

import com.google.gson.annotations.SerializedName;

/**
 * Created by root on 7/29/18.
 */

public class Note {
    @SerializedName("note")
    private String note;

    public String getNote() {
        return note;
    }

    public void setNote(String note) {
        this.note = note;
    }
}

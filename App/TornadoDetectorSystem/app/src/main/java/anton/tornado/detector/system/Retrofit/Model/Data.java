package anton.tornado.detector.system.Retrofit.Model;

import com.google.gson.annotations.SerializedName;

/**
 * Created by root on 7/29/18.
 */

public class Data {
    @SerializedName("var_1")
    private double var_1;
    @SerializedName("var_2")
    private double var_2;
    @SerializedName("var_3")
    private double var_3;
    @SerializedName("indication")
    private String indication;
    @SerializedName("lokasi")
    private String lokasi;
    public double getVar_1() {
        return var_1;
    }

    public void setVar_1(double var_1) {
        this.var_1 = var_1;
    }

    public double getVar_2() {
        return var_2;
    }

    public void setVar_2(double var_2) {
        this.var_2 = var_2;
    }

    public double getVar_3() {
        return var_3;
    }

    public void setVar_3(double var_3) {
        this.var_3 = var_3;
    }

    public String getLokasi() {
        return lokasi;
    }

    public void setLokasi(String lokasi) {
        this.lokasi = lokasi;
    }



    public String getIndication() {
        return indication;
    }

    public void setIndication(String indication) {
        this.indication = indication;
    }


}

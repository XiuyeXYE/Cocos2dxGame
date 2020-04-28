package com.xiuye.app.util;

import android.Manifest;
import android.app.Activity;
import android.app.AlertDialog;
import android.content.Context;
import android.content.pm.PackageManager;
import android.os.AsyncTask;
import android.telephony.TelephonyManager;

import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import com.xiuye.util.log.XLog;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import io.reactivex.Observable;
import io.reactivex.android.schedulers.AndroidSchedulers;
import io.reactivex.disposables.Disposable;
import io.reactivex.schedulers.Schedulers;
import okhttp3.OkHttpClient;
import okhttp3.logging.HttpLoggingInterceptor;
import retrofit2.Retrofit;
import retrofit2.adapter.rxjava2.RxJava2CallAdapterFactory;
import retrofit2.converter.gson.GsonConverterFactory;


public class UIUtil {

    public static boolean DEBUG = true;

    private static Context currentActivty;

    public static synchronized Context getCurrentActivty() {
        return currentActivty;
    }

    public static synchronized void setCurrentActivty(Context activity) {
        currentActivty = activity;//first step
//        AsyncDialogThread.clearPrevActivityRelatedDialog();//second step
    }

    public static <T> void log(Context context, T... tList) {
        if (!DEBUG) return;
        String output = "";
        for (T t : tList) {
            output += t + " ";
        }
        int idx = 0;
        output = output.substring(0, (idx = output.length() - 1) > 0 ? idx : 0);
        alert(context, context.getClass().toString(), output);
    }

    public static void alert(Context context, String title, String msg) {
        if (context == null) return;
        AsyncDialogThread thread = new AsyncDialogThread();
        thread.execute(context, title, msg);
    }


    public static void logCurrentWindow() {
        log(getCurrentActivty(), getCurrentActivty());
    }

    public static <T> void log(T... s) {
        log(getCurrentActivty(), s);
    }

    public static String getDeviceID(Activity activity) {
        TelephonyManager mTelephonyMgr = (TelephonyManager) activity.getSystemService(Context.TELEPHONY_SERVICE);
        int checkResult = activity.checkCallingOrSelfPermission(Manifest.permission.READ_PHONE_STATE);
        if (checkResult == PackageManager.PERMISSION_GRANTED) {
            String imsi = mTelephonyMgr.getSubscriberId(); //获取IMSI号
            String imei = mTelephonyMgr.getDeviceId(); //获取IMEI号
            return imsi + imei;
        }
        return null;
    }

//    public static boolean requestDevicePermission(Activity activity, String[] permissions, int requestCode) {
//
//        activity.requestPermissions(permissions,requestCode);
//        return true;
//    }


    public static Retrofit retrofit(String baseUrl) {
        HttpLoggingInterceptor interceptor = new HttpLoggingInterceptor();
        interceptor.setLevel(HttpLoggingInterceptor.Level.BODY);

        OkHttpClient.Builder client = new OkHttpClient.Builder();
        client.addInterceptor(interceptor);

        Retrofit retrofit = new Retrofit.Builder()
                .client(client.build())
                .addConverterFactory(GsonConverterFactory.create())
                .addCallAdapterFactory(RxJava2CallAdapterFactory.create())
                .baseUrl(baseUrl)
                .build();
        return retrofit;
    }

    public static Disposable handleRetrofitResult(Observable<Map<String, Object>> result,
                                                  Consumer<Map<String, Object>> consumer) {
        return result
                .subscribeOn(Schedulers.io())
                .observeOn(AndroidSchedulers.mainThread())
                .subscribe(d -> {
                    XLog.log(d, Thread.currentThread());
                    consumer.accept(d);
                });

    }

    public interface Consumer<T> {
        void accept(T t);
    }


    public static void checkAndRequestPermission(Activity that, String permission, int requestCode, Runnable runnable) {
        if (ContextCompat.checkSelfPermission(that, permission) != PackageManager.PERMISSION_GRANTED) {
            ActivityCompat.requestPermissions(that, new String[]{permission}, requestCode);
        } else {
            runnable.run();
        }
    }

    public static void handleRequestPermissionResult(Activity activity, int requestCode, String[] permissions, int[] grantResults, int selfRequestCode, Runnable runnable) {
        if (requestCode == selfRequestCode) {
            if (grantResults.length > 0 && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                runnable.run();
            } else {
                UIUtil.log(activity,"拒绝权限无法使用程序!");
                activity.finish();
            }
        }
    }


}


class AsyncDialogThread extends AsyncTask<Object, Void, Object> {

    public static List<AlertDialog> dialogs = new ArrayList<>();

    @Override
    protected Object doInBackground(Object... dialogInfos) {
        if (dialogInfos.length > 0) {
            return dialogInfos;
        }
        return null;
    }

    public static void clearPrevActivityRelatedDialog() {
//        XLog.lg("before remove all dialogs",dialogs.size(),dialogs);
        Iterator<AlertDialog> it = dialogs.iterator();
        while (it.hasNext()) {
            AlertDialog ad = it.next();
            ad.dismiss();
            it.remove();
        }
//        XLog.lg("after remove all dialogs",dialogs.size(),dialogs);
    }

    @Override
    protected void onPostExecute(Object info) {
        super.onPostExecute(info);
        if (info != null) {
            Object[] infos = (Object[]) info;
            Activity currentActivity = (Activity) infos[0];
            if (!currentActivity.isFinishing()) {
                AlertDialog.Builder builder = new AlertDialog.Builder(currentActivity);
                builder.setMessage(infos[2].toString()).setTitle(infos[1].toString());
                AlertDialog dialog = builder.create();
                dialog.show();
                dialogs.add(dialog);
//                XLog.lg("dialogs:",dialogs);
                dialog.setOnDismissListener(v -> {
                    dialogs.remove(dialog);
//                    XLog.lg("remove dialog by itself");
                });


            }

        }

    }
}

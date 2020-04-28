package com.xiuye.app;


import android.app.Activity;
import android.app.Application;
import android.os.Bundle;
import com.xiuye.util.log.XLog;
import com.xiuye.app.util.UIUtil;

public class XYApplication extends Application {
    @Override
    public void onCreate() {
        super.onCreate();
        this.registerActivityLifecycleCallbacks(new Application.ActivityLifecycleCallbacks() {
            @Override
            public void onActivityCreated(Activity activity, Bundle savedInstanceState) {
                XLog.log(XYApplication.class, "onActivityCreated:", activity);
            }

            @Override
            public void onActivityStarted(Activity activity) {
                XLog.log(XYApplication.class, "onActivityStarted:", activity);
            }

            @Override
            public void onActivityResumed(Activity activity) {
                XLog.log(XYApplication.class, "onActivityResumed:", activity);
                UIUtil.setCurrentActivty(activity);
            }

            @Override
            public void onActivityPaused(Activity activity) {
                XLog.log(XYApplication.class, "onActivityPaused:", activity);
            }

            @Override
            public void onActivityStopped(Activity activity) {
                XLog.log(XYApplication.class, "onActivityStopped:", activity);
                if (activity.equals(UIUtil.getCurrentActivty())) {
                    UIUtil.setCurrentActivty(null);
                }
            }

            @Override
            public void onActivitySaveInstanceState(Activity activity, Bundle outState) {
                XLog.log(XYApplication.class, "onActivitySaveInstanceState:", activity);
            }

            @Override
            public void onActivityDestroyed(Activity activity) {
                XLog.log(XYApplication.class, "onActivityDestroyed:", activity);
            }
        });
    }
}

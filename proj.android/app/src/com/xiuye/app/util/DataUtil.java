package com.xiuye.app.util;

import android.content.Context;
import android.content.SharedPreferences;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.io.PrintWriter;

public class DataUtil {

    @FunctionalInterface
    public interface ConsumerForData<T> {
        void accept(T t) throws IOException;
    }

    public static void saveDataToFile(Context context, String filename, ConsumerForData<PrintWriter> consumer) {
        try (PrintWriter bw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(context.openFileOutput(filename, Context.MODE_PRIVATE))))) {
            consumer.accept(bw);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void appendDataToFile(Context context, String filename, ConsumerForData<PrintWriter> consumer) {
        try (PrintWriter bw = new PrintWriter(new BufferedWriter(new OutputStreamWriter(context.openFileOutput(filename, Context.MODE_APPEND))))) {
            consumer.accept(bw);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void readDataFromFile(Context context, String filename, ConsumerForData<BufferedReader> consumer) {
        try (BufferedReader br = new BufferedReader(new InputStreamReader(context.openFileInput(filename)))) {
            consumer.accept(br);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void saveDataToSharedPreferences(Context context, String filename, ConsumerForData<SharedPreferences.Editor> consumer) {
        try {
            consumer.accept(context.getSharedPreferences(filename, Context.MODE_PRIVATE).edit());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void readDataFromSharedPreferences(Context context, String filename, ConsumerForData<SharedPreferences> consumer) {
        try {
            consumer.accept(context.getSharedPreferences(filename, Context.MODE_PRIVATE));
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}

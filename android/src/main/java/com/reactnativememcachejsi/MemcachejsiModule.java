package com.reactnativememcachejsi;

import android.util.Log;

import androidx.annotation.NonNull;

import com.facebook.react.bridge.JavaScriptContextHolder;
import com.facebook.react.bridge.Promise;
import com.facebook.react.bridge.ReactApplicationContext;
import com.facebook.react.bridge.ReactContextBaseJavaModule;
import com.facebook.react.bridge.ReactMethod;
import com.facebook.react.module.annotations.ReactModule;

@ReactModule(name = MemcachejsiModule.NAME)
public class MemcachejsiModule extends ReactContextBaseJavaModule {
    public static final String NAME = "Memcachejsi";
    private native void nativeInstall(long jsi);
    public MemcachejsiModule(ReactApplicationContext reactContext) {
        super(reactContext);
    }

    @Override
    @NonNull
    public String getName() {
        return NAME;
    }

    @Override
    public void initialize() {
      install();
    }

    public boolean install() {
      try {
        System.loadLibrary("memcachejsi");
        JavaScriptContextHolder jsContext = getReactApplicationContext().getJavaScriptContextHolder();
        if (jsContext.get() != 0) {
          nativeInstall(jsContext.get());
          Log.i(NAME, "Installing cache Success");
          return true;
        } else {
          return false;
        }
      } catch (Exception exception) {
        Log.e(NAME, "Failed to install memcachejsi JSI Bingding");
          return false;
      }
    }

    // Example method
    // See https://reactnative.dev/docs/native-modules-android
    @ReactMethod
    public void multiply(int a, int b, Promise promise) {
        promise.resolve(nativeMultiply(a, b));
    }

    public static native int nativeMultiply(int a, int b);
}

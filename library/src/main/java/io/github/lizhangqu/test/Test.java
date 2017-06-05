package io.github.lizhangqu.test;

/**
 * @version V1.0
 * @author: lizhangqu
 * @date: 2017-06-05 13:06
 */
public class Test {
    static {
        System.loadLibrary("test-jni");
    }

    public static native void test();
}

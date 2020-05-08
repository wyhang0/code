package com.wangyu.jnitest;

public class User{
	public static native int getAge(int base);
	public static native String getName(String name);
	public static native String getAddress(String address);
	
	public static void main(String[] args){
		System.out.println("library: " + System.getProperty("java.library.path"));
		System.loadLibrary("user-lib");
		
		System.out.println("age: " + User.getAge(3));
		System.out.println("address: " + User.getAddress("hua xia"));
		System.out.println("name: " + User.getName("wang"));
	}
}

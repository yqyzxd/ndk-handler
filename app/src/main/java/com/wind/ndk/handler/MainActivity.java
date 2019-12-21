package com.wind.ndk.handler;

import android.os.Bundle;
import android.view.View;

import androidx.appcompat.app.AppCompatActivity;

public class MainActivity extends AppCompatActivity {

    JHandler handler;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        handler=new JHandler();

       findViewById(R.id.btn_print).setOnClickListener(new View.OnClickListener() {
           @Override
           public void onClick(View v) {
               handler.sendMessage(1);
           }
       });

        findViewById(R.id.btn_stop).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                handler.sendMessage(19900909);
            }
        });

    }


}

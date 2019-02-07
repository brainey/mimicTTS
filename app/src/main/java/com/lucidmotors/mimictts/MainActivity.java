package com.lucidmotors.mimictts;

import android.graphics.Color;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.TextView;
import android.widget.EditText;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    Button speakBtn;
    EditText editSpeechText;
    TextView speechResultText;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        Initialize();

        speechResultText.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                Toast.makeText(getApplicationContext(), "Speech results was clicked",
                        Toast.LENGTH_LONG).show();
                speechResultText.setText("Visit us: http://examples.javacodegeeks.com");

                if(speechResultText.getLinksClickable() == true) {
                    speechResultText.setLinkTextColor(Color.BLUE);
                }
            }

        });

        speakBtn.setOnClickListener(new View.OnClickListener() {
            public void onClick(View v) {
                // copy editSpeechText to speechResultText
                speechResultText.setText(editSpeechText.getText());
            }
        });
    }

    private void Initialize() {
        speakBtn = (Button) findViewById(R.id.speak);
        editSpeechText = (EditText) findViewById(R.id.editSpeechText);
        speechResultText = (TextView) findViewById(R.id.textResult);
    }
}

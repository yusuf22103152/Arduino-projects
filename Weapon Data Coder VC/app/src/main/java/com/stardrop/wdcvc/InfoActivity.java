package com.stardrop.wdcvc;

import android.app.Activity;
import android.content.Intent;
import android.net.Uri;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.ImageView;

import androidx.annotation.NonNull;
import androidx.annotation.Nullable;
import androidx.appcompat.app.AppCompatActivity;

import com.google.android.gms.ads.AdError;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.FullScreenContentCallback;
import com.google.android.gms.ads.LoadAdError;
import com.google.android.gms.ads.OnPaidEventListener;
import com.google.android.gms.ads.ResponseInfo;
import com.google.android.gms.ads.interstitial.InterstitialAd;
import com.google.android.gms.ads.interstitial.InterstitialAdLoadCallback;

public class InfoActivity extends AppCompatActivity {

    ImageView YouTube,Instagram;
    Button WatchTuto,MoreApps;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_info);
        this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,WindowManager.LayoutParams.FLAG_FULLSCREEN);

        WatchTuto = findViewById(R.id.bt_watch);
        YouTube = findViewById(R.id.iv_youtube);
        Instagram = findViewById(R.id.iv_instagram);
        MoreApps = findViewById(R.id.bt_moreApps);

        WatchTuto.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent tutoInt = new Intent(Intent.ACTION_VIEW);
                tutoInt.setData(Uri.parse("https://stardropapps.blogspot.com/2021/04/weapon-data-cracker-vc.html"));
                startActivity(tutoInt);
            }
        });

        YouTube.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent ytInt = new Intent(Intent.ACTION_VIEW);
                ytInt.setData(Uri.parse("https://www.youtube.com/channel/UCnuQiKtlXK0f2wrgTOG0U9w"));
                startActivity(ytInt);
            }
        });

        Instagram.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent instaInt = new Intent(Intent.ACTION_VIEW);
                instaInt.setData(Uri.parse("https://instagram.com/heremeyusuf"));
                startActivity(instaInt);
            }
        });
        MoreApps.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent moreAppsInt = new Intent(Intent.ACTION_VIEW);
                moreAppsInt.setData(Uri.parse("https://stardropapps.blogspot.com/p/stardrop-apps.html"));
                startActivity(moreAppsInt);
            }
        });

    }


}